const socket = io.connect('', {
    'forceNew': true,
    'reconnection': false
});
socket.on('disconnect', () => {
    setTimeout(() => {
        alert("Потеряно соединение с сервером.");
        document.location.reload();
    }, 2000);
});

const user = window.location.href.split('/');
socket.emit('take_user', user[3], user[4]);

async function out_to_init() {
    if (confirm("Вы точно хотите выйти?")) {
        window.open("/init", "_self");
    }
}

// добавляем строку со статистикой
socket.on('addStat', (data) => {
    data.forEach(element =>
        addStatRow(element['название_дисциплина'], element['ФИО_преподаватель'],
            element['описание_дисциплина'], element['описание_преподаватель'],
            element['дата_экзамена'], element['оценка'], element['даты_сдачи'])
    );
});

async function addStatRow(name, fio, opis_dis, opis_prep, date_ex, rating, dates) {
    let tbody = document.getElementById("table_of_stat").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_name = document.createElement("TD");
    row.appendChild(td_name);

    let td_fio = document.createElement("TD");
    row.appendChild(td_fio);

    let td_date_ex = document.createElement("TD");
    row.appendChild(td_date_ex);

    let td_rating = document.createElement("TD");
    row.appendChild(td_rating);

    let td_dates = document.createElement("TD");
    row.appendChild(td_dates);

    tbody.appendChild(row);

    td_name.innerHTML = name;
    td_name.title = `${opis_dis[`институт`]}, ${opis_dis[`кафедра`]}`;
    td_fio.innerHTML = fio;
    td_fio.title = `${opis_prep[`институт`]}, ${opis_prep[`кафедра`]}`;
    td_date_ex.innerHTML = date_ex;
    td_rating.innerHTML = rating;
    td_dates.innerHTML = dates;
}

async function get_main_stat() {
    socket.emit('get_stat', user[4]);
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {
    get_main_stat();
    document.getElementById('out_to_init').addEventListener('click', () => out_to_init());
});