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
async function open_buyers() {
    window.open(`/buyer`, "_self");
}

async function get_search() {
    let id = document.getElementById("search_id").value;
    let name = document.getElementById("search_name").value;
    let opt = document.getElementById("search_opt").value;
    let roz = document.getElementById("search_roz").value;
    let opis = document.getElementById("search_opisanie").value;

    socket.emit('get_products_by_par', id, name, opt, roz, opis);
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {

    socket.emit('get_products');
    document.getElementById('open_deals').addEventListener('click', () => open_deals());
    document.getElementById('open_buyers').addEventListener('click', () => open_buyers());
    document.getElementById('search_button').addEventListener('click', () => get_search());
    document.getElementById('init_button').addEventListener('click', () => init_button());
});

async function init_button() {
    let tbody = document.getElementById("table_of_product_info").getElementsByTagName("TBODY")[0];
    addProductRow(tbody, i, '', 0, 0, '');
    --i;
}
// добавляем строку со статистикой
socket.on('addProducts', (data) => {
    if (data != null) {
        let tbody = document.getElementById("table_of_product_info").getElementsByTagName("TBODY")[0];
        while (tbody.firstChild) {
            tbody.removeChild(tbody.firstChild);
        }
        data.forEach(element =>
            addProductRow(tbody, element['idтовар'], element['наименование'], element['опт_цена'], element['роз_цена'], element['описание'])
        );
    }
});
async function addProductRow(tbody, id, name, opt, roz, opis) {
    let row = document.createElement("TR");
    row.id = `row_${id}`;

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_name = document.createElement("TD");
    row.appendChild(td_name);

    let td_opt = document.createElement("TD");
    row.appendChild(td_opt);

    let td_roz = document.createElement("TD");
    row.appendChild(td_roz);

    let td_opis = document.createElement("TD");
    row.appendChild(td_opis);

    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    td_id.innerHTML = `<input size="20" value="${id}" id="id_${id}" type="number" readOnly=true>`;
    td_name.innerHTML = `<input size="20" value="${name}" id="name_${id}">`;
    td_opt.innerHTML = `<input size="20" value="${opt}" id="opt_${id}" type="number">`;
    td_roz.innerHTML = `<input size="20" value="${roz}" id="roz_${id}" type="number">`;
    td_opis.innerHTML = `<input size="20" value="${opis}" id="opis_${id}">`;

    td_act.innerHTML = `<button type="button" class="button" id="save_${id}"> Сохранить </button> / <button type="button" class="button" id="remove_${id}"> Удалить </button>`;

    let but_ch = document.getElementById(`save_${id}`);
    but_ch.addEventListener('click', () => save(id));
    let but_del = document.getElementById(`remove_${id}`);
    but_del.addEventListener('click', () => remove(id));

}


socket.on('set_change_product', (old_id, new_id) => {
    if (new_id == null) { new_id = old_id; }
    let row = document.getElementById(`row_${old_id}`);
    let id_ = document.getElementById(`id_${old_id}`);
    let name_ = document.getElementById(`name_${old_id}`);
    let opt_ = document.getElementById(`opt_${old_id}`);
    let roz_ = document.getElementById(`roz_${old_id}`);
    let opis_ = document.getElementById(`opis_${old_id}`);

    id_.value = new_id;

    row.id = `row_${new_id}`;
    id_.id = `id_${new_id}`;
    name_.id = `tel_${new_id}`;
    opt_.id = `kont_${new_id}`;
    roz_.id = `adr_${new_id}`;
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
    let pole_name = document.getElementById(`name_${id}`);
    let pole_opt = document.getElementById(`opt_${id}`);
    let pole_roz = document.getElementById(`roz_${id}`);
    let pole_opis = document.getElementById(`opis_${id}`);

    let name = pole_name.value;
    let opt = pole_opt.value;
    let roz = pole_roz.value;
    let opis = pole_opis.value;

    if (name != null && opt != null && roz != null && opis != null) {

        socket.emit('save_product', id, name, opt, roz, opis);
    } else {
        alert('Вы ставили пустые поля');
    }
}
async function remove(id) {
    if (confirm("Вы точно хотите удалить?")) {
        let row = document.getElementById(`row_${id}`);
        row.remove();

        socket.emit('remove_product', id);
    }
}