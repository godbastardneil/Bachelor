class P2PChannel
{
    p2pId = -1;
    FUserId = "";
    SUserId = "";
    constructor(id, f, s)
    {
        this.p2pId = id;
        this.FUserId = f;
        this.SUserId = s;
    }
}
class ChatChannel
{
    chatId = -1;
    usersId = [];
    tittle = "";
    constructor(id, t)
    {
        this.chatId = id;
        this.tittle = t;
    }
}

class Message
{
    userId = "";
    content = "";
    file = {};
    constructor(id, c, f = {})
    {
        this.userId = id;
        this.content = c;
        this.file = f;
    }
}

module.exports = {
    ChatChannel,
    P2PChannel,
    Message
};