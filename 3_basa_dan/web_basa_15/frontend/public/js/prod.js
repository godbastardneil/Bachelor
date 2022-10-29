
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


async function open_cust()
{
    window.open(`/cust`, "_self");
}
async function open_deal()
{
    window.open(`/deal`, "_self");
}


socket.on('addSearсh', (data) => {
    addRow_searсh(data['idProduct'], data['title'], data['opt_price'], data['roz_price']);
});

socket.on('addProduct', (data) => {
	addRow_product(data['idProduct'], data['title'], data['opt_price'], data['roz_price']);
});

async function set_new_val()
{
    change = true;
    let row = document.getElementById(idd);

    let t = row.cells[0].innerHTML;
    let o = row.cells[1].innerHTML;
    let r = row.cells[2].innerHTML;

    document.getElementById("title_in").value = t;
    document.getElementById("opt_in").value = o;
    document.getElementById("roz_in").value = r;
}

function addRow(tbody, row, id, title, opt_price, roz_price)
{
    row.id = id;

    let td_title = document.createElement("TD");
    row.appendChild(td_title);

    let td_opt_price = document.createElement("TD");
    row.appendChild(td_opt_price);

    let td_roz_price = document.createElement("TD");
    row.appendChild(td_roz_price);

    tbody.appendChild(row);

    td_title.innerHTML = title;
    td_opt_price.innerHTML = opt_price;
    td_roz_price.innerHTML = roz_price;
}
function addRow_searсh(id, title, opt_price, roz_price)
{
    let tbody = document.getElementById("table_of_searсh").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    addRow(tbody, row, id, title, opt_price, roz_price);
    tbody.appendChild(row);
}
function addRow_product(id, title, opt_price, roz_price)
{
	let tbody = document.getElementById("table_of_product").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    addRow(tbody, row, id, title, opt_price, roz_price);
    row.addEventListener("click", function(e){ idd = row.id; set_new_val(); });
    tbody.appendChild(row);
}

async function get_product_info()
{
    let tbody = document.getElementById("table_of_product").getElementsByTagName("TBODY")[0];
    while (tbody.rows.length > 0) { tbody.deleteRow(0); }
    socket.emit('get_products');
}


function include_b()
{
    let t = document.getElementById("title_in").value;
    let o = document.getElementById("opt_in").value;
    let r = document.getElementById("roz_in").value;

    if (t && o && t)
    {
        if (change)
        { // функция обновления
            socket.emit('up_product', idd, t, o, r);
        } else
        { // функция добавления
            socket.emit('init_product', t, o, r);
        }
        get_product_info();
        change = false;
    } else if (!t && !o && !r && change)
    { // удаление
        socket.emit('del_product', idd);
        get_product_info();
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
        socket.emit('get_products_by_title', document.getElementById("searсh_in").value);
    } else if (inp[1].checked)
    {
        socket.emit('get_products_by_opt', (document.getElementById("searсh_in").value));
    } else if (inp[2].checked) { socket.emit('get_products_by_roz', (document.getElementById("searсh_in").value)); }
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function (event)
{
	get_product_info();
    document.getElementById('b_include').addEventListener('click', () => include_b());
    document.getElementById('b_searсh').addEventListener('click', () => searсh_b());
    document.getElementById('b_client').addEventListener('click', () => open_cust());
    document.getElementById('b_deal').addEventListener('click', () => open_deal());
});