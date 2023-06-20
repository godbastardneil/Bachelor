import React, {useState, useEffect} from 'react';
import {useHistory} from "react-router-dom";

import {observer} from "mobx-react-lite";

import {Spinner, Container, Form, ListGroup, Button, Row} from "react-bootstrap";

import {fetchTopic, createTest} from "../http/topicAPI";
import {TEST_ROUTE} from "../utils/consts";

const Topic = observer(() => {
    let map = new Map();
    const history = useHistory();
    const [topic, setTopic] = useState('');
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        fetchTopic().then(data => {
            setTopic(data);
        }).finally(() => setLoading(false));
    }, []);

    if (loading) {
        return <Spinner animation={"grow"}/>
    }

    const click = () => {
        try {
            let kol = 0;
            let can_do = true;
            for (let val of map.values()) {
                if (val === "" || val === 0) { val = 0; can_do = false; }
                kol += Number(val);
            }
            if (can_do)
            {
                createTest(map, kol, topic).then(data => {
                    console.log(data);
                    history.push(TEST_ROUTE + '/' + data.create_new_test);
                });
            }
        } catch (e) {
            alert(e.message);
        }

    }

    return (
        <Container className="mt-3">
            <Row>
                <h2>ЗАДАНИЯ</h2>
            </Row>
            <Row className="d-flex flex-column m-3">
                <ListGroup>
                    {topic.map((top, index) =>
                        <ListGroup.Item
                        style={{cursor: 'pointer'}}
                        key={top.id}>
                            {top.title}

                            {top.task_types.map(type =>
                                <ListGroup.Item
                                style={{cursor: 'pointer'}}
                                key={type.id}>
                                    {type.title}
                                    <Form.Control
                                        className="mt-3"
                                        value={map.get(type.id)}
                                        id={`type_${type.id}`}
                                        onChange={e => {
                                            map.set(type.id, e.target.value);
                                        }}
                                        type="number"
                                    />
        
                                </ListGroup.Item>
                            )}
                        </ListGroup.Item>
                    )}
                </ListGroup>
                <Button variant={"outline-success"} onClick={click}>
                    {'Начать'}
                </Button>
            </Row>
        </Container>
    );
});

export default Topic;