const Router = require('express');
const router = new Router();
const ChatController = require('../controllers/chatController');

router.get('/:id', ChatController.getChat);
router.post('/', ChatController.setChat);

module.exports = router;
