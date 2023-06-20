// пройдемся во всей виртуальной технике и привяжем реакцию на событие, т.е сделаем, чтобы при нажатии на вирт. технику она выделялась кружком (selected vehicle)
// и соответственно выделение снималось, когда нажали на другую вирт. технику (или на ту же самую еще один раз)

const socket = io.connect('', {
    'forceNew': true,
    'reconnection': false
});

// - будем запоминать массивы с занятыми водилами каждый с очередностью
const busyDriversList = new Map();
let UNuniqueArrays = [];
let collisionArray = [];

const orderID = window.location.href.split('/')[4];

let orderCount = 1;
let carCount = 1;

socket.on('setAppOrderFreeDrivers', (AppOrderDriversList) =>
{
    getFreeDriversOnAppAndOrder(AppOrderDriversList);
});

socket.on('setOrderStartEndDuration', orderInfo => {
    collisionArray = orderInfo;
    setCollisionLogicDrivers();
});

socket.on('setOrderHeaderInfo', (data) => {
    setOrderHeaderInfo(data);
    document.querySelector("#to_mp").innerText = "Вернуться в журнал";
    if (data['Статус'] == "Отклонен")
    {
        document.querySelector("#add_save").classList.add('disabled');
    } else if (data['Статус'] == "Принят") {
        document.querySelector("#add_save").innerText = "Отклонить заявку";
    }
});

socket.on('setVirtVehicleInfo', ({
    index,
    virtVehicle
}) => {
    setVirtVehicleInfo(index, virtVehicle);
});

socket.on('setDoneVehicleInfo', ({
    index,
    doneVehicle
}) => {
    setVirtVehicleInfo(index, doneVehicle);
    console.log(doneVehicle);
    addDoneDrivers(index, doneVehicle['Водитель']);
});

socket.on('setRealVehiclesInfo', ({
    index,
    realVehicles
}) => {
    setRealVehiclesInfo(index, realVehicles);
    prepareCollapse();
    document.querySelector("a[href='#vehicle0']").click();
    document.getElementById("collapse-list-of-vehicles").classList.remove('disabled');
});

socket.emit('takeOrderMutex', orderID);

socket.on('disconnect', () => {
    setTimeout(() => {
        alert("Потеряно соединение с сервером. Несохраненные данные были потеряны.");
        document.location.reload();
    }, 2000);
});

let timelines = [];
let globalDate = "";

function op_mp() {
    if (confirm("Вы точно хотите вернуться на главную страницу без сохранения результата?"))
        window.open("/", "_self");
}

function op_save() {
    window.open("/", "_self");
}

function nextMsg() {
    if (messages.length == 0) {
        op_save();
    } else {
        $('#add_save').html(messages.pop()).delay(1000).fadeOut(1000, nextMsg);
    }
};

var messages = [
    "Сохранено!",
].reverse();


async function setOrderHeaderInfo(value) {
    document.getElementById('request-id').innerText = value['ID'];
    document.getElementById('request-date').innerText = value['ВремяДата'];
    document.getElementById('request-department').innerText = value['Цех'];
    document.getElementById('request-place').innerText = value['Места'];
    document.getElementById('request-person').innerText = value['Ответственный'];
    document.getElementById('request-desc').innerText = value['Описание'];
}

function getParsedValues(timeline) {
    let collection = [];
    for (let i = 0; i < timeline.length; ++i) {
        let className = 'bold rounded';
        if (timeline[i]['Работа'] == "Дорога") className = 'drive rounded';
        collection.push({
            id: i,
            group: i + 1,
            className: className,
            start: timeline[i]['Начало'],
            end: timeline[i]['Конец']
        })
    }
    return collection;
}

function getTimepointForVisTimeline(timeline) {
    let collection = [];
    for (let i = 0; i < timeline.length; ++i) {
        collection.push({
            id: i,
            group: timeline[i]['group'],
            className: `${timeline[i]['className']} rounded`,
            start: timeline[i]['Начало'],
            end: timeline[i]['Конец']
        })
    }
    return collection;
}



async function getFreeDriversOnAppAndOrder(AppOrderDriversList)
{
    busyDriversList.set(AppOrderDriversList['ord'], AppOrderDriversList['values']);
    for (const elem of AppOrderDriversList['values'])
    {
        driverSet.add(elem['ФИО']);
        console.log(elem['ФИО']);
    }
    await addDrivers(AppOrderDriversList);
}

async function emmitedDriver(value) {
    let sel = document.getElementById(`${value}`);
    for (let i = 0; i < UNuniqueArrays.length; i++) {
        if (UNuniqueArrays[i].includes(value)) {
            for (let z = 0; z < UNuniqueArrays[i].length; z++) {
                if (UNuniqueArrays[i][z] != value) {
                    let names = []
                    let id = UNuniqueArrays[i][z].replace('inlineFormCustom', '');
                    for (let j of busyDriversList.get(Number.parseInt(id))) {
                        names.push(j['ФИО'])
                    }
                    names.splice(names.indexOf(sel.options[sel.selectedIndex].text), 1)
                    let another = document.getElementById(`${UNuniqueArrays[i][z]}`)
                    let length = another.options.length;
                    let textLast = another.options[another.selectedIndex].text;
                    for (let g = length - 1; g >= 0; g--) {
                        another.options[i] = null;
                    }
                    let index = 0;
                    for (let g = 0; g < names.length; g++) {
                        let row = document.createElement('option')
                        row.value = g + '' + 1;
                        row.innerText = names[g];
                        if (names[g] == textLast) index = g;
                        another.appendChild(row);
                    }
                    another.options.selectedIndex = index
                }
            }
        }
    }
}

async function setCollisionLogicDrivers()
{
    for (let i = 0; i < collisionArray.length; i++)
    {
        let start = collisionArray[i]['Начало'];
        let end = collisionArray[i]['Конец'];
        for (let j = i + 1; j < collisionArray.length; j++)
        {
            // - набор не уникальных
            if ( start ==  collisionArray[j]['Начало'] || start == collisionArray[j]['Конец'] ||
                 end ==  collisionArray[j]['Начало'] || end == collisionArray[j]['Конец'] ||
                (start <=  collisionArray[j]['Начало'] && end >=  collisionArray[j]['Конец']) ||
                (start >=  collisionArray[j]['Начало'] && end <=  collisionArray[j]['Конец']) ||
                (start <=  collisionArray[j]['Начало'] && end >=  collisionArray[j]['Начало'])
            )
            {
                UNuniqueArrays.push([`inlineFormCustom${collisionArray[i]['Очередность']}`, `inlineFormCustom${collisionArray[j]['Очередность']}`])
            }
        }
    }
}

// добавить виртуальную технику на страницу
async function setVirtVehicleInfo(index, virtVehicle) {
    // название виртуальной техники и место работы
    let parent = document.querySelector('#virt-list-of-vehicles');
    let data = document.createElement('dl');
    data.className = `row mt-5`;
    data.id = `technica${index + 1}`
    let autoLink = document.createElement('a');
    autoLink.className = 'virt-vehicle col-3 m-auto';
    autoLink.setAttribute("data-toggle", 'collapse');
    autoLink.setAttribute("role", 'button');
    autoLink.role = 'button';
    autoLink.id = `car${index}`;
    autoLink.href = `#vehicle${index}`;
    autoLink.innerHTML = `<span></span><span>${virtVehicle['Техника']}</span>`;
    let location = document.createElement('dd');
    location.className = 'col-2 m-auto';
    location.innerHTML = `${virtVehicle['Локация']}`;
    // html контейнер dd для таймлайна с задачами
    let timeline = document.createElement('dd');
    timeline.className = 'col-7 m-auto';
    timeline.id = `timeline${index}`;
    // все присоединяем
    data.append(autoLink);
    data.append(location);
    data.append(timeline);
    parent.append(data);

    // формируем таймлайн для виртуальной техники
    let groups = [];
    virtVehicle['Таймлайн'].forEach(singleTask => {
        groups.push(singleTask['Работа']);
    });
    globalDate = virtVehicle['Таймлайн'][0]['Начало'].split(' ')[0];
    timelines.push(new Timeline(`timeline${index}`, globalDate,
        getParsedValues(virtVehicle['Таймлайн']), groups));

    // - добавление инфы о количестве очердностей
    socket.emit('getFreeCarsList', orderID, `${virtVehicle['Техника']}`, carCount++);
}

function prepareCollapse() {
    document.querySelectorAll(".virt-vehicle").forEach((elem) => {
        // при клике скрываем текущий открытый блок div collapse
        $(elem).on('click', () => {
            $('.collapse.show').collapse('hide');
        });
        // выделяем кружком и блокируем нажатия на ссылки пока не раскроется блок с настоящ. техникой
        $(elem.getAttribute("href")).on('show.bs.collapse', () => {
            elem.children[0].classList.add("selected");
            document.querySelectorAll(".virt-vehicle").forEach((elem) => {
                elem.classList.add("no-link")
            });
        });
        // как только раскрылся, включаем ссылки обратно
        $(elem.getAttribute("href")).on('shown.bs.collapse', () => {
            document.querySelectorAll(".virt-vehicle").forEach((elem) => {
                elem.classList.remove("no-link")
            });
        });
        // убираем кружок при закрытии блока с техникой
        $(elem.getAttribute("href")).on('hide.bs.collapse', () => {
            elem.children[0].classList.remove("selected");
        });
    });
}

let driverSet = new Set(), carSet = new Set();

function checkFilledData()
{
    let arrCar = [];
    let arrDrives = [];
    for (let i = 0; i < orderCount-1; i++)
    {
        arrCar.push(document.querySelector(`#car${i}`).innerText);
        let select = document.querySelector(`#inlineFormCustom${i+1}`);
        let text=select.options[select.selectedIndex].text;
        arrDrives.push(text);
    }

    for (let j = 0; j < arrCar.length; ++j)
    {
        if(!carSet.has(arrCar[j])) {
            alert('Вы не заполнили все данные!');
            return false;
        }
    }

    for (let k = 0; k < arrDrives.length; ++k)
    {
        if(!driverSet.has(arrDrives[k])) {
            alert('Вы не заполнили все данные!');
            return false;
        }
    }
    let result = [];
    for (let p = 0; p < arrCar.length; ++p)
    {
        result.push({order: p+1, car: arrCar[p], driver: arrDrives[p]});
    }
    console.log({orderID,result});
    socket.emit('updateRow',orderID,result);
    nextMsg();
}

async function addDoneDrivers(ind, name) {
    let data = document.createElement('dl');
    data.className = 'row mt-5';
    data.id = `driverOf${ind}`;
    let drivers = document.createElement('div')
    drivers.className = 'col-3 font-weight-bold';
    drivers.innerText = 'Исполнитель';
    let dddrivers = document.createElement('dd')
    dddrivers.className = 'col-2'
    let selections = document.createElement('span')
    selections.className = 'custom-select mr-sm-2 text-center slc'
    selections.innerText = name;
    selections.id = `inlineFormCustom${ind}`
    data.appendChild(drivers);
    dddrivers.appendChild(selections);
    data.appendChild(dddrivers);
    const tech = document.querySelector(`#technica${ind+1}`);
    tech.classList.add('nolink');
    tech.parentNode.insertBefore(data, tech.nextSibling);
}

async function addDrivers(ind) {
    let data = document.createElement('dl')
    data.className = 'row mt-5 disabled';
    data.id = `driverOf${ind['ord']}`
    let drivers = document.createElement('div')
    drivers.className = 'col-3 font-weight-bold';
    drivers.innerText = 'Исполнитель';
    data.appendChild(drivers);

    let dddrivers = document.createElement('dd')
    dddrivers.className = 'col-2'
    let selections = document.createElement('select')
    selections.className = 'custom-select mr-sm-2 text-center slc'
    selections.id = `inlineFormCustom${ind['ord']}`
    selections.addEventListener('change', () => emmitedDriver(`inlineFormCustom${ind['ord']}`));
    let names = ind['values'];

    let child = document.createElement('option')
    child.value = ''+0
    child.innerText = 'Не выбрано'
    selections.appendChild(child)

    names.forEach((element, index) =>
    {
        let child = document.createElement('option')
        child.value = index+1
        child.innerText = element['ФИО']
        selections.appendChild(child)
    })

    dddrivers.appendChild(selections);
    data.appendChild(dddrivers);
    const tech = document.querySelector(`#technica${ind['ord']}`);
    tech.parentNode.insertBefore(data, tech.nextSibling);
}

async function vehicleChoice(index, date, start, end) {
    let arr = Array.from(document.querySelectorAll(`div > #list-of-free-vehicles-${index} a`));
    arr.forEach((elem, indexed) => {
        elem.addEventListener('click', () => {
            let veh = document.querySelector(`a[href="#vehicle${index}"]`);
            veh.children[1].innerText = elem.innerText;
            veh.classList.add("text-primary");
            //let driver_row = veh.parentElement.nextElementSibling;
            //driver_row.classList.remove("disabled");
            /* Вставка таймлайна с дорогой*/
            timelines[index].addItem(date, {
                id: timelines[0].iOfLastElem,
                group: 0,
                className: 'drive',
                start: start,
                end: end
            }, 'Дорога')
            document.querySelector(`#driverOf${index + 1}`).classList.remove('disabled')
            veh.click();
        });
    });
    socket.emit('getFreeDriverList', orderID, orderCount);
    orderCount++;
}

async function setRealVehiclesInfo(index, realVehicles) {

    let collapseList = document.getElementById("collapse-list-of-vehicles");
    collapseList.classList.add('disabled');
    let newCollapse = document.createElement("div");
    newCollapse.className = "collapse show";
    newCollapse.setAttribute("id", "vehicle" + index);

    let containerDiv = document.createElement("div");
    containerDiv.className = "container mt-4 app-back-panel";
    newCollapse.append(containerDiv);

    let innerContainerDiv = document.createElement("div");
    innerContainerDiv.className = "row mt-3 mb-5";
    containerDiv.append(innerContainerDiv);

    let listOfVehicles = document.createElement("div");
    listOfVehicles.className = "col-3 ml-2";
    listOfVehicles.id = `list-of-vehicles-${index}`;
    innerContainerDiv.append(listOfVehicles);

    let listOfFreeVehicles = document.createElement("div");
    listOfFreeVehicles.id = `list-of-free-vehicles-${index}`;
    listOfVehicles.append(listOfFreeVehicles);
    let listOfFreeVehiclesTitleRow = document.createElement("div");
    listOfFreeVehiclesTitleRow.className = "row mt-1";
    listOfFreeVehicles.append(listOfFreeVehiclesTitleRow);
    let listOfFreeVehiclesTitle = document.createElement("div");
    listOfFreeVehiclesTitle.className = "col mb-4";
    listOfFreeVehiclesTitle.innerText = "Свободная техника";
    listOfFreeVehiclesTitleRow.append(listOfFreeVehiclesTitle);

    let groupsFree = [];
    let timelinePointsFree = [];
    realVehicles.forEach((vehicle, veh_i) => {
        let vehicleDiv = document.createElement("div");
        vehicleDiv.className = `row mt-4 vec${veh_i}`;
        let vehicleLink = document.createElement("a");
        vehicleLink.className = "col font-weight-bold";
        vehicleLink.innerText = vehicle['Название'];
        carSet.add(vehicle['Название']);
        vehicleDiv.append(vehicleLink);
        let isBusy = vehicle['Занято'];
        if (!isBusy) {
            groupsFree.push(vehicle['Название']);
            if (vehicle['ТочкаМаршрута'].length > 0) {
                for (const vehPoint of vehicle['ТочкаМаршрута'])
                {
                    timelinePointsFree.push({
                        group: veh_i,
                        className: 'busy',
                        Начало: vehPoint['Начало'],
                        Конец: vehPoint['Конец']
                    });
                }
            }
            let startTime = new Date(`${globalDate} ${collisionArray[index]['Начало']}`);
            startTime.setHours(startTime.getHours() + 1);
            timelinePointsFree.push({
                group: veh_i,
                className: 'work',
                Начало: startTime,
                Конец: `${globalDate}T${collisionArray[index]['Конец']}`
            });
            listOfFreeVehicles.append(vehicleDiv);
        }
    });
    // таймлайны
    let listOfTimelines = document.createElement("div");
    listOfTimelines.className = "col ml-2";
    innerContainerDiv.append(listOfTimelines);

    let timelineFreeTitleRow = document.createElement("div");
    timelineFreeTitleRow.className = "row mt-1";
    listOfTimelines.append(timelineFreeTitleRow);
    let timelineFreeTitle = document.createElement("div");
    timelineFreeTitle.className = "col mb-4";
    timelineFreeTitle.innerText = "Операция-время";
    timelineFreeTitleRow.append(timelineFreeTitle);

    let timelineFree = document.createElement("div");
    timelineFree.className = "col";
    timelineFree.id = `timelineFreeRealVeh${index}`;
    listOfTimelines.append(timelineFree);

    collapseList.appendChild(newCollapse);
    let endTimeOfRoad = new Date(`${globalDate} ${collisionArray[index]['Начало']}`);
    endTimeOfRoad.setHours(endTimeOfRoad.getHours() + 1);
    await vehicleChoice(index, globalDate, `${globalDate}T${collisionArray[index]['Начало']}`, endTimeOfRoad);
    let freeTimeline = new Timeline(`timelineFreeRealVeh${index}`, globalDate, getTimepointForVisTimeline(timelinePointsFree), groupsFree);

}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function (event) {
    socket.emit('getOrderInfo', orderID);
    //socket.emit('getTimelineInfo', orderID);
    document.getElementById('to_mp').addEventListener('click', () => op_mp());
    document.getElementById('add_save').addEventListener('click', () => checkFilledData());
    //prepareCollapse();
});