#ifndef TEXTURES_H
#define TEXTURES_H

#include "../stb_image.h"
#include "gl/gl.h"
#include <iostream>

class Texture
{
    public:
        Texture(int M, int N);
        void load(GLuint* texture, char const* filepath);
        GLuint** get_cell_textures() {return cell_textures;}
        GLuint get_cell_texture(int i, int j) {return cell_textures[i][j];}
        GLuint* get_grass_textures() {return grass_textures;}
        GLuint* get_shore_textures() {return shore_textures;}
        GLuint* get_hg_textures() {return hg_textures;}
        GLuint get_water_texture() {return water_texture;}
        void set_cell_texture(int i, int j, GLuint tex) {this->cell_textures[i][j] = tex;}
        GLuint* get_trooper_textures() {return trooper_textures;}
        GLuint* get_jugger_textures() {return jugger_textures;}
        GLuint* get_sniper_textures() {return sniper_textures;}
        GLuint* get_builder_textures() {return builder_textures;}
        GLuint* get_hq_textures() {return hq_textures;}
        GLuint* get_baracks_textures() {return baracks_textures;}
        GLuint* get_tower_textures() {return tower_textures;}
        GLuint* get_treecut_textures() {return treecut_textures;}
        GLuint* get_boer_textures() {return boer_textures;}
        GLuint* get_farm_textures() {return farm_textures;}
        GLuint* get_oilstation_textures() {return oilstation_textures;}
        GLuint* get_tree_textures() {return tree_textures;}
        GLuint* get_iron_textures() {return iron_textures;}
        GLuint* get_oil_textures() {return oil_textures;}
        GLuint* get_building_textures() {return building_textures;}
        GLuint* get_particle_textures() {return particle_textures;}
    private:
        GLuint grass_textures[5];
        GLuint shore_textures[35];
        GLuint hg_textures[2];
        GLuint water_texture;
        GLuint** cell_textures;
        GLuint trooper_textures[5];
        GLuint jugger_textures[5];
        GLuint sniper_textures[5];
        GLuint builder_textures[5];
        GLuint building_textures[2];
        GLuint hq_textures[3];
        GLuint baracks_textures[3];
        GLuint tower_textures[3];
        GLuint treecut_textures[3];
        GLuint boer_textures[3];
        GLuint farm_textures[3];
        GLuint oilstation_textures[3];
        GLuint tree_textures[3];
        GLuint iron_textures[3];
        GLuint oil_textures[3];
        GLuint particle_textures[2];
};

#endif // TEXTURES_H
