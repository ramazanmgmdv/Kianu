#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structmatrix.h"
#include "operationsmatrix.h"
#include "Gauss.h"
#include "MatrixNorma.h"
#include "MatrixExp.h"
#include <locale.h>

int main()
{
    setlocale(0,"Russian");
    size_t deistvie;
    printf("0 - Решить систему линейных уравнений методом Гаусса\n");
    printf("1 - Найти обратную матрицу\n");
    printf("2 - Найти норму матрицы\n");
    printf("3 - Матричная экспонента\n");

    printf("\nВыберите действие: ");
    scanf("%Ix", &deistvie);

    if (deistvie == 0)
    {
        matrix *m, *b, *x;
        size_t h, w;
        printf("\nВведите количество уравнений в системе: ");
        scanf("%Ix", &h);
        w = h;
        m = matrix_alloc(h, w);
        b = matrix_alloc(h, 1);
        x = matrix_alloc(h, 1);

        printf("\nВведите матрицу коэффицентов: ");
        m = matrix_vvod(m);

        printf("\nВведите матрицу свободных членов: ");
        b = matrix_vvod(b);

        x = Gauss_urav(m, b, x);

        if(!x)
        {
            printf("\nМатрица не обратима");
        }
        else
        {
            printf("\nРешение системы:\n");
            matrix_vivod(x);
        }
        matrix_free(m);
        matrix_free(x);
        matrix_free(b);
    }

    else if(deistvie == 1)
    {
        matrix *y, *x, *x_1, *ed;
        size_t h, w;
        printf("\nВведите размер квадратной матрицы: ");
        scanf("%Ix", &h);
        w = h;
        y = matrix_alloc(h, w);
        x = matrix_alloc(h, w);
       // x_1 = matrix_alloc(h, w);
        ed = matrix_alloc(h, w);


        printf("\nВведите элементы матрицы: ");
        x = matrix_vvod(x);
        x_1 = matrix_copy(x);
         matrix_vivod(x_1);
        y = Gauss_obrtnaia(x, y);

        if(!y) printf("\nМатрица не обратима");
        else
        {
            printf("\nОбратная матрица:\n");
            matrix_vivod(y);

            ed = matrix_multi(ed, x_1, y);
            printf("\nПроверка:\n");
            matrix_vivod(ed);

        }
        matrix_free(x);
        matrix_free(y);
        matrix_free(x_1);
        matrix_free(ed);
    }

    else if(deistvie == 2)
    {
        double norma;
        matrix *x;
        size_t h, w;
        printf("\nВведите размер матрицы: ");
        scanf("%Ix%IX", &h, &w);

        x = matrix_alloc(h, w);
        printf("\nВведите элементы матрицы: ");
        x = matrix_vvod(x);

        norma = Norma(x);
        printf("\nНорма матрицы равна: %lf", norma);

        matrix_free(x);
    }

    else if(deistvie == 3)
    {
        double eps;
        matrix *m, *e;
        size_t h, w;
        printf("\nВведите размер квадратной матрицы: ");
        scanf("%Ix", &h);
        w = h;
        e = matrix_alloc(h, w);
        m = matrix_alloc(h, w);

        printf("\nВведите элементы матрицы: ");
        m = matrix_vvod(m);

        printf("\nВведите значение eps: ");
        scanf("%lf", &eps);

        e = Exp(m, e, eps);
        printf("\nМатричная экспонента:\n");
        matrix_vivod(e);

        matrix_free(e);
        matrix_free(m);
    }

    else exit(1);

    return 0;
}
