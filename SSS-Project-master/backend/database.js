let mysql = require('mysql');
const util = require('util');

String.prototype.replaceAll = function (search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database {

    constructor() {

        this.config = {
            host: 'localhost',
            user: 'user',
            password: 'UserUser1!',
            database: 'logistic',
            multipleStatements: true
        }
        this.connection = mysql.createConnection(this.config);
        // обертка для connection.query, чтобы можно было использовать query в async-await связках
        this.query = util.promisify(this.connection.query).bind(this.connection);
        this.setConnection();
    };

    setConnection() {
        this.connection.connect(err => {
            if (err) {
                console.error(`DB: connection error: ${err.stack}`);
            } else {
                console.log(`DB: successful connection for id ${this.connection.threadId}`);
            }
        });
    };

    // - получение списка ID заявок
    async getOrderIdList(date) {
        try {
            let results;
            if (date == "all")
            {
                results = await this.query(`SELECT ID_Заявка FROM заявка order by ID_Заявка`);
            } else {
                results = await this.query(`SELECT ID_Заявка FROM заявка where DATE(\`Дата-время начало\`) = '${date}' order by ID_Заявка`);
            }
            let list = [];
            results.forEach(element => list.push(element['ID_Заявка']));
            return list;
        } catch (error) {
            console.error(`BD-'getOrderIdList' exception: ${error}`);
        }
    };

    async getFilledRow(id) {
        const results = await this.query(`call getFilledRow('${id}')`);
        if (!results[0][0]) throw new Error("Order not found");
        return results[0][0];
    }

    async updateRow(orderID, result) {
        for (const oneRow of result)
        {
            console.log(oneRow);
            await this.query(`call updateRow('${orderID}', ${oneRow['order']}, '${oneRow['driver']}', '${oneRow['car']}')`);
        }
        this.query(`update \`заявка\` set \`ID_Статус\` = 3 where \`ID_Заявка\` = '${orderID}'`);
    }

    async isOrderExist(ID) {
        try {
            const results = await this.query(`SELECT COUNT(*) FROM заявка WHERE ID_Заявка = "${ID}"`);
            const value = results[0]['COUNT(*)'];
            if (value == 1) return true;
            else return false;
        } catch (error) {
            console.error(`BD-'isOrderExist' exception: ${error}`);
            return false;
        }
    }
    // - получение списка заявок с соответстующими данными заявки
    async getOrderList(date) {
        let filledRowList = [];
        try {
            // получаем список ID заявок
            let idList = await this.getOrderIdList(date);
            filledRowList = [];
            for (const ID of idList) {
                let row = await this.getFilledRow(ID);
                filledRowList.push(row);
            };
        } catch (error) {
            console.error(`BD-'getOrderList' exception: ${error}`);
        }
        return filledRowList;
    };

    // - для получения данных о заявке на второй странице (заголовок заявки)
    async getOrderHeaderInfo(ID) {
        try {
            const results = await this.query(`call getOrderInfo('${ID}')`);
            return results[0][0];
        } catch (error) {
            console.error(`BD-'getOrderHeaderInfo' exception: ${error}`);
        }
    }

    async getParsedTimelineInfo(value) {
        let parsedValue = value.replaceAll('[', '').replaceAll(']', '').split(',');
        let results = [];
        for (let i = 0; i < parsedValue.length; i += 3) {
            results.push({
                Работа: parsedValue[i],
                Начало: parsedValue[i + 1],
                Конец: parsedValue[i + 2]
            })
        }
        return results;
    }

    // - для получения информации для виртуальной техники и timeline'a второй страницы
    async getVirtVehiclesInfo(ID) {
        let virtVehiclesInfo = [];
        try {
            const results = await this.query(`call getWorksLocsAndTimesOfApp('${ID}')`);
            for (const element of results[0]) {
                let timeline = await this.getParsedTimelineInfo(element['Таймлайн']);
                virtVehiclesInfo.push({
                    ID_КлассТехники: element['ID_КлассТехники'],
                    Техника: element['Техника'],
                    Локация: element['Локация'],
                    Таймлайн: timeline
                });
            };
        } catch (error) {
            console.error(`BD-'getVirtVehiclesInfo' exception: ${error}`);
        }
        return virtVehiclesInfo;
    }

    // - для получения информации о выбранной технике у готовой заявки
    async getDoneVehiclesInfo(ID) {
        let doneVehiclesInfo = [];
        try {
            const results = await this.query(`call getDoneWorksLocsAndTimesOfApp('${ID}')`);
            for (const element of results[0]) {
                let timeline = await this.getParsedTimelineInfo(element['Таймлайн']);
                doneVehiclesInfo.push({
                    ID_КлассТехники: element['ID_КлассТехники'],
                    Водитель: element['Водитель'],
                    Техника: element['Техника'],
                    Локация: element['Локация'],
                    Таймлайн: timeline
                });
            };
        } catch (error) {
            console.error(`BD-'getDoneVehiclesInfo' exception: ${error}`);
        }
        return doneVehiclesInfo;
    }
    // Получить начало и конец точек маршрута реальной машины
    async getWorksTimesOfRealCar(ID_car) {
        try {
            const results = await this.query(`CALL logistic.getWorksTimesOfRealCar(${ID_car})`);
            return results[0];
        } catch (error) {
            console.error(`BD-'getWorksTimesOfRealCar' exception: ${error}`);
        }
    };

    // - получение списка ID машин и их названий
    async getRealCarIdList(isBusy, ID_app, type, order) {
        try {
            const results = await this.query(`CALL logistic.getRealCars(${isBusy}, '${ID_app}', ${type}, ${order})`);
            return results[0];
        } catch (error) {
            console.error(`BD-'getRealCarIdList' exception: ${error}`);
        }
    };

    // - получение списка реальных машин с таймлайнами, order - очередность вирт. техники
    async getRealCarList(ID_app, type, order) {
        // это просто структура carList, чтобы редактор понимал возвращаемый тип и делал подсказки
        let carList = [{
            Название: "", Занято: true, ТочкаМаршрута: [{Начало: "", Конец: ""}]
        }];
        // поэтому сразу удаляю этот фиктивный элемент - структуру
        carList.pop();
        try {
            // получаем список ID заявок
            let busyCarIdList = await this.getRealCarIdList(true,ID_app,type,order);
            let freeCarIdList = await this.getRealCarIdList(false,ID_app,type,order);
            let fillList = async (isBusy, carIdList) =>
            {
                for (const element of carIdList) {
                    let ID = element['id_транспорт'];
                    let name = element['Название'];
                    let worksTimes = await this.getWorksTimesOfRealCar(ID);
                    let newElem = {
                        Название: name,
                        Занято: isBusy,
                        ТочкаМаршрута: worksTimes
                    }
                    carList.push(newElem);
                };
            }
            if (busyCarIdList.length > 0)
            {
                await fillList(true,  busyCarIdList);
            }
            if (freeCarIdList.length > 0)
            {
                await fillList(false, freeCarIdList);
            }
        } catch (error) {
            console.error(`BD-'getRealCarList' exception: ${error}`);
        }
        return carList;
    };

    async getFreeDriversList(ID_App, order)
    {
        try
        {
            const results = await this.query(`call getFreeDrivers('${ID_App}', ${order})`);
            return results[0];
        } catch (error) {
            console.error(`BD-'getFreeDriversList' exception: ${error}`);
        }
    }

    async getOrderStartEndDurationOfApp(ID_App)
    {
        let listElements = [];
        try
        {
            let ordersCountQuery = await this.query(`SELECT COUNT(distinct (Очередность)) as \`orderSize\` FROM точкамаршрута WHERE ID_Заявка = '${ID_App}'`);
            let ordersCount = ordersCountQuery[0]['orderSize'];
            let fillList = async (list, order) =>
            {
                for (let i = 1; i <= order; i++)
                {
                    const result = await this.query(`call logistic.getOrderStartEndDurationOfApp('${ID_App}', ${i})`);
                    list.push(result[0][0]);
                }
            }

            await fillList(listElements, ordersCount);
        }
        catch (error) {
            console.error(`BD-'getOrderStartEndDurationOfApp' exception: ${error}`);
        }
        return listElements;
    }
};


