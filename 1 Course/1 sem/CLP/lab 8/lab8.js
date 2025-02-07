function task_1() {
    let obj = document.getElementById('text1');
    obj.onmouseover = function() {
        this.style.color = 'red';
    }
    obj.onmouseout = function() {
        this.style.color = 'black';
    }
} task_1();

function task_2() {
    let obj = document.getElementById('text2')
    obj.onclick = function() {
        this.style.fontSize = '30px';
    }
} task_2();

function task_3() {
    let array = new Array('autumn.jpg', 'winter.jpg');
    let obj = document.getElementById('pic1');
    obj.onclick = function() {
        obj.src = array[1];
    }
} task_3();

function task_4() {
    let obj = document.getElementById('text3');
    obj.onclick = function() {
        obj.innerHTML = '<img src="winter.jpg"/>';
    }
} task_4();

function task_5() {
    let obj = document.getElementById('pic2');
    obj.onmouseover = function() {
        this.style.width = '35%';
    }
    obj.onmouseout = function() {
        this.style.width = '20%';
    }
} task_5();

function task_6() {
    let obj = document.getElementById('text4');
    obj.ondblclick = function() {
        this.style.border = 'solid 2px pink';
    }
} task_6();
function task_7() {
    let obj = document.getElementById('pic3');
    obj.onmouseover = function() {
        this.style.border ='solid black 6px';
    }
} task_7();