#include "pch.h"
#include "Combi.h"
#include <algorithm>

#define NINF  ((short)0x8000)

namespace combi
{
    // инициализирует объект перестановки
    permutation::permutation(short n)
    {
        // Выделение памяти под массивы для хранения перестановки и флагов направления
        this->n = n;
        this->sset = new short[n];
        this->dart = new bool[n];
        this->reset();
    };
    // Сброс состояния перестановки в начальное
    void  permutation::reset()
    {
        // Вызов функции для получения первой перестановки
        this->getfirst();
    };
    // Получение первой перестановки и возврат числа перестановок
    __int64  permutation::getfirst()
    {
        this->np = 0;
        // Инициализация начальной перестановки и флагов направления
        for (int i = 0; i < this->n; i++)
        {
            this->sset[i] = i; this->dart[i] = L;
        };
        return  (this->n > 0) ? this->np : -1;
    };
    // Получение следующей перестановки и возврат номера текущей перестановки
    __int64  permutation::getnext()   
    {
        __int64 rc = -1;
        short maxm = NINF, idx = -1;
        // Поиск максимального элемента для обмена
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
        // Если найден элемент для обмена
        if (idx >= 0)
        {
            // Обмен значениями и флагами направления
            std::swap(this->sset[idx],
                this->sset[idx + (this->dart[idx] == L ? -1 : 1)]);
            std::swap(this->dart[idx],
                this->dart[idx + (this->dart[idx] == L ? -1 : 1)]);
            // Обновление флагов направления для оставшихся элементов
            for (int i = 0; i < this->n; i++)
                if (this->sset[i] > maxm) this->dart[i] = !this->dart[i];
            rc = ++this->np;// Увеличение счетчика перестановок
        }
        return rc;
    };
    // Получение элемента перестановки по индексу 'i'
    short permutation::ntx(short i) { return  this->sset[i]; };
    // Функция для вычисления факториала числа 'x'
    unsigned __int64 fact(unsigned __int64 x) { return (x == 0) ? 1 : (x * fact(x - 1)); };
    // Вычисление и возврат общего числа перестановок
    unsigned __int64 permutation::count() const { return fact(this->n); };
}
