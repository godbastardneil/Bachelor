const socket = io.connect('', {
    'forceNew': true,
    'reconnection': false
});
socket.on('disconnect', () => {
    setTimeout(() => {
        alert("Потеряно соединение с сервером.");
        document.location.reload();
        end_test();
    }, 2000);
});

const userlog = window.location.href.split('/')[4];
socket.emit('take_user', userlog);

let id_do_test;
socket.on('set_do_test', (id_t) => {
    id_do_test = id_t;
});

async function out_to_stat() {
    window.open(`/apprentice_main/${userlog}`, "_self");
}

async function do_test() {
    let input_answer = document.getElementsByClassName('input_answer');
    for (let i = 0; i < input_answer.length; i++) {
        let anss_tmp = [];
        let name_tmp = input_answer[i].getAttribute("name");
        let ex = document.getElementsByName(name_tmp);
        ex.forEach(ex_ans => {
            if (ex_ans.checked) {
                anss_tmp.push(ex_ans.value);
            }
            i++;
        });
        i--;
        socket.emit('init_test_stat', id_do_test, name_tmp, anss_tmp);
    }
}

/* Функция добавления задания */
socket.on('set_test', (exs) => {
    let test_div = document.getElementById('div_of_test');

    exs.forEach(ex => {
        test_div.innerHTML += "<p>" + ex['question'] + "</p>";
        test_div.innerHTML += `<p><b>Выберите ответ:</b><br> </p>`;

        for (let j = 0; j < ex['variants'].length; j++) {
            test_div.innerHTML += `<input class="input_answer" name="${ex['idtest_ex']}"
                                        id="${ex['idtest_ex']}_${j}" type="checkbox" value="${j+1}" size="40">${ex['variants'][j]}<br>`;
        }
    });
    test_div.innerHTML += `<form> <button type="button" class="button" id="do_test"> Ответить </button> </form>`;

    let but = document.getElementById(`do_test`);
    but.addEventListener('click', () => {
        do_test();

        out_to_stat();
    });
});
async function get_test() {
    socket.emit('get_test', userlog);
    socket.emit('create_test', userlog);
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {
    get_test();

});