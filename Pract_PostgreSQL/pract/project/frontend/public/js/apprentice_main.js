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

const userlog = window.location.href.split('/')[4];
socket.emit('take_user', userlog);

async function start_theory() {
    window.open(`/apprentice_theory/${userlog}`, "_self");
}
async function start_test() {
    window.open(`/apprentice_test/${userlog}`, "_self");
}
async function start_lab() {
    window.open(`/apprentice_lab/${userlog}`, "_self");
}
async function out_to_init() {
    if (confirm("Вы точно хотите выйти?")) {
        window.open("/init", "_self");
    }
}

// добавляем строку со статистикой
socket.on('addKontr', (data) => {
    if (data != null) {
        data.forEach(element =>
            addKontrRow(element['idkontr_stat'], element['rating'], element['date_kontr'])
        );
    }
});
async function addKontrRow(id, rating, date) {
    let tbody = document.getElementById("table_of_kontr_info").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_date = document.createElement("TD");
    row.appendChild(td_date);

    let td_rating = document.createElement("TD");
    row.appendChild(td_rating);

    tbody.appendChild(row);

    td_id.innerHTML = id;
    td_rating.innerHTML = rating;
    td_date.innerHTML = date;
}

socket.on('addTest', (data) => {
    if (data != null) {
        let max_rat = 0;
        data.forEach(element => {
            addTestRow(element['idtest_stat'], element['rating'], element['date_test']);
            if (element['rating'] > max_rat) { max_rat = element['rating']; }
        });
        document.getElementById("max_test_result").innerHTML += max_rat;
    }
});
async function addTestRow(id, rating, date) {
    let tbody = document.getElementById("table_of_test_info").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_date = document.createElement("TD");
    row.appendChild(td_date);

    let td_rating = document.createElement("TD");
    row.appendChild(td_rating);

    tbody.appendChild(row);

    td_id.innerHTML = id;
    td_rating.innerHTML = rating;
    td_date.innerHTML = date;
}

socket.on('addLab', (data) => {
    if (data != null) {
        data.forEach(element => {
            addLabRow(element['idlab_stat'], element['rating'], element['date_lab']);
        });
    }
});
async function addLabRow(id, rating, date) {
    let tbody = document.getElementById("table_of_lab_info").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_date = document.createElement("TD");
    row.appendChild(td_date);

    let td_rating = document.createElement("TD");
    row.appendChild(td_rating);

    tbody.appendChild(row);

    td_id.innerHTML = id;
    td_rating.innerHTML = rating;
    td_date.innerHTML = date;
}

async function get_stat() {
    socket.emit('get_kontr_stat', userlog);
    socket.emit('get_test_stat', userlog);
    socket.emit('get_lab_stat', userlog);
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {

    get_stat();
    document.getElementById('start_theory').addEventListener('click', () => start_theory());
    document.getElementById('start_test').addEventListener('click', () => start_test());
    document.getElementById('start_lab').addEventListener('click', () => start_lab());
    document.getElementById('out_to_init').addEventListener('click', () => out_to_init());
});