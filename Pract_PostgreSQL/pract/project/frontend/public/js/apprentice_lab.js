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

let i = 0;
let anss = [];
let rat = [];
let lab_query = [];

async function out_to_stat() {
    window.open(`/apprentice_main/${userlog}`, "_self");
}

socket.on('alert_some', (some) => {
    document.getElementById('div_alert_some').innerHTML = `<p>Сообщение: ${some}</p>`;
});

socket.on('set_rat', (_rat) => {
    rat.push(_rat);
    ++i;
    if (i < lab_query.length) {
        socket.emit('get_lab_table');
    } else {
        socket.emit('init_lab_stat', userlog, rat, anss);
        out_to_stat();
    }
});

async function do_lab_query() {
    let que = document.getElementById('input_query').value;

    if (que.slice(-1) == ';') {
        if (que.indexOf('user_table') > -1) {
            let que_tmp = que.toLowerCase().replace(/\s+/g, '');

            let k = 0;
            let n = que.indexOf('\'', k);
            while (n > -1) {
                lab_query[i]['right_query'] = lab_query[i]['right_query'].slice(0, n) + '\'' + lab_query[i]['right_query'].slice(n);
                que = que.slice(0, n) + '\'' + que.slice(n);
                k = n + 2;
                n = que.indexOf('\'', k);
            }
            anss.push(`"${que}"`);

            let nt = -1;
            lab_query[i]['need_this'].forEach(element => {
                let t = que_tmp.indexOf(element);
                if (t > nt) {
                    nt = t;
                }
            });
            console.log(nt);

            if (nt > -1) {
                socket.emit('check_query', que, lab_query[i]['right_query']);
            } else {
                socket.emit('do_right_query', lab_query[i]['right_query']);
            }
        } else {
            document.getElementById('div_alert_some').innerHTML = `<p>Сообщение: Нет запроса на таблицу user_table;</p>`;
        }
    } else {
        document.getElementById('div_alert_some').innerHTML = `<p>Сообщение: Запрос должен заканчиваться на ;</p>`;
    }
}


socket.on('set_table', (table) => {
    document.getElementById('div_alert_some').innerHTML = ``;
    let lab_table = document.getElementById('table_of_text_info');
    let new_tbody = document.createElement('TBODY');

    lab_table.replaceChild(new_tbody, lab_table.getElementsByTagName("TBODY")[0]);

    if (table != null) {
        table.forEach(element => {
            let td_row = document.createElement("TR");

            for (let j = 1; j < 5; ++j) {
                let td = document.createElement("TD");
                td_row.appendChild(td);
                if (element[`col_${j}`] != null) {
                    td.innerHTML = element[`col_${j}`];
                }
            }
            new_tbody.appendChild(td_row);
        });
    }

    set_question();
});


async function set_question() {
    let div_question = document.getElementById('div_question');
    div_question.innerHTML = lab_query[i]['question'];
}
socket.on('set_lab_query', (data) => {
    lab_query = data;
});

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {
    socket.emit('get_lab_query');

    socket.emit('get_first_lab_table');

    document.getElementById('out_to_stat').addEventListener('click', () => out_to_stat());

    document.getElementById('div_of_query').innerHTML += `<form> <button type="button" class="button" id="do_query"> enter </button> </form>`;

    let but = document.getElementById(`do_query`);
    but.addEventListener('click', () => {
        do_lab_query();
    });
});