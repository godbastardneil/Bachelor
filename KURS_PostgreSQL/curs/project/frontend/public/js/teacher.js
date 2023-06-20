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

let rat_select;

socket.on('addRaiting', (data) => {
    rat_select = `<select><option value="0">NULL</option>`;
    data.forEach(element => {
        rat_select += `<option id="option_${element['idоценка']}" value="${element['idоценка']}"> ${element['название']} </option>`;
    });
    rat_select += `</select>`;
});

socket.on('can_not_do_this', (error) => {
    alert(`${error}`);
});



socket.on('change_rat', (id, id_plan, data) => {
    let row = document.getElementById(`row_${id_plan}_${id}`);

    row.cells[2].innerHTML += `,${data['дата_сдачи']}`;

    let td_select = document.getElementById(`select_${id_plan}_${id}`);
    td_select.style.color = "black";

    let but = document.getElementById(`save_raiting_${id_plan}_${id}`);
    if (!data['можно_сдавать']) {
        but.disabled = true;
        td_select.disabled = true;
    }
});
async function save_raiting(id, id_plan) {
    socket.emit('save_change_exam', id, id_plan, document.getElementById(`select_${id_plan}_${id}`).value);
}


socket.on('addStudents', (data, id_plan) => {
    data.forEach(element => {
        addStudentRow(element['idстудент'], element['ФИО'], element['idоценка'], element['даты_сдачи'], element['можно_сдавать'], id_plan);
    });
});
async function addStudentRow(id, fio, id_rat, dates, can, id_plan) {
    let tbody = document.getElementById(`plan_${id_plan}`).getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_fio = document.createElement("TD");
    row.appendChild(td_fio);

    let td_rat = document.createElement("TD");
    row.appendChild(td_rat);

    let td_dates = document.createElement("TD");
    row.appendChild(td_dates);

    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    row.id = `row_${id_plan}_${id}`;

    td_fio.innerHTML = id + ". " + fio;
    td_rat.innerHTML = rat_select;

    let td_select = td_rat.getElementsByTagName("select")[0];
    td_select.id = `select_${id_plan}_${id}`;

    td_select.value = id_rat;

    td_dates.innerHTML = dates;
    td_act.innerHTML = `<button type="button" class="button" id="save_raiting_${id_plan}_${id}"> Сохранить </button>`;

    let but = document.getElementById(`save_raiting_${id_plan}_${id}`);
    if (can || can == null) {
        but.addEventListener('click', () => save_raiting(id, id_plan));
        td_select.onchange = function() {
            this.style.color = "red";
        };

    } else {
        but.disabled = true;
        td_select.disabled = true;
    }
}

socket.on('addDisGroups', (data) => {
    data.forEach(element => {
        addDisGroupRow(element['idуч_план'], element['idдисциплина'], element['название_дисциплина'], element['описание_дисциплина'],
            element['idгруппа'], element['название_группа'], element['описание_группа'], element['дата_экзамена']);
        socket.emit('get_plan_stud', element['idуч_план']);
    });
});
async function addDisGroupRow(id, id_dis, name_dis, opis_dis, id_gr, name_gr, opis_gr, date_ex) {
    let main_div = document.getElementById("main");
    let gr_div = document.createElement("div");

    let dis_div = document.getElementById(`discipline_${id_dis}`);

    if (dis_div == null) {
        let dis_sel = document.createElement("section");
        dis_div = document.createElement("div");
        dis_div.name = `discipline`;
        dis_div.id = `discipline_${id_dis}`;

        dis_div.innerHTML += `<h3 title="${opis_dis[`институт`]}, ${opis_dis[`кафедра`]}">Дисциплина: ${id_dis}. ${name_dis}</h3>`;

        dis_sel.appendChild(dis_div);
        main_div.appendChild(dis_sel);
    }

    gr_div.name = `group`;
    gr_div.id = `group_${id_gr}`;

    dis_div.appendChild(gr_div);
    gr_div.innerHTML += `<h3 title="${opis_gr[`институт`]}, ${opis_gr[`кафедра`]}"> Группа: ${id_gr}. ${name_gr}</h3><p>Дата: ${date_ex}</p>`;
    gr_div.innerHTML += `<table id="plan_${id}" border="1"><thead><tr><th>ФИО</th><th>Оценка</th><th>Даты сдач</th><th>Действия</th></tr></thead><tbody class = "tbody-mp"></tbody></table>`;
}

async function get_data() {
    socket.emit('get_rating');
    socket.emit('get_teacher_plan', user[4]);
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {
    get_data();
    document.getElementById('out_to_init').addEventListener('click', () => out_to_init());
});