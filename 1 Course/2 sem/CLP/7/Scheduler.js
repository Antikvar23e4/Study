import React from 'react'
import Calendar from "./Calendar.js"
import {Notes} from "./Notes.js"

export class Scheduler extends React.Component {
    render() {
        return (
            <Calendar Component={Notes}/>
        )
    }
}

