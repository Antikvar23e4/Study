import React from "react";

export class SignUpPasswordInput extends React.Component {
  state = {
    password: "",
    disableBtn: true,
  };
  handlePassword = (e) => {
    this.setState({ password: e.target.value });
  };

  handleRepeat = (e) => {
    this.state.password === e.target.value
      ? this.setState({ disableBtn: false }, () =>
          this.props.disableBtn(this.state.disableBtn)
        )
      : this.setState({ disableBtn: true }, () =>
          this.props.disableBtn(this.state.disableBtn)
        );
  };
  checkPassword() {
    let password = this.state.password,
      check = 0,
      width = "0%";
    if (password.match(/\d/g)) check++;
    if (password.match(/[a-z]/g)) check++;
    if (password.match(/[A-Z]/g)) check++;
    if (password.match(/\W/g)) check++;
    if (!password.length) width = "0%"; // выглядет ужасно но шо поделать
    else if (password.length < 6 && check < 3) width = "33%";
    else if (password.length < 6 && check >= 3) width = "66%";
    else if (password.length >= 8 && check < 3) width = "66%";
    else if (password.length >= 8 && check >= 3) width = "100%";
    else if (password.length >= 6 && check == 1) width = "33%";
    else if (password.length >= 6 && check > 1 && check < 4) width = "66%";
    else if (password.length >= 6 && check == 4) width = "100%";
    return (
      <div className="progress_bar_bg">
        <div className="progress_bar" style={{ width: width }} />
      </div>
    );
  }
  render() {
    return (
      <>
        <input
          type="password"
          placeholder="Введите пароль"
          onChange={this.handlePassword}
        />
        {this.checkPassword()}
        <input
          type="password"
          placeholder="Повторите пароль"
          onChange={this.handleRepeat}
        />
      </>
    );
  }
}
