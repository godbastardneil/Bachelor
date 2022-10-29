
import React, {useContext} from 'react';

import {observer} from "mobx-react-lite";

import {Container, Row} from "react-bootstrap";

import {Context} from "../index";

import StudentBlank from "../components/StudentBlank";

const Student = observer(() => {
    const {user} = useContext(Context);
    console.log('Student: ' + user.email + ' ' + user.role);

    return (
        <Container className="mt-3">
            <Row>
            {
                <Row className="d-flex">
                    <StudentBlank key={user.email} student={user}/>
                </Row>
            }
            </Row>
        </Container>
    );
});

export default Student;