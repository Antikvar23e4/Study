import React from 'react'
import { SignUpEmailInput } from './SignUpEmailInput'
import { SignUpPasswordInput } from './SignUpPasswordInput'
import { PhoneInput } from './PhoneInput.js'

export class SignUpForm extends React.Component {
    state = {
        disableBtn: false,
    }
    disableBtn = (value) => {
        this.setState({disableBtn: value})
        return this.state.disableBtn
    }
    day() {
        let days = []
        for (let day = 1; day < 32; day++) {
            days.push(
                <option key={day}>{day}</option>
            )
        }
        return (
            <select>
                {days}
            </select>
        )
    }
    month() {
        let months = [
            "Январь",
            "Февраль",
            "Март",
            "Апрель",
            "Май",
            "Июнь",
            "Июль",
            "Август",
            "Сентябрь",
            "Октябрь",
            "Ноябрь",
            "Декабрь",
        ]
        return (
            <select>
                {months.map(month => {
                    return <option key={month}>{month}</option>
                })}
            </select>
        )
    }
    year() {
        let years = []
        for (let year = 1960; year < 2021; year++) {
            years.push(
                <option key={year}>{year}</option>
            )
        }
        return (
            <select>
                {years}
            </select>
        )
    }
    render() {
        return(
            <form>
                <SignUpEmailInput disableBtn={this.disableBtn} />
                <SignUpPasswordInput disableBtn={this.disableBtn} />
                <input type="text" placeholder="Фамилия" />
                <input type="text" placeholder="Имя" />
                <input type="text" placeholder="Отчество" />
                <input type="radio" name="gender" value="male" />муж
                <input type="radio" name="gender" value="female" />жен
                <div className="date">
                {this.day()}
                {this.month()}
                {this.year()}
                </div>
                <br />
                <PhoneInput />
                <br />
                <button disabled={this.state.disableBtn} onClick={this.handleBtnClick}>Отправить</button>
            </form>
        )
    }
}