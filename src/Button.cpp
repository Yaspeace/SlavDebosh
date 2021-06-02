#include "Button.h"

Button::Button(HWND parentWnd, HINSTANCE hInstance, int id, POINT position, POINT size, const char* text)
{
    this->position = position;
    this->size = size;
    this->id = id;
    this->btn = CreateWindow("button",text,WS_CHILD|WS_CLIPSIBLINGS|BS_MULTILINE,position.x,position.y,size.x,size.y,parentWnd,(HMENU)id,hInstance,NULL);
    BringWindowToTop(this->btn);
}

POINT Button::get_position()
{
    return this->position;
}

POINT Button::get_size()
{
    return this->size;
}

int Button::get_id()
{
    return this->id;
}

HWND Button::get_wnd()
{
    return this->btn;
}

void Button::set_position(POINT position)
{
    this->position = position;
}

void Button::set_position(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

void Button::set_size(POINT size)
{
    this->size = size;
}

void Button::set_size(int width, int heigh)
{
    this->size.x = width;
    this->size.y = heigh;
}

void Button::show()
{
    ShowWindow(this->btn,SW_SHOW);
}

void Button::hide()
{
    ShowWindow(this->btn, SW_HIDE);
}

void Button::enable()
{
    EnableWindow(this->btn,true);
}

void Button::disable()
{
    EnableWindow(this->btn,false);
}
