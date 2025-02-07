function Lab_1() {
    return (
      <div className="App">
        <h1>Задание 1</h1>
        <FisrtTask />
        <h1>Задание 2</h1>
        <SecondTask />
        <h1>Задание 3</h1>
        <ThirdTask />
      </div>
    );
  }
  
  export default Lab_1;
  
  function FisrtTask() { 
    let date = new Date();
    return (
        <div className='FisrtTask'>
            <p>Текущая дата и время: {date.toString()}</p>
        </div>
    );
  }
  
  
  const info = [{
    stock_name: "EFX",
    company_name: "Equifax Inc",
    price: 163.55,
    currency: "USD",
    change: "+9.03"
  }, {
    stock_name: "IRM",
    company_name: "Iron Mountain Inc",
    price: 33.21,
    currency: "USD",
    change: "+1.42"
  }, {
    stock_name: "NTAP",
    company_name: "NetApp Inc",
    price: 54.81,
    currency: "USD",
    change: "-6.01"
  }, {
    stock_name: "CTL",
    company_name: "Centurylink Inc",
    price: 13.79,
    currency: "USD",
    change: "-1.37"
  }];
  
  
  function OutInfo(value) {
    let rows = [];
    let cellColour;
  
    if (parseFloat(value.change) > 0) {
      cellColour = "#b6e8cc";
    }
    else {
      cellColour = "#e8b6b6";
    }
  
    for (let arg in value) {
        if (value[arg] === value.change) {
            rows.push(<td style={{ background: cellColour }} >{value[arg]}</td>);
        }
        else {
            rows.push(<td>{value[arg]}</td>);
        }
    }
    return rows;
  }
  
  
  function OutCycle() {
    let table = [];
    for (let i = 0; i < info.length; i++) {
        table.push(<tr>{OutInfo(info[i])}</tr>);
    }
    return table;
  }
  
  
  function SecondTask() {
    return (
        <table class="styled-table">
            <tr>
                <th>Название акции</th>
                <th>Название компании</th>
                <th>Цена</th>
                <th>Валюта</th>
                <th>Изменение</th>
            </tr>
            {OutCycle()}
        </table>
    );
  }
  
  
  
  function ThirdTask() {
    return (
      <table class="chessboard">
        {ChessLetters()}
        {ChessBoard()}
        {ChessLetters()}
      </table>
    );
  }
  
  function ChessBoard() {
    const board = [];
  
    for (let i = 0; i < 8; i += 2) {
      board.push(
        <tr>
          {ChessNumbers(i + 1)}
          <td className="cellOdd" />
          <td className="cellEven" />
          <td className="cellOdd" />
          <td className="cellEven" />
          <td className="cellOdd" />
          <td className="cellEven" />
          <td className="cellOdd" />
          <td className="cellEven" />
          {ChessNumbers(i + 1)}
        </tr>,
        <tr>
          {ChessNumbers(i + 2)}
          <td className="cellEven" />
          <td className="cellOdd" />
          <td className="cellEven" />
          <td className="cellOdd" />
          <td className="cellEven" />
          <td className="cellOdd" />
          <td className="cellEven" />
          <td className="cellOdd" />
          {ChessNumbers(i + 2)}
        </tr>
      );
    }
    return board;
  }
  
  function ChessNumbers(number) {
    return <td className="cellNumber">{number}</td>
  }
  
  function ChessLetters() {
    return (
      <tr>
        <td></td>
        <td>a</td>
        <td>b</td>
        <td>c</td>
        <td>d</td>
        <td>e</td>
        <td>f</td>
        <td>g</td>
        <td>i</td>
        <td></td>
      </tr>
    );
  }
  