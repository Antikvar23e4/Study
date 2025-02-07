img1.onclick = function() {
    let start = Date.now();// запомнить время начала

    let timer = setInterval(function() {
      let timePassed = Date.now() - start; // сколько времени прошло с начала анимации

      img1.style.left = timePassed / 2 + 'px';// в то время как timePassed идёт от 0 до 2000 left изменяет значение 

      if (timePassed > 2000) clearInterval(timer); // закончить анимацию через 2 секунды

    }, 20);
  }

