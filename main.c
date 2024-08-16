#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double discriminant(double a, double b, double c); // прототип функции, которая считает дискриминант
                                                    // квадратного уравнения ax^2 + bx + c = 0
double finalexp(int ine, int znake, int ee, double num); // функция, которая записывает число num в экспоненциальную форму

void mainmenu(char * u); // меню с характеристиками каждого режима работы и его выбором

void input(double koef[], int * err); // ввод пользователем уравнения. первый аргумент - массив с коэффициентами уравнения, второй - код ошибки

void error(int err); // вывод ошибок в соответствии с её кодом

int main()
{
    double a, b, c;// переменные для хранения данных о коэффициентах квадратного уравнения
    double d; // переменная для зранения значения дискриминанта
    int ac; // переменная для хранения точности
    char v; // переменная для ввода решений пользователя
    double koef[3]; // массив для хранения коэффициента одночлена iой степени
    int err = 0; // переменная для отслеживания кода ошибки ввода

    beg: mainmenu(&v); // вывод главного меню и выбор режима работы
    koef[0] = koef[1] = koef[2] = 0.0;
    err = 0;
    if (v == 'a' || v == 'а'){ // простой режим
        printf("Введите ваши уравнения. Для выхода в меню напишите \"q\"\n");
        while (err != -1){
            //err = 0;
            koef[0] = koef[1] = koef[2] = 0.0; // обнуление коэффициента при перезапуске
            input(koef, &err); // ввод уравнения
            if (err == 0 || err == 1 || err == 2){ // вывод корней, если уравнение квадратное, линейное или не зависит от неизвестной
                a = koef[2];
                b = koef[1];
                c = koef[0];
                d = discriminant(a, b, c);
                if (fabs(a) > 1e-37){
                    if (fabs(d) < 1e-37)
                        printf("x1 = x2 = %lf\n", -b/(2.0 * a));
                    else if (d >= 0){
                        d = sqrt(d);
                        printf("x1 = %lf, x2 = %lf\n", (-b + d) / (2 * a), (-b - d) / (2 * a));
                    }
                    else{
                        d = sqrt(-d);
                        printf("x1 = %lf + %lf * i, x2 = %lf + %lf * i\n",  -b / (2.0 * a), d / (2.0 * a), -b / (2.0 * a), d / (2.0 * a));
                    }
                }
                else if (fabs(b) > 1e-37){
                    printf("Уравнение линейно. x = %lf\n", -c/b);
                }
                else if (fabs(c) > 1e-37)
                    printf("Уравнение НЕ имеет решений\n");
                else
                    printf("Уравнение имеет бесконечное количество решений\n");
            }
            else{ // вывод ошибки при неверном вводе уравненении
                error(err);
            }
        }
        printf("\n");
        goto beg;
    }
    else if (v == 'b'){ // детальный режим
        printf("Введите ваше уравнение или напишите \"q\" для выхода в главное меню\nУчитывайте, что программа не умеет решать уранвения со скобками\n");
        printf("Программа игнорирует пробелы.\n");
        printf("Для записи квадрата, используйте \"xx\"\n");
        input(koef, &err); // ввод уравнения
        if (err == -1){ // возвращение в главное меню
            printf("\n");
            goto beg;
        }
        if (err < 0){ // вывод ошибки в случае её возникновения
            error(err);
            return 0;
        }
        a = koef[2];
        b = koef[1];
        c = koef[0];
        printf("Введите необходимую точность: ");
        ac = 0;
        while ((v = getchar()) != '\n'){ // считывание точности
            if ((v < '0' || v > '9') || (ac == 0 && v == '0')){
                while ((v = getchar()) != '\n')
                    continue;
                ac = 0;
                printf("Неверный ввод, попробуйте ещё раз: ");
            }
            else
                ac = ac*10 + v - '0';
        }
        if (fabs(a)>1e-37){ // вывод корней уравнения
            d = discriminant(a, b, c);
            if (fabs(d) < 1e-37)
                printf("x1 = x2 = %lf\n", -b/(2.0 * a));
            if (d < 0)
            {
                d = sqrt(fabs(d));
                printf("Первый корень уравнения: %.*lf + %.*lf * i\n", ac, -b / (2.0 * a), ac, d / (2.0 * a));
                printf("Второй корень уравнения: %.*lf - %.*lf * i\n", ac, -b / (2.0 * a), ac, d / (2.0 * a));
            }
            else
            {
                d = sqrt(d);
                printf("Первый корень уравнения: %.*lf\n", ac, (-b + d) / (2 * a));
                printf("Второй корень уравнения: %.*lf\n", ac, (-b - d) / (2 * a));
            }
        }
        else if (fabs(b) > 1e-37){
            printf("Уравнение линейно. x = %lf\n", -c/b);
        }
        else if (fabs(c) > 1e-37)
            printf("Уравнение НЕ имеет решений\n");
        else
            printf("Уравнение имеет бесконечное количество решений\n");
        printf("Спасибо, что воспользовались программой. До свидания!");

        return 0;
    }
    if (v == 'q'){ // выход из программы
        printf("Спасибо, что воспользовались программой. До свидания!");

        return 0;
    }
}

double discriminant(double a, double b, double c)
{
    return b * b - 4.0 * a * c;
}
double finalexp(int ine, int znake, int ee, double num)
{
    if (ine){ // проверка была ли экспоненциальная часть
        if (znake == +1){ // случай положительной части
            for(;ee>0; ee--){
                num *= 10.0;
            }
        }
        else{ // случай отрицательной части
            for(;ee>0; ee--){
                num /= 10.0;
            }
        }
    }
    return num;
}

void mainmenu(char * u)
{
    printf("Решатор квадратных уравнений\n");
    printf("Программа имеет два режима работы:\n");
    printf("Простой режим - режим с минимальным выводом и возможностью бесконечного ввода уравнений\n");
    printf("Детальный режим - режим, который максимально инструктирует вас, но позволяет ввести уравнение лишь один раз\n");
    printf("(Для первого пользования рекомендуется использовать детальный режим)\n");
    printf("Выберите режим работы:\n");
    printf("a - простой режим\n");
    printf("b - детальный режим\n");
    printf("Или напишите \"q\" для выхода из программы\n");

    // выбор пользователя. засчитывается только конкретная буква
    *u = getchar();
    while (getchar() != '\n' || (*u != 'a' && *u != 'b' && *u != 'а' && *u != 'q')){
        printf("Неправильный ввод, попробуйте снова\n");
        while (getchar() != '\n')
            continue;
        *u = getchar();
    }
}
void input(double koef[], int * err)
{
    char v; // переменная для ввода решений пользователя
    int znak; // переменная для хранения знака одночлена
    int innum; // переменная для отслеживания внутри ли мы числа
    double num; // переменная для хранения числа
    int pow; // переменная для хранения степени одночлена
    int indrob; // переменная для хранения внутри ли мы дроби
    int drob; // переменная для хранения номера числа после запятой
    int drobc; // переменная для хранения оставшихся делений на 10
    int ee; // переменная для хранения экспоненциальной части числа
    int ine; // переменная для отслеживания внутри ли мы экс. части
    int prev; // переменная для хранения предыдущего считанного символа
    int znake; // переменная для хранения знака экс. части
    double vd; // переменная для хранения дроби
    double mnum; // переменная для хранения предыдущего значения num для операций * и /
    int m; // переменная для хранения использовалось ли умножение в многочлене. m=0 - нет
    //m=1 - последнее действие - умножение, m = -1 - последнее действие - деление
    int ifnum; // переменная для отслеживания был ли ввод числа
    *err = 0;
    pow = innum = ifnum = num = ee = ine = drob = indrob = prev = m = mnum = 0;
    znak = +1;
    while ((v = getchar()) != '='){ // считывание левой части уравнения
        if (v == 'q'){ // считывание возвращения в главное меню
            if (getchar() == '\n'){
                *err = -1;
                return;
            }
            else{
                while (getchar() != '\n')
                    continue;
                *err = -2;
                return;
            }
        }
        // считывание цифр
        else if (v >= '0' && v <= '9'){
            if (ine)
                ee = ee * 10 + v - '0';
            else{
                if (indrob){
                    vd = v - '0';
                    for(drobc = drob; drobc > 0; drobc--)
                        vd = vd / 10.0;
                    num += vd;
                    drob++;
                }
                else{
                    num = num * 10 + v - '0';
                    ifnum = 1;
                }
            }
        }
        // считывание начала дробной части
        else if ((v == '.') || (v == ',')){
            indrob = 1;
            drob = 1;
        }
        // считывание начала экспоненциальной части
        else if (v == 'e' || v == 'E' || v == 'е' || v == 'Е'){
            ine = 1;
            prev = 'e';
            znake = +1;
        }
        else if (v == '*'){ // считывание умножения
            num = finalexp(ine, znake, ee, num);
            ine = ee = 0;
            indrob = 0;
            mnum *= num;
            if (m == 0)
                mnum = num;
            m = 1;
            num = 0;
        }
        else if (v == '/'){ // считывание деления
            num = finalexp(ine, znake, ee, num);
            ine = ee = 0;
            indrob = 0;
            mnum /= (num*1.0);
            if (m == 0)
                mnum = num;
            m = -1;
            num = 0;
        }
        // считывание неизвестных
        else if (v == 'x'){
            if (innum)
                pow += 1;
            else
                pow = 1;
            innum = 1;
        }
        // считывание знаков операций + и -
        else if (v == '+'){
            if (prev == 'e'){ // определение знака экспоненты в случае записи
                znake = +1;
                prev = 0;
            }
            else{
                num = finalexp(ine, znake, ee, num); // приведение числа в готовый вид для записи
                if (!ifnum && fabs(num)<1e-36)
                    num = 1.0;
                if (m == 0) // запись числа в коэффициент в соответствии с последней операцией умножения/деления
                    koef[pow] += znak * num;
                else if (m == 1)
                    koef[pow] += znak * num*mnum;
                else if (m == -1)
                    koef[pow] += znak * mnum/num;
                if (*err < pow) // запись максимальной степени выражения
                    *err = pow;
                pow = innum = num = ee = ine = drob = indrob = prev = m = mnum = 0; // обнуление переменных
                znak = +1;
            }
        }
        else if (v == '-'){
            if (prev == 'e'){
                znake = -1;
                prev = 0;
            }
            else{
                num = finalexp(ine, znake, ee, num);
                if (!ifnum && fabs(num)<1e-36)
                    num = 1.0;
                if (m == 0)
                    koef[pow] += znak * num;
                else if (m == 1)
                    koef[pow] += znak * num * mnum;
                else if (m == -1)
                    koef[pow] += znak * mnum / num;
                if (*err < pow)
                    *err = pow;
                pow = innum = num = ee = ine = drob = indrob = prev = m = mnum = 0;
                znak = -1;
            }
        }
        else if (v == ' '); // игнорирование пробела
        else{ // ошибка в случае ввода постороннего символа
            *err = -2;
            while (getchar() != '\n')
                continue;
            return;
        }
    }
    // запись одночлена, который был перед равно
    num = finalexp(ine, znake, ee, num);
    if (!ifnum && fabs(num)<1e-37)
        num = 1.0;
    if (m == 0)
        koef[pow] += znak * num;
    else if (m == 1)
        koef[pow] += znak * num * mnum;
    else if (m == -1)
        koef[pow] += znak * mnum / num;
    if (*err < pow)
        *err = pow;
    pow = innum = num = ee = ine = drob = indrob = prev = m = mnum = 0;
    znak = -1;
    while ((v = getchar()) != '\n'){ // считывание правой части уравнения
        if (v >= '0' && v <= '9'){
            if (ine)
                ee = ee * 10 + v - '0';
            else{
                if (indrob){
                    vd = v - '0';
                    for(drobc = drob; drobc > 0; drobc--)
                        vd = vd / 10.0;
                    num += vd;
                    drob++;
                }
                else{
                    num = num * 10 + v - '0';
                    ifnum = 1;
                }
            }
        }
        else if ((v == '.') || (v == ',')){
            indrob = 1;
            drob = 1;
        }
        else if (v == 'e' || v == 'E' || v == 'е' || v == 'Е'){
            ine = 1;
            prev = 'e';
            znake = +1;
        }
        else if (v == 'x'){
            if (innum)
                pow = 2;
            else
                pow = 1;
            innum = 1;
        }
        else if (v == '=') // считывание повторного равно
            *err = -3;
        else if (v == '+'){
            if (prev == 'e'){
                znake = +1;
                prev = 0;
            }
            else{
                num = finalexp(ine, znake, ee, num);
                if (!ifnum && fabs(num)<1e-37)
                    num = 1.0;
                // запись в коэффициент
                if (m == 0)
                    koef[pow] += znak * num;
                else if (m == 1)
                    koef[pow] += znak * num * mnum;
                else if (m == -1)
                    koef[pow] += znak * mnum / num;
                if (*err < pow)
                    *err = pow;
                pow = innum = num = ee = ine = drob = indrob = prev = m = mnum = 0;
                znak = -1;
            }
        }
        else if (v == '-'){
            if (prev == 'e'){
                znake = -1;
                prev = 0;
            }
            else{
                // финальный вид числа num
                num = finalexp(ine, znake, ee, num);
                if (!ifnum && fabs(num)<1e-37)
                    num = 1.0;
                // запись в коэффициент
                if (m == 0)
                    koef[pow] += znak * num;
                else if (m == 1)
                    koef[pow] += znak * num * mnum;
                else if (m == -1)
                    koef[pow] += znak * mnum / num;
                if (*err < pow)
                    *err = pow;
                pow = innum = num = ee = ine = drob = indrob = prev = m = mnum = 0;
                znak = +1;
            }
        }
        else if (v == ' ');
        else{
            *err = -2;
            while (getchar() != '\n')
                continue;
            return;
        }
    }
    // запись последнего числа
    num = finalexp(ine, znake, ee, num);
    if (!ifnum && fabs(num)<1e-37)
        num = 1.0;
    if (m == 0)
        koef[pow] += znak * num;
    else if (m == 1)
        koef[pow] += znak * num * mnum;
    else if (m == -1)
        koef[pow] += znak * mnum / num;
    if (*err < pow)
        *err = pow;
}

void error(int err)
{
    if (err > 2)
        printf("ОШИБКА: Ваше уравнение - уравнение %d степени\n", err);
    if (err == -2)
        printf("ОШИБКА: В вашем уравнении имеются посторонние символы\n");
    if (err == -3)
        printf("ОШИБКА: Ваше уравнение имеет более одного знака равно\n");
}
