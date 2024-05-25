#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct matrix
{
    double *data;
    size_t h, w;
} matrix;

/*�������� �������
���������� ��������� �� ���������
�� ���� ��������� ������ � ������ �������
*/
matrix * matrix_alloc(size_t h, size_t w)
{
    matrix *m = malloc(sizeof(matrix));
    if(!m) return NULL;
    m->data = malloc(sizeof(double) * h * w);

    if(!m->data)
    {
        free(m);
        return NULL;
    }
    m->h = h;
    m->w = w;
    return m;
}

/*������������ ������
�� ���� ��������� ��������� �� ��������� �������
*/
void matrix_free(matrix *m)
{
    free(m->data);
    free(m);
}

/*������ � ��������� ������� (������������� ������)
�� ���� ��������� ��������� �� ��������� �������, ������� �������� � �������� ������� �������� ������ (i - ������, j - �������)
���������� ��������� �� ���� �������
*/
double *matrix_get(matrix *m, size_t i, size_t j)
{
    if(!m->data || i >= m->h || j >= m->w) return NULL;
    return m->data + m->w * i + j;
}

/*������ � ��������� ������� (����������� ������)
�� ���� ��������� ��������� �� ��������� �������, ������� �������� � �������� ������� �������� ������ (i - ������, j - �������)
���������� ��������� �� ���� �������
*/
double *matrix_constget(const matrix *m, size_t i, size_t j)
{
    if(!m->data || i > m->h || j > m->w) return NULL;
    return m->data + m->w * i + j;
}

/*�������� �������
�� ���� ��������� ��������� �� �������, ������� ����� �����������
���������� ��������� �� ������������� ������� ��� NULL � ������ �������
*/
matrix * matrix_copy(const matrix * m)
{
    if(!m) return NULL;
    matrix *m_copy;
    m_copy = matrix_alloc(m->h, m->w);
    if(!m_copy) return NULL;
    memcpy(m_copy->data, m->data, sizeof(double) * m->h * m->w);
    return m_copy;
}

/*�������������� ������� ������
�� ���� ��������� ��������� �� �������
�������� ������ - ��������� �� ������������������� �������
*/
matrix * matrix_init(matrix * m)
{
    if(!m) return NULL;
    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            *matrix_get(m, i, j) = 0;
        }
    }
    return m;
}

/*���� �������� �������
�� ���� ��������� ��������� �� �������
�������� ������ - ��������� �� ��� �� �������
*/
matrix * matrix_vvod(matrix * m)
{
    if(!m) return NULL;
    double *x;
    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            x = matrix_get(m, i, j);
            scanf("%lf", x);
        }
    }

    return m;
}

/*����� �������� �������
�� ���� ��������� ��������� �� �������
*/
void matrix_vivod(matrix * m)
{
    double *x;
    for (size_t i = 0; i < m->h; ++i )
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            x = matrix_get(m, i, j);
            printf("%lf ", *x);
        }
        printf("\n");
    }
}

/*������� ������� �������
�� ���� ��������� ������ �� ������ �������
���������� ��������� �� ��� ������� ���� NULL � ������ �������
*/
matrix * matrix_zero_alloc(size_t h, size_t w)
{
    matrix * zero;
    zero = matrix_alloc(h, w);
    zero = matrix_init(zero);
    return zero;
}

/*����������� ������� � ���������
�� ���� ��������� ������ �� ������ �������
���������� ��������� �� ��� ������� ���� NULL � ������ �������
*/
matrix * matrix_edenich(matrix * m)
{
    if(!m || m->h != m->w) return NULL;
    for(size_t i = 0; i < m->h; ++i)
    {
        for(size_t j = 0; j < m->w; ++j)
        {
            if(j == i) *matrix_get(m, i, j) = 1;
            else *matrix_get(m, i, j) = 0;
        }
    }
    return m;
}

/*������� ��������� �������
�� ���� ��������� ������ � ������ �������
���������� ��������� �� ��� ������� ���� NULL � ������ �������
*/
matrix * matrix_edenich_alloc(size_t h, size_t w)
{
    matrix * edenich;
    edenich = matrix_alloc(h, w);
    edenich = matrix_edenich(edenich);
    return edenich;
}

/*�������� ������ �������
�� ���� ��������� �������, ��� ������ ����� ��������, ����� ������, ����� ������
�� ������ - ��������� �� ���������� �������
*/
matrix * matrix_resize(matrix *m, size_t new_h, size_t new_w)
{
    matrix_free(m);
    m = matrix_alloc(new_h, new_w);
    if(!m) return NULL;
    return m;
}

/*����������� ����� ������� �������� ������
�� ���� ��������� ��������� �� �������. (� ������� ����� ��������� � �� ��� �������� ����� ���������)
�� ������ ��������� �� ������� � ������� ����������� ������������
*/
matrix * matrix_assign(matrix * m1, const matrix * m2)
{
    if(!m1 || !m2 || m1->h != m2->h || m1->w != m2->w) return NULL;

    for (size_t i = 0; i < m2->h; ++i )
    {
        for (size_t j = 0; j < m2->w; ++j)
        {
            *matrix_get(m1, i, j) = *matrix_constget(m2, i, j);///////////����������� ������ ������
        }
    }
    return m1;
}
