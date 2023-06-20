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

socket.on('alert_error', (error) => {
    alert(`Error: ${error}`);
});

var i = -1;

socket.on('clean_discipline', (id) => {
    let row = document.getElementById(`discipline_${id}`);
    row.remove();
});
socket.on('clean_teacher', (id) => {
    let row = document.getElementById(`teacher_${id}`);
    row.remove();
});
socket.on('clean_group', (id) => {
    let row = document.getElementById(`group_${id}`);
    row.remove();
});
socket.on('clean_student', (id, data) => {
    let row = document.getElementById(`student_${id}`);
    row.remove();

    let row_gr = document.getElementById(`group_${data["idгруппа"]}`);
    row_gr.cells[2].innerHTML = data["кол_во_чел"];
});
socket.on('clean_plan', (id) => {
    let row = document.getElementById(`plan_${id}`);
    row.remove();
});

async function remove_discipline(id) {
    socket.emit('remove_discipline', id);
}
async function remove_teacher(id) {
    socket.emit('remove_teacher', id);
}
async function remove_group(id) {
    socket.emit('remove_group', id);
}
async function remove_student(id) {
    socket.emit('remove_student', id);
}
async function remove_plan(id) {
    socket.emit('remove_plan', id);
}


socket.on('set_change_discipline', (id, data) => {
    let row = document.getElementById(`discipline_${id}`);
    let namepole = document.getElementById(`discipline_name_${id}`);
    let instpole = document.getElementById(`discipline_inst_${id}`);
    let kafpole = document.getElementById(`discipline_kaf_${id}`);

    namepole.style.color = "black";
    instpole.style.color = "black";
    kafpole.style.color = "black";

    row.cells[0].innerHTML = data['idдисциплина'];
    namepole.value = data["название"];
    instpole.value = data['институт'];
    kafpole.value = data['кафедра'];

    row.id = `discipline_${data['idдисциплина']}`;
    namepole.id = `discipline_name_${data['idдисциплина']}`;
    instpole.id = `discipline_inst_${data['idдисциплина']}`;
    kafpole.id = `discipline_kaf_${data['idдисциплина']}`;

    let but_ch = document.getElementById(`change_discipline_${id}`);
    but_ch.removeEventListener('click', () => change_discipline(id));

    let but_del = document.getElementById(`remove_discipline_${id}`);
    but_del.removeEventListener('click', () => remove_discipline(id));

    but_ch.id = (`change_discipline_${data['idдисциплина']}`);
    but_ch.addEventListener('click', () => change_discipline(data['idдисциплина']));

    but_del.id = (`remove_discipline_${data['idдисциплина']}`);
    but_del.addEventListener('click', () => remove_discipline(data['idдисциплина']));
});
socket.on('set_change_teacher', (id, data) => {
    let row = document.getElementById(`teacher_${id}`);
    let idpole = document.getElementById(`teacher_id_${id}`);
    let fiopole = document.getElementById(`teacher_fio_${id}`);
    let paspole = document.getElementById(`teacher_pas_${id}`);
    let instpole = document.getElementById(`teacher_inst_${id}`);
    let kafpole = document.getElementById(`teacher_kaf_${id}`);

    idpole.style.color = "black";
    fiopole.style.color = "black";
    paspole.style.color = "black";
    instpole.style.color = "black";
    kafpole.style.color = "black";

    idpole.readOnly = true;

    idpole.value = data["idпреподаватель"];
    fiopole.value = data["ФИО"];
    paspole.value = data["пароль"];
    instpole.value = data['институт'];
    kafpole.value = data['кафедра'];

    row.id = `teacher_${data['idпреподаватель']}`;
    idpole.id = `teacher_id_${data['idпреподаватель']}`;
    fiopole.id = `teacher_fio_${data['idпреподаватель']}`;
    paspole.id = `teacher_pas_${data['idпреподаватель']}`;
    instpole.id = `teacher_inst_${data['idпреподаватель']}`;
    kafpole.id = `teacher_kaf_${data['idпреподаватель']}`;

    let but_ch = document.getElementById(`change_teacher_${id}`);
    but_ch.removeEventListener('click', () => change_teacher(id));

    let but_del = document.getElementById(`remove_teacher_${id}`);
    but_del.removeEventListener('click', () => remove_teacher(id));

    but_ch.id = (`change_teacher_${data['idпреподаватель']}`);
    but_ch.addEventListener('click', () => change_teacher(data['idпреподаватель']));

    but_del.id = (`change_teacher_${data['idпреподаватель']}`);
    but_del.addEventListener('click', () => remove_teacher(data['idпреподаватель']));
});
socket.on('set_change_group', (id, data) => {
    let row = document.getElementById(`group_${id}`);
    let namepole = document.getElementById(`group_name_${id}`);
    let instpole = document.getElementById(`group_inst_${id}`);
    let kafpole = document.getElementById(`group_kaf_${id}`);

    namepole.style.color = "black";
    instpole.style.color = "black";
    kafpole.style.color = "black";

    row.cells[0].innerHTML = data['idгруппа'];
    namepole.value = data["название"];
    row.cells[2].innerHTML = data['кол_во_чел'];
    instpole.value = data['институт'];
    kafpole.value = data['кафедра'];

    row.id = `group_${data['idгруппа']}`;
    namepole.id = `group_name_${data['idгруппа']}`;
    instpole.id = `group_inst_${data['idгруппа']}`;
    kafpole.id = `group_kaf_${data['idгруппа']}`;

    let but_ch = document.getElementById(`change_group_${id}`);
    but_ch.removeEventListener('click', () => change_group(id));

    let but_del = document.getElementById(`remove_group_${id}`);
    but_del.removeEventListener('click', () => remove_group(id));

    but_ch.id = (`change_group_${data['idгруппа']}`);
    but_ch.addEventListener('click', () => change_group(data['idгруппа']));

    but_del.id = (`change_group_${data['idгруппа']}`);
    but_del.addEventListener('click', () => remove_group(data['idгруппа']));
});
socket.on('set_change_student', (id, data) => {
    let row = document.getElementById(`student_${id}`);

    let idpole = document.getElementById(`student_id_${id}`);
    let fiopole = document.getElementById(`student_fio_${id}`);
    let paspole = document.getElementById(`student_pas_${id}`);
    let grpole = document.getElementById(`student_gr_${id}`);

    idpole.style.color = "black";
    fiopole.style.color = "black";
    paspole.style.color = "black";
    grpole.style.color = "black";

    idpole.readOnly = true;

    idpole.value = data["idстудент"];
    fiopole.value = data["ФИО"];
    paspole.value = data["пароль"];

    row.id = `student_${data['idстудент']}`;
    idpole.id = `student_id_${data['idстудент']}`;
    fiopole.id = `student_fio_${data['idстудент']}`;
    paspole.id = `student_pas_${data['idстудент']}`;
    grpole.id = `student_gr_${data['idстудент']}`;

    if (data["idстарая_группа"] != null) {
        let old_gr = document.getElementById(`group_${data["idстарая_группа"]}`);
        old_gr.cells[2].innerHTML = data["idстарая_группа_кол"];
    }

    let new_gr = document.getElementById(`group_${data["idновая_группа"]}`);
    new_gr.cells[2].innerHTML = data["idновая_группа_кол"];

    let but_ch = document.getElementById(`change_student_${id}`);
    but_ch.removeEventListener('click', () => change_student(id));

    let but_del = document.getElementById(`remove_student_${id}`);
    but_del.removeEventListener('click', () => remove_student(id));

    but_ch.id = (`change_student_${data['idстудент']}`);
    but_ch.addEventListener('click', () => change_group(data['idстудент']));

    but_del.id = (`remove_student_${data['idстудент']}`);
    but_del.addEventListener('click', () => remove_group(data['idстудент']));
});
socket.on('set_change_plan', (id, data) => {
    let row = document.getElementById(`plan_${id}`);
    let dispole = document.getElementById(`plan_dis_${id}`);
    let preppole = document.getElementById(`plan_prep_${id}`);
    let grpole = document.getElementById(`plan_gr_${id}`);
    let datepole = document.getElementById(`plan_date_${id}`);

    dispole.style.color = "black";
    preppole.style.color = "black";
    grpole.style.color = "black";
    datepole.style.color = "black";

    row.cells[0].innerHTML = data['idуч_план'];
    dispole.value = data["idдисциплина"];
    preppole.value = data["idпреподаватель"];
    grpole.value = data["idгруппа"];
    if (data['дата_экзамена']) {
        datepole.value = data['дата_экзамена'];
    }

    row.id = `plan_${data['idуч_план']}`;
    dispole.id = `plan_dis_${data['idуч_план']}`;
    preppole.id = `plan_prep_${data['idуч_план']}`;
    grpole.id = `plan_gr_${data['idуч_план']}`;
    datepole.id = `plan_date_${data['idуч_план']}`;

    let but_ch = document.getElementById(`change_plan_${id}`);
    but_ch.removeEventListener('click', () => change_plan(id));

    let but_del = document.getElementById(`remove_plan_${id}`);
    but_del.removeEventListener('click', () => remove_plan(id));

    but_ch.id = (`change_plan_${data['idуч_план']}`);
    but_ch.addEventListener('click', () => change_plan(data['idстудент']));
    change_plan
    but_del.id = (`remove_plan_${data['idуч_план']}`);
    but_del.addEventListener('click', () => remove_plan(data['idуч_план']));
});

async function change_discipline(id) {
    let pole_name = document.getElementById(`discipline_name_${id}`);
    let pole_inst = document.getElementById(`discipline_inst_${id}`);
    let pole_kaf = document.getElementById(`discipline_kaf_${id}`);

    let name = pole_name.value;
    let inst = pole_inst.value;
    let kaf = pole_kaf.value;

    if (name != null && inst != null && kaf != null) {

        socket.emit('change_discipline', id, name, inst, kaf);
    } else {
        alert('Вы ставили пустые поля');
    }
}
async function change_teacher(id) {
    let pole_id = document.getElementById(`teacher_id_${id}`);
    let pole_fio = document.getElementById(`teacher_fio_${id}`);
    let pole_pas = document.getElementById(`teacher_pas_${id}`);
    let pole_inst = document.getElementById(`teacher_inst_${id}`);
    let pole_kaf = document.getElementById(`teacher_kaf_${id}`);

    let new_id = pole_id.value;
    let fio = pole_fio.value;
    let pas = pole_pas.value;
    let inst = pole_inst.value;
    let kaf = pole_kaf.value;


    if (fio != null && pas != null && new_id != null && inst != null && kaf != null) {

        socket.emit('change_teacher', id, new_id, fio, pas, inst, kaf);
    } else {
        alert('Вы ставили пустые поля');
    }
}
async function change_group(id) {
    let pole_name = document.getElementById(`group_name_${id}`);
    let pole_inst = document.getElementById(`group_inst_${id}`);
    let pole_kaf = document.getElementById(`group_kaf_${id}`);

    let name = pole_name.value;
    let inst = pole_inst.value;
    let kaf = pole_kaf.value;

    if (name != null && inst != null && kaf != null) {

        socket.emit('change_group', id, name, inst, kaf);
    } else {
        alert('Вы ставили пустые поля');
    }
}
async function change_student(id) {
    let pole_id = document.getElementById(`student_id_${id}`);
    let pole_fio = document.getElementById(`student_fio_${id}`);
    let pole_pas = document.getElementById(`student_pas_${id}`);
    let pole_gr = document.getElementById(`student_gr_${id}`);

    let new_id = pole_id.value;
    let fio = pole_fio.value;
    let pas = pole_pas.value;
    let id_gr = pole_gr.value;

    if (new_id && fio && pas && id_gr) {
        socket.emit('change_student', id, new_id, fio, pas, id_gr);
    } else {
        alert('Вы ставили пустые поля');
    }
}
async function change_plan(id) {
    let pole_dis = document.getElementById(`plan_dis_${id}`);
    let pole_prep = document.getElementById(`plan_prep_${id}`);
    let pole_gr = document.getElementById(`plan_gr_${id}`);
    let pole_date = document.getElementById(`plan_date_${id}`);

    let id_dis = pole_dis.value;
    let id_prep = pole_prep.value;
    let id_gr = pole_gr.value;
    let date = pole_date.value;

    if (id_dis && id_prep && id_gr && date) {

        socket.emit('change_plan', id, id_dis, id_prep, id_gr, date);
    } else {
        alert('Вы ставили пустые поля');
    }
}


socket.on('set_discipline', (data) => {
    if (data) {
        data.forEach(element => {
            addDisciplineRow(element['idдисциплина'], element['название'], element['институт'], element['кафедра']);
        });
    }
});
async function addDisciplineRow(id, name, inst, kaf) {
    let tbody = document.getElementById("table_of_discipline").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_name = document.createElement("TD");
    row.appendChild(td_name);

    let td_inst = document.createElement("TD");
    row.appendChild(td_inst);

    let td_kaf = document.createElement("TD");
    row.appendChild(td_kaf);

    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    row.id = `discipline_${id}`;

    td_id.innerHTML = id;
    td_name.innerHTML = `<input size="20" value="${name}" id="discipline_name_${id}">`;
    td_inst.innerHTML = `<input size="20" value="${inst}" id="discipline_inst_${id}">`;
    td_kaf.innerHTML = `<input size="20" value="${kaf}" id="discipline_kaf_${id}">`;

    td_act.innerHTML = `<button type="button" class="button" id="change_discipline_${id}"> Сохранить </button> / <button type="button" class="button" id="remove_discipline_${id}"> Удалить </button>`;

    let but_ch = document.getElementById(`change_discipline_${id}`);
    but_ch.addEventListener('click', () => change_discipline(id));

    let but_del = document.getElementById(`remove_discipline_${id}`);
    but_del.addEventListener('click', () => remove_discipline(id));

    document.getElementById(`discipline_name_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`discipline_inst_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`discipline_kaf_${id}`).onchange = function() {
        this.style.color = "red";
    };
}

socket.on('set_teacher', (data) => {
    if (data) {
        data.forEach(element => {
            addTeacherRow(element['idпреподаватель'], element['ФИО'], element['пароль'], element['институт'], element['кафедра']);
        });
    }
});
async function addTeacherRow(id, fio, pas, inst, kaf) {
    let tbody = document.getElementById("table_of_teacher").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_fio = document.createElement("TD");
    row.appendChild(td_fio);

    let td_pas = document.createElement("TD");
    row.appendChild(td_pas);

    let td_inst = document.createElement("TD");
    row.appendChild(td_inst);

    let td_kaf = document.createElement("TD");
    row.appendChild(td_kaf);

    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    row.id = `teacher_${id}`;

    td_id.innerHTML = `<input size="20" value="${id}" id="teacher_id_${id}" type="number">`;
    td_fio.innerHTML = `<input size="20" value="${fio}" id="teacher_fio_${id}">`;
    td_pas.innerHTML = `<input size="20" value="${pas}" id="teacher_pas_${id}">`;
    td_inst.innerHTML = `<input size="20" value="${inst}" id="teacher_inst_${id}">`;
    td_kaf.innerHTML = `<input size="20" value="${kaf}" id="teacher_kaf_${id}">`;

    td_act.innerHTML = `<button type="button" class="button" id="change_teacher_${id}"> Сохранить </button> / <button type="button" class="button" id="remove_teacher_${id}"> Удалить </button>`;

    let but_ch = document.getElementById(`change_teacher_${id}`);
    but_ch.addEventListener('click', () => change_teacher(id));

    let but_del = document.getElementById(`remove_teacher_${id}`);
    but_del.addEventListener('click', () => remove_teacher(id));

    document.getElementById(`teacher_id_${id}`).readOnly = true;
    document.getElementById(`teacher_id_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`teacher_fio_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`teacher_pas_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`teacher_inst_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`teacher_kaf_${id}`).onchange = function() {
        this.style.color = "red";
    };
}

socket.on('set_group', (data) => {
    if (data) {
        data.forEach(element => {
            addGroupRow(element['idгруппа'], element['название'], element['кол_во_чел'], element['институт'], element['кафедра']);
        });
    }
});
async function addGroupRow(id, name, kol, inst, kaf) {
    let tbody = document.getElementById("table_of_group").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_name = document.createElement("TD");
    row.appendChild(td_name);

    let td_kol = document.createElement("TD");
    row.appendChild(td_kol);

    let td_inst = document.createElement("TD");
    row.appendChild(td_inst);

    let td_kaf = document.createElement("TD");
    row.appendChild(td_kaf);

    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    row.id = `group_${id}`;

    td_id.innerHTML = id;
    td_name.innerHTML = `<input size="20" value="${name}" id="group_name_${id}">`;
    td_kol.innerHTML = kol;
    td_inst.innerHTML = `<input size="20" value="${inst}" id="group_inst_${id}">`;
    td_kaf.innerHTML = `<input size="20" value="${kaf}" id="group_kaf_${id}">`;

    td_act.innerHTML = `<button type="button" class="button" id="change_group_${id}"> Сохранить </button> / <button type="button" class="button" id="remove_group_${id}"> Удалить </button>`;

    let but_ch = document.getElementById(`change_group_${id}`);
    but_ch.addEventListener('click', () => change_group(id));

    let but_del = document.getElementById(`remove_group_${id}`);
    but_del.addEventListener('click', () => remove_group(id));

    document.getElementById(`group_name_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`group_inst_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`group_kaf_${id}`).onchange = function() {
        this.style.color = "red";
    };
}

socket.on('set_student', (data) => {
    if (data) {
        data.forEach(element => {
            addStudentRow(element['idстудент'], element['ФИО'], element['пароль'], element['idгруппа']);
        });
    }
});
async function addStudentRow(id, fio, pas, id_gr) {
    let tbody = document.getElementById("table_of_student").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_fio = document.createElement("TD");
    row.appendChild(td_fio);

    let td_pas = document.createElement("TD");
    row.appendChild(td_pas);

    let td_gr = document.createElement("TD");
    row.appendChild(td_gr);

    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    row.id = `student_${id}`;

    td_id.innerHTML = `<input size="20" value="${id}" id="student_id_${id}" type="number">`;
    td_fio.innerHTML = `<input size="20" value="${fio}" id="student_fio_${id}">`;
    td_pas.innerHTML = `<input size="20" value="${pas}" id="student_pas_${id}">`;
    td_gr.innerHTML = `<input size="20" value="${id_gr}" id="student_gr_${id}" type="number">`;

    td_act.innerHTML = `<button type="button" class="button" id="change_student_${id}"> Сохранить </button> / <button type="button" class="button" id="remove_student_${id}"> Удалить </button>`;

    let but_ch = document.getElementById(`change_student_${id}`);
    but_ch.addEventListener('click', () => change_student(id));

    let but_del = document.getElementById(`remove_student_${id}`);
    but_del.addEventListener('click', () => remove_student(id));

    document.getElementById(`student_id_${id}`).readOnly = true;
    document.getElementById(`student_id_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`student_fio_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`student_pas_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`student_gr_${id}`).onchange = function() {
        this.style.color = "red";
    };
}

socket.on('set_plan', (data) => {
    if (data) {
        data.forEach(element => {
            addPlanRow(element['idуч_план'], element['idдисциплина'], element['idгруппа'], element['idпреподаватель'], element['дата_экзамена']);
        });
    }
});
async function addPlanRow(id, id_dis, id_gr, id_prep, date_ex) {
    let tbody = document.getElementById("table_of_plan").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_dis = document.createElement("TD");
    row.appendChild(td_dis);

    let td_prep = document.createElement("TD");
    row.appendChild(td_prep);

    let td_gr = document.createElement("TD");
    row.appendChild(td_gr);

    let td_date = document.createElement("TD");
    row.appendChild(td_date);

    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    row.id = `plan_${id}`;

    td_id.innerHTML = id;
    td_dis.innerHTML = `<input size="20" value="${id_dis}" id="plan_dis_${id}" type="number">`;
    td_prep.innerHTML = `<input size="20" value="${id_prep}" id="plan_prep_${id}" type="number">`;
    td_gr.innerHTML = `<input size="20" value="${id_gr}" id="plan_gr_${id}" type="number">`;
    td_date.innerHTML = `<input size="20" value="${(date_ex)}" id="plan_date_${id}" type="date">`;
    if (date_ex != null) {
        document.getElementById(`plan_date_${id}`).value = date_ex;
    }
    td_act.innerHTML = `<button type="button" class="button" id="change_plan_${id}"> Сохранить </button> / <button type="button" class="button" id="remove_plan_${id}"> Удалить </button>`;

    let but_ch = document.getElementById(`change_plan_${id}`);
    but_ch.addEventListener('click', () => change_plan(id));

    let but_del = document.getElementById(`remove_plan_${id}`);
    but_del.addEventListener('click', () => remove_plan(id));

    document.getElementById(`plan_dis_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`plan_prep_${id}`).onchange = function() {
        this.style.color = "red";
    };
    document.getElementById(`plan_gr_${id}`).onchange = function() {
        this.style.color = "red";
    };
}

async function get_data() {
    socket.emit('get_discipline');
    socket.emit('get_teacher');
    socket.emit('get_group');
    socket.emit('get_student');
    socket.emit('get_plan');
}
// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {
    get_data();
    document.getElementById('out_to_init').addEventListener('click', () => out_to_init());

    document.getElementById('add_discipline').addEventListener('click', () => {
        addDisciplineRow(i, '', '', '');
        --i;
    });
    document.getElementById('add_teacher').addEventListener('click', () => {
        addTeacherRow(i, '', '', '', '');
        document.getElementById(`teacher_id_${i}`).readOnly = false;
        --i;
    });
    document.getElementById('add_group').addEventListener('click', () => {
        addGroupRow(i, '', 0, '', '');
        --i;
    });
    document.getElementById('add_student').addEventListener('click', () => {
        addStudentRow(i, '', '', '');
        document.getElementById(`student_id_${i}`).readOnly = false;
        --i;
    });
    document.getElementById('add_plan').addEventListener('click', () => {
        addPlanRow(i, '', '', '', '');
        --i;
    });
});