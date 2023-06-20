import React, {useContext} from 'react';
import {useLocation, useHistory} from "react-router-dom";

import {observer} from "mobx-react-lite";

import {Navbar, Nav, Button, Container} from "react-bootstrap";

import {Context} from "../index";
import {logout} from "../http/userAPI";

import {TEACHER_ROUTE,
        STUDENT_ROUTE,
        LOGIN_ROUTE,
        REGISTRATION_ROUTE,
        SETTINGS_ROUTE,
        TOPIC_ROUTE} from '../utils/consts';


const NavBar = observer(() => {
    let {user} = useContext(Context);
    const history = useHistory();
    const location = useLocation();

    console.log('NavBar: ' + user.email + ' ' + user.role);

    const isLogin = location.pathname === LOGIN_ROUTE;

    const logOut = () => {
        user.set(logout());

        if (isLogin)
        {
            history.push(REGISTRATION_ROUTE);
        } else { history.push(LOGIN_ROUTE); }
    }
  
    return (
        <Navbar bg="dark" variant="dark">
            <Container>
                {
                    (user.role == '' || user.role == undefined || user.role == null) ?
                        (isLogin) ?
                            <Nav className="ml-auto" style={{color: 'white'}}>
                                <Button variant={"outline-light"} onClick={() => logOut()}> Регистрация </Button>
                            </Nav>
                        :
                            <Nav className="ml-auto" style={{color: 'white'}}>
                                <Button variant={"outline-light"} onClick={() => logOut()}> Авторизация </Button>
                            </Nav>
                    :
                        <Nav className="ml-auto" style={{color: 'white'}}>
                            <Button variant={"outline-light"} onClick=
                                {() => history.push(
                                    (user.role === 'student') ?
                                        STUDENT_ROUTE
                                    :
                                        TEACHER_ROUTE
                                )}
                            >
                                Главная
                            </Button>
                            <Button variant={"outline-light"} onClick={() => history.push(SETTINGS_ROUTE)}> Настройки </Button>

                            <Button variant={"outline-light"} onClick={() => history.push(TOPIC_ROUTE)}> Темы </Button>
                            <Button variant={"outline-light"} onClick={() => logOut()} className="ml-2"> Выйти </Button>
                        </Nav>
                }
            </Container>
        </Navbar>
    );
});
  
  export default NavBar;