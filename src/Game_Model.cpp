#include "Game_Model.h"

Game_Model* Game_Model::g_m_instance = NULL;

Game_Model::Game_Model()
{
    list_begin = this->object_list.begin();
    list_end = this->object_list.end();
}

Game_Model* Game_Model::get_game_model()
{
    if(g_m_instance == NULL)
        g_m_instance = new Game_Model();
    return g_m_instance;
}

void Game_Model::add_object(Game_Object* obj)
{
    this->object_list.push_back(obj);
}

Game_Object* Game_Model::get_object(int x, int y)
{
    for(auto obj: this->object_list)
    {
        POINT pos = obj->get_position();
        POINT size = obj->get_size();
        if(x >= pos.x && x < (pos.x + size.x) && y >= pos.y && y < (pos.y + size.y))
            return obj;
    }
    return NULL;
}

void Game_Model::delete_object(Game_Object* del_obj)
{
    for(auto obj: this->object_list)
    {
        POINT pos = obj->get_position();
        POINT size = obj->get_size();
        if(del_obj->get_position().x >= pos.x && del_obj->get_position().x < (pos.x + size.x) && del_obj->get_position().y >= pos.y && del_obj->get_position().y < (pos.y + size.y))
            object_list.remove(obj);
    }
}

void Game_Model::update_particles(int M, int N, Texture* textures)
{
    for(auto p: particles)
    {
        p->update();
        p->draw(M,N,textures);
        if(p->to_be_deleted())
            particles.remove(p);
    }
}
