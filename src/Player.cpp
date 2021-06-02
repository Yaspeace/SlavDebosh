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

void Player::add_gain(Unit* u)
{
    set_iron_gain(get_iron_gain() + u->get_res_gain(Iron));
    set_meat_gain(get_meat_gain() + u->get_res_gain(Meat));
    set_wood_gain(get_wood_gain() + u->get_res_gain(Tree));
    set_oil_gain(get_oil_gain() + u->get_res_gain(Oil));
}

void Player::add_gain(Building* b)
{
    set_iron_gain(get_iron_gain() + b->get_res_gain(Iron));
    set_meat_gain(get_meat_gain() + b->get_res_gain(Meat));
    set_wood_gain(get_wood_gain() + b->get_res_gain(Tree));
    set_oil_gain(get_oil_gain() + b->get_res_gain(Oil));
}

void Player::remove_gain(Unit* u)
{
    set_iron_gain(get_iron_gain() - u->get_res_gain(Iron));
    set_meat_gain(get_meat_gain() - u->get_res_gain(Meat));
    set_wood_gain(get_wood_gain() - u->get_res_gain(Tree));
    set_oil_gain(get_oil_gain() - u->get_res_gain(Oil));
}

void Player::remove_gain(Building* b)
{
    set_iron_gain(get_iron_gain() - b->get_res_gain(Iron));
    set_meat_gain(get_meat_gain() - b->get_res_gain(Meat));
    set_wood_gain(get_wood_gain() - b->get_res_gain(Tree));
    set_oil_gain(get_oil_gain() - b->get_res_gain(Oil));
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
