class Clock extends React.Component {
    constructor(props) {
        super(props); // Состояние отвечающее за дату
        this.state = {
          date: new Date(), //Начальное состояние this.state объектом с текущим временем
        };
    }
  
    componentDidMount() {
      this.timerID = setInterval( 
        //Метод жизненного цикла, компонент Clock указывает браузеру установить таймер, который будет вызывать tick() раз в секунду
        () => this.tick(),
        1000
      );
    }
  
    componentWillUnmount() {
      //Вызывается непосредственно перед размонтированием и уничтожением компонента
      clearInterval(this.timerID);
    }
  
    tick() { //React обновляет состояние компонента, вызывая setState() с текущим временем
      this.setState({
        date: new Date()
      }); 
    }
  
    render() {
        return (
          <div>
            {new Intl.DateTimeFormat('en-US', { //Объект отвечающий за форматирование даты
            hour: 'numeric', 
            minute: 'numeric', 
            second: 'numeric',
            hour12: this.props.format,
            timeZone: this.props.timezone
          }).format(this.state.date)}
          </div>
        );
    }
  }
  
  //////////////////////////2 задание//////////////////////////////////
  
  class JobSelect extends React.Component {
    constructor(props) {
      super(props);
      this.state = {
        id: 0,
      };
    }
  
    // Функция запускается при изменении кнопок и принимает пропсы
    selected = (props) => {
      // Меняем состояние 
      // пропс - эвент, таргет - обращается к элементу, что вызвал функцию   
      this.setState({ id: props.target.value });
    };
  
    jobs = [
      {
        id: 1,
        name: "Программист",
      },
      {
        id: 2,
        name: "Художник",
      },
      {
        id: 3,
        name: "Спортсмен",
      },
      {
        id: 4,
        name: "Писатель",
      },
      {
        id: 5,
        name: "Продавец",
      },
    ];
  
    render() {
      return (
        <div>
           {/* Применяем обработчик событий*/}
          <select className={"select"} onChange={this.selected}>
            <option selected={true} value={0}>
              Выбор
            </option>
            {this.jobs.map((item) => (
              <option key={item.id} value={item.id}>
                {item.name}
              </option>
            ))}
          </select>
            {/* Вызываем компонент внутри другого компонент, передает как пропс текущий выбор */}
          <LinksForJobs id={this.state.id} name={this.state.name} />
        </div>
      );
    }
  }
  
  
  class LinksForJobs extends React.Component {
    switchJobs() {
       // Создаем массив в который поместим ссылки
      let links = [];
      let id = this.props.id;
  
      switch (id) {
        case "1": {
          links.push(
            {
              name: "Metanit.com",
              url: "https://metanit.com/",
            },
            {
              name: "Github.com",
              url: "https://github.com/",
            }
          );
          break;
        }
        case "2": {
          links.push(
            {
              name: "Artstation.com",
              url: "https://www.artstation.com/",
            },
            {
              name: "Deviantart.com",
              url: "https://www.deviantart.com/",
            }
          );
          break;
        }
        case "3": {
          links.push(
            {
              name: "Sports.ru",
              url: "https://www.sports.ru/",
            },
            {
              name: "Championat.com",
              url: "https://www.championat.com/",
            }
          );
          break;
        }
        case "4": {
          links.push(
            {
              name: "Penfox.ru",
              url: "https://penfox.ru/",
            },
            {
              name: "Pishi.pro",
              url: "https://pishi.pro/",
            }
          );
          break;
        }
        case "5": {
          links.push(
            {
              name: "Kufar.by",
              url: "https://www.kufar.by/l",
            },
            {
              name: "Onliner.by",
              url: "https://www.onliner.by/",
            }
          );
          break;
        }
      }
      console.log(links);
  
      return (
        <div>
          <ul>
             {/* Метод мап принимает в параметры функцию и выполняет ее для каждого элеменыта массива */}
            {links.map((item) => (
              <li>
                <a className="menu-link" href={item.url}>
                  {item.name}
                </a>
              </li>
            ))}
          </ul>
        </div>
      );
    }
  
    render() {
      return <div>
        {this.switchJobs()}
        </div>;
    }
  }
  
  