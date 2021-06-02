#include "Particle.h"

Particle::Particle(Sprite_Type type)
{
    this->type = type;
    this->cur_time = time(0);
    this->life_time = cur_time + 1;
}

void Particle::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    glColor3f(1,1,1);

    GLuint* tex = textures->get_particle_textures();
    switch(this->type)
    {
    case(Blood):
        glBindTexture(GL_TEXTURE_2D, tex[0]);
    break;
    case(Explotion):
        glBindTexture(GL_TEXTURE_2D, tex[1]);
    break;
    }

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y);
        glTexCoord2f(1,0); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y);
        glTexCoord2f(1,1); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glTexCoord2f(0,1); glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
}
