module.exports = class mutex
{
    constructor()
    {
        // ключ имя - значение ID
        this.name_id = new Map();
        // ключ ID - значение имя
        this.id_name = new Map();
    }

    add(name, id)
    {
        this.name_id.set(name, id);
        this.id_name.set(id, name);
    }

    delete_by_name(name)
    {
        let id = this.name_id.get(name);
        this.name_id.delete(name, id);
        this.id_name.delete(id, name);
    }

    delete_by_id(id)
    {
        let name = this.id_name.get(id);
        this.name_id.delete(name, id);
        this.id_name.delete(id, name);
    }

    is_busy_by_name(name)
    {
        return this.name_id.has(name);
    }

    is_busy_by_id(id)
    {
        return this.id_name.has(id);
    }

    reset() {
        this.name_id.clear();
        this.id_name.clear();
    }
}