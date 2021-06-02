#include "Menu.h"

Menu::Menu(HWND parentWnd, HINSTANCE hInstance, POINT position, POINT size)
{
    this->position = position;
    this->size = size;
    this->hInstance = hInstance;
    this->mainWnd = parentWnd;
    this->background = CreateWindow("static","",WS_CHILD|WS_CLIPSIBLINGS,position.x,position.y,size.x,size.y,parentWnd,NULL,hInstance,NULL);
}

void Menu::set_position(POINT position)
{
    this->position = position;
}

void Menu::set_position(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

void Menu::set_size(POINT size)
{
    this->size = size;
}

void Menu::set_size(int width, int heigh)
{
    this->size.x = width;
    this->size.y = heigh;
}

POINT Menu::get_position()
{
    return this->position;
}

POINT Menu::get_size()
{
    return this->size;
}

Button* Menu::get_button(int id)
{
    for(auto it = btnList.begin(); it != btnList.end(); it++)
        if((*it)->get_id() == id)
            return *it;
    return NULL;
}

Label* Menu::get_label(int id)
{
    for(auto it = lblList.begin(); it != lblList.end(); it++)
        if((*it)->get_id() == id)
            return *it;
    return NULL;
}


void Menu::AddButton(Button* btn)
{
    this->btnList.push_back(btn);
}

void Menu::AddButton(int id, POINT position, POINT size, char* text)
{
    Button* btn = new Button(mainWnd, hInstance, id, position, size, text);
    this->btnList.push_back(btn);
}

void Menu::AddLabel(Label* lbl)
{
    this->lblList.push_back(lbl);
}

void Menu::AddLabel(int id, POINT position, POINT size, char* text)
{
    Label* lbl = new Label(mainWnd, hInstance, id, position, size, text);
    this->lblList.push_back(lbl);
}

void Menu::show()
{
    ShowWindow(this->background,SW_SHOW);
    for(auto it = btnList.begin(); it != btnList.end(); it++)
        (*it)->show();
    for(auto it = lblList.begin(); it != lblList.end(); it++)
        (*it)->show();
}

void Menu::hide()
{
    ShowWindow(background,SW_HIDE);
    for(auto it = btnList.begin(); it != btnList.end(); it++)
        (*it)->hide();
    for(auto it = lblList.begin(); it != lblList.end(); it++)
        (*it)->hide();
}

