#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "Unit.h"
#include "Building.h"
#include "Spawner.h"
#include "Resourse.h"
#include "Field.h"
#include "Textures.h"
#include "Player.h"
#include "Game_Model.h"
#include "Particle.h"
#include <list>
#include <string>

using namespace std;

class Game
{
    public:
        Player* P1;
        Player* P2;
        Player* cur_player;

        std::list<Player*> players_list;

        Game(int M, int N)
        {
            this->M = M;
            this->N = N;
            map = new Field(M,N);
            P1 = new Player(1, "BLUE");
            players_list.push_back(P1);
            P2 = new Player(2, "RED");
            players_list.push_back(P2);
            cur_player = P1;
            game_started = false;
            view_grid = new bool*[M];
            for(int i = 0; i < M; i++)
            {
                view_grid[i] = new bool[N];
                for(int j = 0; j < N; j++)
                    view_grid[i][j] = false;
            }
        }
        bool load(HWND window, HINSTANCE hInstance);
        Game_Object* chosen_obj = NULL;
        Game_Object* action_obj = NULL;

        Field* get_field() {return map;}

        Texture* textures;
        Field* map;

        void add_object(Game_Object* obj);
        void delete_object(Game_Object* del_obj);

        int N;
        int M;

        void start() {this->game_started = true;}
        void end_game() {this->game_started = false;}
        void show_help() {help->show(); this->help_shown = true;}
        void hide_help() {help->hide(); this->help_shown = false;}
        void show();
        void end_action();
        void end_turn();

        Player* get_player(int team);
    private:
        void spawn_HQ();
        void show_menu(bool flag);
        void show_states();
        void change_cur_player();
        void update_view_grid();
        bool game_started;
        bool help_shown;
        //std::list<Menu> menus;
        Menu* default_menu;
        Menu* action_menu;
        Menu* build_menu;
        Menu* HQ_spawn_menu;
        Menu* unit_spawn_menu;
        Menu* enemy_menu;
        Menu* main_menu;
        Menu* help;
        bool** view_grid;
};

#endif // GAME_H
