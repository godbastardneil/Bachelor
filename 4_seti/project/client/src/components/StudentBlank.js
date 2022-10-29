import React, {useState, useEffect} from 'react';

import {observer} from "mobx-react-lite";

import {Spinner, Row, Col, Container} from "react-bootstrap";

import {BootstrapTable, 
            TableHeaderColumn} from 'react-bootstrap-table';

import '../../node_modules/react-bootstrap-table/css/react-bootstrap-table.css'

import {getStat} from "../http/studentAPI";


const StudentBlank = observer((student) => {
    let [user, setUser] = useState('');
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        console.log(student.email);
        getStat(student.email).then(data => {
            setUser(data);
            console.log(user);
        }).finally(() => setLoading(false))
    }, []);

    if (loading) {
        return <Spinner animation={"grow"}/>
    }

    return (
        <Container className="mt-3">
            <Row>
                <Col>
                    <h2>{user.email}</h2>
                </Col>
                <Col>
                    <Row className="d-flex flex-column align-items-center">
                        <div
                            className="d-flex align-items-center justify-content-center"
                            style={{background: `no-repeat center center`, backgroundSize: 'cover'}}
                        >
                            Количество тестов: {user.test_score}; <br></br>
                            Максимальный процент: {user.max_percent};<br></br>
                            Минимальный процент: {user.min_percent};<br></br>
                            Средний процент: {user.middle_percent};<br></br>
                        </div>
                    </Row>
                </Col>
            </Row>
            <Row className="d-flex flex-column m-3">
                <h4>Статисткика по тестам</h4>
                {
                    (user.test_score > 0) ?
                        <div>
                            <BootstrapTable data={user.test_lists}>
                                <TableHeaderColumn isKey dataField='id' thStyle={{fontWeight: 'bold', color: 'red'}}>
                                    ID
                                </TableHeaderColumn>
                                <TableHeaderColumn dataField='scores'>
                                    Scores
                                </TableHeaderColumn>
                                <TableHeaderColumn dataField='dates'>
                                    Dates
                                </TableHeaderColumn>
                                <TableHeaderColumn dataField='answers'>
                                    Answers
                                </TableHeaderColumn>
                            </BootstrapTable>
                        </div>
                    : 
                        <div>Вы не проходили тесты</div>
                }
            </Row>
        </Container>
    );
});

export default StudentBlank;