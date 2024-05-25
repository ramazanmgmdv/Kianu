#ifndef GAUSS_H_INCLUDED
#define GAUSS_H_INCLUDED

typedef struct matrix matrix;

/*������� �������� �������
�� ���� ��������� ��������� �� �������� ������� � ��������� �� ������� ��� ������ ����������
���������� ��������� �� �������� �������
*/
matrix * Gauss_obrtnaia(matrix * x, matrix * y);


/*������� ��������� ������� ������
�� ���� ��������� ��������� �� ������� �������������, �� ������� ��������� ������, ������� ��� ������ ���������
���������� ��������� �� ������� ������� �������
*/
matrix * Gauss_urav(matrix * m, matrix * b, matrix * x);

#endif // GAUSS_H_INCLUDED
