#ifndef CELL_H
#define CELL_H

#include "Game_Object.h"

enum Terrain_type {grass, water, hg};

class Cell : public Game_Object
{
    public:
        Cell() {this->object_attributes.id = CellID;}
        Cell(Terrain_type type) {this->type = type; this->object_attributes.id = CellID;}
        Terrain_type get_type() {return this->type;}
        void set_type(Terrain_type type) {this->type = type;}
        void draw(int M, int N, Texture* textures) override;
        void chosen(bool isChosen) {this->is_chosen = isChosen;}
    private:
        Terrain_type type;
        bool is_chosen = false;
};

#endif // CELL_H
