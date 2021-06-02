#pragma once

#include <string>
#include <chrono>
#include <time.h>
#include "gl/gl.h"
#include "Game_Object.h"
#include "Game_Model.h"
#include "Building.h"
#include "Resourse.h"

using namespace std;

enum U_ID {TrooperID, JuggernautID, SniperID, BuilderID}; // ID ���� ������

struct Unit_attributes
{
    string unit_name;

    int team;

    int damage;

    int cur_health;
    int max_health;

    int rad_move;
    int rad_attack;

    int max_act_num;
    int cur_act_num;

    int fov;

    bool on_high;

    U_ID u_id;

    Resource_t res_cost;
    Resource_t res_gain;

    bool flipped = false;
};

class Unit : public Game_Object
{
public:
	Unit(int team);

	void set_fov(int num) {this->unit_attributes.fov = num;};

	void set_team(int team) {this->unit_attributes.team = team;};
	void set_damage(int damage) {this->unit_attributes.damage = damage;};
	void set_rad_move(int rad) {this->unit_attributes.rad_move = rad;};
	void set_rad_attack(int rad) {this->unit_attributes.rad_attack = rad;};
	void set_max_act_num(int num) {this->unit_attributes.max_act_num = num;};
	void set_cur_act_num(int num) {this->unit_attributes.cur_act_num = num;};
    void set_cur_health (int num) {this->unit_attributes.cur_health = num;};
    void set_max_health (int num) {this->unit_attributes.max_health = num;};
    void set_u_id(U_ID id) {this->unit_attributes.u_id = id;};
    void set_res_gain(Res_Type type, int gain);
    void set_res_cost(Res_Type type, int cost);


    int get_fov() {return this->unit_attributes.fov;};

	int get_team() {return this->unit_attributes.team;};
    int get_rad_move() {return this->unit_attributes.rad_move;};
    int get_rad_attack() {return this->unit_attributes.rad_attack;};
	int get_cur_health() {return this->unit_attributes.cur_health;};
	int get_max_health() {return this->unit_attributes.max_health;};
	int get_damage() {return this->unit_attributes.damage;};
	int get_max_act_num() {return this->unit_attributes.max_act_num;};
	int get_cur_act_num() {return this->unit_attributes.cur_act_num;};
	int get_u_id() {return this->unit_attributes.u_id;};
	int get_res_gain(Res_Type type);
	int get_res_cost(Res_Type type);
	string get_name() {return this->unit_attributes.unit_name;}

	void flip() {this->unit_attributes.flipped = !this->unit_attributes.flipped;}
    void attack(Game_Object* obj);
	void move_to(int dx, int dy);
    virtual void spell(Game_Object* action_obj) = 0;
protected:
    Unit_attributes unit_attributes;

    void deal_damage(Unit* unit_to_attack);
    void deal_damage(Building* building_to_attack);

    bool check_move(int x, int y);
    bool check_attack(int x, int y);

    void draw_hp_bar(int M, int N);
};

class Trooper : public Unit
{
public:
    int grenade_count = 2;
    Trooper(int team) : Unit(team)
	{
	    this->unit_attributes.unit_name = "Trooper";

	    this->set_fov(4);
	    this->set_damage(5);
	    this->set_cur_health(20);
	    this->set_max_health(20);

	    this->set_u_id(TrooperID);
        this->set_rad_attack(3);
        this->set_rad_move(3);
        this->set_max_act_num(2);
        this->set_cur_act_num(0);
        set_res_gain(Meat,-2);
        set_res_cost(Meat, 3);
        set_res_cost(Iron, 3);
		set_view_rad(get_rad_attack());
	}
	void spell(Game_Object* action_obj) override;
    void draw(int M, int N, Texture* textures) override;
};

class Juggernaut : public Unit
{
public:
    bool spell_on = false;
	Juggernaut(int team) : Unit(team)
	{
	    this->unit_attributes.unit_name = "Juggernaut";

        this->set_fov(3);
	    this->set_damage(3);
	    this->set_cur_health(40);
	    this->set_max_health(40);

	    this->set_u_id(JuggernautID);
	    this->set_rad_attack(2);
        this->set_rad_move(2);
        this->set_max_act_num(2);
        this->set_cur_act_num(0);
        set_res_gain(Meat,-3);
        set_res_cost(Oil, 1);
        set_res_cost(Meat, 10);
        set_res_cost(Iron, 5);
		set_view_rad(get_rad_attack());
	}
    void spell(Game_Object* action_obj) override;
    void draw(int M, int N, Texture* textures) override;
};

class Sniper : public Unit
{
public:
    bool spell_on = false;
	Sniper(int team) : Unit(team)
	{
	    this->unit_attributes.unit_name = "Sniper";

        this->set_fov(4);
	    this->set_damage(6);
	    this->set_cur_health(10);
	    this->set_max_health(10);

	    this->set_u_id(SniperID);
	    this->set_rad_attack(3);
        this->set_rad_move(4);
        this->set_max_act_num(3);
        this->set_cur_act_num(0);
        set_res_gain(Meat,-3);
        set_res_cost(Meat, 5);
        set_res_cost(Iron, 10);
		set_view_rad(get_rad_attack());
	}
    void spell(Game_Object* action_obj) override;
    void draw(int M, int N, Texture* textures) override;
};

class Builder : public Unit
{
private:
    bool build_menu_opened = false;
public:
	Builder(int team) : Unit(team)
	{
	    this->unit_attributes.unit_name = "builder";

        this->set_fov(3);
	    this->set_damage(1);
	    this->set_cur_health(5);
	    this->set_max_health(5);

        this->set_u_id(BuilderID);
	    this->set_rad_attack(2);
        this->set_rad_move(2);
        this->set_max_act_num(2);
        this->set_cur_act_num(0);
        set_res_gain(Meat,-1);
        set_res_cost(Meat, 1);
		set_view_rad(get_rad_attack());
	}
    void spell(Game_Object* action_obj)  override;
    static Game_Object* spawn_building(int ID, int team);
    void show_build_menu(bool flag) {this->build_menu_opened = flag;}
    bool is_build_menu_opened() {return this->build_menu_opened;}
    void draw(int M, int N, Texture* textures) override;
};
