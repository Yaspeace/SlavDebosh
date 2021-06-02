#ifndef LABEL_H
#define LABEL_H

#include <windows.h>
#include "gl/gl.h"
#include <string>

#define PlayerLbl 0x2000
#define ActNumLbl 0x2001
#define MeatAmountLbl 0x2002
#define TreeAmountLbl 0x2003
#define IronAmountLbl 0x2004
#define OilAmountLbl 0x2005
#define EnemyTypeLbl 0x2006
#define EnemyHealthLbl 0x2007
#define EnemyDamageLbl 0x2008
#define HealthLbl 0x2009
#define DamageLbl 0x200A
#define UnitNameLbl 0x200B
#define helpLbl 0x200C
#define resLbl 0x200D

class Label
{
    public:
        Label(HWND parentWnd, HINSTANCE hInstance, int id, POINT position, POINT size, char* text);
        POINT get_size();
        POINT get_position();
        int get_id();
        char* get_text() {return this->text;}

        void set_size(POINT size);
        void set_size(int width, int heigh);
        void set_position(POINT position);
        void set_position(int x, int y);

        void show();
        void hide();
        void change_text(char* text);
    private:
        POINT position;
        POINT size;
        int id;
        char* text;
        HWND lbl;
};

#endif // LABEL_H
