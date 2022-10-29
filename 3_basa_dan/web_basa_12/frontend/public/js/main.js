
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
let product = new Map();
let customer = new Map();

let change = false;
let idd = -1;


async function open_cust()
{
    window.open(`/cust`, "_self");
}
async function open_prod()
{
    window.open(`/prod`, "_self");
}

socket.on('addProduct', (data) => {
    let s = document.getElementById("title_in");

    product.set(data['title'], data['idProduct']);

    s.innerHTML += `<option value="${data['idProduct']}">${data['title']} - ${data['opt_price']}, ${data['roz_price']}</option>`;
});
socket.on('addCustomer', (data) => {
    let s = document.getElementById("fio_in");

    customer.set(data['name'], data['idCustomer']);

    s.innerHTML += `<option value="${data['idCustomer']}">${data['name']}</option>`;
});

socket.on('addSearсh', (data) => {
    let price;
    if (data['isOpt'])
    {
        price = data['opt_price'];
    } else { price = data['roz_price']; }
    addRow_searсh(data['idDeal'], data['date'], data['name'], data['title'], price, data['kolvo'], data['isOpt']);
});

socket.on('addDeal', (data) => {
    let price;
    if (data['isOpt'])
    {
        price = data['opt_price'];
    } else { price = data['roz_price']; }
	addRow_deal(data['idDeal'], data['date'], data['name'], data['title'], price, data['kolvo'], data['isOpt']);
});

async function set_new_val()
{
    change = true;
    let row = document.getElementById(idd);

    let d = row.cells[0].innerHTML;
    let f = row.cells[1].innerHTML;
    let t = row.cells[2].innerHTML;
    let k = row.cells[4].innerHTML;
    let i = row.cells[5].innerHTML;

        let f_s = document.getElementById("fio_in");
        f_s.value = customer.get(f);

        let t_s = document.getElementById("title_in");
        t_s.value = product.get(t);

    document.getElementById("date_in").value = d;
    document.getElementById("kol_in").value = k;

    if(i == 1)
    {
        document.getElementById("isOpt_in").checked = true;
    } else { document.getElementById("isOpt_in").checked = false; }
}

function addRow(tbody, row, id, data, fio, title, price, kol, isOpt)
{
    row.id = id;

    let td_data = document.createElement("TD");
    row.appendChild(td_data);

    let td_fio = document.createElement("TD");
    row.appendChild(td_fio);

    let td_title = document.createElement("TD");
    row.appendChild(td_title);

    let td_price = document.createElement("TD");
    row.appendChild(td_price);

    let td_kol = document.createElement("TD");
    row.appendChild(td_kol);

    let td_isOpt = document.createElement("TD");
    row.appendChild(td_isOpt);

    tbody.appendChild(row);

    td_data.innerHTML = data;
    td_fio.innerHTML = fio;
    td_title.innerHTML = title;
    td_price.innerHTML = price;
    td_kol.innerHTML = kol;
    td_isOpt.innerHTML = isOpt;
}
function addRow_searсh(id, data, fio, title, price, kol, isOpt)
{
    let tbody = document.getElementById("table_of_searсh").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    addRow(tbody, row, id, data, fio, title, price, kol, isOpt);
    tbody.appendChild(row);
}
function addRow_deal(id, data, fio, title, price, kol, isOpt)
{
	let tbody = document.getElementById("table_of_deals").getElementsByTagName("TBODY")[0];
    let row = document.createElement("TR");

    addRow(tbody, row, id, data, fio, title, price, kol, isOpt);
    row.addEventListener("click", function(e){ idd = row.id; set_new_val(); });
    tbody.appendChild(row);
}

async function get_deal_info()
{
    let tbody = document.getElementById("table_of_deals").getElementsByTagName("TBODY")[0];
    while (tbody.rows.length > 0) { tbody.deleteRow(0); }
    socket.emit('get_deals');
}


function include_b()
{
    let d = document.getElementById("date_in").value;
    let f = document.getElementById("fio_in").value;
    let t = document.getElementById("title_in").value;
    let k = document.getElementById("kol_in").value;
    let i_t = document.getElementById("isOpt_in").checked;
    let i;
    if (i_t)
    {
        i = 1;
    } else { i = 0; }

    if (d && f && t && k)
    {
        alert(`${(d)}, ${(f)}, ${(t)}, ${(k)}`);
        if (change)
        { // функция обновления
            socket.emit('up_deal', idd, d, f, t, k, i);
        } else
        { // функция добавления
            socket.emit('init_deal', d, f, t, k, i);
        }
        get_deal_info();
        change = false;
    } else if (!f && !t && !k && change)
    { // удаление
        socket.emit('del_deal', idd);
        get_deal_info();
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
        socket.emit('get_deals_by_date', document.getElementById("searсh_in").value);
    } else if (inp[1].checked)
    {
        socket.emit('get_deals_by_fio', customer.get(document.getElementById("searсh_in").value));
    } else if (inp[2].checked) { socket.emit('get_deals_by_tit', product.get(document.getElementById("searсh_in").value)); }
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function (event)
{
    socket.emit('get_customer_for_deal');
    socket.emit('get_product_for_deal');
	get_deal_info();
    document.getElementById('b_include').addEventListener('click', () => include_b());
    document.getElementById('b_searсh').addEventListener('click', () => searсh_b());
    document.getElementById('b_client').addEventListener('click', () => open_cust());
    document.getElementById('b_product').addEventListener('click', () => open_prod());
});