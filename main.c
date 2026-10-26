#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void part1();
void part2();
void pressEnterToContinue();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("cls");

    printf("Лотоцький Назар РС-зп61\т\n");
    printf("Лабораторна робота №2\n\n");

    printf("Оберіть частину програми для виконання\n"
           "1-Частина перша. Реалізація оператору розгалуження\n"
           "2-Частина друга. Обчислення визначеного інтегралу\n"
           "інше число - за умовчуванням 1 та 2-га послідовно: ");
    int t = 0;
    scanf("%d", &t);
    switch(t){
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

void part1(){
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
    if(0 <= x && x <5) y = (x-1)/(x+1);
    else if(5 <= x && x < 25) 5*x+10;
    else if(100 <= x && x < 125) x/sqrt(x+pow(x,2))-4*pow(x,3);
    else x/10 + 4;

    printf("Обчислена залежна зміна y: %.2lf\n", y);
    pressEnterToContinue();
}
void part2(){
    system("cls");

    printf("Частина друга. Обчислення визначеного інтегралу\n");
    printf("Варіант 2:\n");
    printf(" 1\n"
           " /  xdx\n"
           " | ------\n"
           " / (x+2)²\n"
           " 0\n");

    pressEnterToContinue();
}

//Очікує Enter від користувача щоб продовжити
void pressEnterToContinue() {
    printf("\nНатисніть Enter щоб продовжити...");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    getchar();
}
