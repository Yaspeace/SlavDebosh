#ifndef PARTICLE_H
#define PARTICLE_H

#include "Game_Object.h"
#include "Textures.h"
#include <time.h>

enum Sprite_Type {Blood, Explotion};

class Particle : public Game_Object
{
    public:
        Particle(Sprite_Type type);
        void draw(int M, int N, Texture* textures) override;
        bool to_be_deleted() {return cur_time >= life_time;}
        void update() {cur_time = time(0);}
    private:
        long long cur_time;
        long long life_time;
        Sprite_Type type;
};

#endif // PARTICLE_H
