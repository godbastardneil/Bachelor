const sequelize = require('../database');
const {DataTypes} = require('sequelize');

const User = sequelize.define('user', {
    id: {type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true},
    login: {type: DataTypes.STRING, unique: true, allowNull: false},
    password: {type: DataTypes.STRING, unique: true, allowNull: false}
});

const Chat_Type = sequelize.define('chat_type', {
    id: {type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true},
    type: {type: DataTypes.STRING, unique: true, allowNull: false}
});

const Chat = sequelize.define('chat', {
    id: {type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true}
});
Chat.hasMany(Chat_Type); Chat_Type.belongsTo(Chat);

const Chat_user = sequelize.define('chat_user', {});
Chat_user.hasMany(Chat); Chat.belongsTo(Chat_user);
Chat_user.hasMany(User); User.belongsTo(Chat_user);

const Messege = sequelize.define('messege', {
    id: {type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true},
    text: {type: DataTypes.STRING, allowNull: false},
    date: {type: DataTypes.DATE, allowNull: false},
});
Messege.hasMany(Chat); Chat.belongsTo(Messege);
Messege.hasMany(User); User.belongsTo(Messege);

module.exports = {
    User,
    Chat_Type,
    Chat,
    Chat_user,
    Messege
};

Chat_Type.create({id: 1,  type: 'Групповой'});
Chat_Type.create({id: 2,  type: 'P2P'});