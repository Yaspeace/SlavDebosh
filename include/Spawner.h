#ifndef SPAWNER_H
#define SPAWNER_H

#include "Unit.h"
#include "Building.h"
#include "Field.h"

class Spawner
{
    public:
        static Game_Object* spawn_object(int ButtonID, Game_Object* action_obj, Game_Object* chosen_obj, Field* map);
    private:
        static bool check_spawn(Game_Object* action_obj, Game_Object* chosen_obj, Game_Object* spawning_object, Field* map);
};

#endif // SPAWNER_H
