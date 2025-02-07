function myMove(){
    var elem = document.getElementById("img1");
    var pos = 0;
    var id = setInterval(frame,10);
    function frame (){
if (pos == 520 ){
    var id2 = setInterval(frame2,10);
    function frame2(){
   if (pos==0){
    clearInterval(id2);
    }
    else{
    pos--;
    elem.style.top = pos - 'px';
    elem.style.left = pos - 'px';
    }
    }
}
else {
pos++;
elem.style.top = pos + 'px';
elem.style.left = pos + 'px';
  } 
 }
}