import {$authHost} from "./index";
import jwt_decode from "jwt-decode";

export const getTest = async (id) => {
    console.log(id);
    const {data} = await $authHost.get('api/test/' + id);
    console.log(data);
    return data;
}

export const setTest = async (map, id) => {
    let user = jwt_decode(localStorage.getItem('token'));
    await $authHost.post('api/test', {
        email: user.email,
        map: JSON.stringify(Array.from(map.entries()), null, 2),
        id
    });
}