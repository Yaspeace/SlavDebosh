#include "Unit.h"
#include "Building.h"
#include "Button.h"

Unit::Unit(int team)
{
    this->unit_attributes.team = team;
    this->object_attributes.id = UnitID;
}

void Unit::set_res_gain(Res_Type type, int gain)
{
    switch(type)
    {
    case(Tree):
        this->unit_attributes.res_gain.wood = gain;
    break;
    case(Meat):
        this->unit_attributes.res_gain.meat = gain;
    break;
    case(Iron):
        this->unit_attributes.res_gain.iron = gain;
    break;
    case(Oil):
        this->unit_attributes.res_gain.oil = gain;
    break;
    }
}

void Unit::set_res_cost(Res_Type type, int cost)
{
    switch(type)
    {
    case(Tree):
        this->unit_attributes.res_cost.wood = cost;
    break;
    case(Meat):
        this->unit_attributes.res_cost.meat = cost;
    break;
    case(Iron):
        this->unit_attributes.res_cost.iron = cost;
    break;
    case(Oil):
        this->unit_attributes.res_cost.oil = cost;
    break;
    }
}

int Unit::get_res_gain(Res_Type type)
{
    switch(type)
    {
    case(Tree):
        return this->unit_attributes.res_gain.wood;
    case(Meat):
        return this->unit_attributes.res_gain.meat;
    case(Iron):
        return this->unit_attributes.res_gain.iron;
    case(Oil):
        return this->unit_attributes.res_gain.oil;
    }
}

int Unit::get_res_cost(Res_Type type)
{
    switch(type)
    {
    case(Tree):
        return this->unit_attributes.res_cost.wood;
    case(Meat):
        return this->unit_attributes.res_cost.meat;
    case(Iron):
        return this->unit_attributes.res_cost.iron;
    case(Oil):
        return this->unit_attributes.res_cost.oil;
    }
}

bool Unit::check_move(int x, int y)
{
    int G_X1, G_X2;
	G_X1 = this->object_attributes.position.x + this->get_rad_move();
	G_X2 = this->object_attributes.position.x - this->get_rad_move();

	int G_Y1, G_Y2;
	G_Y1 = this->object_attributes.position.y + this->get_rad_move();
	G_Y2 = this->object_attributes.position.y - this->get_rad_move();

	if ((x <= G_X1) && (x >= G_X2) && (y <= G_Y1) && (y >= G_Y2))
        return true;
    return false;
}

bool Unit::check_attack(int x, int y)
{
    int G_X1, G_X2;
	G_X1 = this->object_attributes.position.x + this->get_rad_attack();
	G_X2 = this->object_attributes.position.x - this->get_rad_attack();

	int G_Y1, G_Y2;
	G_Y1 = this->object_attributes.position.y + this->get_rad_attack();
	G_Y2 = this->object_attributes.position.y - this->get_rad_attack();
	if ((G_X1 >= x) && (G_X2 <= x))
		if ((y <= G_Y1) && (y >= G_Y2))
			return true;
	return false;
}

void Unit::move_to(int dx, int dy)
{
    if((check_move(dx, dy)) && (this->get_cur_act_num() > 0))
    {
        if((dx > get_position().x && unit_attributes.flipped) || (dx < get_position().x && !unit_attributes.flipped))
            flip();
        this->set_position(dx, dy);
        this->set_cur_act_num(this->get_cur_act_num() - 1);
    }
}

void Unit::deal_damage(Unit* unit_to_attack)
{
    int coeff = 0;
    if(this->unit_attributes.on_high)
        coeff +=2;
    if(unit_to_attack->unit_attributes.on_high)
        coeff -=2;
    unit_to_attack->unit_attributes.cur_health -= (this->get_damage() + coeff);
    this->set_cur_act_num(this->get_cur_act_num() - 1);
}

void Unit::deal_damage(Building* building_to_attack)
{
    int coeff = 0;
    if(this->unit_attributes.on_high)
        coeff +=2;
    building_to_attack->set_cur_health(building_to_attack->get_cur_health() - (this->get_damage()) + coeff);
    this->set_cur_act_num(this->get_cur_act_num() - 1);
}

void Unit::attack(Game_Object* obj)
{
    if((obj->get_position().x > this->get_position().x && unit_attributes.flipped)||(obj->get_position().x < this->get_position().x && !unit_attributes.flipped))
        this->flip();
    switch(obj->get_id())
    {
    case(EnemyID):
        {
            Unit* unit_to_attack = dynamic_cast<Unit*>(obj);
            if((check_attack(unit_to_attack->object_attributes.position.x, unit_to_attack->object_attributes.position.y)) && (this->unit_attributes.cur_act_num > -10))
                this->deal_damage(unit_to_attack);
            if(unit_to_attack->get_cur_health() <= 0)
                obj->set_death(true);
        }
    break;
    case(EnemyBuildingID):
        {
            Building* building_to_attack = dynamic_cast<Building*>(obj);
            if((check_attack(building_to_attack->get_position().x, building_to_attack->get_position().y)) && (this->unit_attributes.cur_act_num > 0))
                this->deal_damage(building_to_attack);
            if(building_to_attack->get_cur_health() <= 0)
                obj->set_death(true);
        }
    break;
    }

}

Game_Object* Builder::spawn_building(int ID, int team)
{
    switch(ID)
    {
        case(buildBaracksBtn):
                return new Baracks(team);
        case(buildTowerBtn):
                return new Tower(team);
        case(buildBoerBtn):
                return new Boer(team);
        case(buildFarmBtn):
                return new Farm(team);
        case(buildTreeCutBtn):
                return new Treecutter(team);
        case(buildOilStationBtn):
                return new Oil_Station(team);
    }

}

void Trooper::spell(Game_Object* action_obj)
{
    if(check_attack(action_obj->get_position().x, action_obj->get_position().y) && this->get_cur_act_num() > 0 && this->grenade_count > 0
       && Game_Model::get_game_model()->get_object(action_obj->get_position().x,action_obj->get_position().y))
    {
        for(int i = action_obj->get_position().x - 1; i < action_obj->get_position().x + 2; i++)
            for(int j = action_obj->get_position().y - 1; j < action_obj->get_position().y + 2; j++)
            {
                Particle* p = new Particle(Explotion);
                p->set_position(i,j);
                Game_Model::get_game_model()->add_particle(p);
                if(Game_Model::get_game_model()->get_object(i,j))
                {
                    Game_Object* tmp = Game_Model::get_game_model()->get_object(i,j);
                    switch(tmp->get_id())
                    {
                        case(UnitID):
                        case(EnemyID):
                        {
                            Unit* u = dynamic_cast<Unit*>(tmp);
                            u->set_cur_health(u->get_cur_health()-5);
                            if(u->get_cur_health() <= 0)
                                Game_Model::get_game_model()->delete_object(tmp);
                        }
                        break;

                        case(BuildingID):
                        case(EnemyBuildingID):
                        {
                            Building* b = dynamic_cast<Building*>(tmp);
                            b->set_cur_health(b->get_cur_health() - 3);
                            if(b->get_cur_health() <= 0)
                                Game_Model::get_game_model()->delete_object(tmp);
                        }
                        break;

                        case(ResourceID):
                            {
                                Resource* r = dynamic_cast<Resource*>(tmp);
                                if(r->res_type == Tree)
                                    Game_Model::get_game_model()->delete_object(tmp);
                            }
                        break;
                    }
                }
            }
            this->set_cur_act_num(this->get_cur_act_num() - 1);
            this->grenade_count--;
    }
}

void Juggernaut::spell(Game_Object* action_obj)
{
    if(!(this->spell_on) && (this->get_cur_act_num()>0))
    {
        this->set_rad_move(1);
        this->set_cur_act_num(this->get_cur_act_num() - 1);
        this->set_cur_health(this->get_cur_health() + 20);
        this->set_damage(this->get_damage() + 5);
        this->spell_on = true;
    }
}

void Sniper::spell(Game_Object* action_obj)
{
    if(this->spell_on)
    {
        this->set_rad_move(4);
        this->set_rad_attack(3);
        this->set_view_rad(this->get_rad_attack());
        this->set_cur_act_num(this->get_cur_act_num() - 1);
        this->spell_on = false;
    }
    else if(!(this->spell_on) && (this->get_cur_act_num()>0))
    {
        this->set_rad_move(0);
        this->set_cur_act_num(this->get_cur_act_num() - 1);
        this->set_view_rad(this->get_rad_attack() + 2);
        this->set_rad_attack(0);
        this->spell_on = true;
    }
}

void Builder::spell(Game_Object* action_obj)
{
    if(action_obj)
    if(check_attack(action_obj->get_position().x, action_obj->get_position().y) && this->get_cur_act_num() > 0)
        if(Game_Model::get_game_model()->get_object(action_obj->get_position().x,action_obj->get_position().y))
        {
            Game_Object* tmp = Game_Model::get_game_model()->get_object(action_obj->get_position().x,action_obj->get_position().y);
            if(tmp->get_id() == BuildingID)
            {
                Building* b = dynamic_cast<Building*>(tmp);
                if(b->get_cur_health() < b->get_max_health())
                {
                    b->set_cur_health(get_cur_health() + 3);
                    this->set_cur_act_num(0);
                    if(b->get_cur_health() > b->get_max_health())
                        b->set_cur_health(get_max_health());
                }
            }
        }
}


void Unit::draw_hp_bar(int M, int N)
{
    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    float coef = (float)this->get_cur_health() / (float)this->get_max_health();
    if(coef < 0.25)
        glColor3f(1.0,0.0,0.0);
    else if(coef >= 0.25 && coef < 0.5)
        glColor3f(1.0,0.5,0);
    else if(coef >= 0.5 && coef < 0.75)
        glColor3f(1.0,1.0,0);
    else
        glColor3f(0.0,1.0,0.0);
    POINT pos = this->get_position();
    int heigh = 4;
    if(this->get_u_id() == JuggernautID)
        heigh = 2;
    glBegin(GL_QUADS);
        glVertex2f(pos.x * cell_size.x + 0.001, (pos.y * cell_size.y)- (cell_size.y / heigh) - 0.005);
        glVertex2f(pos.x * cell_size.x + (cell_size.x * coef) - 0.001, (pos.y * cell_size.y)- (cell_size.y / heigh) - 0.005);
        glVertex2f(pos.x * cell_size.x + (cell_size.x * coef) - 0.001, (pos.y * cell_size.y)- (cell_size.y / heigh));
        glVertex2f(pos.x * cell_size.x + 0.001, (pos.y * cell_size.y)- (cell_size.y / heigh));
    glEnd();

    if(this->get_team() == 1)
        glColor3f(0,0,1);
    if(this->get_team() == 2)
        glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex2f(pos.x * cell_size.x + (cell_size.x / 4) , (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 8));
        glVertex2f(pos.x * cell_size.x + (3 * cell_size.x / 4), (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 8));
        glVertex2f(pos.x * cell_size.x + (3 * cell_size.x / 4), (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 8) + 0.003);
        glVertex2f(pos.x * cell_size.x + (cell_size.x / 4), (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 8) + 0.003);
    glEnd();

}

void Trooper::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
     glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    POINT pos = this->get_position();
    glColor3f(1,1,1);

    GLuint* tex = textures->get_trooper_textures();
    long int now = static_cast<long int> (time(NULL));
    if(now % 2 == 0)
        glBindTexture(GL_TEXTURE_2D, tex[0]);
    else
        glBindTexture(GL_TEXTURE_2D, tex[1]);
    int x1,x2;
    if(this->unit_attributes.flipped)
    {
        x1 = 0;
        x2 = 1;
    }
    else
    {
        x1 = 1;
        x2 = 0;
    }
    glBegin(GL_QUADS);
        glTexCoord2f(x2,0); glVertex2f((pos.x * cell_size.x) + (cell_size.x / 4),       (pos.y * cell_size.y)- (cell_size.y / 4));
        glTexCoord2f(x1,0); glVertex2f((pos.x * cell_size.x) + (3 * cell_size.x / 4),   (pos.y * cell_size.y) - (cell_size.y / 4));
        glTexCoord2f(x1,1); glVertex2f((pos.x * cell_size.x) + (3 * cell_size.x / 4),   (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 4));
        glTexCoord2f(x2,1); glVertex2f((pos.x * cell_size.x) + (cell_size.x / 4),       (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 4));
    glEnd();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Builder::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    POINT pos = this->get_position();
    glColor3f(1,1,1);

    GLuint* tex = textures->get_builder_textures();

    long int now = static_cast<long int> (time(NULL));
    if(now % 2 == 0)
        glBindTexture(GL_TEXTURE_2D, tex[0]);
    else
        glBindTexture(GL_TEXTURE_2D, tex[1]);
        int x1,x2;
    if(this->unit_attributes.flipped)
    {
        x1 = 0;
        x2 = 1;
    }
    else
    {
        x1 = 1;
        x2 = 0;
    }

    glBegin(GL_QUADS);
        glTexCoord2f(x2,0); glVertex2f((pos.x * cell_size.x) + (cell_size.x / 4),       (pos.y * cell_size.y)- (cell_size.y / 4));
        glTexCoord2f(x1,0); glVertex2f((pos.x * cell_size.x) + (3 * cell_size.x / 4),   (pos.y * cell_size.y) - (cell_size.y / 4));
        glTexCoord2f(x1,1); glVertex2f((pos.x * cell_size.x) + (3 * cell_size.x / 4),   (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 4));
        glTexCoord2f(x2,1); glVertex2f((pos.x * cell_size.x) + (cell_size.x / 4),       (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 4));
    glEnd();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Sniper::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    POINT pos = this->get_position();
    glColor3f(1,1,1);

    GLuint* tex = textures->get_sniper_textures();

    //long int now = static_cast<long int> (time(NULL));
    //if(now % 2 == 0)
        glBindTexture(GL_TEXTURE_2D, tex[0]);
    //else
        //glBindTexture(GL_TEXTURE_2D, tex[1]);

        int x1,x2;
    if(this->unit_attributes.flipped)
    {
        x1 = 0;
        x2 = 1;
    }
    else
    {
        x1 = 1;
        x2 = 0;
    }

    glBegin(GL_QUADS);
        glTexCoord2f(x2,0); glVertex2f((pos.x * cell_size.x) + (cell_size.x / 4),       (pos.y * cell_size.y)- (cell_size.y / 4));
        glTexCoord2f(x1,0); glVertex2f((pos.x * cell_size.x) + (3 * cell_size.x / 4),   (pos.y * cell_size.y) - (cell_size.y / 4));
        glTexCoord2f(x1,1); glVertex2f((pos.x * cell_size.x) + (3 * cell_size.x / 4),   (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 4));
        glTexCoord2f(x2,1); glVertex2f((pos.x * cell_size.x) + (cell_size.x / 4),       (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 4));
    glEnd();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Juggernaut::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    POINT pos = this->get_position();
    glColor3f(1,1,1);

    GLuint* tex = textures->get_jugger_textures();

    //long int now = static_cast<long int> (time(NULL));
    //if(now % 2 == 0)
        glBindTexture(GL_TEXTURE_2D, tex[0]);
    //else
        //glBindTexture(GL_TEXTURE_2D, tex[1]);

        int x1,x2;
    if(this->unit_attributes.flipped)
    {
        x1 = 0;
        x2 = 1;
    }
    else
    {
        x1 = 1;
        x2 = 0;
    }

    glBegin(GL_QUADS);
        glTexCoord2f(x2,0); glVertex2f((pos.x * cell_size.x) + (cell_size.x / 8),       (pos.y * cell_size.y)- (cell_size.y / 2));
        glTexCoord2f(x1,0); glVertex2f((pos.x * cell_size.x) + (7 * cell_size.x / 8),   (pos.y * cell_size.y) - (cell_size.y / 2));
        glTexCoord2f(x1,1); glVertex2f((pos.x * cell_size.x) + (7 * cell_size.x / 8),   (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 4));
        glTexCoord2f(x2,1); glVertex2f((pos.x * cell_size.x) + (cell_size.x / 8),       (pos.y * cell_size.y) + cell_size.y - (cell_size.y / 4));
    glEnd();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}
