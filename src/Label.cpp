#include "Label.h"

Label::Label(HWND parentWnd, HINSTANCE hInstance, int id, POINT position, POINT size, char* text)
{
    this->position = position;
    this->size = size;
    this->id = id;
    this->text = text;
    //this->parentWnd = parentWnd;
    //this->hInst = hInstance;
    this->lbl = CreateWindow("static",text,WS_CHILD|WS_CLIPSIBLINGS,position.x,position.y,size.x,size.y,parentWnd,(HMENU)id,hInstance,NULL);
    BringWindowToTop(this->lbl);
}

int Label::get_id()
{
    return this->id;
}

POINT Label::get_position()
{
    return this->position;
}

POINT Label::get_size()
{
    return this->size;
}

void Label::set_position(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

void Label::set_position(POINT position)
{
    this->position = position;
}

void Label::set_size(int width, int heigh)
{
    this->size.x = width;
    this->size.y = heigh;
}

void Label::set_size(POINT size)
{
    this->size = size;
}

void Label::show()
{
    ShowWindow(this->lbl, SW_SHOW);
}

void Label::hide()
{
    ShowWindow(this->lbl, SW_HIDE);
}

void Label::change_text(char* text)
{
    if(std::string(text) == std::string(this->text))
        return;
    this->text = text;
    SetWindowText(this->lbl, this->text);
}
