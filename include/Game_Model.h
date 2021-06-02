#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "Game_Object.h"
#include "Particle.h"
#include <list>

class Game_Model
{
    public:
        static Game_Model* get_game_model();

        Game_Object* get_object(int x, int y);
        Game_Object* get_iter_object() {return *iter;}
        void add_object(Game_Object* obj);
        void delete_object(Game_Object* obj);

        bool objects_ended() {return this->iter == this->list_end;}
        void increase_iter() {iter++;}
        void reset_iter() {    list_begin = this->object_list.begin(); list_end = this->object_list.end(); iter = list_begin;}

        void add_particle(Particle* particle) {this->particles.push_back(particle);}
        void update_particles(int M, int N, Texture* textures);

    private:
        Game_Model();
        static Game_Model* g_m_instance;
        std::list<Game_Object*> object_list;
        std::list<Game_Object*>::iterator list_begin;
        std::list<Game_Object*>::iterator list_end;
        std::list<Game_Object*>::iterator iter;
        std::list<Particle*> particles;
};

#endif // GAME_MODEL_H
