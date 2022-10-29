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

var i = -1;

async function open_deals() {
    window.open(`/deal`, "_self");
}
async function open_products() {
    window.open(`/product`, "_self");
}

async function get_search() {
    let id = document.getElementById("search_id").value;
    let tel = document.getElementById("search_tel").value;
    let kont = document.getElementById("search_kont_lizo").value;
    let adr = document.getElementById("search_address").value;
    let opis = document.getElementById("search_opisanie").value;

    socket.emit('get_buyers_by_par', id, tel, kont, adr, opis);
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {

    socket.emit('get_buyers');
    document.getElementById('open_deals').addEventListener('click', () => open_deals());
    document.getElementById('open_products').addEventListener('click', () => open_products());
    document.getElementById('search_button').addEventListener('click', () => get_search());
    document.getElementById('init_button').addEventListener('click', () => init_button());
});

async function init_button() {
    let tbody = document.getElementById("table_of_buyer_info").getElementsByTagName("TBODY")[0];
    addBuyerRow(tbody, i, '', '', '', '');
    --i;
}

// добавляем строку со статистикой
socket.on('addBuyers', (data) => {
    if (data != null) {
        let tbody = document.getElementById("table_of_buyer_info").getElementsByTagName("TBODY")[0];
        while (tbody.firstChild) {
            tbody.removeChild(tbody.firstChild);
        }
        data.forEach(element =>
            addBuyerRow(tbody, element['idпокупатель'], element['телефон'], element['конт_лицо'], element['адрес'], element['описание'])
        );
    }
});
async function addBuyerRow(tbody, id, tel, kont, adr, opis) {
    let row = document.createElement("TR");
    row.id = `row_${id}`;

    let td_id = document.createElement("TD");
    row.appendChild(td_id);
    let td_tel = document.createElement("TD");
    row.appendChild(td_tel);
    let td_kont = document.createElement("TD");
    row.appendChild(td_kont);
    let td_adr = document.createElement("TD");
    row.appendChild(td_adr);
    let td_opis = document.createElement("TD");
    row.appendChild(td_opis);
    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    td_id.innerHTML = `<input size="20" value="${id}" id="id_${id}" type="number" readOnly=true>`;
    td_tel.innerHTML = `<input size="20" value="${tel}" id="tel_${id}">`;
    td_kont.innerHTML = `<input size="20" value="${kont}" id="kont_${id}">`;
    td_adr.innerHTML = `<input size="20" value="${adr}" id="adr_${id}">`;
    td_opis.innerHTML = `<input size="20" value="${opis}" id="opis_${id}">`;

    td_act.innerHTML = `<button type="button" class="button" id="save_${id}"> Сохранить </button> / <button type="button" class="button" id="remove_${id}"> Удалить </button>`;

    let but_ch = document.getElementById(`save_${id}`);
    but_ch.addEventListener('click', () => save(id));
    let but_del = document.getElementById(`remove_${id}`);
    but_del.addEventListener('click', () => remove(id));

}

socket.on('set_change_buyer', (old_id, new_id) => {
    if (new_id == null) { new_id = old_id; }
    let row = document.getElementById(`row_${old_id}`);
    let id_ = document.getElementById(`id_${old_id}`);
    let tel_ = document.getElementById(`tel_${old_id}`);
    let kont_ = document.getElementById(`kont_${old_id}`);
    let adr_ = document.getElementById(`adr_${old_id}`);
    let opis_ = document.getElementById(`opis_${old_id}`);

    id_.value = new_id;

    row.id = `row_${new_id}`;
    id_.id = `id_${new_id}`;
    tel_.id = `tel_${new_id}`;
    kont_.id = `kont_${new_id}`;
    adr_.id = `adr_${new_id}`;
    opis_.id = `opis_${new_id}`;

    let but_ch = document.getElementById(`save_${old_id}`);
    but_ch.removeEventListener('click', () => save(old_id));
    let but_del = document.getElementById(`remove_${old_id}`);
    but_del.removeEventListener('click', () => remove(old_id));

    but_ch.id = (`save_${new_id}`);
    but_ch.addEventListener('click', () => save(new_id));

    but_del.id = (`remove_${new_id}`);
    but_del.addEventListener('click', () => remove(new_id));
});

async function save(id) {
    let pole_tel = document.getElementById(`tel_${id}`);
    let pole_kont = document.getElementById(`kont_${id}`);
    let pole_adr = document.getElementById(`adr_${id}`);
    let pole_opis = document.getElementById(`opis_${id}`);

    let tel = pole_tel.value;
    let kont = pole_kont.value;
    let adr = pole_adr.value;
    let opis = pole_opis.value;

    if (tel != null && kont != null && adr != null && opis != null) {

        socket.emit('save_buyer', id, tel, kont, adr, opis);
    } else {
        alert('Вы ставили пустые поля');
    }
}

async function remove(id) {
    if (confirm("Вы точно хотите удалить?")) {
        let row = document.getElementById(`row_${id}`);
        row.remove();

        socket.emit('remove_buyer', id);
    }
}