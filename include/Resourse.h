#ifndef RESOURSE_H_INCLUDED
#define RESOURSE_H_INCLUDED

#include "Game_Object.h"
#include "Textures.h"

enum Res_Type {Tree, Iron, Meat, Oil};

typedef struct {
    int meat = 0;
    int wood = 0;
    int iron = 0;
    int oil = 0;
}Resource_t;

class Resource : public Game_Object
{
public:
    Res_Type res_type;
    int gain;

    Resource(Res_Type type, int gain)
    {
        this->res_type = type;
        this->gain = gain;
        this->object_attributes.id = ResourceID;
    }
    void draw(int M, int N, Texture* textures) override;
    //void set_gain(int gain) {this->gain = gain;}
    int get_gain() {return this->gain;}
    Res_Type get_type() {return this->res_type;}
};

#endif // RESOURSE_H_INCLUDED
