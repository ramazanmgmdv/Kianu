#ifndef MATRIXEXP_H_INCLUDED
#define MATRIXEXP_H_INCLUDED

typedef struct matrix matrix;

/*Maтричная экспонента
На вход поступают указатель на исходную матрицу, указатель на матрицу для записи результата и значение eps
на выходе указатель на матрицу результата
*/
matrix * Exp(const matrix * m, matrix * e, double eps);

#endif // MATRIXEXP_H_INCLUDED
