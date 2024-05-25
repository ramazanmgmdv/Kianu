#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structmatrix.h"
#include "operationsmatrix.h"

typedef struct matrix
{
    double *data;
    size_t h, w;
} matrix;

/*Ќаходит обратною матрицу
Ќа вход поступают указатель на исходную матрицу и указатель на матрицу дл€ записи результата
¬озвращает указатель на обратную матрицу
*/
matrix * Gauss_obrtnaia(matrix * x, matrix * y)
{
    if(!x || !y) return NULL;
    size_t j = 0, i = 0, k = 0;                                      //k - строка
    double p;                                                        //сосуд дл€ значений

    y = matrix_edenich(y);

    for(; k < x->w; ++k)
    {
        while (*matrix_constget(x, i, j) == 0 && i < x->h)           //поиск самого левого лидера
        {
            ++i;

            if(*matrix_constget(x, i, j) == 0 && i == x->h - 1)
            {
                ++j;
                i = 0;
            }
        }

        if(i != x->h)                                                           //зануление всех чисел ниже лидера
        {
            x = matrix_str_swap(x, k, i);
            y = matrix_str_swap(y, k, i);

            for(i = k + 1; i < x->h; ++i)
            {
                if(*matrix_constget(x, i, j) != 0)
                {
                    p = *matrix_constget(x, i, j);
                    matrix_str_multi_cislo(x, - *matrix_constget(x, k, j), i);
                    matrix_str_multi_cislo(y, - *matrix_constget(x, k, j), i);
                    matrix_str_mainsum(x, i, k, p);
                    matrix_str_mainsum(y, i, k, p);
                }
            }
        }
        j = k +1; i = k + 1;
    }

    if(*matrix_constget(x, x->h - 1, x->w - 1) == 0)
    {
        return NULL;
    }

     for(j = x->w - 1; j > 0; --j)
           {
               for(i = 0; i < j; ++i)                                                         //зануление чисел выше лидера
                {
                    p = *matrix_constget(x, i, j);
                    matrix_str_multi_cislo(x, - *matrix_constget(x, j, j), i);
                    matrix_str_multi_cislo(y, - *matrix_constget(x, j, j), i);
                    matrix_str_mainsum(x, i, j, p);
                    matrix_str_mainsum(y, i, j, p);
                }
           }


    for(i = 0; i < x->h; ++i)
    {
        p = *matrix_get(x, i, i);
        *matrix_get(x, i, i) /= p;
        matrix_str_multi_cislo(y, 1 / p, i);                                          //еденички на диагонали
    }
    return y;
}

/*–ешение уравнени€ методом √аусса
Ќа вход поступает указатель на матрицу коэффициентов, на матрицу свободных членов, матрица дл€ записи результта
¬озвращает указатель на матрицу решени€ уравни€
*/
matrix * Gauss_urav(matrix * m, matrix * b, matrix * x)
{
    if(!x || !m || !b) return NULL;
    size_t j = 0, i = 0, k = 0;                                      //k - строка
    double p;                                                        //сосуд дл€ значений

    for(; k < m->w; ++k)
    {
        while (*matrix_constget(m, i, j) == 0 && i < m->h)           // поиск самого левого лидера
        {
            ++i;

            if(*matrix_constget(m, i, j) == 0 && i == m->h - 1)
            {
                ++j;
                i = 0;
            }
        }
        if(i != m->h)                                                           //зануление всех чисел ниже лидера
        {
            m = matrix_str_swap(m, k, i);     b = matrix_str_swap(b, k, i);
            for(i = k + 1; i < m->h; ++i)
            {
                if(*matrix_constget(m, i, j) != 0)
                {
                    p = *matrix_constget(m, i, j);
                    matrix_str_multi_cislo(m, - *matrix_constget(m, k, j), i);   matrix_str_multi_cislo(b, - *matrix_constget(m, k, j), i);
                    matrix_str_mainsum(m, i, k, p);         matrix_str_mainsum(b, i, k, p);
                }
            }
        }
        j = k +1; i = k + 1;
    }


    if(*matrix_constget(m, m->h - 1, m->w - 1) == 0)
    {
        return NULL;
    }

     for(j = m->w - 1; j > 0; --j)
           {
               for(i = 0; i < j; ++i)                                                         //зануление чисел выше лидера
                {
                    p = *matrix_constget(m, i, j);
                    matrix_str_multi_cislo(m, - *matrix_constget(m, j, j), i);  matrix_str_multi_cislo(b, - *matrix_constget(m, j, j), i);
                    matrix_str_mainsum(m, i, j, p);   matrix_str_mainsum(b, i, j, p);
                }
           }


    for(i = 0; i < x->h; ++i)
    {
        p = *matrix_get(m, i, i);
        *matrix_get(m, i, i) /= p; *matrix_get(b, i, 0) /= p;
    }

    x = matrix_assign(x, b);

    return x;
}
