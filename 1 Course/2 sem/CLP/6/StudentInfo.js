import React from "react";

export class StudentInfo extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      FIO: "Aaaaaaa Bbbbbb Ccccccc",
      birthDate: "16.05.2000",
      uniYear: "2020",
      faculty: "IT",
      group: "10",
      speciality: "POIT",
      email: "abcd@mail.ru",
      phoneNumber: "80291000000",
    };
  }
  render() {
      return(
          this.props.render(this.state)
      )
  }
}
