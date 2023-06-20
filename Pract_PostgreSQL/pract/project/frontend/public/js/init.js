const socket = io();

socket.on('disconnect', () => {
    setTimeout(() => {
        alert("Потеряно соединение с сервером.");
        document.location.reload();
    }, 2000);
});

let log;
let pas;

// если вход в программу разрешен, то вводится, иначе выводим ошибку
socket.on('passSuccess', () => {
    window.open(`/apprentice_main/${log}`, "_self");
});

socket.on('user_alreaby_in_system', () => {
    alert(`Пользователь ${log} уже вошел!`);
});
socket.on('user_do_not_exist', () => {
    alert(`Вы ввели неверный Логин или Пароль!`);
});

socket.on('can_to_init', () => {
    socket.emit('check_for_init', log);
});

async function get_data_for_init() {
    log = document.getElementById("init_login-edit").value;
    pas = document.getElementById("init_password-edit").value;

    socket.emit('check_user', log, pas);
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {
    document.getElementById('init_button').addEventListener('click', () => get_data_for_init());
});