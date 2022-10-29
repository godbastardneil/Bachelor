const {User} = require('../models/models');
const ApiError = require('../error/ApiError');

class UserListController {
    async get(req, res) {
        const user = await User.findAll();
        return res.json(user);
    }
}



module.exports = new UserListController();
