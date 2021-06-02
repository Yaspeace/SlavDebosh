#include "Resourse.h"

void Resource::draw(int M, int N, Texture* textures)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.8f);

    POINTFLOAT cell_size;
    cell_size.x = 1.0/N;
    cell_size.y = 1.0/M;

    glColor3f(1,1,1);

    GLuint* texture;
    switch(this->res_type)
    {
    case(Tree):
        {
            texture = textures->get_tree_textures();
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
    break;
    case(Iron):
        {
            texture = textures->get_iron_textures();
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
    break;
    case(Oil):
        {
            texture = textures->get_oil_textures();
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
    break;
    }

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(cell_size.x * this->object_attributes.position.x, cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,0); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y - (cell_size.y / 2));
        glTexCoord2f(1,1); glVertex2f(cell_size.x * this->object_attributes.position.x + cell_size.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
        glTexCoord2f(0,1); glVertex2f(cell_size.x * this->object_attributes.position.x,cell_size.y * this->object_attributes.position.y + cell_size.y);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
}
