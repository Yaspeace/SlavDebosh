#include "Building.h"
#include "Unit.h"

Building::Building(int team)
{
    this->building_attributes.team = team;
    this->object_attributes.id = BuildingID;
    set_res_gain(Meat,0);
    set_res_gain(Tree,0);
    set_res_gain(Iron,0);
    set_res_gain(Oil,0);
}

void Building::set_res_gain(Res_Type type, int gain)
{
    switch(type)
    {
    case(Tree):
        this->building_attributes.resource_gain.wood = gain;
    break;
    case(Meat):
        this->building_attributes.resource_gain.meat = gain;
    break;
    case(Iron):
        this->building_attributes.resource_gain.iron = gain;
    break;
    case(Oil):
        this->building_attributes.resource_gain.oil = gain;
    break;
    }
}

void Building::set_res_cost(Res_Type type, int cost)
{
    switch(type)
    {
    case(Tree):
        this->building_attributes.resource_cost.wood = cost;
    break;
    case(Meat):
        this->building_attributes.resource_cost.meat = cost;
    break;
    case(Iron):
        this->building_attributes.resource_cost.iron = cost;
    break;
    case(Oil):
        this->building_attributes.resource_cost.oil = cost;
    break;
    }
}

int Building::get_res_gain(Res_Type type)
{
    switch(type)
    {
    case(Tree):
        return this->building_attributes.resource_gain.wood;
    case(Meat):
        return this->building_attributes.resource_gain.meat;
    case(Iron):
        return this->building_attributes.resource_gain.iron;
    case(Oil):
        return this->building_attributes.resource_gain.oil;
    }
}

int Building::get_res_cost(Res_Type type)
{
    switch(type)
    {
    case(Tree):
        return this->building_attributes.resource_cost.wood;
    case(Meat):
        return this->building_attributes.resource_cost.meat;
    case(Iron):
        return this->building_attributes.resource_cost.iron;
    case(Oil):
        return this->building_attributes.resource_cost.oil;
    }
}

Game_Object* Building::spawn_unit(int ID, int team)
{
    switch(ID)
    {
        case(spawnTrooperBtn):
                return new Trooper(team);
        case(spawnJuggerBtn):
                return new Juggernaut(team);
        case(spawnSniperBtn):
                return new Sniper(team);
        case(spawnBuilderBtn):
                return new Builder(team);
    }

}

void Building::draw_hp_bar(int M, int N)
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
    glBegin(GL_QUADS);
        glVertex2f(pos.x * cell_size.x + 0.001, (pos.y * cell_size.y) - 0.005);
        glVertex2f(pos.x * cell_size.x + (cell_size.x * get_size().x * coef) - 0.001, (pos.y * cell_size.y) - 0.005);
        glVertex2f(pos.x * cell_size.x + (cell_size.x * get_size().x * coef) - 0.001, (pos.y * cell_size.y)- 0.002);
        glVertex2f(pos.x * cell_size.x + 0.001, (pos.y * cell_size.y)-0.002);
    glEnd();

    if(this->get_team() == 1)
        glColor3f(0,0,1);
    if(this->get_team() == 2)
        glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex2f(pos.x * cell_size.x, (pos.y * cell_size.y) + (cell_size.y * get_size().y));
        glVertex2f(pos.x * cell_size.x + (cell_size.x * get_size().x), (pos.y * cell_size.y) + (cell_size.y * get_size().y));
        glVertex2f(pos.x * cell_size.x + (cell_size.x * get_size().x), (pos.y * cell_size.y) + (cell_size.y * get_size().y) + 0.003);
        glVertex2f(pos.x * cell_size.x, (pos.y * cell_size.y) + (cell_size.y * get_size().y) + 0.003);
    glEnd();
}

void HQ::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
     glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    POINT pos = this->get_position();
    glColor3f(1,1,1);

    GLuint* tex;

    if(this->building_attributes.cur_build_count > 0)
        tex = textures->get_building_textures();
    else
        tex = textures->get_hq_textures();

    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f((pos.x * cell_size.x),                        (pos.y * cell_size.y));
        glTexCoord2f(1,0); glVertex2f((pos.x * cell_size.x) + (2 * cell_size.x),    (pos.y * cell_size.y));
        glTexCoord2f(1,1); glVertex2f((pos.x * cell_size.x) + (2 * cell_size.x),    (pos.y * cell_size.y) + (2 * cell_size.y));
        glTexCoord2f(0,1); glVertex2f((pos.x * cell_size.x),                        (pos.y * cell_size.y) + (2 * cell_size.y));
    glEnd();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Baracks::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
     glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    POINT pos = this->get_position();
    glColor3f(1,1,1);

    GLuint* tex;
    if(this->building_attributes.cur_build_count > 0)
        tex = textures->get_building_textures();
    else
        tex = textures->get_baracks_textures();

    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f((pos.x * cell_size.x),                        (pos.y * cell_size.y));
        glTexCoord2f(1,0); glVertex2f((pos.x * cell_size.x) + (2 * cell_size.x),    (pos.y * cell_size.y));
        glTexCoord2f(1,1); glVertex2f((pos.x * cell_size.x) + (2 * cell_size.x),    (pos.y * cell_size.y) + (2 * cell_size.y));
        glTexCoord2f(0,1); glVertex2f((pos.x * cell_size.x),                        (pos.y * cell_size.y) + (2 * cell_size.y));
    glEnd();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Treecutter::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    glColor3f(1,1,1);

    GLuint* tex;
    if(this->building_attributes.cur_build_count > 0)
        tex = textures->get_building_textures();
    else
        tex = textures->get_treecut_textures();
    glBindTexture(GL_TEXTURE_2D, tex[0]);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,0); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,1); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glTexCoord2f(0,1); glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Farm::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    glColor3f(1,1,1);

    GLuint* tex;
    if(this->building_attributes.cur_build_count > 0)
        tex = textures->get_building_textures();
    else
        tex = textures->get_farm_textures();
    glBindTexture(GL_TEXTURE_2D, tex[0]);

    POINT pos = this->get_position();

    glBegin(GL_QUADS);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f((pos.x * cell_size.x),                        (pos.y * cell_size.y));
        glTexCoord2f(1,0); glVertex2f((pos.x * cell_size.x) + (2 * cell_size.x),    (pos.y * cell_size.y));
        glTexCoord2f(1,1); glVertex2f((pos.x * cell_size.x) + (2 * cell_size.x),    (pos.y * cell_size.y) + (2 * cell_size.y));
        glTexCoord2f(0,1); glVertex2f((pos.x * cell_size.x),                        (pos.y * cell_size.y) + (2 * cell_size.y));
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Tower::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    glColor3f(1,1,1);

    GLuint* tex;
    if(this->building_attributes.cur_build_count > 0)
        tex = textures->get_building_textures();
    else
        tex = textures->get_tower_textures();
    glBindTexture(GL_TEXTURE_2D, tex[0]);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,0); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,1); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glTexCoord2f(0,1); glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Boer::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    glColor3f(1,1,1);

    GLuint* tex;
    if(this->building_attributes.cur_build_count > 0)
        tex = textures->get_building_textures();
    else
        tex = textures->get_boer_textures();
    glBindTexture(GL_TEXTURE_2D, tex[0]);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,0); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,1); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glTexCoord2f(0,1); glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}

void Oil_Station::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    glColor3f(1,1,1);

    GLuint* tex;
    if(this->building_attributes.cur_build_count > 0)
        tex = textures->get_building_textures();
    else
        tex = textures->get_oilstation_textures();
    glBindTexture(GL_TEXTURE_2D, tex[0]);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,0); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,1); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glTexCoord2f(0,1); glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    draw_hp_bar(M,N);
}
