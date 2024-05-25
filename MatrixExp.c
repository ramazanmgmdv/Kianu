#include "structmatrix.h"
#include "operationsmatrix.h"
#include "MatrixNorma.h"
typedef struct matrix
{
    double *data;
    size_t h, w;
} matrix;

/*Maтричная экспонента
На вход поступают указатель на исходную матрицу, указатель на матрицу для записи результата и значение eps
на выходе указатель на матрицу результата
*/
matrix * Exp(const matrix * m, matrix * e, double eps)
{
    if(!m || !e || m->h != m->w) return NULL;

    if(e->h != m->h || e->w != m->w )
    {
        e = matrix_resize(e, m->h, m->w);
    }

    matrix * a_n;
    double n = 1, k;
    a_n = matrix_edenich_alloc( m->h , m->w );
    e = matrix_edenich(e);

    do
    {
        k = 1 / n;
        a_n = matrix_add_multi(a_n, m);
        a_n = matrix_skalear_multi(a_n, a_n, k);
        e = matrix_add(e, a_n);
        ++n;
     }
    while(Norma(a_n) >= eps);

    matrix_free(a_n);

    return e;
}
