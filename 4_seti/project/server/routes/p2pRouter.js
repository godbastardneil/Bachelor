const Router = require('express');
const router = new Router();
const P2PController = require('../controllers/p2pController');

router.get('/:id', P2PController.get);
router.post('/', P2PController.set);

module.exports = router;
