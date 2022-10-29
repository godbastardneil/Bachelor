// подключаем нужные модули (библиотеки)
const express = require('express');
const app = express();
const http = require('http').Server(app);
const io = require('socket.io')(http, {
    'pingInterval': 10000
});
const path = require('path');
const port = 8080;

const {ChatChannel, P2PChannel, Message} = require('./models.js');

var Users = new Map();
var Messages = new Map();
var chats = [new ChatChannel(0, "Общий")];
var p2p = [];
var i = 0;
var j = -1;

// сокеты
io.on('connection', (socket) => {
    console.log(`${socket.id} user connected`);
	socket.emit('create_user', socket.id);
	
	socket.on('adduser', function(userName)
	{
		socket.username = userName;
		Users.set(socket.id, userName);
		chats[0].usersId.push(socket.id);

		socket.chat = `chat_0`;
		socket.join(`chat_0`);

		socket.emit('updatechats', chats);
		socket.emit('updateusers', Array.from(Users, ([key, value]) => ({ key, value })));

		io.sockets.emit('updateusers', Array.from(Users, ([key, value]) => ({ key, value })));
		
		if (Messages.has(`chat_0`))
		{
			socket.emit('setmessages', JSON.stringify(Array.from(Users.entries())), Messages.get(`chat_0`));
		}
		socket.emit('updatechat', 'SERVER', new Message(socket.id, 'you have connected to Общий'));
		socket.broadcast.to(`chat_0`).emit('updatechat', 'SERVER', new Message(socket.id, `${userName} has connected to Общий`));
	});
	
	function send(ch, tmp)
	{
		io.sockets.in(ch).emit('updatechat', socket.username, tmp);
		if (Messages.has(ch))
		{
			Messages.get(ch).push(tmp);
		} else { Messages.set(ch, [tmp]); }
	}
	socket.on('sendfile', function (data)
	{
		let tmp = new Message(socket.id, "", data);
		send(socket.chat, tmp);
	});
	socket.on('sendchat', function (data)
	{
		let tmp = new Message(socket.id, data);
		send(socket.chat, tmp);
	});
	
	socket.on('switchChat', function(newchat)
	{
		let tmp = `chat_${newchat}`;
		socket.leave(socket.chat);

		socket.join(tmp);
		socket.chat = tmp;

		if (Messages.has(tmp))
		{
			socket.emit('setmessages', JSON.stringify(Array.from(Users.entries())), Messages.get(tmp));
		} else { socket.emit('setmessages', JSON.stringify(Array.from(Users.entries())), new Message(socket.id, ``)) }
		socket.emit('updatechat', 'SERVER', new Message(socket.id, `you have connected to ${chats[newchat].tittle}`));
		socket.broadcast.to(tmp).emit('updatechat', 'SERVER', new Message(socket.id, `${socket.username} has joined this ${chats[newchat].tittle}`));
	});
	
	socket.on('switchUser', function(newuser)
	{
		let p = -1;
		for (let t=0; t<p2p.length; ++t)
		{
			if ((socket.id == p2p[t].FUserId && newuser == p2p[t].SUserId)
				|| (newuser == p2p[t].FUserId && socket.id == p2p[t].SUserId))
			{
				p = t;
			}
		}
		if (p == -1)
		{
			++j;
			p2p.push(new P2PChannel(j, socket.id, newuser));
			p = j;
		}
		let tmp = `p2p_${p}`;

		socket.leave(socket.chat);

		socket.chat = tmp;
		socket.join(tmp);

		if (Messages.has(tmp))
		{
			socket.emit('setmessages', JSON.stringify(Array.from(Users.entries())), Messages.get(tmp));
		} else { socket.emit('setmessages', JSON.stringify(Array.from(Users.entries())), new Message(socket.id, ``)) }
		socket.broadcast.to(tmp).emit('updatechat', 'SERVER', new Message(socket.id, `${socket.username} has joined`));
	});

	socket.on('disconnect', function()
	{
		console.log(`${socket.id} user disconnected`);
		socket.broadcast.emit('updatechat', 'SERVER', new Message(socket.id, `${socket.username} has disconnected`));
		socket.leave(socket.chat);
		Users.delete(socket.id);
		for (let t=1; t<chats.length; ++t)
		{
			let l = chats[t].usersId.indexOf(socket.id);
			if (l > -1)
			{
				chats[t].usersId.splice(l, 1);
				if (chats[t].usersId.length == 0)
				{
					chats.splice(t, 1);
					if (Messages.has(`chat_${t}`))
					{
						Messages.delete(`chat_${t}`);
					}
				}
			}
		}
		for (let t=0; t<p2p.length; ++t)
		{
			if (socket.id == p2p[t].FUserId &&  socket.id == p2p[t].SUserId)
			{
				p2p.splice(t, 1);
				if (Messages.has(`p2p_${t}`))
				{
					Messages.delete(`p2p_${t}`);
				}
			}
		}
		io.sockets.emit('updateusers', Array.from(Users, ([key, value]) => ({ key, value })));
		io.sockets.emit('updatechats', chats);
	});
	

	socket.on('addchat', function(list, chat_name)
	{
		++i;
		chats.push(new ChatChannel(i, chat_name))
		chats[i].usersId = list;
		chats[i].usersId.push(socket.id);

		socket.emit('updatechats', chats);
		socket.emit('updateusers', Array.from(Users, ([key, value]) => ({ key, value })));
		io.sockets.emit('updatechats', chats);
	});
});


app.use(express.static("./frontend/"));
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, './frontend', 'main.html'));
});
http.listen(port, () => {
    console.log(`Server running on port: ${port}`);
});