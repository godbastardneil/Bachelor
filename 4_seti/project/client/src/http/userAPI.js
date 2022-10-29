import {$authHost, $host} from "./index";
import jwt_decode from "jwt-decode";

export const registration = async (email, password, role) => {
    const {data} = await $host.post('api/user/registration', {email, password, role});
    localStorage.setItem('token', data.token);
    console.log('registration: ' + jwt_decode(data.token).email
                            + ' ' + jwt_decode(data.token).role);
    return jwt_decode(data.token);
}

export const login = async (email, password, role) => {
    const {data} = await $host.post('api/user/login', {email, password, role});
    localStorage.setItem('token', data.token);
    console.log('login: ' + jwt_decode(data.token).email
                    + ' ' + jwt_decode(data.token).role);
    return jwt_decode(data.token);
}

export const check = async () => {
    const {data} = await $authHost.get('api/user/auth');
    localStorage.setItem('token', data.token);
    console.log('check: ' + jwt_decode(data.token).email
                    + ' ' + jwt_decode(data.token).role);
    return jwt_decode(data.token);
}

export const logout = async () =>  {
    localStorage.removeItem('token');
    console.log('logout');
    return {email: '', rule: ''};
}