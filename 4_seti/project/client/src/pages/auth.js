import React, {useContext, useState} from 'react';
import {NavLink, useLocation, useHistory} from "react-router-dom";

import {observer} from "mobx-react-lite";

import {Container, Form, Card, Button, Row} from "react-bootstrap";

import {Context} from "../index";

import {LOGIN_ROUTE,
        REGISTRATION_ROUTE,
        STUDENT_ROUTE,
        TEACHER_ROUTE} from "../utils/consts";
import {login, registration} from "../http/userAPI";


const Auth = observer(() => {
    let {user} = useContext(Context);
    const location = useLocation();
    const history = useHistory();

    const isLogin = location.pathname === LOGIN_ROUTE;

    const [role, setRole] = useState('');
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');

    const click = async () => {
        console.log('0');
        try {
            let data;
            console.log(role);
            if (isLogin) {
                data = await login(email, password, role);
            } else {
                data = await registration(email, password, role);
            }
            console.log('3');
            console.log(data);

            user.setRole(data.role);
            user.setEmail(data.email);
            
            console.log('Auth: ' + user.email + ' ' + user.role);
            if (role === 'student') {
                history.push(STUDENT_ROUTE);
            } else { history.push(TEACHER_ROUTE); }
            console.log('4');
        } catch (e) {
            console.log(e.message);
            alert(e.message);
        }

    }

    return (
        <Container
            className="d-flex justify-content-center align-items-center"
            style={{height: window.innerHeight - 54}}
        >
            <Card style={{width: 600}} className="p-5">
                <h2 className="m-auto">{isLogin ? 'Авторизация' : "Регистрация"}</h2>
                <Form className="d-flex flex-column">
                    <Form.Control
                        className="mt-3"
                        placeholder="Введите ваш email..."
                        value={email}
                        onChange={e => {setEmail(e.target.value); setRole('student');}}
                    />
                    <Form.Control
                        className="mt-3"
                        placeholder="Введите ваш пароль..."
                        value={password}
                        onChange={e => setPassword(e.target.value)}
                        type="password"
                    />

                    <Form.Control
                        className="mt-3"
                        placeholder="Преподаватель"
                        value='teacher'
                        onChange={e => setRole(e.target.value)}
                        type="radio"
                    />
                    <Form.Control
                        className="mt-3"
                        placeholder="Студент"
                        value='student'
                        onChange={e => setRole(e.target.value)}
                        type="radio"
                    />

                    <Row className="d-flex justify-content-between mt-3 pl-3 pr-3">
                        {isLogin ?
                            <div>
                                Нет аккаунта? <NavLink to={REGISTRATION_ROUTE}>Зарегистрируйся!</NavLink>
                            </div>
                            :
                            <div>
                                Есть аккаунт? <NavLink to={LOGIN_ROUTE}>Войдите!</NavLink>
                            </div>
                        }

                        <Button variant={"outline-success"} onClick={click}>
                            {isLogin ? 'Войти' : 'Регистрация'}
                        </Button>
                    </Row>

                </Form>
            </Card>
        </Container>
    );
});

export default Auth;