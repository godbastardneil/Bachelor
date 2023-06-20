const Router = require('express');
const router = new Router();

const userRouter = require('./userRouter');
const userlistRouter = require('./userlistRouter');
const dialogRouter = require('./dialogRouter');
const chatRouter = require('./chatRouter');
const p2pRouter = require('./p2pRouter');

router.use('/user', userRouter);
router.use('/userlist', userlistRouter);
router.use('/dialog', dialogRouter);
router.use('/chat', chatRouter);
router.use('/p2p', p2pRouter);

module.exports = router;
