#ifndef BUTTON_H
#define BUTTON_H


#include <windows.h>
#include "gl/gl.h"

#define moveBtn 0x1000
#define attackBtn 0x1001
#define buildBtn 0x1002
#define spellBtn 0x1003
#define buildBaracksBtn 0x1004
#define buildTowerBtn 0x1005
#define buildTreeCutBtn 0x1006
#define buildFarmBtn 0x1007
#define buildBoerBtn 0x1008
#define spawnTrooperBtn 0x1009
#define spawnJuggerBtn 0x100A
#define spawnSniperBtn 0x100B
#define spawnBuilderBtn 0x100C
#define endTurnBtn 0x100D
#define returnBtn 0x100E
#define buildOilStationBtn 0x100F
#define newGameBtn 0x1010
#define quitBtn 0x1011
#define helpBtn 0x1012
#define okBtn 0x1013

class Button
{
    public:
        Button(HWND parentWnd, HINSTANCE hInstance, int id, POINT position, POINT size, const char* text);
        POINT get_size();
        POINT get_position();
        int get_id();
        HWND get_wnd();


        void set_size(POINT size);
        void set_size(int width, int heigh);
        void set_position(POINT position);
        void set_position(int x, int y);

        void show();
        void hide();
        void enable();
        void disable();

    protected:

    private:
        POINT position;
        POINT size;
        int id;
        HWND btn;
};

#endif // BUTTON_H
