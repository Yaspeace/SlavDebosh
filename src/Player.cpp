#include "Player.h"

Player::Player(int team, char* name)
{
    this->name = name;
    this->team = team;

    set_meat_amount(15);
    set_wood_amount(10);
    set_iron_amount(5);
    set_oil_amount(0);

    set_meat_gain(0);
    set_wood_gain(0);
    set_iron_gain(0);
    set_oil_gain(0);
}

void Player::update_resources_gain()
{
    int meat = 0, wood = 0, iron = 0, oil = 0;
    Game_Model* gm_pointer = Game_Model::get_game_model();
    gm_pointer->reset_iter();
    while(!gm_pointer->objects_ended())
    {
        switch(gm_pointer->get_iter_object()->get_id())
        {
        case(UnitID):
        case(EnemyID):
            {
            Unit* u = dynamic_cast<Unit*>(gm_pointer->get_iter_object());
            if(u->get_team() == this->get_team())
            {
                meat += u->get_res_gain(Meat);
                wood += u->get_res_gain(Tree);
                iron += u->get_res_gain(Iron);
                oil += u->get_res_gain(Oil);
            }
            }
        break;
        case(BuildingID):
        case(EnemyBuildingID):
            {
            Building* b = dynamic_cast<Building*>(gm_pointer->get_iter_object());
            if(b->get_team() == this->get_team() && b->get_cur_build_count() <= 0)
            {
                meat += b->get_res_gain(Meat);
                wood += b->get_res_gain(Tree);
                iron += b->get_res_gain(Iron);
                oil += b->get_res_gain(Oil);
            }
            }
        break;
        }
        gm_pointer->increase_iter();
    }
    this->set_meat_gain(meat);
    this->set_wood_gain(wood);
    this->set_iron_gain(iron);
    this->set_oil_gain(oil);
}

void Player::update_resources_amount()
{
    set_meat_amount(get_meat_amount() + get_meat_gain());
    if(get_meat_amount() < 0)
        set_meat_amount(0);
    set_wood_amount(get_wood_amount() + get_wood_gain());
    if(get_wood_amount() < 0)
        set_wood_amount(0);
    set_iron_amount(get_iron_amount() + get_iron_gain());
    if(get_iron_amount() < 0)
        set_iron_amount(0);
    set_oil_amount(get_oil_amount() + get_oil_gain());
    if(get_oil_amount() < 0)
        set_oil_amount(0);
}

bool Player::is_anough(int meat, int wood, int iron, int oil)
{
    return (get_meat_amount() >= meat && get_wood_amount() >= wood && get_iron_amount() >= iron && get_oil_amount() >= oil);
}

bool Player::is_anough(Unit* u)
{
    return (get_meat_amount() >= u->get_res_cost(Meat) && get_wood_amount() >= u->get_res_cost(Tree) && get_iron_amount() >= u->get_res_cost(Iron) && get_oil_amount() >= u->get_res_cost(Oil));
}

bool Player::is_anough(Building* b)
{
    return (get_meat_amount() >= b->get_res_cost(Meat) && get_wood_amount() >= b->get_res_cost(Tree) && get_iron_amount() >= b->get_res_cost(Iron) && get_oil_amount() >= b->get_res_cost(Oil));
}

void Player::buy(Unit* u)
{
    set_iron_amount(get_iron_amount() - u->get_res_cost(Iron));
    set_meat_amount(get_meat_amount() - u->get_res_cost(Meat));
    set_wood_amount(get_wood_amount() - u->get_res_cost(Tree));
    set_oil_amount(get_oil_amount() - u->get_res_cost(Oil));
}

void Player::buy(Building* b)
{
    set_iron_amount(get_iron_amount() - b->get_res_cost(Iron));
    set_meat_amount(get_meat_amount() - b->get_res_cost(Meat));
    set_wood_amount(get_wood_amount() - b->get_res_cost(Tree));
    set_oil_amount(get_oil_amount() - b->get_res_cost(Oil));
}
