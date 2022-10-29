module.exports = class mutex {
    constructor() {
        // ключ ID заявки - значение ID сокета
        this.orderSocket = new Map();
        // ключ ID сокета - значение ID заявки
        this.socketOrder = new Map();
    }

    addOrder(orderID, socketID) {
        this.orderSocket.set(orderID, socketID);
        this.socketOrder.set(socketID, orderID);
    }

    deleteOrderByOrderID(orderID) {
        let socketID = this.orderSocket.get(orderID);
        this.orderSocket.delete(orderID, socketID);
        this.socketOrder.delete(socketID, orderID);
    }

    deleteOrderBySocketID(socketID) {
        let orderID = this.socketOrder.get(socketID);
        this.orderSocket.delete(orderID, socketID);
        this.socketOrder.delete(socketID, orderID);
    }

    isBusyByOrderID(orderID) {
        return this.orderSocket.has(orderID);
    }

    isBusyBySocketID(socketID) {
        return this.socketOrder.has(socketID);
    }

    testReset() {
        this.orderSocket.clear();
        this.socketOrder.clear();
    }
}