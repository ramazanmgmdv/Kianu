#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct matrix
{
    double *data;
    size_t h, w;
} matrix;

/*Создание матрицы
Возвращает указатель на структуру
На вход поступают высота и ширина матрицы
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

/*Освобождение памяти
На вход поступает указатель на структуру матрицы
*/
void matrix_free(matrix *m)
{
    free(m->data);
    free(m);
}

/*Доступ к элементам матрицы (неконстантный случай)
На вход поступает указатель на структуру матрицы, индексы элемента к которому хочется получить доступ (i - строка, j - столбец)
Возвращает указатель на этот элемент
*/
double *matrix_get(matrix *m, size_t i, size_t j)
{
    if(!m->data || i >= m->h || j >= m->w) return NULL;
    return m->data + m->w * i + j;
}

/*Доступ к элементам матрицы (константный случай)
На вход поступает указатель на структуру матрицы, индексы элемента к которому хочется получить доступ (i - строка, j - столбец)
Возвращает указатель на этот элемент
*/
double *matrix_constget(const matrix *m, size_t i, size_t j)
{
    if(!m->data || i > m->h || j > m->w) return NULL;
    return m->data + m->w * i + j;
}

/*копирует матрицу
На вход поступает указатель на матрицу, которую нужно скопировать
Возвращает указатель на скопированную матрицу или NULL в случае неудачи
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

/*Инициализирует матрицу нулями
На вход поступает указалеть на матрицу
Выходные данные - указатель на иницмализированнную матрицу
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

/*Ввод значений матрицы
На вход поступает указалеть на матрицу
Выходные данные - указатель на эту же матрицу
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

/*Вывод значений матрицы
На вход поступает указалеть на матрицу
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

/*Создает нулевую матрицу
На вход поступают высота ии ширина матрицы
возвращает указатель на эту матрицу либо NULL в случае неудачи
*/
matrix * matrix_zero_alloc(size_t h, size_t w)
{
    matrix * zero;
    zero = matrix_alloc(h, w);
    zero = matrix_init(zero);
    return zero;
}

/*Преобразует матрицу в еденичную
На вход поступают высота ии ширина матрицы
возвращает указатель на эту матрицу либо NULL в случае неудачи
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

/*Создает еденичную матрицу
На вход поступают высота и ширина матрицы
возвращает указатель на эту матрицу либо NULL в случае неудачи
*/
matrix * matrix_edenich_alloc(size_t h, size_t w)
{
    matrix * edenich;
    edenich = matrix_alloc(h, w);
    edenich = matrix_edenich(edenich);
    return edenich;
}

/*изменяет размер матрицы
на вход поступает матрица, чей размер нужно изменить, новая высота, новая ширина
на выходе - указатель на измененную матрицу
*/
matrix * matrix_resize(matrix *m, size_t new_h, size_t new_w)
{
    matrix_free(m);
    m = matrix_alloc(new_h, new_w);
    if(!m) return NULL;
    return m;
}

/*присваивает одной матрице значения другой
на вход поступают указатели на матрицы. (к которой нужно присвоить и ту чьи значения нужно присвоить)
на выходе указатель на матрицу к которой происходило присваивание
*/
matrix * matrix_assign(matrix * m1, const matrix * m2)
{
    if(!m1 || !m2 || m1->h != m2->h || m1->w != m2->w) return NULL;

    for (size_t i = 0; i < m2->h; ++i )
    {
        for (size_t j = 0; j < m2->w; ++j)
        {
            *matrix_get(m1, i, j) = *matrix_constget(m2, i, j);///////////исправление утечки памяти
        }
    }
    return m1;
}
