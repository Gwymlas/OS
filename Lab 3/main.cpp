#include <windows.h>

void MyDraw(HWND h) {
    //POINT pt[3] = { {130, 10}, {105,50}, {155,50} };
    HDC dc = GetDC(h); // получить контекст

    HBRUSH b_red = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH b_green = CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH b_blue = CreateSolidBrush(RGB(0, 0, 255));
    HBRUSH b_brown = CreateSolidBrush(RGB(108, 69, 64));
    HBRUSH b_dark_brown = CreateSolidBrush(RGB(79, 32, 4));
    HBRUSH b_light_brown = CreateSolidBrush(RGB(228, 141, 87));
    HBRUSH b_white = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH b_black = CreateSolidBrush(RGB(0, 0, 0));



    SelectObject(dc, b_brown); Pie(dc, 200, 400, 300, 500, 300, 450, 200, 450); // нога левая
    SelectObject(dc, b_brown); Pie(dc, 300, 400, 400, 500, 400, 450, 300, 450); // нога правая

    SelectObject(dc, b_brown); Ellipse(dc, 250, 250, 350, 420); // туловище
    SelectObject(dc, b_light_brown); Ellipse(dc, 275, 250, 325, 335);

    SelectObject(dc, b_brown); Ellipse(dc, 380, 90, 560, 270); // ухо правое
    SelectObject(dc, b_dark_brown); Ellipse(dc, 410, 120, 530, 240);

    SelectObject(dc, b_brown); Ellipse(dc, 40, 90, 220, 270); // ухо левое
    SelectObject(dc, b_dark_brown); Ellipse(dc, 70, 120, 190, 240);

    SelectObject(dc, b_brown); Ellipse(dc, 180, 80, 420, 280); // голова
    SelectObject(dc, b_light_brown); Ellipse(dc, 210, 110, 390, 250);

    SelectObject(dc, b_white); Ellipse(dc, 235, 205, 285, 155); // левый глаз
    SelectObject(dc, b_black); Ellipse(dc, 240, 205, 285, 160);
    SelectObject(dc, b_white); Ellipse(dc, 262, 180, 272, 190);

    SelectObject(dc, b_white); Ellipse(dc, 315, 205, 365, 155); // правый глаз
    SelectObject(dc, b_black); Ellipse(dc, 320, 205, 365, 160);
    SelectObject(dc, b_white); Ellipse(dc, 342, 180, 352, 190);

    POINT pt_nose[3] = { {300, 200}, {290, 210}, {310, 210} }; // нос
    SelectObject(dc, b_black); Polygon(dc, pt_nose, 3);

    SelectObject(dc, b_red); Chord(dc, 270, 210, 330, 230, 270, 220, 330, 240); // рот

    POINT pt_right_hand[4] = { {335, 280}, {345, 310}, {400, 350}, {400, 330} }; // правая рука
    SelectObject(dc, b_brown); Polygon(dc, pt_right_hand, 4);

    POINT pt_left_hand[4] = { {265, 280}, {255, 310}, {200, 350}, {200, 330} }; // левая рука
    SelectObject(dc, b_brown); Polygon(dc, pt_left_hand, 4);

    SelectObject(dc, b_black); Rectangle(dc, 400, 270, 405, 360); // флаг
    SelectObject(dc, b_white); Rectangle(dc, 405, 270, 465, 285);
    SelectObject(dc, b_blue); Rectangle(dc, 405, 285, 465, 300);
    SelectObject(dc, b_red); Rectangle(dc, 405, 300, 465, 315);
    POINT pt_flag[4] = { {400, 270}, {465, 270}, {465, 315}, {400, 315} };
    SelectObject(dc, b_black); Polyline(dc, pt_flag, 4);

    //SelectObject(dc, b_dark_brown); Rectangle(dc, 10, 10, 50, 50); // прямоугольник
    //SelectObject(dc, b_dark_brown); Ellipse(dc, 60, 10, 100, 50); // кружок
    //SelectObject(dc, b_dark_brown); Polygon(dc, pt, 3); // треугольник


    DeleteObject(b_red); DeleteObject(b_green); DeleteObject(b_blue); // удалить кисти
    DeleteObject(b_brown); DeleteObject(b_dark_brown); DeleteObject(b_light_brown); // удалить кисти
    DeleteObject(b_white); DeleteObject(b_black);// удалить кисти

    ReleaseDC(h, dc); DeleteDC(dc); // освободить контекст
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    switch (Message) {
        //case WM_PAINT:
        //    MyDraw(hwnd);
        //     break;
        case WM_KEYDOWN:
            if (wparam == VK_ESCAPE) PostQuitMessage(0);
            break;
        case WM_LBUTTONDOWN:
            if ((LOWORD(lparam) < 20) && (LOWORD(lparam) < 20)) PostQuitMessage(0);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    MSG msg; // сообщение
    WNDCLASS w; // класс окна
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // WHITE_BRUSH
    w.lpszClassName = LPCWSTR("My Class");
    RegisterClass(&w);
    HWND hwnd = CreateWindow(LPCWSTR("My Class"), LPCWSTR("Example"),
                             WS_OVERLAPPEDWINDOW, 100, 100, 700, 500,
                             NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MyDraw(hwnd);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); DispatchMessage(&msg);
    }
    return msg.wParam;
}