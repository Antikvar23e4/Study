#include "pch.h"
#include "Combi.h"
#include <algorithm>
namespace combi
{
    // Конструктор: Инициализация комбинации размеров 'n' и 'm'
    xcombination::xcombination(short n, short m)
    {
        this->n = n;
        this->m = m;
        this->sset = new short[m + 2];
        this->reset();// Инициализация комбинации
    }
    // Сброс комбинации в начальное состояние
    void  xcombination::reset()     
    {
        this->nc = 0;
        for (int i = 0; i < this->m; i++) this->sset[i] = i;
        this->sset[m] = this->n;
        this->sset[m + 1] = 0;
    };
    // Получение размера первой комбинации
    short xcombination::getfirst()
    {
        return (this->n >= this->m) ? this->m : -1;
    };
    // Получение размера следующей комбинации
    short xcombination::getnext()    
    {
        short rc = getfirst();
        if (rc > 0)
        {

            short j;
            // Поиск индекса j, где sset[j] + 1 не равно sset[j + 1]
            for (j = 0; this->sset[j] + 1 == this->sset[j + 1]; ++j)
                this->sset[j] = j;
            if (j >= this->m) rc = -1;
            else {
                this->sset[j]++;
                this->nc++;

            };

        }
        return rc;
    };
    // Получение элемента с индексом 'i' в текущей комбинации
    short xcombination::ntx(short i)
    {
        return this->sset[i];
    };
    // Расчет и возврат общего числа комбинаций
    unsigned __int64 fact(unsigned __int64 x) { return(x == 0) ? 1 : (x * fact(x - 1)); };
    // Функция для вычисления факториала числа 'x'
    unsigned __int64 xcombination::count() const
    {
        return (this->n >= this->m) ?
            fact(this->n) / (fact(this->n - this->m) * fact(this->m)) : 0;
    };
}