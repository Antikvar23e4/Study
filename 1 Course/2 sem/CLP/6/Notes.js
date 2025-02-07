import React from "react";

export class Notes extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      title: "",
      date: "",
      desc: "",
      notes: [],
    };
  }
  style(length) {
    if (length > 8) {
      return { background: "red" };
    }
    return { background: "yellow" };
  }
  titleHandle = (e) => {
    this.setState({ title: e.target.value });
  };
  dateHandle = (e) => {
    this.setState({ date: e.target.value });
  };
  descHandle = (e) => {
    this.setState({ desc: e.target.value });
  };
  addNote = () => {
    this.setState({
      notes: [
        ...this.state.notes,
        {
          title: this.state.title,
          date: this.state.date,
          desc: this.state.desc,
        },
      ],
      title: "",
      date: "",
      desc: "",
    });
  };
  deleteFirst = () => {
    this.setState({notes: this.state.notes.slice(1, this.state.notes.length)})
  }
  deleteLast = () => {
    this.setState({notes: this.state.notes.slice(0, this.state.notes.length - 1)})
  }
  render() {
    let length = 0;
    return (
      <>
        <form>
          <input
            type="text"
            placeholder="title"
            onChange={this.titleHandle}
            value={this.state.title}
          />
          <input
            type="text"
            placeholder="date"
            onChange={this.dateHandle}
            value={this.state.date}
          />
          <textarea
            placeholder="your note"
            onChange={this.descHandle}
            value={this.state.desc}
          />
        </form>
        <button onClick={this.addNote}>Add</button>
        {this.state.notes.length > 3 && (
          <>
            <button onClick={this.deleteFirst}>delete first</button>
            <button onClick={this.deleteLast}>delete last</button>
          </>
        )}
        {this.state.notes.map((item) => {
          length++;
          return (
            <div key={item.title} className="notes" style={this.style(length)}>
            <p>{length > 7 && "Too much notes"}</p>
              <h3>{item.title}</h3>
              <h4>{item.date}</h4>
              <p>{item.desc}</p>
            </div>
          );
        })}
      </>
    );
  }
}
