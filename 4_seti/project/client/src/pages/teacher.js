import React, {useContext, useState, useEffect} from 'react';

import {observer} from "mobx-react-lite";

import {Spinner, Row} from "react-bootstrap";

import {Context} from "../index";

import StudentBlank from "../components/StudentBlank";
import {getStudents} from "../http/teacherAPI";

const Teacher = observer(() => {
    const {user} = useContext(Context);
    const [students, setStudents] = useState('');
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        getStudents(user.email).then(data => {
            setStudents(data);
            console.log(students);
        }).finally(() => setLoading(false))
    }, []);

    if (loading) {
        return <Spinner animation={"grow"}/>
    }

    return (
        students.map(student =>
            <Row className="d-flex">
                <StudentBlank key={student.email} student={student}/>
            </Row>
        )
    );
});

export default Teacher;