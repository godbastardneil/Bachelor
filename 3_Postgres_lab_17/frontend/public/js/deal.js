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

async function open_buyers() {
    window.open(`/buyer`, "_self");
}
async function open_products() {
    window.open(`/product`, "_self");
}

async function get_search() {
    let id = document.getElementById("search_id").value;
    let date = document.getElementById("search_date").value;
    let idpr = document.getElementById("search_idpr").value;
    let kol = document.getElementById("search_kol").value;
    let idbuy = document.getElementById("search_idbuy").value;
    let isopt = document.getElementById("search_isopt").checked;

    socket.emit('get_deals_by_par', id, date, idpr, kol, idbuy, isopt);
}

// как только документ прогрузится вызвать эти функции
document.addEventListener("DOMContentLoaded", function(event) {

    socket.emit('get_deals');
    document.getElementById('open_buyers').addEventListener('click', () => open_buyers());
    document.getElementById('open_products').addEventListener('click', () => open_products());
    document.getElementById('search_button').addEventListener('click', () => get_search());
    document.getElementById('init_button').addEventListener('click', () => init_button());
});

async function init_button() {
    let tbody = document.getElementById("table_of_deal_info").getElementsByTagName("TBODY")[0];
    addDealRow(tbody, i, '', -1, 0, -1, false);
    --i;
}

socket.on('addDeals', (data) => {
    if (data != null) {
        let tbody = document.getElementById("table_of_deal_info").getElementsByTagName("TBODY")[0];
        while (tbody.firstChild) {
            tbody.removeChild(tbody.firstChild);
        }
        data.forEach(element =>
            addDealRow(tbody, element['idсделка'], element['дата_сделки'], element['idтовар'], element['кол'], element['idпокупатель'], element['признак_опт_прод'])
        );
    }
});
async function addDealRow(tbody, id, date, idpr, kol, idbuy, isopt) {
    let row = document.createElement("TR");
    row.id = `row_${id}`;

    let td_id = document.createElement("TD");
    row.appendChild(td_id);

    let td_date = document.createElement("TD");
    row.appendChild(td_date);

    let td_idpr = document.createElement("TD");
    row.appendChild(td_idpr);

    let td_kol = document.createElement("TD");
    row.appendChild(td_kol);

    let td_idbuy = document.createElement("TD");
    row.appendChild(td_idbuy);

    let td_isopt = document.createElement("TD");
    row.appendChild(td_isopt);

    let td_act = document.createElement("TD");
    row.appendChild(td_act);

    tbody.appendChild(row);

    td_id.innerHTML = `<input size="20" value="${id}" id="id_${id}" type="number"  readOnly=true>`;
    td_date.innerHTML = `<input size="20" value="${date}" id="date_${id}" type="date">`;
    td_idpr.innerHTML = `<input size="20" value="${idpr}" id="idpr_${id}" type="number">`;
    td_kol.innerHTML = `<input size="20" value="${kol}" id="kol_${id}" type="number">`;
    td_idbuy.innerHTML = `<input size="20" value="${idbuy}" id="idbuy_${id}" type="number">`;

    td_isopt.innerHTML = `<input size="20" id="isopt_${id}" type="checkbox">`;
    document.getElementById(`isopt_${id}`).checked = isopt;

    td_act.innerHTML = `<button type="button" class="button" id="save_${id}"> Сохранить </button> / <button type="button" class="button" id="remove_${id}"> Удалить </button>`;

    let but_ch = document.getElementById(`save_${id}`);
    but_ch.addEventListener('click', () => save(id));
    let but_del = document.getElementById(`remove_${id}`);
    but_del.addEventListener('click', () => remove(id));

}


socket.on('set_change_deal', (old_id, new_id) => {
    if (new_id == null) { new_id = old_id; }
    let row = document.getElementById(`row_${old_id}`);
    let id_ = document.getElementById(`id_${old_id}`);
    let date_ = document.getElementById(`date_${old_id}`);
    let idpr_ = document.getElementById(`idpr_${old_id}`);
    let kol_ = document.getElementById(`kol_${old_id}`);
    let idbuy_ = document.getElementById(`idbuy_${old_id}`);
    let isopt_ = document.getElementById(`isopt_${old_id}`);

    id_.value = new_id;

    row.id = `row_${new_id}`;
    id_.id = `id_${new_id}`;
    date_.id = `date_${new_id}`;
    idpr_.id = `idpr_${new_id}`;
    kol_.id = `kol_${new_id}`;
    idbuy_.id = `idbuy_${new_id}`;
    isopt_.id = `isopt_${new_id}`;

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
    let date_pole = document.getElementById(`date_${id}`);
    let idpr_pole = document.getElementById(`idpr_${id}`);
    let kol_pole = document.getElementById(`kol_${id}`);
    let idbuy_pole = document.getElementById(`idbuy_${id}`);
    let isopt_pole = document.getElementById(`isopt_${id}`);

    let date = date_pole.value;
    let idpr = idpr_pole.value;
    let kol = kol_pole.value;
    let idbuy = idbuy_pole.value;
    let isopt = isopt_pole.checked;

    if (date != null && idpr != null && kol != null && idbuy != null && isopt != null) {

        socket.emit('save_deal', id, date, idpr, kol, idbuy, isopt);
    } else {
        alert('Вы ставили пустые поля');
    }
}
async function remove(id) {
    if (confirm("Вы точно хотите удалить?")) {
        let row = document.getElementById(`row_${id}`);
        row.remove();

        socket.emit('remove_deal', id);
    }
}