#include <stdlib.h>
#include "structmatrix.h"

typedef struct matrix
{
    double *data;
    size_t h, w;
} matrix;

/*���������� 2 �������, ��������� ��������� � ������
�� ���� ��������� 3 �������. ������ �� � ������� ���������� ���������, ���������� - �� ������� ������������
�� ������ ��������� �� ������� ��������� ��������
*/
matrix * matrix_sum(matrix *m,const matrix *x,const matrix *y)
{
    if(!m || !x || !y || m->h != x->h || m->w != x->w || m->h != y->h || m->w != y->w) return NULL;
    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            *matrix_get(m, i, j) = *matrix_constget(x, i, j) + *matrix_constget(y, i, j);
        }
    }
    return m;
}

/*� ������� m ���������� ������� x (�������� m += x)
�� ���� ��������� ������� � ������� ����� ��������� ����������, ������� ������� ����� ���������
���������� ��������� �� ������� � ������� ���� ��������� ����������
*/
matrix * matrix_add(matrix * m, const matrix * x)
{
    if(!m || !x || m->h != x->h || m->w != x->w) return NULL;
    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            *matrix_get(m, i, j) += *matrix_constget(x, i, j);
        }
    }
    return m;
}

/*��������� ������� �� ������(������������ �����)
�� ���� ��������� ��������� �� ������� � ������� ����� ������� ��������� ���������, ��������� �� ������� ������� ��������, ������
�� ������ ��������� �� ������� � ����������� ���������
*/
matrix * matrix_skalear_multi(matrix *m, matrix *x, double a)
{
    if(!m || !x) return NULL;
    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            *matrix_get(m, i, j) = *matrix_constget(x, i, j) * a;
        }
    }
    return m;
}

/*�� ������� x �������� ������� y, ��������� ��������� � m
�� ���� ��������� 3 �������. ������ �� � ������� ���������� ���������, ���������� - �� ������� ����������
�� ������ ��������� �� ������� ��������� ��������
*/
matrix * matrix_vichet(matrix *m, const matrix *x, const matrix *y)
{
    if(!m || !x || !y || m->h != x->h || m->w != x->w || m->h != y->h || m->w != y->w) return NULL;
    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            *matrix_get(m, i, j) = *matrix_constget(x, i, j) - *matrix_constget(y, i, j);
        }
    }
    return m;
}

/*�� ������� m �������� ������� x (�������� m -= x)
�� ���� ��������� ������� � ������� ����� ��������� ��������, ������� ������� ����� ��������
���������� ��������� �� ������� � ������� ���� ��������� ���������
*/
matrix * matrix_add_vichet(matrix * m, const matrix * x)
{
    if(!m || !x || m->h != x->h || m->w != x->w) return NULL;
    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            *matrix_get(m, i, j) -= *matrix_constget(x, i, j);
        }
    }
    return m;
}

/*��������� ������� x �� y
�� ����� ��������� �� ������� ��� ������ ���������� ���������
�� ������ ��������� �� ������� � ����������� ���������
*/
matrix * matrix_multi(matrix * m, const matrix * x, const matrix * y)
{
    if(!m || !x || !y || x->w != y->h) return NULL;
    if(m->w != x->w || m->h != y->h) m = matrix_resize(m, x->h, y->w);

    double h;

    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            h = 0;
            for (size_t k = 0; k < x->w; ++k)
            {
                h += *matrix_constget(x, i, k) * *matrix_constget(y, k, j);
            }
            *matrix_get(m, i, j) = h;
        }
    }
    return m;
}

/*������� m �������� �� ������� x (�������� m *= x)
�� ���� ��������� ������� � ������� ����� ��������� ����������-���������, ������� �� ������� ����� ��������
���������� ��������� �� ������� � ������� ���� ��������� ����������-���������
*/
matrix * matrix_add_multi(matrix * m, const matrix * x)
{
    if(!m || !x || m->w != x->h) return NULL;
    matrix * y;
    y = matrix_alloc(m->h, x->w);
    y = matrix_multi(y, m, x);
    if(m->h != y->h || m->w != y->w) m = matrix_resize(m, y->h, y->w);
    m = matrix_assign(m, y);
    matrix_free(y);//////////////����������� ������ ������
    return m;
}

/*������������� �������
�� ���� ��������� ��������� �� �������, ������� ����� ������������������
�� ������ ��������� �� ����������������� �������*/
matrix * matrix_transport(matrix * m)
{
    if(!m) return NULL;
    matrix * y;
    y = matrix_alloc(m->w, m->h);
    for (size_t i = 0; i < m->w; ++i )
    {
        for (size_t j = 0; j < m->h; ++j)
        {
            *matrix_get(y, i, j) = *matrix_get(m, j, i);
        }
    }
    if(m->h != m->w) m = matrix_resize(m, y->h, y->w);
    m = matrix_assign(m, y);
    matrix_free(y);///////////////////// ����������� ������ ������
    return m;
}

/*�������� ������ ������� �� �����
�� ����� ��������� �� �������, ������������ �����, ����� ������
���������� ��������� �� �������
*/
matrix * matrix_str_multi_cislo(matrix * m, double a, size_t i)
{
    if(!m || i >= m->h) return NULL;
    for(size_t j = 0; j < m->w; ++j)
    {
        *matrix_get(m, i, j) *= a;
    }
    return m;
}

/*������ ������� ��� ������
�� ���� ��������� �� �������, ������ �����, ������� ����� �������� �������
���������� ��������� �� �������
*/
matrix * matrix_str_swap(matrix * m, size_t i1, size_t i2)
{
    if(!m || i1 >= m->h || i2 >= m->h) return NULL;
    double k;
    for(size_t j = 0; j < m->w; ++j)
    {
        k = *matrix_get(m, i1, j);
        *matrix_get(m, i1, j) = *matrix_get(m, i2, j);
        *matrix_get(m, i2, j) = k;
    }
    return m;

}

/*� ������ i1 ��������� i2 (i1 += i2)
�� ���� ��������� �� �������, ������ �����,
���������� ��������� �� �������
*/
matrix * matrix_str_sum(matrix * m, size_t i1, size_t i2)
{
    if(!m || i1 >= m->h || i2 >= m->h) return NULL;
    for(size_t j = 0; j < m->w; ++j)
    {
        *matrix_get(m, i1, j) += *matrix_get(m, i2, j);
    }
    return m;

}

/*� ������ i1 ��������� i2 ���������� �� ����������� ����� �(i1 += i2 * �)
�� ���� ��������� �� �������, ������ �����,
���������� ��������� �� �������
*/
matrix * matrix_str_mainsum(matrix * m, size_t i1, size_t i2, double a)
{
    if(!m || i1 >= m->h || i2 >= m->h) return NULL;
    for(size_t j = 0; j < m->w; ++j)
    {
        *matrix_get(m, i1, j) += *matrix_get(m, i2, j) * a;
    }
    return m;

}
