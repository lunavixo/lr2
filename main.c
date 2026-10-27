#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Похибка повинна бути в межах 0.00001 ≤ err ≤ 0.001
#define MAX_INTEGRATION_ERROR 0.000017

void part1();
void part2();
double f(double x);
double integrLeftSquareMethod(double (*f)(double), unsigned int n, double a, double b);
double integrRightSquareMethod(double (*f)(double), unsigned int n, double a, double b);
double integrTrapezoidMethod(double (*f)(double), unsigned int n, double a, double b);
double integrParabolaMethod(double (*f)(double), unsigned int n, double a, double b);
void insertColumn(double source[3], double destination[3][3], unsigned int column);
double getIntgr3PointParabola(double points[3][2], double start, double end);
void copyMatrix(double source[3][3], double destination[3][3]);
double det(double matrix[3][3]);
void printMatrix(double matrix[3][3]);
void pressEnterToContinue();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("cls");

    printf("Лотоцький Назар РС-зп61\n");
    printf("Лабораторна робота №2\n\n");

    printf("Оберіть частину програми для виконання\n"
           "1-Частина перша. Реалізація оператору розгалуження\n"
           "2-Частина друга. Обчислення визначеного інтегралу\n"
           "інше число - за умовчуванням 1 та 2-га послідовно: ");
    int t = 0;
    scanf("%d", &t);
    switch(t)
    {
    case 1:
        part1();
        break;
    case 2:
        part2();
        break;
    default:
        part1();
        part2();
        break;
    }

    return 0;
}

//Перша частина лабораторної роботи
void part1()
{
    system("cls");

    printf("Частина перша. Реалізація оператору розгалуження\n");
    printf("Варіант 2:\n");
    printf("    / x-1\n"
           "    | ---, 0 ≤ x < 5\n"
           "    | x+1\n"
           "    | \n"
           "    | 5x+10, 5 ≤ x < 25\n"
           "    |   x\n"
           "y = { ------ - 4x³, 100 ≤ x < 125\n"
           "    |   ____\n"
           "    | \\/x+x²\n"
           "    | \n"
           "    | x\n"
           "    | -- + 4, для усіх інших значень x\n"
           "    \\ 10\n\n");

    printf("Введіть аргумент x для обчислення залежної зміни y: ");

    double x, y;
    scanf("%lf", &x);

    //Обчислення залежної зміни y
    if(0 <= x && x < 5) y = (x - 1) / (x + 1);
    else if(5 <= x && x < 25) y = 5 * x + 10;
    else if(100 <= x && x < 125) y = x / sqrt(x + pow(x, 2)) - 4 * pow(x, 3);
    else y = x / 10 + 4;

    printf("Обчислена залежна зміна y: %.2lf\n", y);
    pressEnterToContinue();
}

//Друга частина лабораторної роботи
void part2()
{
    system("cls");

    printf("Частина друга. Обчислення визначеного інтегралу\n");
    printf("Варіант 2:\n");
    printf(" 1\n"
           " /  xdx\n"
           " | ------\n"
           " / (x+2)²\n"
           " 0\n");

    double results[60] =
    {
         integrLeftSquareMethod(f, 10, 0, 1),
         integrLeftSquareMethod(f, 12, 0, 1),
         integrLeftSquareMethod(f, 10, 0, 1) - integrLeftSquareMethod(f, 12, 0, 1),

         integrRightSquareMethod(f, 10, 0, 1),
         integrRightSquareMethod(f, 12, 0, 1),
         integrRightSquareMethod(f, 10, 0, 1) - integrRightSquareMethod(f, 12, 0, 1),

         integrTrapezoidMethod(f, 10, 0, 1),
         integrTrapezoidMethod(f, 12, 0, 1),
         integrTrapezoidMethod(f, 10, 0, 1) - integrTrapezoidMethod(f, 12, 0, 1),

         integrParabolaMethod(f, 10, 0, 1),
         integrParabolaMethod(f, 12, 0, 1),
         integrParabolaMethod(f, 10, 0, 1) - integrParabolaMethod(f, 12, 0, 1),


         integrLeftSquareMethod(f, 20, 0, 1),
         integrLeftSquareMethod(f, 22, 0, 1),
         integrLeftSquareMethod(f, 20, 0, 1) - integrLeftSquareMethod(f, 12, 0, 1),

         integrRightSquareMethod(f, 20, 0, 1),
         integrRightSquareMethod(f, 22, 0, 1),
         integrRightSquareMethod(f, 20, 0, 1) - integrRightSquareMethod(f, 12, 0, 1),

         integrTrapezoidMethod(f, 20, 0, 1),
         integrTrapezoidMethod(f, 22, 0, 1),
         integrTrapezoidMethod(f, 20, 0, 1) - integrTrapezoidMethod(f, 12, 0, 1),

         integrParabolaMethod(f, 20, 0, 1),
         integrParabolaMethod(f, 22, 0, 1),
         integrParabolaMethod(f, 20, 0, 1) - integrParabolaMethod(f, 12, 0, 1),

         integrLeftSquareMethod(f, 50, 0, 1),
         integrLeftSquareMethod(f, 52, 0, 1),
         integrLeftSquareMethod(f, 50, 0, 1) - integrLeftSquareMethod(f, 12, 0, 1),

         integrRightSquareMethod(f, 50, 0, 1),
         integrRightSquareMethod(f, 52, 0, 1),
         integrRightSquareMethod(f, 50, 0, 1) - integrRightSquareMethod(f, 12, 0, 1),

         integrTrapezoidMethod(f, 50, 0, 1),
         integrTrapezoidMethod(f, 52, 0, 1),
         integrTrapezoidMethod(f, 50, 0, 1) - integrTrapezoidMethod(f, 12, 0, 1),

         integrParabolaMethod(f, 50, 0, 1),
         integrParabolaMethod(f, 52, 0, 1),
         integrParabolaMethod(f, 50, 0, 1) - integrParabolaMethod(f, 12, 0, 1),

         integrLeftSquareMethod(f, 100, 0, 1),
         integrLeftSquareMethod(f, 102, 0, 1),
         integrLeftSquareMethod(f, 100, 0, 1) - integrLeftSquareMethod(f, 102, 0, 1),

         integrRightSquareMethod(f, 100, 0, 1),
         integrRightSquareMethod(f, 102, 0, 1),
         integrRightSquareMethod(f, 100, 0, 1) - integrRightSquareMethod(f, 102, 0, 1),

         integrTrapezoidMethod(f, 100, 0, 1),
         integrTrapezoidMethod(f, 102, 0, 1),
         integrTrapezoidMethod(f, 100, 0, 1) - integrTrapezoidMethod(f, 102, 0, 1),

         integrParabolaMethod(f, 100, 0, 1),
         integrParabolaMethod(f, 102, 0, 1),
         integrParabolaMethod(f, 100, 0, 1) - integrParabolaMethod(f, 102, 0, 1),

         integrLeftSquareMethod(f, 1000, 0, 1),
         integrLeftSquareMethod(f, 1002, 0, 1),
         integrLeftSquareMethod(f, 1000, 0, 1) - integrLeftSquareMethod(f, 1002, 0, 1),

         integrRightSquareMethod(f, 1000, 0, 1),
         integrRightSquareMethod(f, 1002, 0, 1),
         integrRightSquareMethod(f, 1000, 0, 1) - integrRightSquareMethod(f, 1002, 0, 1),

         integrTrapezoidMethod(f, 1000, 0, 1),
         integrTrapezoidMethod(f, 1002, 0, 1),
         integrTrapezoidMethod(f, 1000, 0, 1) - integrTrapezoidMethod(f, 1002, 0, 1),

         integrParabolaMethod(f, 1000, 0, 1),
         integrParabolaMethod(f, 1002, 0, 1),
         integrParabolaMethod(f, 1000, 0, 1) - integrParabolaMethod(f, 1002, 0, 1),
    };

    printf("Межа помилки: %.3e\n", MAX_INTEGRATION_ERROR);
    printf("N - кількість проміжків\n");

    printf("\n                                      N = 10      N + 2 = 12         Різниця Входить в межі помилки?\n");
    printf(" Метод лівих прямокутників:  %15.7e %15.7e %15.7e %s\n", results[0], results[1], results[2], fabs(results[2]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод правих прямокутників: %15.7e %15.7e %15.7e %s\n", results[3], results[4], results[5], fabs(results[5]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод трапецій:             %15.7e %15.7e %15.7e %s\n", results[6], results[7], results[8], fabs(results[8]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод парабол:              %15.7e %15.7e %15.7e %s\n", results[9], results[10], results[11], fabs(results[11]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");

    printf("\n                                      N = 20      N + 2 = 22         Різниця Входить в межі помилки?\n");
    printf(" Метод лівих прямокутників:  %15.7e %15.7e %15.7e %s\n", results[12], results[13], results[14], fabs(results[14]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод правих прямокутників: %15.7e %15.7e %15.7e %s\n", results[15], results[16], results[17], fabs(results[17]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод трапецій:             %15.7e %15.7e %15.7e %s\n", results[18], results[19], results[20], fabs(results[20]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод парабол:              %15.7e %15.7e %15.7e %s\n", results[21], results[22], results[23], fabs(results[23]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");

    printf("\n                                      N = 50      N + 2 = 52         Різниця Входить в межі помилки?\n");
    printf(" Метод лівих прямокутників:  %15.7e %15.7e %15.7e %s\n", results[24], results[25], results[26], fabs(results[26]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод правих прямокутників: %15.7e %15.7e %15.7e %s\n", results[27], results[28], results[29], fabs(results[29]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод трапецій:             %15.7e %15.7e %15.7e %s\n", results[30], results[31], results[32], fabs(results[32]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод парабол:              %15.7e %15.7e %15.7e %s\n", results[33], results[34], results[35], fabs(results[35]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");

    printf("\n                                     N = 100     N + 2 = 102         Різниця Входить в межі помилки?\n");
    printf(" Метод лівих прямокутників:  %15.7e %15.7e %15.7e %s\n", results[36], results[37], results[38], fabs(results[38]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод правих прямокутників: %15.7e %15.7e %15.7e %s\n", results[39], results[40], results[41], fabs(results[41]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод трапецій:             %15.7e %15.7e %15.7e %s\n", results[42], results[43], results[44], fabs(results[43]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод парабол:              %15.7e %15.7e %15.7e %s\n", results[45], results[46], results[47], fabs(results[47]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");

    printf("\n                                    N = 1000    N + 2 = 1002         Різниця Входить в межі помилки?\n");
    printf(" Метод лівих прямокутників:  %15.7e %15.7e %15.7e %s\n", results[48], results[49], results[50], fabs(results[50]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод правих прямокутників: %15.7e %15.7e %15.7e %s\n", results[51], results[52], results[53], fabs(results[53]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод трапецій:             %15.7e %15.7e %15.7e %s\n", results[54], results[55], results[56], fabs(results[56]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");
    printf(" Метод парабол:              %15.7e %15.7e %15.7e %s\n", results[57], results[58], results[59], fabs(results[59]) <= MAX_INTEGRATION_ERROR ? "Так" : "Ні");

    pressEnterToContinue();
}

//Функція залежності y від x всередині інтеграла
double f(double x)
{
    return x/pow(x+2, 2);
}

//Обчислення визначеного інтеграла методом лівих прямокутників
//аргументи - функція y від x, кількість проміжків n і границі інтегрування від a до b
double integrLeftSquareMethod(double (*f)(double), unsigned int n, double a, double b)
{
    if(n == 0 || a > b)return 0.0/0.0;

    double delta = (b - a) / n;
    double sum = 0;
    for(unsigned int i = 1; i < n + 1; i++)
    {
        sum += f(a + delta * i) * delta;
    }
    return sum;
}

//Обчислення визначеного інтеграла методом правих прямокутників
//аргументи - функція y від x, кількість проміжків n і границі інтегрування від a до b
double integrRightSquareMethod(double (*f)(double), unsigned int n, double a, double b)
{
    if(n == 0 || a > b)return 0.0/0.0;

    double delta = (b - a) / n;
    double sum = 0;
    for(unsigned int i = 0; i < n; i++)
    {
        sum += f(a + delta * i) * delta;
    }
    return sum;
}

//Обчислення визначеного інтеграла методом трапецій
//аргументи - функція y від x, кількість проміжків n і границі інтегрування від a до b
double integrTrapezoidMethod(double (*f)(double), unsigned int n, double a, double b)
{
    if(n == 0 || a > b)return 0.0/0.0;

    double delta = (b - a) / n;
    double sum = 0;
    for(unsigned int i = 0; i < n; i++)
    {
        sum += (f(a + delta * i) + f(a + delta * (i+1))) / 2 * delta;
    }
    return sum;
}

//Обчислення визначеного інтеграла методом парабол
//аргументи - функція y від x, кількість проміжків n і границі інтегрування від a до b
double integrParabolaMethod(double (*f)(double), unsigned int n, double a, double b)
{
    if(n == 0 || a > b)return 0.0/0.0;

    double delta = (b - a) / n;
    double sum = 0;
    for(unsigned int i = 0; i < n; i++){
        sum += getIntgr3PointParabola(
        (double[3][2]){
            {
                (a + delta * i),
                f(a + delta * i)
            },
            {
                (a + delta * ((double)i+0.5)),
                f(a + delta * ((double)i+0.5))
            },
            {
                (a + delta * (i+1)),
                f(a + delta * (i+1))
            }
        },
        (a + delta * i),
        a + delta * (i+1));
    }

    return sum;
}

// Функція для обчислення визначених інтегралів парабол з трьох точок
/*  На кожному проміжку маємо три точки:
    x1 = (a + delta * i)                 y1 = f(x1)
    x2 = (a + delta * ((double)i+0.5))   y2 = f(x2)
    x3 = (a + delta * (i+1))             y3 = f(x3)
    Знайти параболу:

    / ax1^2 + bx1 + c = y1
    { ax2^2 + bx2 + c = y2
    \ ax3^2 + bx3 + c = y3

    / x1^2 x1 1 \   / a \   / y1 \      / x1^2 x1 1 \
    | x2^2 x2 1 | * | b | = | y2 |, A = | x2^2 x2 1 |
    \ x3^2 x3 1 /   \ c /   \ y3 /      \ x3^2 x3 1 /

   `За теоремою Гауса:

    a = det_a A / det A
    b = det_b A / det A
    c = det_c A / det A

    Та отримуємо параболу:

    f(x) = ax^2 + bx + c

    Інтеграл визначений f(x)dx = [a*x^3/3 + b*x^2/2 + cx] від start по end

    ( a * pow(end, 3) / 3 + b * pow(end, 2) / 2 + c * end ) - ( a * pow(start, 3) / 3 + b * pow(start, 2) / 2 + c * start )

    Для роботи з матрицями надалі використано двухвимірний масив, де:
           номер стовпя
           |
          \|/
           V
    points[0][0]
              ʌ
             /|\
              |
              номер рядка
    */
double getIntgr3PointParabola(double points[3][2], double start, double end)
{
    double a, b, c;
    double matrix_A[3][3] = {
        {
            pow(points[0][0], 2),
            pow(points[1][0], 2),
            pow(points[2][0], 2)
        },
        {
            points[0][0],
            points[1][0],
            points[2][0]
        },
        {
            1, 1, 1
        }
    };
    double matrix_B[3] =
    {
        points[0][1],
        points[1][1],
        points[2][1]
    };
    double matrix_temp[3][3];

    copyMatrix(matrix_A, matrix_temp);
    insertColumn(matrix_B, matrix_temp, 0);
    a = det(matrix_temp) / det(matrix_A);
    //printf("det: %.2lf\n",a);

    copyMatrix(matrix_A, matrix_temp);
    insertColumn(matrix_B, matrix_temp, 1);
    b = det(matrix_temp) / det(matrix_A);
    //printf("det: %.2lf\n",b);

    copyMatrix(matrix_A, matrix_temp);
    insertColumn(matrix_B, matrix_temp, 2);
    c = det(matrix_temp) / det(matrix_A);
    //printf("det: %.2lf\n",c);

    return ( a * pow(end, 3) / 3 + b * pow(end, 2) / 2 + c * end )
    - ( a * pow(start, 3) / 3 + b * pow(start, 2) / 2 + c * start );
}

// Замінює стовпець column матриці destination вектором source
void insertColumn(double source[3], double destination[3][3], unsigned int column)
{
    if(column > 2)column = 2;
    for(int i = 0; i < 3; i++){
        destination[column][i] = source[i];
    }
    //printf("\ninsert\n");
    //printMatrix(destination);
}

// Копіює матрицю souse в destination
void copyMatrix(double source[3][3], double destination[3][3])
{
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            destination[i][j] = source[i][j];
        }
    }
    //printf("\ncopy\n");
    //printMatrix(destination);
}

// Обчислює детермінант матриці
double det(double matrix[3][3])
{
    return matrix[0][0] * matrix[1][1] * matrix[2][2]
    + matrix[1][0] * matrix[2][1] * matrix[0][2]
    + matrix[2][0] * matrix[0][1] * matrix[1][2]
    - matrix[2][0] * matrix[1][1] * matrix[0][2]
    - matrix[1][0] * matrix[0][1] * matrix[2][2]
    - matrix[0][0] * matrix[2][1] * matrix[1][2];
}

//Очікує Enter від користувача щоб продовжити
void pressEnterToContinue()
{
    printf("\nНатисніть Enter щоб продовжити...");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    getchar();
}
void printMatrix(double matrix[3][3])
{
    printf("\n%.2lf %.2lf %.2lf\n"
           "%.2lf %.2lf %.2lf\n"
           "%.2lf %.2lf %.2lf\n",
           matrix[0][0], matrix[1][0], matrix[2][0],
           matrix[0][1], matrix[1][1], matrix[2][1],
           matrix[0][2], matrix[1][2], matrix[2][2]);
}
