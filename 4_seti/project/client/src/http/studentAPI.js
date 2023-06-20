import {$authHost} from "./index";

export const getStat = async (user) => {
    const {data} = await $authHost.get('api/student', {user});
    return data;
}