var socket = io.connect('http://localhost:8080');

var user_name = "";
var user_id;

socket.on('create_user', (userId) =>
{
    user_id = userId;
    console.log(user_id);
    while(user_name.length == 0)
    {
        user_name = prompt("What's your name?");
        user_name = user_name.trim();
    }
    console.log(user_name);
    socket.emit('adduser', user_name);
});

socket.on('updatechat', (userName, value) =>
{
    if (value.content == "")
    {
        console.log(value.file);
        $('#conversation').append(`<b>${userName}:</b><a download="${value.file.fileName}" href="${value.file.file}">${value.file.fileName}</a><br>`);
    } else { $('#conversation').append(`<b>${userName}:</b>${value.content}<br>`); }
});
socket.on('setmessages', (users, messages) =>
{
    var newusers = new Map(JSON.parse(users));
    console.log(users);
    $('#conversation').empty();
    $.each(messages, function(key, value)
    {
        if (value.content == "")
        {
            console.log(value.file);
            $('#conversation').append(`<b>${newusers.get(value.userId)}:</b><a download="${value.file.fileName}" href="${value.file.file}">${value.file.fileName}</a><br>`);
        } else { $('#conversation').append(`<b>${newusers.get(value.userId)}:</b>${value.content}<br>`); }
    });
});

socket.on('updatechats', (chats) =>
{
    $('#chats').empty();
    $.each(chats, function(key, value)
    {
        if (value.usersId.includes(user_id))
        {
            $('#chats').append(`<div><a href="#" onclick="switchChat('${value.chatId}')">${value.tittle}</a></div>`);
        }
    });
});
socket.on('updateusers', (users) =>
{
    $('#users').empty();
    $.each(users, function(key, value)
    {
        if (value["key"] != user_id)
        {
            $('#users').append(`<div><input type="checkbox" id='${value["key"]}' value='${value["key"]}' name="users" class="users"><a id='${value["key"]}' href="#" onclick="switchUser('${value["key"]}')">${value["value"]}</a></div>`);
        }
    });
});
``
function switchChat(chat)
{
    socket.emit('switchChat', chat);
}
function switchUser(user)
{
    socket.emit('switchUser', user);
}

function readFile(input) {
    let data = input.files[0];
  
    var reader = new FileReader();
    reader.onload = function(evt){
        var msg = {};
        msg.userId = user_id;
        msg.file = evt.target.result;
        msg.fileName = data.name;
        msg.fileType = data.type;

        console.log(msg);
        socket.emit('sendfile', msg);
    };
    reader.readAsDataURL(data);
}

// on load of page
$(function()
{
    // when the client clicks SEND
    $('#datasend').click( function() {
        var message = $('#data').val();
        message = message.trim();
        if (message.length != 0)
        {
            $('#data').val('');
            // tell server to execute 'sendchat' and send along one parameter
            socket.emit('sendchat', message);
        }
    });
    // when the client hits ENTER on their keyboard
    $('#data').keypress(function(e) {
        if(e.which == 13) {
            $(this).blur();
            $('#datasend').focus().click();
        }
    });


    $('#userssend').click( function() {
        var list = $("input[name='users']:checked").map(function () {
            return this.value;
        }).get();
        var chat_name = $('#chat_name').val();
        chat_name = chat_name.trim();

        console.log(chat_name);
        console.log(list);

        if (list.length > 0 && chat_name.length != 0)
        {
            $('#chat_name').val('');
            socket.emit('addchat', list, chat_name);
        }
    });
    $('#chat_name').keypress(function(e) {
        if(e.which == 13) {
            $(this).blur();
            $('#userssend').focus().click();
        }
    });

});
