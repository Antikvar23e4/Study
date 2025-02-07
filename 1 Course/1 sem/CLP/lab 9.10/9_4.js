function draw(){
	event.preventDefault();

	if(document.getElementById("canvas"))//Удаление старого холста
		document.getElementById("canvas").remove();
	if(document.getElementById("divY"))
		document.getElementById("divY").remove();
	if(document.getElementById("divX"))
		document.getElementById("divX").remove();

	let canvas = document.createElement("canvas"),
		graph = event.target.graph.value,
		color = document.getElementById("select").value,
		y,
		ctx = canvas.getContext('2d'),
		divX = document.body.appendChild(document.createElement("div")),
		divY = document.body.appendChild(document.createElement("div"));
//предварительная настройка халста
	canvas.width = 700;
	canvas.height = 400;
	canvas.style.position = "absolute";
	canvas.style.top = "40px";
	canvas.id = "canvas";

	divX.style = "position: absolute; font-size: 15px;";
	divY.style = "position: absolute; font-size: 15px;";
	divY.style.top = 40 + "px";
	divY.style.left = canvas.width / 2 + 20 + "px";
	divX.style.top = canvas.height / 2 + 50 + "px";
	divX.style.left = canvas.width - 10 + "px";

    //рисование фигур
	ctx.lineWidth = 1;//Нанесение системы координат
	ctx.strokeStyle = "black";
	ctx.moveTo(canvas.width / 2 - 0.5, 0); // перемещает "курсор" в позицию x, y и делает её текущей
	ctx.lineTo(canvas.width / 2 - 0.5, canvas.height);// ведёт линию из текущей позиции в указанную, и делает в последствии указанную текущей
	ctx.moveTo(0, canvas.height / 2 - 0.5);
	ctx.lineTo(canvas.width, canvas.height / 2 - 0.5);

	ctx.moveTo(canvas.width / 2 - 0.5, 0);
	ctx.lineTo(canvas.width / 2 - 5.5, 10.5);
	ctx.moveTo(canvas.width / 2 - 0.5, 0);
	ctx.lineTo(canvas.width / 2 + 5.5, 10.5);

	ctx.moveTo(canvas.width, canvas.height / 2 - 0.5);
	ctx.lineTo(canvas.width - 10.5, canvas.height / 2 - 5.5);
	ctx.moveTo(canvas.width, canvas.height / 2 - 0.5);
	ctx.lineTo(canvas.width - 10.5, canvas.height / 2 + 5.5);

	ctx.stroke();

	ctx.fillStyle = color;// определяет цвет заливки 

	if (graph == 1) {//y = x^2
		for(let x = -canvas.width / 2; x < canvas.width / 2; x += 0.01)
		{
			y = canvas.height / 2 - 40 * Math.pow(x / 40, 2);
			ctx.fillRect(x + canvas.width / 2 - 0.5, y - 0.5, 1, 1);
		}
	}

	if (graph == 2) {//y = x^3
		for(let x = -canvas.width / 2; x < canvas.width / 2; x += 0.01)
		{
			y = (canvas.height / 2 - 40 * Math.pow(x / 40, 3));
			ctx.fillRect(x + canvas.width / 2 - 0.5, y - 0.5, 1, 1);
		}
	}

	if (graph == 3) {//y = sin(x)
		for(let x = -canvas.width / 2; x < canvas.width / 2; x += 0.01)
		{
			y = (canvas.height / 2 - 40 * Math.sin(x / 40));
			ctx.fillRect(x + canvas.width / 2 - 0.5, y - 0.5, 1, 1); // Рисует закрашеную линию(прямую) 
		}
	}

	if (graph == 4) {//y = cos(x)
		for(let x = -canvas.width / 2; x < canvas.width / 2; x += 0.01)
		{
			y = canvas.height / 2 -  40 * Math.cos(x / 40);
			ctx.fillRect(x + canvas.width / 2 - 0.5, y - 0.5, 1, 1);
		}
	}
	
	document.body.appendChild(canvas);
}