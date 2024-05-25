#include <stdio.h>
#include <math.h>
#include "operationsmatrix.h"
#include "structmatrix.h"

typedef struct matrix
{
    double *data;
    size_t h, w;
} matrix;

/*Вычисляет норму матрицы
На вход поступает указатель на матрицу
На выходе вещественнре неотрицательное число - норма
*/
double Norma(matrix  * x)
{
    size_t i = 0, j = 0;
    double sum = 0, norma = 0;

    for(j = 0; j < x->w; ++j)
    {
        norma += fabs(*matrix_constget(x, i, j));
    }

    for( i = 1; i < x->h; ++i)
    {
        for(j = 0; j < x->w; ++j)
        {
            sum += fabs(*matrix_constget(x, i, j));
        }
        if(sum > norma) norma = sum;
        sum = 0;
    }

    return norma;

}

