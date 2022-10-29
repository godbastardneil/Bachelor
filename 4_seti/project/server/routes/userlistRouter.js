const Router = require('express');
const router = new Router();
const UserListController = require('../controllers/userlistController');

router.get('/', UserListController.get);

module.exports = router;
