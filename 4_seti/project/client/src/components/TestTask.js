import React, {useContext} from 'react';

import {observer} from "mobx-react-lite";

import Container from "react-bootstrap/Container";

import {Context} from "../index";

const TestTask = observer(() => {
    const {user} = useContext(Context);

    console.log(user);

    return (
        <Container className="mt-3">

        </Container>
    );
});

export default TestTask;