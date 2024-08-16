#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double discriminant(double a, double b, double c); // �������� �������, ������� ������� ������������
                                                    // ����������� ��������� ax^2 + bx + c = 0
double finalexp(int ine, int znake, int ee, double num); // �������, ������� ���������� ����� num � ���������������� �����

void mainmenu(char * u); // ���� � ���������������� ������� ������ ������ � ��� �������

void input(double koef[], int * err); // ���� ������������� ���������. ������ �������� - ������ � �������������� ���������, ������ - ��� ������

void error(int err); // ����� ������ � ������������ � � �����

int main()
{
    double a, b, c;// ���������� ��� �������� ������ � ������������� ����������� ���������
    double d; // ���������� ��� �������� �������� �������������
    int ac; // ���������� ��� �������� ��������
    char v; // ���������� ��� ����� ������� ������������
    double koef[3]; // ������ ��� �������� ������������ ��������� i�� �������
    int err = 0; // ���������� ��� ������������ ���� ������ �����

    beg: mainmenu(&v); // ����� �������� ���� � ����� ������ ������
    koef[0] = koef[1] = koef[2] = 0.0;
    err = 0;
    if (v == 'a' || v == '�'){ // ������� �����
        printf("������� ���� ���������. ��� ������ � ���� �������� \"q\"\n");
        while (err != -1){
            //err = 0;
            koef[0] = koef[1] = koef[2] = 0.0; // ��������� ������������ ��� �����������
            input(koef, &err); // ���� ���������
            if (err == 0 || err == 1 || err == 2){ // ����� ������, ���� ��������� ����������, �������� ��� �� ������� �� �����������
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
                    printf("��������� �������. x = %lf\n", -c/b);
                }
                else if (fabs(c) > 1e-37)
                    printf("��������� �� ����� �������\n");
                else
                    printf("��������� ����� ����������� ���������� �������\n");
            }
            else{ // ����� ������ ��� �������� ����� �����������
                error(err);
            }
        }
        printf("\n");
        goto beg;
    }
    else if (v == 'b'){ // ��������� �����
        printf("������� ���� ��������� ��� �������� \"q\" ��� ������ � ������� ����\n����������, ��� ��������� �� ����� ������ ��������� �� ��������\n");
        printf("��������� ���������� �������.\n");
        printf("��� ������ ��������, ����������� \"xx\"\n");
        input(koef, &err); // ���� ���������
        if (err == -1){ // ����������� � ������� ����
            printf("\n");
            goto beg;
        }
        if (err < 0){ // ����� ������ � ������ � �������������
            error(err);
            return 0;
        }
        a = koef[2];
        b = koef[1];
        c = koef[0];
        printf("������� ����������� ��������: ");
        ac = 0;
        while ((v = getchar()) != '\n'){ // ���������� ��������
            if ((v < '0' || v > '9') || (ac == 0 && v == '0')){
                while ((v = getchar()) != '\n')
                    continue;
                ac = 0;
                printf("�������� ����, ���������� ��� ���: ");
            }
            else
                ac = ac*10 + v - '0';
        }
        if (fabs(a)>1e-37){ // ����� ������ ���������
            d = discriminant(a, b, c);
            if (fabs(d) < 1e-37)
                printf("x1 = x2 = %lf\n", -b/(2.0 * a));
            if (d < 0)
            {
                d = sqrt(fabs(d));
                printf("������ ������ ���������: %.*lf + %.*lf * i\n", ac, -b / (2.0 * a), ac, d / (2.0 * a));
                printf("������ ������ ���������: %.*lf - %.*lf * i\n", ac, -b / (2.0 * a), ac, d / (2.0 * a));
            }
            else
            {
                d = sqrt(d);
                printf("������ ������ ���������: %.*lf\n", ac, (-b + d) / (2 * a));
                printf("������ ������ ���������: %.*lf\n", ac, (-b - d) / (2 * a));
            }
        }
        else if (fabs(b) > 1e-37){
            printf("��������� �������. x = %lf\n", -c/b);
        }
        else if (fabs(c) > 1e-37)
            printf("��������� �� ����� �������\n");
        else
            printf("��������� ����� ����������� ���������� �������\n");
        printf("�������, ��� ��������������� ����������. �� ��������!");

        return 0;
    }
    if (v == 'q'){ // ����� �� ���������
        printf("�������, ��� ��������������� ����������. �� ��������!");

        return 0;
    }
}

double discriminant(double a, double b, double c)
{
    return b * b - 4.0 * a * c;
}
double finalexp(int ine, int znake, int ee, double num)
{
    if (ine){ // �������� ���� �� ���������������� �����
        if (znake == +1){ // ������ ������������� �����
            for(;ee>0; ee--){
                num *= 10.0;
            }
        }
        else{ // ������ ������������� �����
            for(;ee>0; ee--){
                num /= 10.0;
            }
        }
    }
    return num;
}

void mainmenu(char * u)
{
    printf("������� ���������� ���������\n");
    printf("��������� ����� ��� ������ ������:\n");
    printf("������� ����� - ����� � ����������� ������� � ������������ ������������ ����� ���������\n");
    printf("��������� ����� - �����, ������� ����������� ������������� ���, �� ��������� ������ ��������� ���� ���� ���\n");
    printf("(��� ������� ����������� ������������� ������������ ��������� �����)\n");
    printf("�������� ����� ������:\n");
    printf("a - ������� �����\n");
    printf("b - ��������� �����\n");
    printf("��� �������� \"q\" ��� ������ �� ���������\n");

    // ����� ������������. ������������� ������ ���������� �����
    *u = getchar();
    while (getchar() != '\n' || (*u != 'a' && *u != 'b' && *u != '�' && *u != 'q')){
        printf("������������ ����, ���������� �����\n");
        while (getchar() != '\n')
            continue;
        *u = getchar();
    }
}
void input(double koef[], int * err)
{
    char v; // ���������� ��� ����� ������� ������������
    int znak; // ���������� ��� �������� ����� ���������
    int innum; // ���������� ��� ������������ ������ �� �� �����
    double num; // ���������� ��� �������� �����
    int pow; // ���������� ��� �������� ������� ���������
    int indrob; // ���������� ��� �������� ������ �� �� �����
    int drob; // ���������� ��� �������� ������ ����� ����� �������
    int drobc; // ���������� ��� �������� ���������� ������� �� 10
    int ee; // ���������� ��� �������� ���������������� ����� �����
    int ine; // ���������� ��� ������������ ������ �� �� ���. �����
    int prev; // ���������� ��� �������� ����������� ���������� �������
    int znake; // ���������� ��� �������� ����� ���. �����
    double vd; // ���������� ��� �������� �����
    double mnum; // ���������� ��� �������� ����������� �������� num ��� �������� * � /
    int m; // ���������� ��� �������� �������������� �� ��������� � ����������. m=0 - ���
    //m=1 - ��������� �������� - ���������, m = -1 - ��������� �������� - �������
    int ifnum; // ���������� ��� ������������ ��� �� ���� �����
    *err = 0;
    pow = innum = ifnum = num = ee = ine = drob = indrob = prev = m = mnum = 0;
    znak = +1;
    while ((v = getchar()) != '='){ // ���������� ����� ����� ���������
        if (v == 'q'){ // ���������� ����������� � ������� ����
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
        // ���������� ����
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
        // ���������� ������ ������� �����
        else if ((v == '.') || (v == ',')){
            indrob = 1;
            drob = 1;
        }
        // ���������� ������ ���������������� �����
        else if (v == 'e' || v == 'E' || v == '�' || v == '�'){
            ine = 1;
            prev = 'e';
            znake = +1;
        }
        else if (v == '*'){ // ���������� ���������
            num = finalexp(ine, znake, ee, num);
            ine = ee = 0;
            indrob = 0;
            mnum *= num;
            if (m == 0)
                mnum = num;
            m = 1;
            num = 0;
        }
        else if (v == '/'){ // ���������� �������
            num = finalexp(ine, znake, ee, num);
            ine = ee = 0;
            indrob = 0;
            mnum /= (num*1.0);
            if (m == 0)
                mnum = num;
            m = -1;
            num = 0;
        }
        // ���������� �����������
        else if (v == 'x'){
            if (innum)
                pow += 1;
            else
                pow = 1;
            innum = 1;
        }
        // ���������� ������ �������� + � -
        else if (v == '+'){
            if (prev == 'e'){ // ����������� ����� ���������� � ������ ������
                znake = +1;
                prev = 0;
            }
            else{
                num = finalexp(ine, znake, ee, num); // ���������� ����� � ������� ��� ��� ������
                if (!ifnum && fabs(num)<1e-36)
                    num = 1.0;
                if (m == 0) // ������ ����� � ����������� � ������������ � ��������� ��������� ���������/�������
                    koef[pow] += znak * num;
                else if (m == 1)
                    koef[pow] += znak * num*mnum;
                else if (m == -1)
                    koef[pow] += znak * mnum/num;
                if (*err < pow) // ������ ������������ ������� ���������
                    *err = pow;
                pow = innum = num = ee = ine = drob = indrob = prev = m = mnum = 0; // ��������� ����������
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
        else if (v == ' '); // ������������� �������
        else{ // ������ � ������ ����� ������������ �������
            *err = -2;
            while (getchar() != '\n')
                continue;
            return;
        }
    }
    // ������ ���������, ������� ��� ����� �����
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
    while ((v = getchar()) != '\n'){ // ���������� ������ ����� ���������
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
        else if (v == 'e' || v == 'E' || v == '�' || v == '�'){
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
        else if (v == '=') // ���������� ���������� �����
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
                // ������ � �����������
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
                // ��������� ��� ����� num
                num = finalexp(ine, znake, ee, num);
                if (!ifnum && fabs(num)<1e-37)
                    num = 1.0;
                // ������ � �����������
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
    // ������ ���������� �����
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
        printf("������: ���� ��������� - ��������� %d �������\n", err);
    if (err == -2)
        printf("������: � ����� ��������� ������� ����������� �������\n");
    if (err == -3)
        printf("������: ���� ��������� ����� ����� ������ ����� �����\n");
}
