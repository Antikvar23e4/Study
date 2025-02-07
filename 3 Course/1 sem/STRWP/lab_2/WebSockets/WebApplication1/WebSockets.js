var ws = null;
var ta;
var bstart;
var bstop;

window.onload = function () {
    if (Modernizr.websockets) {
        console.log('Поддерживается');
        ta = document.getElementById('ta')
        bstart = document.getElementById('bstart');
        bstop = document.getElementById('bstop');
        bstart.disabled = false;
        bstop.disabled = true;
    }
}

function sendMessage() {
    if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send("Соединение");
    } else {
        ta.value += "Отправка сообщений недоступна\n";
    }
}

function exe_start() {
    if (!ws) {
        ws = new WebSocket('ws://localhost:59391/Websockets.websocket');

        ws.onopen = function () {
            ta.value += "Соединение открыто\n";
            bstart.disabled = true;
            bstop.disabled = false;
            sendMessage();

        };

        ws.onmessage = function (event) {
            ta.value += event.data + "\n";
        };

        ws.onclose = function () {
            ta.value += "Соединение закрыто.\n";
        };
    }
}

function exe_stop() {
    if (ws) {
        ws.close(3001, ' stopapplication');
        ws = null;
        bstart.disabled = false;
        bstop.disabled = true;
    }
}