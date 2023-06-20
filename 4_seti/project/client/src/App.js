import React, {useContext, useEffect, useState} from 'react';
import {BrowserRouter} from 'react-router-dom';

import {observer} from "mobx-react-lite";

import {Spinner} from "react-bootstrap";

import {Context} from "./index";
import {check} from "./http/userAPI";

import AppRouter from './components/AppRouter';
import NavBar from './components/NavBar';

const App = observer(() => {
  let {user} = useContext(Context);
  const [loading, setLoading] = useState(true);

  console.log('App 1: ' + user.email + ' ' + user.role);

  useEffect(() => {
    check().then(data => {
        user.setRole(data.role);
        user.setEmail(data.email);

        console.log('App 2 - data: ' + data.email + ' ' + data.role);
        console.log('App 2 - user: ' + user.email + ' ' + user.role);
    }).finally(() => setLoading(false));
  }, []);

  if (loading) {
    return <Spinner animation={"grow"}/>
  }

  return (
    <BrowserRouter>
      <NavBar />
      <AppRouter />
    </BrowserRouter>
  );
});

export default App;
