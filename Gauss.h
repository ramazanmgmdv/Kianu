#ifndef GAUSS_H_INCLUDED
#define GAUSS_H_INCLUDED

typedef struct matrix matrix;

/*Находит обратною матрицу
На вход поступают указатель на исходную матрицу и указатель на матрицу для записи результата
Возвращает указатель на обраьную матрицу
*/
matrix * Gauss_obrtnaia(matrix * x, matrix * y);


/*Решение уравнения методом Гаусса
На вход поступает указатель на матрицу коэффициентов, на матрицу свободных членов, матрица для записи результта
Возвращает указатель на матрицу решения уравния
*/
matrix * Gauss_urav(matrix * m, matrix * b, matrix * x);

#endif // GAUSS_H_INCLUDED
