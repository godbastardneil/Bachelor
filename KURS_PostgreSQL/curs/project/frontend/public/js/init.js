const socket = io();

socket.on('disconnect', () => {
    setTimeout(() => {
        alert("Потеряно соединение с сервером.");
        document.location.reload();
    }, 2000);
});

let user;
let pas;
let type;

// если вход в программу разрешен, то вводится, иначе выводим ошибку
socket.on('passSuccess_for_student', () => {
    window.open(`/student/${user}`, "_self");
});
socket.on('passSuccess_for_teacher', () => {
    window.open(`/teacher/${user}`, "_self");
});


socket.on('passSuccess_for_admin', () => {
    window.open(`/admin/${user}`, "_self");
});

socket.on('user_alreaby_in_system', () => {
    alert(`Пользователь ${user} уже вошел!`);
});
socket.on('user_do_not_exist', () => {
    alert(`Вы ввели неверный Логин или Пароль!`);
});

socket.on('can_to_init', () => {
    socket.emit('check_for_init', user, type);
});

async function get_data_for_init() {
    user = document.getElementById("init_login-edit").value;
    pas = document.getElementById("init_password-edit").value;
    type = document.querySelector('input[name="type"]:checked').value;
    if (type == 'student') {
        socket.emit('check_student', user, pas);
    } else if (type == 'teacher') {
        socket.emit('check_teacher', user, pas);
    } else {
        socket.emit('check_admin', user, pas);
    }
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {
    document.getElementById('init_button').addEventListener('click', () => get_data_for_init());
});