#ifndef MENU_H
#define MENU_H

#include <windows.h>
#include <list>
#include "Button.h"
#include "Label.h"

class Menu
{
    public:
        Menu(HWND parentWnd, HINSTANCE hInstance, POINT position, POINT size);
        void AddButton(Button*);
        void AddButton(int id, POINT position, POINT size, char* text);
        void AddLabel(Label*);
        void AddLabel(int id, POINT position, POINT size, char* text);
        void show();
        void hide();
        Button* get_button(int id);
        Label* get_label(int id);
        POINT get_position();
        POINT get_size();
        void set_position(POINT position);
        void set_position(int x, int y);
        void set_size(POINT size);
        void set_size(int width, int heigh);
    private:
        HWND background;
        HWND mainWnd;
        HINSTANCE hInstance;
        POINT position;
        POINT size;
        std::list<Button*> btnList;
        std::list<Label*> lblList;
};

#endif // MENU_H
