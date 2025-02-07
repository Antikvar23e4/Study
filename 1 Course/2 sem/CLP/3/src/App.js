import React from 'react';
import { Component } from "react";
import './App.css';

function App() {
  return (
    <div className="App">
      <h2>Задание 1</h2>
      <PhoneNumber/>
      <h2>Задание 2</h2>
      <SortTable/>
    </div>
  );
}

export default App;

class PhoneNumber extends Component {
  state = {
    number: "",
    showTheList: false,
    value: "Беларусь",
    img: "/images/bel.png",
    mask: "XXXX (XX) XXX-XX-XX",
    count: 13,
  };
  info = [
    {
      value: "Беларусь",
      code: "+375",
      img: "/images/bel.png",
      mask: "XXXX (XX) XXX-XX-XX",
      count: 13,
    },
    {
      value: "Украина",
      code: "+380",
      img: "/images/uk.png",
      mask: "XXXX (XX) XXX-XX-XX",
      count: 13,
    },
    {
      value: "Россия",
      code: "+7",
      img: "/images/rus.png",
      mask: "XX (XXX) XXX-XX-XX",
      count: 12,
    },
    {
      value: "Польша",
      code: "+48",
      img: "/images/poland.png",
      mask: "XXX XXX-XXX-XXX",
      count: 12,
    },
    {
      value: "Литва",
      code: "+370",
      img: "/images/lithuania.png",
      mask: "XXXX (XX) XXX-XX-XX",
      count: 13,
    },
    {
      value: "Латвия",
      code: "+371",
      img: "/images/latvia.png",
      mask: "XXXX XXXX-XXXX",
      count: 12,
    },
  ];


 theList() {
    return (
      <div class="table">
      <ul>
        {this.info.map((item) => { //Создание выпадающего списка со всеми элементами массива info  
          return (
            <li onClick= {() => //При нажатии изменяется состояние (значения берутся из массива info)
                this.setState({
                  number: item.code,
                  showTheList: false,
                  img: item.img,
                  mask: item.mask,
                  count: item.count,
                })
              }
              key={item.value} //Внутри метода map обязательно нужно указывать ключи для элементов, если они в массиве
              > 
              <img src={item.img} alt=""/>
              <label>
                <input type="radio" name="country" value={item.value} /> 
                {item.value}
                {item.code}
              </label>
            </li> );
          })}
      </ul>
      </div>
    );
  }

  numberField() {
    return (
      <div>
        <label>
          <img src={this.state.img}  style={{height: "15px", width: "30px",}}alt=""/>
          <input
            onClick={() => this.setState({ showTheList: !this.state.showTheList })} 
            //Изменение состояния (showTheList=true), что показывает список
            id="number"
            type="tel"
            name="myPhone"
            placeholder="Выберите страну..."
            value={this.state.number}
            onChange={this.handleNumberChange} //При вводе вызывается функция handleNumberChange 
            maxLength={this.state.count} 
          />
        </label>
      </div>
    );
  }
  
  handleNumberChange = (number) => {
    //Осуществляет форматирование номера телефона
    this.setState(
      {
        number: number.target.value,
      },
      () => {
        this.info.map((item) => {
          if (this.state.number === item.code) //Сверка введённого пользователем кода страны с уже существующими
            this.setState({
              value: item.value,
              img: item.img,
              mask: item.mask,
              count: item.count,
            });
            return 0
        }
        );

        if (this.state.count === this.state.number.length) { //Cверка длины введённого номера и маски
          let maskArr = this.state.mask.split(""), // split - Разбиение строки в массив
            numberArr = this.state.number.split("");
          for (let i = 0, j = 0; i < maskArr.length; i++)
            if (maskArr[i] === "X") { //Если совпадает с Х, то отображаются введённые числа, иначе отображается маска
              maskArr[i] = numberArr[j];
              j++;
            }
          let number = maskArr.join(""); //Обратное объедние массива в строку
          this.setState({ number: number });
        }
        else {
          let clearArr = this.state.number.split(/\(|-|\)| /), //Удаление маски, если длина номера не совпадает с нужной
          number = clearArr.join("");
          this.setState({ number: number });
        }
      }
    );
  };
  
  render() {
    return (
      //Рендеринг поля ввода номера
      <div class="phone">
        {this.numberField()} 
        {this.state.showTheList ? this.theList() : null}
      </div>
    );
  }
}


/////////////////////////////////////////////////

class SortTable extends Component {
  constructor(props) {
    super(props);
    this.sorted = { name: true, price: true, inStock: true };
    this.state = { array: this.goods };
  }
  goods = [
    { id: "Milk", name: "Milk", price: 0.8, inStock: 0 },
    { id: "Butter", name: "Butter", price: 1.3, inStock: 13 },
    { id: "Coffee", name: "Coffee", price: 12, inStock: 23 },
    { id: "Tea", name: "Tea", price: 13, inStock: 2 },
    { id: "Sugar", name: "Sugar", price: 1.2, inStock: 4 },
    { id: "Apples", name: "Apples", price: 1, inStock: 16 },
    { id: "Cheese", name: "Cheese", price: 10, inStock: 9 },
  ];
  styles = {
    td: {
      padding: "10px 20px",
      border: "1px solid",
    },
    table: {
      margin: "100px",
      borderCollapse: "collapse",
    },
  };

  sort(byWhat) {
    let direction = this.sorted[byWhat] ? 1 : -1,
      goodsCopy = [...this.goods].sort(function (a, b) {
        if (a[byWhat] > b[byWhat]) {
          return direction;
        }
        if (a[byWhat] < b[byWhat]) {
          return direction * -1;
        }
        return 0;
      });
    this.sorted[byWhat] = !this.sorted[byWhat];
    this.setState({ array: goodsCopy });
  }
  
  table() {
    let stringNumber = 0;
    return this.state.array.map((item) => {
      let inStockStyle = {};
      if (+item.inStock < 3) inStockStyle = { background: "yellow" };
      if (+item.inStock === 0) inStockStyle = { background: "red" };
      return (
        <tr key={item.id}>
          <td style={this.styles.td}>{++stringNumber}</td>
          <td style={this.styles.td}>{item.name}</td>
          <td style={this.styles.td}>${item.price}</td>
          <td style={Object.assign({}, this.styles.td, inStockStyle)}>
            {item.inStock}
          </td>
        </tr>
      );
    });
  }
  head = [
    <tr>
      <td style={this.styles.td}>№</td>
      <td style={this.styles.td}>
        <button onClick={() => this.sort("name")}>Name</button>
      </td>
      <td style={this.styles.td}>
        <button onClick={() => this.sort("price")}>Price</button>
      </td>
      <td style={this.styles.td}>
        <button onClick={() => this.sort("inStock")}>In Stock</button>
      </td>
    </tr>,
  ];
  render() {
    return (
      <table style={this.styles.table}>
        {this.head}
        {this.table()}
      </table>
    );
  }
}
