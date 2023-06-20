import { TEACHER_ROUTE,
    STUDENT_ROUTE,
    SETTINGS_ROUTE,
    LOGIN_ROUTE,
    REGISTRATION_ROUTE,
    TOPIC_ROUTE,
    TEST_ROUTE } from "./utils/consts";

import Teacher from "./pages/teacher";
import Student from "./pages/student";
import Settings from "./pages/settings";
import Auth from "./pages/auth";
import Topic from "./pages/topic";
import Test from "./pages/test";

export const teacherRouter = [
{
   path: TEACHER_ROUTE,
   Component: Teacher
},
{
   path: TOPIC_ROUTE,
   Component: Topic
},
{
   path: SETTINGS_ROUTE,
   Component: Settings
}
]
export const studentRouter = [
{
   path: STUDENT_ROUTE,
   Component: Student
},
{
   path: TOPIC_ROUTE,
   Component: Topic
},
{
   path: SETTINGS_ROUTE,
   Component: Settings
},
{
   path: TEST_ROUTE + '/:id',
   Component: Test
}
]

export const publicRouter = [
{
   path: LOGIN_ROUTE,
   Component: Auth
},
{
   path: REGISTRATION_ROUTE,
   Component: Auth
}
]