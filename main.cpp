#include <windows.h>
#include <iostream>
#include <cmath>
#include <vector>

//DWORD WINAPI mythread1(void *q) { // Поток-читатель
//    HANDLE e1 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev1");
//    HANDLE e3 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev3");
//    while(1){
//        WaitForSingleObject(e1, INFINITE); // Ждать разрешения
//        HANDLE f = CreateFile(".\\file.dat",GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
//        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // Открыть файл
//        HANDLE m = CreateFileMapping(f, 0, PAGE_READONLY, 0, 0, NULL);
//        unsigned char *p = (unsigned char *) MapViewOfFile(m, FILE_MAP_READ, 0, 0, 0);
//        std::cout << p[0]; // Отобразить переданную букву
//        CloseHandle(m);
//        CloseHandle(f);
//        SetEvent(e3); // Доложить о выполнении
//    }
//}


DWORD WINAPI Thread_Mul (void *q) {
    DWORD n;
    HANDLE e1 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev1");
    HANDLE e0 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev0");
    while(1) {
        WaitForSingleObject(e1, INFINITE); // Ждать разрешения
        HANDLE f = CreateFile(".\\file.dat",GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                              NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // Открыть файл
        HANDLE m = CreateFileMapping(f, 0, PAGE_READWRITE, 0, 0, NULL); // PAGE_READWRITE instead PAGE_READONLY
        float *p = (float *) MapViewOfFile(m, FILE_MAP_ALL_ACCESS, 0, 0, 0); // FILE_MAP_ALL_ACCESS instead FILE_MAP_READ
        float result = p[0] * p[1];
        std::cout << p[0] << " * " << p[1] << " = " << result << std::endl; // Отобразить операцию
        p[0] = result;
        CloseHandle(m);
        CloseHandle(f);
        SetEvent(e0); // Доложить о выполнении
    }
}

DWORD WINAPI Thread_Add (void *q) {
    DWORD n;
    HANDLE e2 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev2");
    HANDLE e0 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev0");
    while(1) {
        WaitForSingleObject(e2, INFINITE); // Ждать разрешения
        HANDLE f = CreateFile(".\\file.dat",GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                              NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // Открыть файл
        HANDLE m = CreateFileMapping(f, 0, PAGE_READWRITE, 0, 0, NULL); // PAGE_READWRITE instead PAGE_READONLY
        float *p = (float *) MapViewOfFile(m, FILE_MAP_ALL_ACCESS, 0, 0, 0); // FILE_MAP_ALL_ACCESS instead FILE_MAP_READ
        float result = p[0] + p[1];
        std::cout << p[0] << " + " << p[1] << " = " << result << std::endl; // Отобразить операцию
        p[0] = result;
        CloseHandle(m);
        CloseHandle(f);
        SetEvent(e0); // Доложить о выполнении
    }
}

DWORD WINAPI Thread_Div (void *q) {
    DWORD n;
    HANDLE e3 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev3");
    HANDLE e0 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev0");
    while(1) {
        WaitForSingleObject(e3, INFINITE); // Ждать разрешения
        HANDLE f = CreateFile(".\\file.dat",GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                              NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // Открыть файл
        HANDLE m = CreateFileMapping(f, 0, PAGE_READWRITE, 0, 0, NULL); // PAGE_READWRITE instead PAGE_READONLY
        float *p = (float *) MapViewOfFile(m, FILE_MAP_ALL_ACCESS, 0, 0, 0); // FILE_MAP_ALL_ACCESS instead FILE_MAP_READ
        float result = (float)p[0] / p[1];
        std::cout << p[0] << " / " << p[1] << " = " << result << std::endl; // Отобразить операцию
        p[0] = result;
        CloseHandle(m);
        CloseHandle(f);
        SetEvent(e0); // Доложить о выполнении
    }
}

DWORD WINAPI Thread_Sqrt (void *q) {
    DWORD n;
    HANDLE e4 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev4");
    HANDLE e0 = OpenEvent(EVENT_ALL_ACCESS, TRUE, "ev0");
    while(1) {
        WaitForSingleObject(e4, INFINITE); // Ждать разрешения
        HANDLE f = CreateFile(".\\file.dat",GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                              NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // Открыть файл
        HANDLE m = CreateFileMapping(f, 0, PAGE_READWRITE, 0, 0, NULL); // PAGE_READWRITE instead PAGE_READONLY
        float *p = (float *) MapViewOfFile(m, FILE_MAP_ALL_ACCESS, 0, 0, 0); // FILE_MAP_ALL_ACCESS instead FILE_MAP_READ
        float result = sqrt(p[0]);
        std::cout << "sqrt(" << p[0] << ") " <<  " = " << result << std::endl; // Отобразить операцию
        p[0] = result;
        CloseHandle(m);
        CloseHandle(f);
        SetEvent(e0); // Доложить о выполнении
    }
}

int main() {
    DWORD n;
    float a, b, c, res1, res2;
    float four = 4;
    float two = 2;
    float neg_one = -1;
    float x1, x2;

    std::cout << "Input value of a, b, c:" << std::endl;
    std::cin >> a >> b >> c;
    std::cout << "The values:" << "\na = " << a << "\nb = " << b << "\nc = " << c << std::endl;

    HANDLE e0 = CreateEvent(NULL, FALSE, FALSE, "ev0"); // возвращение к main thread
    HANDLE e1 = CreateEvent(NULL, FALSE, FALSE, "ev1"); // разрешение выполнения thread mul
    HANDLE e2 = CreateEvent(NULL, FALSE, FALSE, "ev2"); // разрешение выполнения thread add
    HANDLE e3 = CreateEvent(NULL, FALSE, FALSE, "ev3"); // разрешение выполнения thread div
    HANDLE e4 = CreateEvent(NULL, FALSE, FALSE, "ev4"); // разрешение выполнения thread sqrt

    HANDLE h1 = CreateThread(NULL, 0, &Thread_Mul, NULL, 0, NULL);
    HANDLE h2 = CreateThread(NULL, 0, &Thread_Add, NULL, 0, NULL);
    HANDLE h3 = CreateThread(NULL, 0, &Thread_Div, NULL, 0, NULL);
    HANDLE h4 = CreateThread(NULL, 0, &Thread_Sqrt, NULL, 0, NULL);

    HANDLE commands[14] = {e1, e1, e1, e1, e2, e4, e1, e2, e3, e3, e1, e2, e3, e3};

    float* arg[42] = {&a, &c, &res1,
                      &four, &res1, &res1,
                      &b, &b, &res2,
                      &res1,&neg_one, &res1,
                      &res2,&res1, &res1,
                      &res1,&res1, &res1,
                      &neg_one, &b, &res2,
                      &res2, &res1, &x1,
                      &x1, &two, &x1,
                      &x1, &a, &x1,
                      &neg_one, &res1, &res1,
                      &res2, &res1, &x2,
                      &x2, &two, &x2,
                      &x2, &a, &x2};

    for (int i = 0, j = 0; i < 14, j < 42; ++i, j+=3) {
        HANDLE h = CreateFile(".\\file.dat",GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                              NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // Создать файл

        float elem[2] = {*arg[j], *arg[j+1]};
        WriteFile(h, &elem, 8, &n, NULL); // Передать аргументы

        CloseHandle(h); // Закрыть файл

        SetEvent(commands[i]); // Разрешить потоку выполнить операцию
        WaitForSingleObject(e0, INFINITE); // Ждать доклад

        h = CreateFile(".\\file.dat",GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                       NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        HANDLE m = CreateFileMapping(h, 0, PAGE_READONLY, 0, 0, NULL); // test
        *arg[j+2] = *(float *) MapViewOfFile(m, FILE_MAP_READ, 0, 0, 0);

        CloseHandle(m);
        CloseHandle(h);
    }

    std::cout << "Result:" << "\nx_1 = " << x1 << "\nx_2 = " << x2 << std::endl;

    CloseHandle(e0);
    CloseHandle(e1);
    CloseHandle(e2);
    CloseHandle(e3);
    CloseHandle(e4);
}
