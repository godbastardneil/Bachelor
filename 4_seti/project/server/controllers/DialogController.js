const {Chat, Chat_user} = require('../models/models');
const ApiError = require('../error/ApiError');

class DialogController {
    async get(req, res) {
        const {id} = req.user;

        const dialogs;
        Chat_user.findAll({
            where: { 'iduser': id },
            include: {
                model: Chat,
                required: false
            }
        }).then(data => { dialogs = data; });

        return res.json(dialogs);
    }
}

module.exports = new DialogController();
