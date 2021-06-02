#include "Cell.h"

void Cell::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    if(is_chosen)
        glColor3f(0.5,0.5,0.5);
    else
        glColor3f(1,1,1);

       GLuint texture = textures->get_cell_texture(object_attributes.position.y, object_attributes.position.x);
       glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y);
        glTexCoord2f(1,0); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y);
        glTexCoord2f(1,1); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glTexCoord2f(0,1); glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y);
        glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y);
        glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y);
        glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
}
