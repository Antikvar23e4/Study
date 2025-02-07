#include "stdafx.h"
#include "Combi.h"
#include <algorithm>
#define NINF  ((short)0x8000)

namespace combi
{
	// Класс "permutation" представляет собой перестановку элементов.
	permutation::permutation(short n)
	{
		this->n = n;
		this->sset = new short[n];
		this->dart = new bool[n];
		this->reset();  // Сбрасываем состояние перестановки.
	};

	// Сброс параметров перестановки к начальному состоянию.
	void permutation::reset()
	{
		this->getfirst();
	};

	// Инициализация перестановки начальным состоянием.
	__int64 permutation::getfirst()
	{
		this->np = 0;
		for (int i = 0; i < this->n; i++)
		{
			this->sset[i] = i;
			this->dart[i] = L;
		};
		return  (this->n > 0) ? this->np : -1;  // Возвращаем индекс, либо -1, если перестановка пуста.
	};

	// Получение следующей перестановки.
	__int64 permutation::getnext()
	{
		__int64 rc = -1;
		short maxm = NINF, idx = -1;

		// Поиск индекса для обмена.
		for (int i = 0; i < this->n; i++)
		{
			if (i > 0 &&
				this->dart[i] == L &&
				this->sset[i] > this->sset[i - 1] &&
				maxm < this->sset[i])  maxm = this->sset[idx = i];

			if (i < (this->n - 1) &&
				this->dart[i] == R &&
				this->sset[i] > this->sset[i + 1] &&
				maxm < this->sset[i])  maxm = this->sset[idx = i];
		};

		// Если найден индекс для обмена, производим обмен и обновляем направление.
		if (idx >= 0)
		{
			std::swap(this->sset[idx],
				this->sset[idx + (this->dart[idx] == L ? -1 : 1)]);
			std::swap(this->dart[idx],
				this->dart[idx + (this->dart[idx] == L ? -1 : 1)]);

			// Обновление направления для остальных элементов.
			for (int i = 0; i < this->n; i++)
				if (this->sset[i] > maxm) this->dart[i] = !this->dart[i];

			rc = ++this->np;  // Увеличиваем счетчик перестановок и возвращаем номер текущей.
		}
		return rc;
	};

	// Возвращает i-й элемент текущей перестановки.
	short permutation::ntx(short i) { return  this->sset[i]; };

	// Вычисление факториала числа x.
	unsigned __int64 fact(unsigned __int64 x) { return (x == 0) ? 1 : (x * fact(x - 1)); };

	// Возвращает общее количество возможных перестановок.
	unsigned __int64 permutation::count() const { return fact(this->n); };
}
