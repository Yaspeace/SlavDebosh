#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED
#include <string>
#include <iostream>
#include "Game_Object.h"
#include "gl/gl.h"
#include "Resourse.h"

enum B_ID {HQID, BaracksID, TowerID, BoerID, FarmID, TreecutterID, OilID};

using namespace std;

struct Building_attributes
{
    string building_name[32];

    int team;

    int max_build_count;
    int cur_build_count;

    int cur_health;
    int max_health;

    int cur_act_num;
    int max_act_num;

    B_ID b_id;

    Resource_t resource_cost;
    Resource_t resource_gain;
};

class Building : public Game_Object
{
public:
    Building(int team);

	void set_max_build_count(int num) {this->building_attributes.max_build_count = num;};
	void set_cur_build_count(int num) {this->building_attributes.cur_build_count = num;};
	void set_cur_health(int num) {this->building_attributes.cur_health = num;};
	void set_max_health(int num) {this->building_attributes.max_health = num;};
	void set_max_act_num(int num) {this->building_attributes.max_act_num = num;};
	void set_cur_act_num(int num) {this->building_attributes.cur_act_num = num;};
    void set_b_id(B_ID id) {this->building_attributes.b_id = id;};
    void set_res_cost(Res_Type type, int cost);
    void set_res_gain(Res_Type type, int gain);

    int get_max_build_count() {return this->building_attributes.max_build_count;};
    int get_cur_build_count() {return this->building_attributes.cur_build_count;};
	int get_team() {return this->building_attributes.team;};
	int get_cur_health() {return this->building_attributes.cur_health;};
	int get_max_health() {return this->building_attributes.max_health;};
    int get_max_act_num() {return this->building_attributes.max_act_num;};
	int get_cur_act_num() {return this->building_attributes.cur_act_num;};
	int get_b_id() {return this->building_attributes.b_id;};
	int get_res_cost(Res_Type type);
	int get_res_gain(Res_Type type);

    Game_Object* spawn_unit(int ID, int team);
protected:
    Building_attributes building_attributes;
    void draw_hp_bar(int M, int N);
};

class HQ: public Building
{
public:
    HQ(int team) : Building(team)
    {
        this->set_b_id(HQID);
        this->set_max_build_count(0);
        this->set_cur_build_count(0);
        this->set_cur_act_num(1);
        this->set_max_act_num(1);
        this->set_cur_health(12);
        this->set_max_health(12);
        this->object_attributes.size = {2,2};
		set_view_rad(2);
    }
    void draw(int M, int N, Texture* textures) override;
};

class Baracks : public Building
{
public:
    int grenade_count = 2;
    Baracks(int team) : Building(team)
    {
        this->set_b_id(BaracksID);
        this->set_max_build_count(2);
        this->set_cur_build_count(2);
        this->set_cur_act_num(1);
        this->set_max_act_num(1);
        this->set_cur_health(8);
        this->set_max_health(8);
        this->object_attributes.size = {2,2};
        set_res_cost(Tree, 15);
        set_res_cost(Meat, 10);
		set_view_rad(1);
    }
    void draw(int M, int N, Texture* textures) override;
};

class Tower : public Building
{
public:
    Tower(int team) : Building(team)
    {
        this->set_b_id(TowerID);
        this->set_max_build_count(1);
        this->set_cur_build_count(1);
        this->set_cur_act_num(1);
        this->set_max_act_num(1);
        this->set_cur_health(4);
        this->set_max_health(4);
        set_res_cost(Tree,10);
        set_res_cost(Iron, 1);
		set_view_rad(4);
    }
    void draw(int M, int N, Texture* textures) override;
};

class Boer : public Building
{
public:
    Boer(int team) : Building(team)
    {
        this->set_b_id(BoerID);
        this->set_max_build_count(1);
        this->set_cur_build_count(1);
        this->set_cur_health(4);
        this->set_max_health(4);
        set_res_cost(Tree, 5);
		set_view_rad(1);
    }
    void draw(int M, int N, Texture* textures) override;
};

class Farm : public Building
{
public:
    Farm(int team) : Building(team)
    {
        this->set_b_id(FarmID);
        this->set_max_build_count(1);
        this->set_cur_build_count(1);
        this->set_cur_health(2);
        this->set_max_health(2);
        this->object_attributes.size = {2,2};
        set_res_gain(Meat, 2);
        set_res_cost(Tree, 3);
		set_view_rad(1);
    }
    void draw(int M, int N, Texture* textures) override;
};

class Treecutter : public Building
{
public:
    Treecutter(int team) : Building(team)
    {
        this->set_b_id(TreecutterID);
        this->set_max_build_count(1);
        this->set_cur_build_count(1);
        this->set_cur_health(2);
        this->set_max_health(2);
        set_res_cost(Iron,5);
		set_view_rad(1);
    }
    void draw(int M, int N, Texture* textures) override;
};

class Oil_Station : public Building
{
public:
    Oil_Station(int team) : Building(team)
    {
        this->set_b_id(OilID);
        this->set_max_build_count(1);
        this->set_cur_build_count(1);
        this->set_cur_health(4);
        this->set_max_health(4);
        set_res_cost(Iron, 10);
        set_res_cost(Tree, 30);
		set_view_rad(1);
    }
    void draw(int M, int N, Texture* textures) override;
};


#endif // BUILDING_H_INCLUDED
