#include "Handler.h"


Game_Object* Handler::get_clicked_obj(int x, int y)
{
    Game_Object* obj;
    std::list<Game_Object*> obj_list;
    obj = Game_Model::get_game_model()->get_object(x,y);
    if(obj)  //���� obj ���������� ��������� �� �����- ���������� ���
        return obj;
    obj = game->map->get_cell(y, x); //���� �� ������ ������� ��� �� ������, �� ������, �� ��������, �� ���������� ��������� �� ������ ���� �������
    return obj;
}

void Handler::to_map_coordinates(HWND hwnd, int* x, int* y)
{
    RECT rct;
    GetClientRect(hwnd, &rct);
    POINTFLOAT cell_size;
    cell_size.x = rct.right / (float)game->N;
    cell_size.y = rct.bottom / (float)game->M;
    (*x) /= cell_size.x;
    (*y) /= cell_size.y;
}

void Handler::mouse_click(MSG msg)
{
    int x,y;
    x = LOWORD(msg.lParam);
    y = HIWORD(msg.lParam);
    to_map_coordinates(msg.hwnd, &x,&y);
    if (x < game->N - 4 && get_clicked_obj(x,y)->is_shown()) {
        if(game->chosen_obj) {
                if(x >= game->chosen_obj->get_position().x && x < (game->chosen_obj->get_position().x + game->chosen_obj->get_size().x)
                        && y >= game->chosen_obj->get_position().y && y < (game->chosen_obj->get_position().y + game->chosen_obj->get_size().y))
                    {
                        game->map->get_cell(game->chosen_obj->get_position().y, game->chosen_obj->get_position().x)->chosen(false);
                        game->chosen_obj = NULL;
                        if(game->action_obj) {
                            game->map->get_cell(game->action_obj->get_position().y,game->action_obj->get_position().x)->chosen(false);
                            game->action_obj = NULL;
                        }
                    }
        else {
                if(game->chosen_obj->get_id() == UnitID || game->chosen_obj->get_id() == BuildingID)
                {

                        if(game->action_obj)
                            game->map->get_cell(game->action_obj->get_position().y,game->action_obj->get_position().x)->chosen(false);
                        game->action_obj = get_clicked_obj(x,y);
                        game->map->get_cell(game->action_obj->get_position().y,game->action_obj->get_position().x)->chosen(true);
                    }

                else{
                    game->map->get_cell(game->chosen_obj->get_position().y,game->chosen_obj->get_position().x)->chosen(false);
                        game->chosen_obj = get_clicked_obj(x,y);
                        game->map->get_cell(game->chosen_obj->get_position().y,game->chosen_obj->get_position().x)->chosen(true);
                }
        }
        }
        else{
                game->chosen_obj = get_clicked_obj(x,y);
                game->map->get_cell(game->chosen_obj->get_position().y,game->chosen_obj->get_position().x)->chosen(true);
        }
    }
}

void Handler::button_click(MSG msg)
{
    switch(msg.wParam)
    {
    case(moveBtn):
        {
            if(game->action_obj && game->action_obj->get_id() == CellID)
            {
                Unit* u = dynamic_cast<Unit*>(game->chosen_obj);
                u->move_to(game->action_obj->get_position().x, game->action_obj->get_position().y);
                Cell* c = dynamic_cast<Cell*>(game->action_obj);
                if(c->get_type() == water)
                    game->delete_object(game->chosen_obj);
            }
            game->end_action();
        }
        break;
    case(attackBtn):
        {
            if(game->action_obj)
            {
            Unit* tmp = dynamic_cast<Unit*> (game->chosen_obj);
            tmp->attack(game->action_obj);
            if(game->action_obj->get_death())
            {
                if(game->action_obj->get_id() == EnemyBuildingID)
                {
                    Building* b = dynamic_cast<Building*>(game->action_obj);
                    if(b->get_b_id() == HQID)
                    {
                        game->end_game();
                    }
                }
                game->delete_object(game->action_obj);
                Particle* p = new Particle(Blood);
                p->set_position(game->action_obj->get_position());
                Game_Model::get_game_model()->add_particle(p);
            }
            game->end_action();
            }
        }
        break;
    case(buildBtn):
        {
            Builder* b = dynamic_cast<Builder*>(game->chosen_obj);
            b->show_build_menu(true);
        }
        break;

    case(buildBaracksBtn):
    case(buildBoerBtn):
    case(buildFarmBtn):
    case(buildTowerBtn):
    case(buildTreeCutBtn):
    case(spawnBuilderBtn):
    case(spawnTrooperBtn):
    case(spawnJuggerBtn):
    case(spawnSniperBtn):
    {
        if(game->action_obj)
        {
            Game_Object* temp = Spawner::spawn_object(msg.wParam, game->action_obj, game->chosen_obj, game->get_field());
            if(temp)
            {
                if(temp->get_id() == UnitID)
                {
                    Unit* u = dynamic_cast<Unit*>(temp);
                    if(game->cur_player->is_anough(u))
                        game->add_object(temp);
                }
                else if(temp->get_id() == BuildingID)
                {
                    Building* b = dynamic_cast<Building*>(temp);
                    if(game->cur_player->is_anough(b))
                        game->add_object(temp);
                }
                else
                    game->add_object(temp);
            }
        }
        game->end_action();
    }
    break;

    case(spellBtn):
        {
            Unit* tmp = dynamic_cast<Unit*>(game->chosen_obj);
            tmp->spell(game->action_obj);
            game->end_action();
        }

    break;

    case(returnBtn):
        {
            Builder* b = dynamic_cast<Builder*>(game->chosen_obj);
            b->show_build_menu(false);
        }
        break;

    case(endTurnBtn):
        {
            game->end_turn();
        }
    break;
    case(newGameBtn):
        game->start();
    break;
    case(helpBtn):
        game->show_help();
    break;
    case(okBtn):
        game->hide_help();
    break;
    }
}
