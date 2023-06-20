
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

socket.on('addZakazchic', (data) => {
    let s = document.getElementById("title_in");

    s.innerHTML += `<option value="${data['ID_Заказчик']}">${data['Название']}</option>`;
});
socket.on('addAgent', (data) => {
    let s = document.getElementById("fio_in");

    s.innerHTML += `<option value="${data['ID_Агент']}">${data['ФИО']}</option>`;
});

socket.on('addSearсh', (data) => {
    addRow_searсh(data['Сумма'], data['Дата'], data['ФИО'], data['Название']);
});

function addRow_searсh(sum, date, fio, tit)
{
    let tbody = document.getElementById("table_of_searсh").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    let td_sum = document.createElement("TD");
    row.appendChild(td_sum);

    let td_date = document.createElement("TD");
    row.appendChild(td_date);

    let td_fio = document.createElement("TD");
    row.appendChild(td_fio);

    let td_tit = document.createElement("TD");
    row.appendChild(td_tit);

    tbody.appendChild(row);

    td_sum.innerHTML = sum;
    td_date.innerHTML = date;
    td_fio.innerHTML = fio;
    td_tit.innerHTML = tit;

    tbody.appendChild(row);
}

function searсh_b()
{
    var inp = document.getElementsByName('searсh_rad');

    let tbody = document.getElementById("table_of_searсh").getElementsByTagName("TBODY")[0];
    while (tbody.rows.length > 0) { tbody.deleteRow(0); }

    if(inp[0].checked)
    {
        socket.emit('get_zakaz_by_sum', document.getElementById("sum_in").value);
    } else if (inp[1].checked)
    {
        socket.emit('get_zakaz_by_date', document.getElementById("date1_in").value, document.getElementById("date2_in").value);
    } else if (inp[2].checked)
    {
        socket.emit('get_zakaz_by_agent', (document.getElementById("fio_in").value));
    } else if (inp[3].checked) { socket.emit('get_zakaz_by_zakazchik', (document.getElementById("title_in").value)); }
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function (event)
{
    socket.emit('get_agent');
    socket.emit('get_zakazchic');
    document.getElementById('b_searсh').addEventListener('click', () => searсh_b());
});