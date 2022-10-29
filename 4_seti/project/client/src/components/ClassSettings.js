import React, {useContext} from 'react';
import Container from "react-bootstrap/Container";

import {observer} from "mobx-react-lite";

import {Context} from "../index";

const ClassSettings = observer(() => {
    const {user} = useContext(Context);

    console.log(user);

    return (
        <Container className="mt-3">

        </Container>
    );
});

export default ClassSettings;