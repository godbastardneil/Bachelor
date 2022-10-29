import React, {useState, useEffect} from 'react';
import {useParams, useHistory} from 'react-router-dom'

import {observer} from "mobx-react-lite";

import {Spinner, Container, Form, Button, Row} from "react-bootstrap";

import {getTest, setTest} from "../http/testAPI";
import { STUDENT_ROUTE } from '../utils/consts';

const Test = observer(() => {
    let map = new Map();
    const history = useHistory();
    const id = useParams().id;
    const [test, _setTest] = useState('');
    const [loading, setLoading] = useState(true);

    const click = () => {
        for (let into of test) {
            if (!map.has(into.taskId)) { map.set(into.taskId, "null"); }
        }
        console.log(map);
        
        setTest(map, id);
        history.push(STUDENT_ROUTE);
    }

    useEffect(() => {
        getTest(id).then(data => {
            console.log(data);
            _setTest(data);
        }).finally(() => setLoading(false))
    }, []);

    if (loading) {
        return <Spinner animation={"grow"}/>
    }

    return (
        <Container className="mt-3">
            <Row>
                <h2>Тест № {test[0].testId}</h2>
            </Row>
            <Row className="d-flex flex-column m-3">
                {test.map((info, index) =>
                    // это в TestTask
                    <Row key={info.id} style={{background: index % 2 === 0 ? 'lightgray' : 'transparent', padding: 10}}>

                        <h4>Задание № {info.taskId}</h4>
                        <div className="content" dangerouslySetInnerHTML={{__html: info.task.text}}></div>

                        <Form.Control
                            className="mt-3"
                            value={map.get(info.taskId)}
                            id={`ex_${info.taskId}`}
                            onChange={e => {
                                map.set(info.taskId, e.target.value);
                            }}
                        />
                    </Row>
                )}
                <Button variant={"outline-success"} onClick={click}>
                    {'Завершить'}
                </Button>
            </Row>
        </Container>
    );
});

export default Test;