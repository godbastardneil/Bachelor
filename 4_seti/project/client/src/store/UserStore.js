import {makeAutoObservable} from 'mobx';

export default class UserStore {
    constructor() {
        this._role = '';
        this._email = '';
        makeAutoObservable(this);
    }

    setRole(role) {
        this._role = role;
    }
    setEmail(email) {
        this._email = email;
    }
    set(data) {
        this._email = data.email;
        this._role = data.role;
    }

    get role() {
        return this._role;
    }
    get email() {
        return this._email;
    }
}