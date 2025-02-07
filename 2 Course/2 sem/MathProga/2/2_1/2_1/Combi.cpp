#include "pch.h"
#include "Combi.h"
#include <algorithm>
namespace combi
{
    // Конструктор: Инициализация подмножества размера 'n
    subset::subset(short n)
    {
        this->n = n;
        this->sset = new short[n];
        this->reset();// Инициализация подмножества
    };
    // Сброс подмножества в пустое состояние
    void  subset::reset()
    {
        this->sn = 0;
        this->mask = 0;
    };
    // Получение первого подмножества и возврат его размера
    short subset::getfirst()
    {
        __int64 buf = this->mask;
        this->sn = 0;
        // Итерация по каждому биту в маске
        for (short i = 0; i < n; i++)
        {
            if (buf & 0x1) this->sset[this->sn++] = i; // Если бит установлен, добавить индекс в подмножество
            buf >>= 1;
        }
        return this->sn; // Возврат размера подмножества
    };
    // Получение следующего подмножества и возврат его размера
    short subset::getnext() 
    {
        int rc = -1;
        this->sn = 0;
        // Инкрементирование маски и проверка, находится ли она в пределах допустимых значений
        if (++this->mask < this->count()) rc = getfirst();// Если в пределах, получить следующее подмножество
        return rc;
    };
    // Получение элемента с индексом 'i' в текущем подмножестве
    short subset::ntx(short i)
    {
        return  this->sset[i];
    };
    // Расчет и возврат общего числа подмножеств
    unsigned __int64 subset::count()
    {
        return (unsigned __int64)(1 << this->n);
    };
};
