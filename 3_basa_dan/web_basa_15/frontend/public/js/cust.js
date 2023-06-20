
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

let change = false;
let idd = -1;


async function open_prod()
{
    window.open(`/prod`, "_self");
}
async function open_deal()
{
    window.open(`/deal`, "_self");
}


socket.on('addSearсh', (data) => {
    addRow_searсh(data['idCustomer'], data['name'], data['phone'], data['address']);
});

socket.on('addCustomers', (data) => {
	addRow_customer(data['idCustomer'], data['name'], data['phone'], data['address']);
});

async function set_new_val()
{
    change = true;
    let row = document.getElementById(idd);

    let n = row.cells[0].innerHTML;
    let p = row.cells[1].innerHTML;
    let a = row.cells[2].innerHTML;

    document.getElementById("fio_in").value = n;
    document.getElementById("phone_in").value = p;
    document.getElementById("addr_in").value = a;
}

function addRow(tbody, row, id, name, phone, address)
{
    row.id = id;

    let td_fio = document.createElement("TD");
    row.appendChild(td_fio);

    let td_phone = document.createElement("TD");
    row.appendChild(td_phone);

    let td_address = document.createElement("TD");
    row.appendChild(td_address);

    tbody.appendChild(row);

    td_fio.innerHTML = name;
    td_phone.innerHTML = phone;
    td_address.innerHTML = address;
}
function addRow_searсh(id, name, phone, address)
{
    let tbody = document.getElementById("table_of_searсh").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    addRow(tbody, row, id, name, phone, address);
    tbody.appendChild(row);
}
function addRow_customer(id, name, phone, address)
{
	let tbody = document.getElementById("table_of_customer").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    addRow(tbody, row, id, name, phone, address);
    row.addEventListener("click", function(e){ idd = row.id; set_new_val(); });
    tbody.appendChild(row);
}

async function get_customer_info()
{
    let tbody = document.getElementById("table_of_customer").getElementsByTagName("TBODY")[0];
    while (tbody.rows.length > 0) { tbody.deleteRow(0); }
    socket.emit('get_customers');
}


function include_b()
{
    let n = document.getElementById("fio_in").value;
    let p = document.getElementById("phone_in").value;
    let a = document.getElementById("addr_in").value;

    if (n && p && a)
    {
        if (change)
        { // функция обновления
            socket.emit('up_customer', idd, n, p, a);
        } else
        { // функция добавления
            socket.emit('init_customer', n, p, a);
        }
        get_customer_info();
        change = false;
    } else if (!n && !p && !a && change)
    { // удаление
        socket.emit('del_customer', idd);
        get_customer_info();
        change = false;
    } else { alert(`Вы ввели не все значения`); }
}


function searсh_b()
{
    var inp = document.getElementsByName('searсh_rad');

    let tbody = document.getElementById("table_of_searсh").getElementsByTagName("TBODY")[0];
    while (tbody.rows.length > 0) { tbody.deleteRow(0); }

    if (inp[0].checked)
    {
        socket.emit('get_customers_by_name', document.getElementById("searсh_in").value);
    } else if (inp[1].checked)
    {
        socket.emit('get_customers_by_phone', (document.getElementById("searсh_in").value));
    } else if (inp[2].checked) { socket.emit('get_customers_by_address', (document.getElementById("searсh_in").value)); }
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function (event)
{
	get_customer_info();
    document.getElementById('b_include').addEventListener('click', () => include_b());
    document.getElementById('b_searсh').addEventListener('click', () => searсh_b());
    document.getElementById('b_product').addEventListener('click', () => open_prod());
    document.getElementById('b_deal').addEventListener('click', () => open_deal());
});