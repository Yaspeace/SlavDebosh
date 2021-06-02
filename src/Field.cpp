#include "Field.h"

static int trees_num = 0;
static int ore_count = 0;
static int oil_count = 0;

using namespace std;

Field::Field(int M, int N)
{
	this->M = M;
	this->N = N;
	a = new Cell*[M];
	for(int i = 0; i < M; i++)
    {
        a[i] = new Cell[N];
        for(int j = 0; j < N; j++)
            a[i][j].set_position(j,i);
    }
}

void Field::make_high()
{
	int t1, t2, i = 0;
	std::random_device rd;
	std::mt19937 mersenne(rd());
    int x = (mersenne() % (M - 3)) + 1;
    int y = (mersenne() % (N - 11)) + 4;
	int count = mersenne() % 150;
	this->a[x][y].set_type(hg);
	while (i < count)
	{
		std::random_device rb;
		std::mt19937 mersenne(rb());
		t1 = x - 1 + (mersenne() % 3);
		t2 = y - 1 + (mersenne() % 3);
			if ((t1 < this->M - 3) && (t2 < this->N - 11) && (t1 > 1) && (t2 > 4) && (this->a[t1][t2].get_type() != hg))
			{
				x = t1;
				y = t2;
				this->a[x][y].set_type(hg);
				i++;
			}
			else
			{
				std::random_device rc;
				std::mt19937 mersenne(rc());
				x = (mersenne() % (M - 3)) + 1;
                y = (mersenne() % (N - 11)) + 4;
				this->a[x][y].set_type(hg);
				i++;
			}
		}
}

void Field::make_ore()
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    while(ore_count < 10)
    {
        int x, y;
        do
        {
            x = (mersenne() % (M - 3)) + 1;
            y = (mersenne() % (N - 6));
        }while(this->get_cell(x,y)->get_type() == water ||  this->get_cell(x,y)->get_type() == hg || Game_Model::get_game_model()->get_object(y,x));
        Game_Object* tmp = new Resource(Iron, (mersenne() % 4) + 1);
        tmp->set_position(y,x);
        Game_Model::get_game_model()->add_object(tmp);
        ore_count++;
        make_ore();
    }
}

void Field::make_oil()
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    while(oil_count < 5)
    {
        int x, y;
        do
        {
            x = (mersenne() % (M - 3)) + 1;
            y = (mersenne() % (N - 22)) + 8;
        }while(this->get_cell(x,y)->get_type() == water ||  this->get_cell(x,y)->get_type() == hg || Game_Model::get_game_model()->get_object(y,x));
        Game_Object* tmp = new Resource(Oil, (mersenne() % 4) + 1);
        tmp->set_position(y,x);
        Game_Model::get_game_model()->add_object(tmp);
        oil_count++;
        make_oil();
    }
}

void Field::make_forest()
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    while(trees_num < 100) {
    int x, y;
    do
    {
        x = (mersenne() % (M - 3)) + 1;
        y = (mersenne() % (N - 6));
    }while(this->get_cell(x,y)->get_type() == water ||  this->get_cell(x,y)->get_type() == hg || Game_Model::get_game_model()->get_object(y,x));

    Game_Object* tmp = new Resource(Tree, mersenne() % 3);
    tmp->set_position(y,x);
    Game_Model::get_game_model()->add_object(tmp);
    trees_num++;

    if(this->a[x][y+1].get_type() != water  && this->a[x][y+1].get_type() != hg && !Game_Model::get_game_model()->get_object(y+1,x))
    {
        tmp = new Resource(Tree, (mersenne() % 3) + 1);
        tmp->set_position(y+1,x);
        Game_Model::get_game_model()->add_object(tmp);
        trees_num++;
    }
    else make_forest();

    if(this->a[x+1][y].get_type() != water  && this->a[x+1][y].get_type() != hg && !Game_Model::get_game_model()->get_object(y,x+1))
    {
        tmp = new Resource(Tree, (mersenne() % 3) + 1);
        tmp->set_position(y,x+1);
        Game_Model::get_game_model()->add_object(tmp);
        trees_num++;
    }
    else make_forest();

    if(this->a[x+1][y+1].get_type() != water  && this->a[x+1][y+1].get_type() != hg && !Game_Model::get_game_model()->get_object(y+1,x+1))
    {
        tmp = new Resource(Tree, (mersenne() % 3) + 1);
        tmp->set_position(y+1,x+1);
        Game_Model::get_game_model()->add_object(tmp);
        trees_num++;
    }
    else make_forest();
    }
}



void Field::make_river()
{
    int i = 0;
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int x = (mersenne() % (M - 3)) + 1;
    int y = (mersenne() % (N - 11)) + 4;
    int count = mersenne() % 100;
    this->a[x][y].set_type(water);
    while (i < count)
    {
        std::random_device rb;
        std::mt19937 mersenne(rb());
        int counts = (mersenne() % 3)+1;
        int j = 0;
        int t = 1;
        while ((t + x < this->M - 3) && (j < counts))
        {
            this->a[x + 1][y].set_type(water);
            t++;
            j++;
        }
        t = 1;
        while ((x - t > 3) && (j<counts))
        {
            this->a[x-t][y].set_type(water);
            j++;
            t++;
        }
        do
        {
            x = x - 1 + (mersenne() % 3);
            y = y - 1 + (mersenne() % 3);
        } while ((this->M - 3 <= x) || (this->N - 11 <= y) || (1 >= x) || (4 >= y));
        this->a[x][y].set_type(water);
        i++;
    }
}

void Field::generation()
{
	for (int i = 0; i < this->M; i++)
		for (int j = 0; j < this->N; j++)
			this->a[i][j].set_type(grass);
	std::random_device rd;
	std::mt19937 mersenne(rd());
	//int temp = mersenne() % 6;
	//if (temp <= 3)
		Field::make_high();
	Field::make_river();
	Field::make_forest();
	Field::make_ore();
	Field::make_oil();
}

Cell* Field::get_cell(int i, int j)
{
    return &a[i][j];
}

void Field::bind_map_textures(Texture* textures)
{
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
        {
            switch(this->a[i][j].get_type())
            {
            case(grass):
                {
                    if(i == M - 1)
                        textures->set_cell_texture(i,j,textures->get_grass_textures()[1]);
                    else
                        textures->set_cell_texture(i,j,textures->get_grass_textures()[0]);
                }
            break;
            case(hg):
                {
                    if(i == M - 1 || a[i+1][j].get_type() != hg)
                        textures->set_cell_texture(i,j,textures->get_hg_textures()[1]);
                    else
                        textures->set_cell_texture(i,j,textures->get_hg_textures()[0]);
                }
            break;
            case(water):
                textures->set_cell_texture(i,j,textures->get_water_texture());
            break;
            }
        }
}
