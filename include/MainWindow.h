#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <gl/gl.h>
#include "../stb_image.h"
#include "Game.h"

class MainWindow
{
    public:
        MainWindow(HINSTANCE hInstance, int nCmdShow, LRESULT(CALLBACK *WndProc)(HWND,UINT,WPARAM,LPARAM));
        ~MainWindow();
        HWND getHWND() {return this->hWnd;}
        HDC getHDC() {return this->hDC;}
        HGLRC getHRC() {return this->hRC;}

        POINT getSize();

        void Show(Game* game);
        void ShowMainMenu();

    private:
        WNDCLASSEX wcex;
        HWND hWnd;
        HDC hDC;
        HGLRC hRC;


        void EnableOpenGL(); //���������� OpenGL
        void DisableOpenGL(); //��������� OpenGL
};

#endif // MAINWINDOW_H
