const Router = require('express');
const router = new Router();
const DialogController = require('../controllers/DialogController');

router.get('/', DialogController.get);

module.exports = router;
