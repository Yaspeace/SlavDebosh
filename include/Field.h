#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include "stdlib.h"
#include <stdio.h>
#include <windows.h>
#include "Cell.h"
#include <random>
#include <ctime>

#include "Game_Model.h"
#include "Resourse.h"

class Field
{
public:
	Field(int M,int N);
	void generation();
	Cell* get_cell(int i, int j);
    void bind_map_textures(Texture* textures);
private:
    int M;
	int N;
    Cell** a;
	void make_high();
	void make_river();
	void make_forest();
	void make_ore();
	void make_oil();
};

#endif // FIELD_H
