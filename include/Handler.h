#ifndef HANDLER_H
#define HANDLER_H

#include <stdio.h>
#include <iostream>
#include "Game.h"

class Handler
{
    public:
        Handler(Game* game) {this->game = game;}
        Game_Object* get_clicked_obj(int x, int y);
        void mouse_click(MSG msg);
        void button_click(MSG msg);

    protected:

    private:
        Game* game;
        void to_map_coordinates(HWND hwnd, int* x, int* y);
};

#endif // HANDLER_H
