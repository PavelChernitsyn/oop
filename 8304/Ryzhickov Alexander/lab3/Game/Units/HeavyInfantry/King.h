//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_KING_H
#define GAME_KING_H


#include "HeavyInfantry.h"

class King : public HeavyInfantry {
public:
    King(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);
    void attack(Unit *unit) override ;
};


#endif //GAME_KING_H
