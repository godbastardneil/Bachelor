import {$authHost} from "./index";

export const getStudents = async (email) => {
    const {data} = await $authHost.post('api/teacher', {email});
    return data;
}