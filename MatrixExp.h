#ifndef MATRIXEXP_H_INCLUDED
#define MATRIXEXP_H_INCLUDED

typedef struct matrix matrix;

/*Ma������� ����������
�� ���� ��������� ��������� �� �������� �������, ��������� �� ������� ��� ������ ���������� � �������� eps
�� ������ ��������� �� ������� ����������
*/
matrix * Exp(const matrix * m, matrix * e, double eps);

#endif // MATRIXEXP_H_INCLUDED
