#include "MainWindow.h"

MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow, LRESULT(CALLBACK *WndProc)(HWND,UINT,WPARAM,LPARAM))
{
    this->wcex.cbSize = sizeof(WNDCLASSEX);
    this->wcex.style = CS_OWNDC;
    this->wcex.lpfnWndProc = WndProc;
    this->wcex.cbClsExtra = 0;
    this->wcex.cbWndExtra = 0;
    this->wcex.hInstance = hInstance;
    this->wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    this->wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    this->wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    this->wcex.lpszMenuName = NULL;
    this->wcex.lpszClassName = "GLSample";
    this->wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&(this->wcex));

    this->hWnd = CreateWindowEx(0,
                        "GLSample",
                        "���������� �����",
                        WS_OVERLAPPEDWINDOW|WS_MAXIMIZE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_VISIBLE,
                        0,
                        0,
                        1920,
                        1080,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
    if(!this->hWnd)
        MessageBox(NULL, "ERROR", "Can't show window", MB_OK);

    EnableOpenGL();
}

MainWindow::~MainWindow()
{
    DisableOpenGL();
    DestroyWindow(hWnd);
}

POINT MainWindow::getSize()
{
    RECT rct;
    GetClientRect(this->hWnd, &rct);
    POINT size;
    size.x = rct.right;
    size.y = rct.bottom;
    return size;
}

void MainWindow::EnableOpenGL()
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    this->hDC = GetDC(this->hWnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(this->hDC, &(pfd));

    SetPixelFormat(this->hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    this->hRC = wglCreateContext(this->hDC);

    glEnable(GL_TEXTURE_2D);

    wglMakeCurrent(this->hDC, this->hRC);
    if(!this->hDC || !this->hRC)
        MessageBox(NULL, "ERROR", "Can't enable opengl!", MB_OK);
}

void MainWindow::DisableOpenGL()
{
    glDisable(GL_TEXTURE_2D);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(this->hRC);
    ReleaseDC(this->hWnd, this->hDC);
}

void MainWindow::Show(Game* game)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������ � ������ �������
    glLoadIdentity(); // ����� ���������

    glPushMatrix();
    glTranslatef(-1,1,0);
    glScalef(2,-2,0);

    game->show();

    glPopMatrix();
}

void MainWindow::ShowMainMenu()
{

}
