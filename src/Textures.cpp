#include "Textures.h"

Texture::Texture(int M, int N)
{
    cell_textures = new GLuint*[M];
    for(int i = 0; i < M; i++)
        cell_textures[i] = new GLuint[N];
    load(&grass_textures[0], "textures/grass.png");
    load(&grass_textures[1], "textures/grass_low.png");
    load(&hg_textures[0], "textures/hg.png");
    load(&hg_textures[1], "textures/trans.png");
    load(&water_texture, "textures/water.png");
    load(&trooper_textures[0], "textures/trooper1.png");
    load(&trooper_textures[1], "textures/trooper2.png");
    load(&trooper_textures[2], "textures/trooper_dead1.png");
    load(&trooper_textures[3], "textures/trooper_dead2.png");
    load(&jugger_textures[0], "textures/jugger1.png");
    load(&sniper_textures[0], "textures/sniper1.png");
    load(&builder_textures[0], "textures/builder1.png");
    load(&builder_textures[1], "textures/builder2.png");
    load(&hq_textures[0], "textures/hq.png");
    load(&baracks_textures[0], "textures/baracks.png");
    load(&tower_textures[0], "textures/tower.png");
    load(&tree_textures[0], "textures/tree.png");
    load(&oil_textures[0], "textures/oil.png");
    load(&oilstation_textures[0], "textures/oilstation.png");
    load(&treecut_textures[0], "textures/treecut.png");
    load(&building_textures[0], "textures/buildingArea.png");
    load(&farm_textures[0], "textures/farm1.png");
    load(&iron_textures[0], "textures/iron.png");
    load(&boer_textures[0], "textures/boer.png");
    load(&particle_textures[0], "textures/blood.png");
    load(&particle_textures[1], "textures/explotion.png");
}

void Texture::load(GLuint* texture, char const* filepath)
{
    unsigned char *data;
    int width, heigh, nrChannels;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load(filepath, &width, &heigh, &nrChannels, STBI_rgb_alpha);
    if(!data)
        std::cout << "Can't open " << filepath << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}
