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

async function out_to_stat() {
    window.open(`/apprentice_main/${userlog}`, "_self");
}
async function do_kontr() {
    let input_answer = document.getElementsByClassName('input_answer');
    let ans;
    let anss = [];
    for (let j = 0; j < input_answer.length; j++) {
        ans = input_answer[j].value;
        if (ans == null || ans == '') {
            ans = 'нет ответа';
        }
        anss.push(`"${ans}"`);
    }
    socket.emit('init_kontr_stat', userlog, anss);
}

socket.on('set_kontr', (quests) => {
    let kontr_div = document.getElementById('div_of_kontr_quest');

    quests.forEach(quest => {
        kontr_div.innerHTML += "<p>" + quest['question'] + "</p>";
        kontr_div.innerHTML += `<p><b>Введите ответ:</b><br> <input class="input_answer" id="id_${quest['idkontr_quest']}" type="text" size="40"></p>`;
    });
    kontr_div.innerHTML += `<form> <button type="button" class="button" id="do_kontr"> Ответить </button> </form>`;

    let but = document.getElementById(`do_kontr`);
    but.addEventListener('click', () => {
        do_kontr();

        out_to_stat();
    });
});

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {

    document.getElementById('out_to_stat').addEventListener('click', () => out_to_stat());
    /*document.getElementById('do_kontr').addEventListener('click', () => {
        do_kontr();

        out_to_stat();
    });*/

    socket.emit('get_kontr');
});