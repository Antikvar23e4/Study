import React from "react";

export class Calendar extends React.Component {
  constructor(props) {
    super(props);
    this.state = { date: new Date(), selectedDays: [] };
  }
 
  changeDate = (value) => { //устанавливаем новую дату в состояние компонента. 
    this.setState({ date: value });
  };
 
  selectDays = (day) => {// добавляем/удаляем выбранный день из массива выбранных дней в зависимости от того, был ли он уже выбран. 
    for (let i = 0; i < this.state.selectedDays.length; i++) {
      if (
        day.getDate() === this.state.selectedDays[i].getDate() &&
        day.getMonth() === this.state.selectedDays[i].getMonth() &&
        day.getFullYear() === this.state.selectedDays[i].getFullYear()
      )
        return this.setState(({ selectedDays }) => ({
          selectedDays: [
            ...selectedDays.slice(0, i),
            ...selectedDays.slice(i + 1),
          ],
        }));
    }
   
    this.setState(({ selectedDays }) => ({
      selectedDays: [...selectedDays, day],
    }));
  };
  render() {
    return (
    //В методе render отображаются два дочерних компонента Calendar: CalendarHeadи CalendarBody
    // CalendarHead отображает заголовок календаря(название текущего месяца и года,  кнопки для перехода на предыдущий и следующий месяц)
    // CalendarBody отображает календарь с днями текущего месяца и позволяет выбирать даты. 
      <>
        <CalendarHead changeDate={this.changeDate}//Метод  передается в качестве свойства, чтобы можно было изменять текущую дату 
         />
        <CalendarBody
          date={this.state.date}//устанавливается равным текущей дате из состояния компонента 
          selectDays={this.selectDays}//передается в качестве свойства selectDays, чтобы можно было выбирать даты 
          selectedDays={this.state.selectedDays}//передается в качестве свойства selectedDays, чтобы отображать выбранные даты 
        />
      </>
    );
  }
}

class CalendarHead extends React.Component {
  constructor(props) {
    super(props);
    this.state = { date: new Date() };//устанавливаем начальное состояние, которое содержит текущую дату
  }
  monthNames = [//Массив содержащий названия месяцев
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
  ];
  
  prevMonth = () => {// изменяем текущую дату на предыдущий месяц 
    let date = new Date(
      this.state.date.getFullYear(),
      this.state.date.getMonth() - 1
    );
    this.setState({ date }, () => this.props.changeDate(this.state.date));
  };
  
  nextMonth = () => {// изменяем текущую дату на следующий месяц 
    let date = new Date(
      this.state.date.getFullYear(),
      this.state.date.getMonth() + 1
    );
    this.setState({ date }, () => this.props.changeDate(this.state.date));
  };
 
  render() {
    return (
      <>
        {this.monthNames[this.state.date.getMonth()]}//Название текущего месяца  отображаются с помощью свойств объекта Date
        {this.state.date.getFullYear()}//Название текущего года
        //обработчики событий, которые вызывают методы prevMonth и nextMonth
        <button onClick={this.prevMonth}>{"<"}</button>
        <button onClick={this.nextMonth}>{">"}</button>
      </>
    );
  }
}

class CalendarBody extends React.Component {
  dayNames = ["пн", "вт", "ср", "чт", "пт", "сб", "вс"];//массив сокращенных названий дней недели 
  currentDate = new Date(); // текущая дата.
  startDay(date) {//возвращаем номер дня недели, с которого начинается месяц, соответствующий этой дате.
    let startDay;
    date.getDay() === 0 ? (startDay = 6) : (startDay = date.getDay() - 1);
    return startDay;
  }
 
  oneMonth(date) {//возвращает двумерный массив, содержащий все дни месяца, соответствующего этой дате
    let fullMonth = [],
      day = 1 - this.startDay(date),//объект, содержащий информацию о дне
      month = date.getMonth(),//объект, содержащий информацию о месяце 
      year = date.getFullYear();//объект, содержащий информацию о годе.
    for (let i = 0; i < 6; i++) {
      //недели
      fullMonth[i] = [];
      for (let j = 0; j < 7; j++) {
        //дни
        fullMonth[i][j] = new Date(year, month, day++);
      }
    }
    return fullMonth;
  }
  
  styleTd = (wdate, currentDate, date, selectedDays) => {
    if (date.getMonth() !== wdate.getMonth())//Если день  не относится к текущему месяцу, ячейка становится серой.
      return { color: "rgb(224, 223, 223)" };
    for (let i = 0; i < selectedDays.length; i++) {//Если день  был выбран пользователем, ячейка получает фоновый цвет
      if (
        selectedDays[i].getDate() === wdate.getDate() &&
        selectedDays[i].getMonth() === wdate.getMonth() &&
        selectedDays[i].getFullYear() === wdate.getFullYear()
      )
        return { background: "#B6CDF0" };
    }
    if (//Если день  соответствует текущей дате, ячейка получает фоновый цвет
      wdate.getDate() === currentDate.getDate() &&
      wdate.getMonth() === currentDate.getMonth() &&
      wdate.getFullYear() === currentDate.getFullYear()
    )
      return { background: "#D89FEE" };
  };
  selectDays = (wdate) => { 
    this.setState({}, () => this.props.selectDays(wdate));// вызываем метод selectDays, передавая ему выбранную дату.
  };
  
  render() {
    const date = new Date(
        this.props.date.getFullYear(),
        this.props.date.getMonth(),
        1
      ), //первое число текущего месяца
      selectedDays = this.props.selectedDays;//массив, содержащий выбранные пользователем даты
    return (
      <table>
        <thead>
          <tr>
            {this.dayNames.map((name) => (
              <td key={name}>{name}</td>
            ))}
          </tr>
        </thead>
        <tbody>
          {this.oneMonth(date).map((week, index) => (// отображает заголовок таблицы с названиями дней недели и тело таблицы с днями месяца
            <tr key={index}>
              {week.map((wdate, index) => (
                <td
                  key={index}
                  style={this.styleTd(
                    wdate,
                    this.currentDate,
                    date,
                    selectedDays
                  )}
                  onClick={() => {//Если пользователь кликает на ячейку, вызывается метод `selectDays`, передавая ему выбранную дату.
                    if (date.getMonth() === wdate.getMonth())
                      this.selectDays(wdate);
                  }}
                >
                  {wdate.getDate()}
                </td> // wdate === fullMonth[i][j]
              ))}
            </tr>
          ))}
        </tbody>
      </table>
    );
  }
}
