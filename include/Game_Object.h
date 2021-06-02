#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "gl/gl.h"
#include "Textures.h"
#include <time.h>
#include "Button.h"

#define CellID 1
#define UnitID 2
#define BuildingID 3
#define ResourceID 4
#define EnemyID 5
#define EnemyBuildingID 6

typedef struct
{
    POINT position;
    POINT size = {1,1};
    int id;

    bool death;
	
	int rad_of_view = 0;
    bool shown = false;


} Object_attributes;

class Game_Object
{
public:
   void set_position(int x, int y) {this->object_attributes.position.x = x; this->object_attributes.position.y = y;};
    void set_position(POINT new_pos){this->object_attributes.position = new_pos;}
    void set_death(bool b) {this->object_attributes.death = b;};
    void set_id(int id) {this->object_attributes.id = id;}
    void set_view_rad(int rad) {this->object_attributes.rad_of_view = rad;}

    POINT get_position() {return this->object_attributes.position;};
    POINT get_size() {return this->object_attributes.size;};
    bool get_death() {return this->object_attributes.death;};
    int get_id() {return this->object_attributes.id;}
    int get_view_rad() {return this->object_attributes.rad_of_view;}

    void visible(bool is_visible) {this->object_attributes.shown = is_visible;}
    bool is_shown() {return this->object_attributes.shown;}

    virtual void draw(int M, int N, Texture* textures) = 0;

protected:
    Object_attributes object_attributes;
};

#endif // GAME_OBJECT_H
