#pragma once 

namespace combi
{
    struct xcombination           // генератор  сочетаний (эвристика) 
    {
        short n;                  // количество элементов исходного множества  
        short m;                  // количество элементов в сочетаниях 
        short* sset;              // массив индексов текущего сочетания  
        short nc;                 // количество текущих сочетаний

        xcombination(short n = 1, short m = 1);
        void reset();              // сбросить генератор, начать сначала 
        short getfirst();          // сформировать первый массив индексов    
        short getnext();           // сформировать следующий массив индексов  
        short ntx(short i);
        unsigned __int64 count() const;
    };
}