import React, {useContext} from 'react';
import {Switch, Route, Redirect} from 'react-router-dom'

import {observer} from "mobx-react-lite";

import {Context} from "../index";

import {teacherRouter,
        studentRouter,
        publicRouter} from '../routes';
import {LOGIN_ROUTE} from '../utils/consts';

const AppRouter = observer(() => {
    const {user} = useContext(Context);

    console.log('AppRouter: ' + user.email + ' ' + user.role);

    return (
        <Switch>
            {console.log('render: ' + user.email + ' ' + user.role)};
            {user.role === 'teacher' && teacherRouter.map(({path, Component}) =>
                <Route key={path} path={path} component={Component} exact/>
            )};
            {user.role === 'student' && studentRouter.map(({path, Component}) =>
                <Route key={path} path={path} component={Component} exact/>
            )};
            {publicRouter.map(({path, Component}) =>
                <Route key={path} path={path} component={Component} exact/>
            )};
            <Redirect to={LOGIN_ROUTE}/>
        </Switch>
    );
});

export default AppRouter;