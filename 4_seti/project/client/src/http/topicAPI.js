import {$host, $authHost} from "./index";
import jwt_decode from "jwt-decode";

export const fetchTopic = async () => {
    const {data} = await $host.get('api/topic');
    return data;
}

export const createTest = async (map, kol, topic) => {
    let email = jwt_decode(localStorage.getItem('token')).email;
    console.log(map);
    console.log(topic);
    const {data} = await $authHost.post('api/topic',{
        email,
        map: JSON.stringify(Array.from(map.entries()), null, 2),
        kol,
        topic: JSON.stringify(topic, null, 2)
    });
    console.log(data);
    return data;
}
