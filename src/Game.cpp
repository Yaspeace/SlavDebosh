#include "Game.h"

bool Game::load(HWND window, HINSTANCE hInstance)
{

    spawn_HQ();

    map->generation();
    this->textures = new Texture(M,N);
    map->bind_map_textures(textures);

    RECT rct;
    GetClientRect(window, &rct);

    POINT btn_size;
    POINT btn_pos;
    POINT tmp_pos = {0,0};
    POINT tmp_size = {rct.right, rct.bottom};
    this->main_menu = new Menu(window, hInstance, tmp_pos, tmp_size);
    this->help = new Menu(window, hInstance, tmp_pos, tmp_size);
    btn_size.x = rct.right / 12;
    btn_size.y = rct.bottom / 24;
    btn_pos.x = rct.right - (3 * btn_size.x / 2);
    btn_pos.y = rct.bottom - (3 * btn_size.y / 2);
    tmp_size.y -= 2*btn_size.y;
    help->AddButton(okBtn, btn_pos, btn_size,"OK");
    help->AddLabel(helpLbl,tmp_pos, tmp_size, "����� ���������� � ���� \"���������� �����\"!\n��� ���� � ����� ��������� ��������� ��� ���� �������� ������- ���������� ������� ���� ����� ����� �����.\n� ����� ������������ �������� ������ ���� ������, � ������ ���� ��������.\n\n�����:\n*���������: ���������������� ��������������, ��������� ���� ������� ���������. ����: 5. ��������: 20. ���� ��������: 2.\n*�������: ���� ��� ������� ��� �� ������� ���������. ����: 7. ��������: 10. ���� ��������: 3.\n*�����������: ������ ������������� ���� ��� �������� ����� ��������� �����. ����: 3. ��������: 50. ���� ��������: 2.\n*���������: ��������� ���� ����������� ��� ������������� ����� ����. ����: 1. ��������: 5. ���� ��������: 2.\n\n������:\n*������� ����: � ���� ������� �� ��������� ����. ������ ��� �������� ����������� ����������. ��� ����������� ������ ����� �� ���������� ��� �����. ����� ���������� ������ ������ ��������� �� ���. ��������: 12.\n*�������: ���������� ������ ��� ����� �����. �� ��������� ������ ��� ����. ����� ���������� ������ ������ ����� �� ���. ��������: 8.\n*�����: ����������� ���������� ��� ���������� ����� ������� ���������. �������� ���� ���. ��������: 4.\n���������� ������: ���������� ������� ��� ����� �����. ����� ���� ��������� �� ������������� �� ���� �������� (������, ������, �����), ���� �� �������� ��������� (�����). �� ������������� ������ ���� ���.\n\n�����:\n������ ����� ���� ������������ ����� ��������� �����. �� ����� ���� �����, ������������� � ����. ���� � ������������� �������������, � ����� �� �������������- �����������. ��� ��������� ����� � ���� �� �������.\n\n��������:\n������ ���� ����� ��������� �����-���� �������� (�����������, ����� � �.�.) ���� � ���� ���� ���� ��������. ���������� �������� ������ ���� ����. �������������� ���� ����� ������ � ������� ������ �����������, ���������/������������ �����������- ������ � ������� �����, ���������(���������)- ������ � ������� ����� ������. �������� ��������, ��� ��� ������������� �� ���������� ������ �� ������� ����� ����� ������� ���� ������ (���� ��� �������� ������ ����� ������).\n��� �������� ���������� ������� ������� ������ � ������/�������, ������� ����� ��������� ��������, � ����� ������ � �������� ��� ��������. �������� ����� ����� ��������� �������� �� ���������� �����/������.\n\n�������: � ������ ���� ��� ���� ������� ���������� ��������. ������ ���� � ������ ������� ��������� ���������� ����������� �������� ��� ��������/���������. ����� ������� ����� ����� ��������, ������� ����� ���������� ������ ��� (�������� ��� ����� � ������� ���� ���-�� ��������). ���� ���������� ������ ���, ���� ����� ����� �������� ���� ������ 20% �� �� ������������� �������� ������ ���.\n��� ���� �������� ���� �������� �������.\n\n����� � ��Ѩ��� ����!\n\n\n\n(�)���� � ���� inc. 2021. ��� ����� ���������.");
    btn_size.x = rct.right / 4;
    btn_size.y = rct.right / 8;
    btn_pos.x = (rct.right / 2) - (btn_size.x / 2);
    btn_pos.y = btn_size.y / 2;

    main_menu->AddButton(newGameBtn, btn_pos, btn_size, "NEW GAME");
    btn_pos.y += btn_size.y;
    main_menu->AddButton(helpBtn, btn_pos, btn_size, "ABOUT GAME");
    btn_pos.y += btn_size.y;
    main_menu->AddButton(quitBtn, btn_pos, btn_size, "QUIT GAME");

    POINT cell_size;
    cell_size.x = rct.right / this->N;
    cell_size.y = rct.bottom / this->M;

    POINT side_menu_size;
    side_menu_size.x = cell_size.x * 4;
    side_menu_size.y = rct.bottom;

    POINT side_menu_pos;
    side_menu_pos.x = rct.right - side_menu_size.x;
    side_menu_pos.y = 0;

    btn_size.x = cell_size.x * 3;
    btn_size.y = cell_size.y * 2;

    btn_pos.x = side_menu_pos.x + (cell_size.x / 2);
    btn_pos.y = cell_size.y;
    POINT lbl_pos;
    POINT lbl_size;
    lbl_pos.x = btn_pos.x;
    lbl_pos.y = side_menu_pos.y;
    lbl_size.x = btn_size.x;
    lbl_size.y = cell_size.y / 2;

    this->default_menu = new Menu(window,hInstance,side_menu_pos,side_menu_size);
    this->action_menu = new Menu(window,hInstance,side_menu_pos,side_menu_size);
    this->build_menu = new Menu(window,hInstance,side_menu_pos,side_menu_size);
    this->HQ_spawn_menu = new Menu(window,hInstance,side_menu_pos,side_menu_size);
    this->unit_spawn_menu = new Menu(window,hInstance,side_menu_pos,side_menu_size);
    this->enemy_menu = new Menu(window,hInstance,side_menu_pos,side_menu_size);

    build_menu->AddLabel(0,lbl_pos, lbl_size,"meat;wood;iron;oil");
    unit_spawn_menu->AddLabel(0,lbl_pos, lbl_size,"meat;wood;iron;oil");
    HQ_spawn_menu->AddLabel(0,lbl_pos, lbl_size,"meat;wood;iron;oil");
    action_menu->AddButton(moveBtn,btn_pos,btn_size,"MOVE");
    build_menu->AddButton(buildBaracksBtn,btn_pos,btn_size,"Build baracks\n10;15;0;0");
    unit_spawn_menu->AddButton(spawnTrooperBtn,btn_pos,btn_size,"Spawn trooper\n3;0;3;0");
    HQ_spawn_menu->AddButton(spawnBuilderBtn,btn_pos,btn_size,"Spawn builder\n1;0;0;0");
    default_menu->AddLabel(PlayerLbl, btn_pos, btn_size, "Turn of ");
    enemy_menu->AddLabel(EnemyTypeLbl, btn_pos, btn_size, "Enemy ");

    lbl_pos.y += lbl_size.y;

    build_menu->AddLabel(resLbl,lbl_pos, lbl_size,"meat;wood;iron;oil");
    unit_spawn_menu->AddLabel(resLbl,lbl_pos, lbl_size,"meat;wood;iron;oil");
    HQ_spawn_menu->AddLabel(resLbl,lbl_pos, lbl_size,"meat;wood;iron;oil");

    btn_pos.y += btn_size.y + cell_size.y;

    HQ_spawn_menu->AddLabel(HealthLbl,btn_pos,btn_size, "Health: ");
    enemy_menu->AddLabel(EnemyHealthLbl, btn_pos, btn_size, "Health: ");
    default_menu->AddLabel(TreeAmountLbl, btn_pos, btn_size, "Tree amount: ");
    action_menu->AddButton(attackBtn,btn_pos,btn_size,"Attack");
    build_menu->AddButton(buildTowerBtn,btn_pos,btn_size,"Build tower\n0;10;1;0");
    unit_spawn_menu->AddButton(spawnJuggerBtn,btn_pos,btn_size,"Spawn juggernaut\n10;0;5;1");

    btn_pos.y += btn_size.y + cell_size.y;

    enemy_menu->AddLabel(EnemyDamageLbl, btn_pos, btn_size, "Damage: ");
    default_menu->AddLabel(MeatAmountLbl, btn_pos, btn_size, "Meat amount: ");
    action_menu->AddButton(spellBtn,btn_pos,btn_size,"Spell");
    build_menu->AddButton(buildTreeCutBtn,btn_pos,btn_size,"Build tree cutter\n0;0;5;0");
    unit_spawn_menu->AddButton(spawnSniperBtn,btn_pos,btn_size,"Spawn sniper\n5;0;10;0");

    btn_pos.y += btn_size.y + cell_size.y;

    default_menu->AddLabel(IronAmountLbl, btn_pos, btn_size, "Iron amount: ");
    action_menu->AddButton(buildBtn,btn_pos,btn_size,"Build");
    unit_spawn_menu->AddButton(endTurnBtn,btn_pos,btn_size,"End turn");

    build_menu->AddButton(buildFarmBtn,btn_pos,btn_size,"Build farm\n2;3;0;0");

    btn_pos.y += btn_size.y + cell_size.y;

    action_menu->AddLabel(UnitNameLbl, btn_pos, btn_size, "Builder");
    default_menu->AddLabel(OilAmountLbl, btn_pos, btn_size, "Oil amount: ");
    build_menu->AddButton(buildBoerBtn,btn_pos,btn_size,"Build boer\n0;5;0;0");
    unit_spawn_menu->AddLabel(HealthLbl,btn_pos,btn_size,"Health: ");

    btn_pos.y += btn_size.y + cell_size.y;

    action_menu->AddLabel(ActNumLbl, btn_pos, btn_size, "Actions more: ");
    default_menu->AddButton(endTurnBtn, btn_pos, btn_size, "End Turn");
    build_menu->AddButton(buildOilStationBtn, btn_pos, btn_size, "Build oil station\n0;30;10;0");

    btn_pos.y += btn_size.y + cell_size.y;

    build_menu->AddButton(returnBtn,btn_pos,btn_size,"Return");
    action_menu->AddLabel(HealthLbl, btn_pos, btn_size, "Health: ");

    btn_pos.y += btn_size.y + cell_size.y;

    action_menu->AddLabel(DamageLbl, btn_pos, btn_size, "Damage: ");

    return true;
}

void Game::spawn_HQ()
{
    int x, y;
    std::random_device rd;
	std::mt19937 mersenne(rd());
    Game_Object* obj = new HQ(P1->get_team());
    x = 1;
	y = (mersenne() % (M - 3)) + 1;
    obj->set_position(x,y);
    Game_Model::get_game_model()->add_object(obj);
    this->end_turn();
    obj = new HQ(P2->get_team());
    x = 33;
	y = (mersenne() % (M - 3)) + 1;
    obj->set_position(x,y);
    Game_Model::get_game_model()->add_object(obj);
    this->end_turn();
}

Player* Game::get_player(int team)
{
    for(auto p : players_list)
        if(p->get_team() == team)
            return p;
    return NULL;
}

void Game::add_object(Game_Object* obj)
{
    switch(obj->get_id())
    {
    case(UnitID):
        {
            Unit* u = dynamic_cast<Unit*>(obj);
            cur_player->buy(u);
            cur_player->add_gain(u);
        }
    break;
    case(BuildingID):
        {
            Building* b = dynamic_cast<Building*>(obj);
            cur_player->buy(b);
        }
    break;
    }
    Game_Model::get_game_model()->add_object(obj);
}

void Game::delete_object(Game_Object* del_obj)
{
    if(del_obj->get_id() == UnitID)
    {
        Unit* u = dynamic_cast<Unit*>(del_obj);
        get_player(u->get_team())->remove_gain(u);
    }
    if(del_obj->get_id() == BuildingID)
    {
        Building* b = dynamic_cast<Building*>(del_obj);
        get_player(b->get_team())->remove_gain(b);
    }
     Game_Model::get_game_model()->delete_object(del_obj);
}

void Game::show_menu(bool flag)
{
    if(flag)
    {
    if(!chosen_obj)
    {
        action_menu->hide();
        default_menu->show();
        build_menu->hide();
        HQ_spawn_menu->hide();
        unit_spawn_menu->hide();
        enemy_menu->hide();
    }
    else
    {
        switch(chosen_obj->get_id())
        {
        case(UnitID):
            {
                Unit* tmp = dynamic_cast<Unit*>(chosen_obj);
                if(tmp->get_u_id() == BuilderID)
                {
                    Builder* b = dynamic_cast<Builder*>(tmp);
                    if(b->is_build_menu_opened())
                    {
                        action_menu->hide();
                        default_menu->hide();
                        build_menu->show();
                        HQ_spawn_menu->hide();
                        unit_spawn_menu->hide();
                        enemy_menu->hide();
                    }
                    else
                    {
                        action_menu->show();
                        action_menu->get_button(buildBtn)->show();
                        default_menu->hide();
                        build_menu->hide();
                        HQ_spawn_menu->hide();
                        unit_spawn_menu->hide();
                        enemy_menu->hide();
                    }
                }
                else
                {
                    action_menu->show();
                    action_menu->get_button(buildBtn)->hide();
                    default_menu->hide();
                    build_menu->hide();
                    HQ_spawn_menu->hide();
                    unit_spawn_menu->hide();
                    enemy_menu->hide();
                }
            }
            break;
        case(BuildingID):
            {
                Building* tmp = dynamic_cast<Building*>(chosen_obj);
                if(tmp->get_cur_build_count() <= 0)
                {
                    if(tmp->get_b_id() == HQID)
                    {
                        action_menu->hide();
                        default_menu->hide();
                        build_menu->hide();
                        HQ_spawn_menu->show();
                        unit_spawn_menu->hide();
                        enemy_menu->hide();
                    }
                    if(tmp->get_b_id() == BaracksID)
                    {
                        action_menu->hide();
                        default_menu->hide();
                        build_menu->hide();
                        HQ_spawn_menu->hide();
                        unit_spawn_menu->show();
                        enemy_menu->hide();
                    }
                }
            }
            break;
        default:
            {
                action_menu->hide();
                default_menu->show();
                build_menu->hide();
                HQ_spawn_menu->hide();
                unit_spawn_menu->hide();
                enemy_menu->hide();
            }
            break;
        }
    }
    }
    else
    {
        action_menu->hide();
        default_menu->hide();
        build_menu->hide();
        HQ_spawn_menu->hide();
        unit_spawn_menu->hide();
        enemy_menu->hide();
    }
}

void Game::show_states()
{
    std::string text = "Turn of " + string(cur_player->get_name());
    this->default_menu->get_label(PlayerLbl)->change_text(strdup(text.c_str()));

    text = std::to_string(cur_player->get_meat_amount()) + ";" + std::to_string(cur_player->get_wood_amount()) + ";" + std::to_string(cur_player->get_iron_amount()) + ";" + std::to_string(cur_player->get_oil_amount());
    this->HQ_spawn_menu->get_label(resLbl)->change_text(strdup(text.c_str()));
    this->unit_spawn_menu->get_label(resLbl)->change_text(strdup(text.c_str()));
    this->build_menu->get_label(resLbl)->change_text(strdup(text.c_str()));

    if(!chosen_obj || chosen_obj->get_id() == CellID)
    {
    text = "Meat: " + std::to_string(cur_player->get_meat_amount()) + " (";
    if(cur_player->get_meat_gain() >= 0)
        text += "+";
    text += std::to_string(cur_player->get_meat_gain()) + ")";
    default_menu->get_label(MeatAmountLbl)->change_text(strdup(text.c_str()));

    text = "Wood: " + std::to_string(cur_player->get_wood_amount()) + " (";
    if(cur_player->get_wood_gain() >= 0)
        text += "+";
    text += std::to_string(cur_player->get_wood_gain()) + ")";
    default_menu->get_label(TreeAmountLbl)->change_text(strdup(text.c_str()));

    text = "Iron: " + std::to_string(cur_player->get_iron_amount()) + " (";
    if(cur_player->get_iron_gain() >= 0)
        text += "+";
    text += std::to_string(cur_player->get_iron_gain()) + ")";
    default_menu->get_label(IronAmountLbl)->change_text(strdup(text.c_str()));

    text = "Oil: " + std::to_string(cur_player->get_oil_amount()) + " (";
    if(cur_player->get_oil_gain() >= 0)
        text += "+";
    text += std::to_string(cur_player->get_oil_gain()) + ")";
    default_menu->get_label(OilAmountLbl)->change_text(strdup(text.c_str()));
    }
    else {
    if(chosen_obj->get_id() == UnitID)
    {
        Unit* u = dynamic_cast<Unit*>(chosen_obj);
        action_menu->get_label(UnitNameLbl)->change_text(strdup(u->get_name().c_str()));
        text = "Actions more: " + std::to_string(u->get_cur_act_num());
        action_menu->get_label(ActNumLbl)->change_text(strdup(text.c_str()));
        text = "Health: " + std::to_string(u->get_cur_health());
        action_menu->get_label(HealthLbl)->change_text(strdup(text.c_str()));
        text = "Damage: " + std::to_string(u->get_damage());
        action_menu->get_label(DamageLbl)->change_text(strdup(text.c_str()));
    }
    if(chosen_obj->get_id() == EnemyID)
    {
        Unit* u = dynamic_cast<Unit*>(chosen_obj);
        text = "Enemy ";
        switch(u->get_u_id())
        {

            case(TrooperID):
                text += "trooper";
            break;
            case(JuggernautID):
                text += "juggernaut";
            break;
            case(SniperID):
                text += "sniper";
            break;
            case(BuilderID):
                text += "builder";
            break;
        }
        default_menu->get_label(TreeAmountLbl)->change_text(strdup(text.c_str()));
        text = "Health: " + std::to_string(u->get_cur_health());
        default_menu->get_label(MeatAmountLbl)->change_text(strdup(text.c_str()));
        text = "Damage: " + std::to_string(u->get_damage());
        default_menu->get_label(IronAmountLbl)->change_text(strdup(text.c_str()));
        default_menu->get_label(OilAmountLbl)->change_text("");
    }
    if(chosen_obj->get_id() == EnemyBuildingID)
    {
        Building* b = dynamic_cast<Building*>(chosen_obj);
        text = "Enemy ";
        switch(b->get_b_id())
        {
        case(HQID):
            text += "HQ";
        break;
        case(BaracksID):
            text += "baracks";
        break;
        case(TowerID):
            text += "tower";
        break;
        case(TreecutterID):
            text += "tree cutter";
        break;
        case(FarmID):
            text += "farm";
        break;
        case(BoerID):
            text += "iron mine";
        break;
        case(OilID):
            text += "oil station";
        break;
        }
        default_menu->get_label(TreeAmountLbl)->change_text(strdup(text.c_str()));
        text = "Health: " + std::to_string(b->get_cur_health());
        default_menu->get_label(MeatAmountLbl)->change_text("");
        default_menu->get_label(IronAmountLbl)->change_text("");
        default_menu->get_label(OilAmountLbl)->change_text("");
    }
    if(chosen_obj->get_id() == BuildingID)
    {
        Building* b = dynamic_cast<Building*>(chosen_obj);
        text = "Health: " + std::to_string(b->get_cur_health());
        HQ_spawn_menu->get_label(HealthLbl)->change_text(strdup(text.c_str()));
        unit_spawn_menu->get_label(HealthLbl)->change_text(strdup(text.c_str()));
        std::string text1 = "";
        switch(b->get_b_id())
        {
        case(TowerID):
            text = "Tower";
        break;
        case(TreecutterID):
            text = "Tree cutter";
            text1 += std::to_string(b->get_res_gain(Tree));
        break;
        case(FarmID):
            text = "Farm";
            text1 += std::to_string(b->get_res_gain(Meat));
        break;
        case(BoerID):
            text = "Iron mine";
            text1 += std::to_string(b->get_res_gain(Iron));
        break;
        case(OilID):
            text = "Oil station";
            text1 += std::to_string(b->get_res_gain(Oil));
        break;
        }
        default_menu->get_label(TreeAmountLbl)->change_text(strdup(text.c_str()));
        text = "Health: " + std::to_string(b->get_cur_health());
        default_menu->get_label(MeatAmountLbl)->change_text(strdup(text.c_str()));
        text = "Gain: +" + text1;
        default_menu->get_label(IronAmountLbl)->change_text("");
        default_menu->get_label(OilAmountLbl)->change_text("");
    }
    if(chosen_obj->get_id() == ResourceID)
    {
        std::string text1 = "";
        Resource* r = dynamic_cast<Resource*>(chosen_obj);
        switch(r->get_type())
        {
        case(Tree):
            text = "Tree";
            text1 = "Wood +" + std::to_string(r->get_gain());
        break;
        case(Iron):
            text = "Iron";
            text1 = "Iron +" + std::to_string(r->get_gain());
        break;
        case(Oil):
            text = "Oil";
            text1 = "Oil +" + std::to_string(r->get_gain());
        break;
        }
        default_menu->get_label(TreeAmountLbl)->change_text(strdup(text.c_str()));
        default_menu->get_label(MeatAmountLbl)->change_text(strdup(text1.c_str()));
        default_menu->get_label(IronAmountLbl)->change_text("");
        default_menu->get_label(OilAmountLbl)->change_text("");
    }
    }
}

void Game::end_action()
{
    if(chosen_obj && chosen_obj->get_id() == UnitID)
    {
        Unit* u = dynamic_cast<Unit*>(chosen_obj);
        if(u->get_u_id() == BuilderID)
        {
            Builder* b = dynamic_cast<Builder*>(u);
            if(b->is_build_menu_opened())
                b->show_build_menu(false);
        }
    }
    for(int i= 0; i < M; i++)
        for(int j = 0; j < N; j++)
            map->get_cell(i,j)->chosen(false);
    chosen_obj = NULL;
    action_obj = NULL;
}

void Game::show()
{
    if(!game_started)
    {
        if(!help_shown)
        {
            main_menu->show();
            help->hide();
            show_menu(false);
        }
        else
        {
            main_menu->hide();
            help->show();
            show_menu(false);
        }
    }
    else
    {
        main_menu->hide();
        show_menu(true);
        show_states();
        update_view_grid();
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
            {
                if(map->get_cell(i,j)->is_shown())
                    map->get_cell(i,j)->draw(M,N,textures);
            }
        Game_Model::get_game_model()->reset_iter();
        while(!Game_Model::get_game_model()->objects_ended())
        {
            if(Game_Model::get_game_model()->get_iter_object()->is_shown())
                Game_Model::get_game_model()->get_iter_object()->draw(M,N,textures);
            Game_Model::get_game_model()->increase_iter();
        }
        Game_Model::get_game_model()->update_particles(M,N,textures);

    }
}

void Game::change_cur_player()
{
    cur_player == P1 ? cur_player = P2 : cur_player = P1;
    Game_Model::get_game_model()->reset_iter();
    while(!Game_Model::get_game_model()->objects_ended())
    {
        Game_Object* obj = Game_Model::get_game_model()->get_iter_object();
        switch(obj->get_id())
        {
        case(UnitID):
            obj->set_id(EnemyID);
        break;
        case(BuildingID):
            obj->set_id(EnemyBuildingID);
        break;

        case(EnemyID):
            {
                obj->set_id(UnitID);
                Unit* u = dynamic_cast<Unit*>(obj);
                u->set_cur_act_num(u->get_max_act_num());
                if(cur_player->get_meat_amount() == 0)
                {
                    u->set_cur_health(u->get_cur_health() - (u->get_max_health()/ 5));
                    if(u->get_cur_health() <= 0)
                    {
                        Particle* p = new Particle(Blood);
                        p->set_position(obj->get_position());
                        Game_Model::get_game_model()->add_particle(p);
                        delete_object(obj);
                    }
                }

            }
        break;

        case(EnemyBuildingID):
            {
                (obj)->set_id(BuildingID);
                Building* b = dynamic_cast<Building*>(obj);
                b->set_cur_act_num(b->get_max_act_num());
                if(b->get_cur_build_count() > 0)
                {
                    if(b->get_cur_build_count() == 1)
                        cur_player->add_gain(b);
                    b->set_cur_build_count(b->get_cur_build_count() - 1);
                }
            }
        break;
        }
        Game_Model::get_game_model()->increase_iter();
    }
}

void Game::end_turn()
{
    this->end_action();
    cur_player->update_resources_amount();
    this->change_cur_player();
}

void Game::update_view_grid()
{
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            view_grid[i][j] = false;
    Game_Model::get_game_model()->reset_iter();
    while(!Game_Model::get_game_model()->objects_ended())
    {
        Game_Object* obj = Game_Model::get_game_model()->get_iter_object();
        Building* b = NULL;
        if(obj->get_id() == BuildingID)
            b = dynamic_cast<Building*>(obj);
        if((obj->get_id() == UnitID || obj->get_id() == BuildingID) && obj->get_view_rad() > 0)
        {
            if(b && b->get_cur_build_count() > 0)
                break;
            for(int i = obj->get_position().y - obj->get_view_rad(); i <= obj->get_position().y + obj->get_size().y - 1 + obj->get_view_rad(); i++)
                for(int j = obj->get_position().x - obj->get_view_rad(); j <= obj->get_position().x + obj->get_size().x - 1 + obj->get_view_rad(); j++)
                {
                    if(i < 0)
                        i = 0;
                    if(j < 0)
                        j = 0;
                    if(i > M - 1)
                        i = M - 1;
                    if(j > N - 1)
                        j = N - 1;
                    view_grid[i][j] = true;
                }
        }
        Game_Model::get_game_model()->increase_iter();
    }
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
    {
        map->get_cell(i,j)->visible(view_grid[i][j]);
        if(Game_Model::get_game_model()->get_object(j,i))
            Game_Model::get_game_model()->get_object(j,i)->visible(view_grid[i][j]);
    }
}
