#include <windows.h>

#include "MainWindow.h"
#include "Menu.h"
#include "Game.h"
#include "Handler.h"

MSG msg;
BOOL bQuit = FALSE;

int M = 30;
int N = 40;

Game* game;
Handler* handler;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    MainWindow m_wnd(hInstance,nCmdShow,WindowProc);
    game = new Game(M,N);
    game->load(m_wnd.getHWND(), hInstance);
    handler = new Handler(game);
    while(!bQuit)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            m_wnd.Show(game);
            SwapBuffers(m_wnd.getHDC());
            Sleep (1);
        }
    }

    delete &m_wnd;

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_DESTROY:
        return 0;

    case WM_QUIT:
        {
            bQuit = true;
            PostQuitMessage(0);
        }
    break;

    case WM_LBUTTONUP:
        {
            MSG new_msg;
            new_msg.hwnd = hWnd;
            new_msg.wParam = wParam;
            new_msg.lParam = lParam;
            handler->mouse_click(new_msg);
        }
    break;

    case WM_KEYDOWN:
        {
            switch(wParam)
            {
                case(VK_ESCAPE):
                {
                    bQuit = TRUE;
                    PostQuitMessage(0);
                }
                break;
            }
        }
    break;

    case WM_COMMAND:
        {
            if(wParam == quitBtn)
                bQuit = TRUE;
            MSG new_msg;
            new_msg.hwnd = hWnd;
            new_msg.wParam = wParam;
            new_msg.lParam = lParam;
            handler->button_click(new_msg);
        }
    break;

    default:
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
    return 0;
}

