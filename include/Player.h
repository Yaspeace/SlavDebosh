#ifndef PLAYER_H
#define PLAYER_H

#include "Resourse.h"
#include "Unit.h"
#include "Building.h"

class Player
{
    public:
        Player(int team, char* name);

        int get_team() {return this->team;}
        char* get_name() {return this->name;}
        int get_meat_amount() {return this->resources_amount.meat;}
        int get_wood_amount() {return this->resources_amount.wood;}
        int get_iron_amount() {return this->resources_amount.iron;}
        int get_oil_amount() {return this->resources_amount.oil;}
        int get_meat_gain() {return this->resources_gain.meat;}
        int get_wood_gain() {return this->resources_gain.wood;}
        int get_iron_gain() {return this->resources_gain.iron;}
        int get_oil_gain() {return this->resources_gain.oil;}

        void set_meat_amount(int amount) {this->resources_amount.meat = amount;}
        void set_wood_amount(int amount) {this->resources_amount.wood = amount;}
        void set_iron_amount(int amount) {this->resources_amount.iron = amount;}
        void set_oil_amount(int amount) {this->resources_amount.oil = amount;}

        void set_meat_gain(int gain) {this->resources_gain.meat = gain;}
        void set_wood_gain(int gain) {this->resources_gain.wood = gain;}
        void set_iron_gain(int gain) {this->resources_gain.iron = gain;}
        void set_oil_gain(int gain) {this->resources_gain.oil = gain;}

        void update_resources_amount();
        bool is_anough(int meat, int wood, int iron, int oil);
        bool is_anough(Unit* u);
        bool is_anough(Building* b);

        void add_gain(Unit* u);
        void add_gain(Building* b);
        void remove_gain(Unit* u);
        void remove_gain(Building* b);
        void buy(Unit* u);
        void buy(Building* b);

    private:
        int team;
        char* name;
        Resource_t resources_amount;
        Resource_t resources_gain;
};

#endif // PLAYER_H
