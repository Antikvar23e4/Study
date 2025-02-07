import React from 'react'
import "./index.css"
import { Notes } from './Notes'
import { StudentInfoHandler } from './StudentInfoHandler'

function App() {
  return (
<>
<StudentInfoHandler />
<br/>
<Notes />
</>
  );
}

export default App;
