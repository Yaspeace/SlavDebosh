#include "Spawner.h"
#include <random>

Game_Object* Spawner::spawn_object(int ButtonID, Game_Object* action_obj, Game_Object* chosen_obj, Field* map)
{
    Game_Object* obj;
    switch(chosen_obj->get_id())
    {
    case(UnitID):
        {
            Unit* u = dynamic_cast<Unit*> (chosen_obj);
            if((u->get_cur_act_num() > 0)&&(u->get_u_id() == BuilderID))
            {
                    Builder* b = dynamic_cast<Builder*>(u);
                    obj = b->spawn_building(ButtonID, b->get_team());
                    obj->set_position(action_obj->get_position());
                    if(Spawner::check_spawn(action_obj, chosen_obj, obj, map))
                    {
                        if((action_obj->get_id()) == ResourceID)
                        {
                            Building* temp = dynamic_cast<Building*>(obj);
                            Resource* temp2 = dynamic_cast<Resource*>(action_obj);
                            temp->set_res_gain(temp2->res_type, temp2->gain);
                            Game_Model::get_game_model()->delete_object(action_obj);
                        }
                        u->set_cur_act_num(u->get_cur_act_num() - 1);
                    }
                    else return NULL;
            }
            else return NULL;
        }
        break;
    case(BuildingID):
        {
            Building* b = dynamic_cast<Building*> (chosen_obj);
            if((b->get_cur_act_num() > 0) && ((b->get_b_id() == HQID) || (b->get_b_id() == BaracksID)))
            {
                obj = b->spawn_unit(ButtonID, b->get_team());
                obj->set_position(action_obj->get_position());
                if(Spawner::check_spawn(action_obj, chosen_obj, obj, map))
                    b->set_cur_act_num(b->get_cur_act_num() - 1);
                else return NULL;
            }
            else return NULL;
        }
        break;
    default:
        return NULL;
    }
    return obj;
}


bool Spawner::check_spawn(Game_Object* action_obj, Game_Object* chosen_obj, Game_Object* spawning_object, Field* map)
{
    int G_X1, G_X2;
	G_X1 = chosen_obj->get_position().x + chosen_obj->get_size().x;
	G_X2 = chosen_obj->get_position().x - 1;

	int G_Y1, G_Y2;
	G_Y1 = chosen_obj->get_position().y + chosen_obj->get_size().y;
	G_Y2 = chosen_obj->get_position().y - 1;

	if ((G_X1 >= spawning_object->get_position().x) && (G_X2 <= spawning_object->get_position().x))
		if ((spawning_object->get_position().y <= G_Y1) && (spawning_object->get_position().y >= G_Y2))
			{
			    if(spawning_object->get_id() == BuildingID)
                {
                    if(Game_Model::get_game_model()->get_object(spawning_object->get_position().x, spawning_object->get_position().y))
                    {
                        Building* b;
                        if(Game_Model::get_game_model()->get_object(spawning_object->get_position().x, spawning_object->get_position().y)->get_id() == ResourceID)
                        {
                           Resource* tmp = dynamic_cast<Resource*>(Game_Model::get_game_model()->get_object(spawning_object->get_position().x, spawning_object->get_position().y));
                            if(spawning_object->get_id() == BuildingID)
                            b = dynamic_cast<Building*>(spawning_object);
                            if((b->get_b_id() == TreecutterID) && (tmp->res_type == Tree))
                                return true;

                            if((b->get_b_id() == BoerID) && (tmp->res_type == Iron))
                                return true;

                            if((b->get_b_id() == OilID) && (tmp->res_type == Oil))
                                return true;
                            return false;
                        }
                    }
                    else
                    {
                        Building* b = dynamic_cast<Building*>(spawning_object);
                        if(b->get_b_id() == BaracksID || b->get_b_id() == TowerID || b->get_b_id() == HQID || b->get_b_id() == FarmID)
                        {
                            if(!(Game_Model::get_game_model()->get_object(spawning_object->get_position().x, spawning_object->get_position().y)) &&
                               !(Game_Model::get_game_model()->get_object(spawning_object->get_position().x + ((spawning_object->get_size().x) - 1), spawning_object->get_position().y)))
                                if(!(Game_Model::get_game_model()->get_object(spawning_object->get_position().x, spawning_object->get_position().y + (spawning_object->get_size().y -1))) &&
                                   !(Game_Model::get_game_model()->get_object(spawning_object->get_position().x + (spawning_object->get_size().x - 1), spawning_object->get_position().y + (spawning_object->get_size().y-1))))
                                   if(map->get_cell(spawning_object->get_position().y, spawning_object->get_position().x)->get_type() == grass
                                      && map->get_cell(spawning_object->get_position().y + spawning_object->get_size().y - 1, spawning_object->get_position().x)->get_type() == grass
                                      && map->get_cell(spawning_object->get_position().y, spawning_object->get_position().x + spawning_object->get_size().x - 1)->get_type() == grass
                                      && map->get_cell(spawning_object->get_position().y + spawning_object->get_size().y - 1, spawning_object->get_position().x + spawning_object->get_size().x - 1)->get_type() == grass)
                                        return true;
                            else return false;
                        }
                        else return false;
                    }
                }
                else
                return true;
			}
	return false;
}

