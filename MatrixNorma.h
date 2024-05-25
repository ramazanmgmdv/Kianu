#ifndef MATRIXNORMA_H_INCLUDED
#define MATRIXNORMA_H_INCLUDED

typedef struct matrix matrix;

/*Вычисляет норму матрицы
На вход поступает указатель на матрицу
На выходе вещественнре неотрицательное число - норма
*/
double Norma(matrix  * x);

#endif // MATRIXNORMA_H_INCLUDED
