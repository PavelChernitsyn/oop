#include "base.h"

Base::Base(int maxUnitsCount, int health, int xx, int yy, int baseNumb) : baseNumb(baseNumb),
    unitCount(0), maxCount(maxUnitsCount),
    unitCurr(0),health(health), x(xx), y(yy)
{
    units = new CompositeUnit();

}

int Base::getBaseNumb() const
{
    return baseNumb;
}

int Base::getX() const
{
    return x;
}

int Base::getY() const
{
    return y;
}

int Base::getUnitCount() const
{
    return unitCount;
}

int Base::getMaxCount() const
{
    return maxCount;
}

int Base::getHealth() const
{
    return health;
}

Unit *Base::createUnit(UnitsType type)
{
    AbstractArmy* humanityArmy = new HumanityArmy();
    AbstractArmy* creaturesArmy = new CreaturesArmy();
    Unit* unit = nullptr;
    if (type == ARCHER){
        unit = humanityArmy->createArrow();
    }
    else if (type == SHAMAN){
        unit = creaturesArmy->createArrow();
    }
    else if (type == KNIGTH){
        unit = humanityArmy->createCavelry();
    }
    else if (type == RIDER){
        unit = creaturesArmy->createCavelry();
    }
    else if (type == SWARDMAN){
        unit = humanityArmy->createInfantry();
    }
    else if (type == ORK){
        unit = creaturesArmy->createInfantry();
    }
    try {
        this->getCreateMediator()->notify(unit, x, y);
        gameMediator->Notify(unit, true);
    } catch (out_of_range& e) {
        throw e;
    }
    catch (invalid_argument& e) {
        throw e;
    }
    units->addUnit(unit);
    unitCount++;
    return unit;
}

Unit *Base::createUnit(string type)
{
    AbstractArmy* humanityArmy = new HumanityArmy();
    AbstractArmy* creaturesArmy = new CreaturesArmy();
    Unit* unit = nullptr;
    if (type == "archer"){
        unit = humanityArmy->createArrow();
    }
    else if (type == "shaman"){
        unit = creaturesArmy->createArrow();
    }
    else if (type == "knigth"){
        unit = humanityArmy->createCavelry();
    }
    else if (type == "rider"){
        unit = creaturesArmy->createCavelry();
    }
    else if (type == "swardman"){
        unit = humanityArmy->createInfantry();
    }
    else if (type == "ork"){
        unit = creaturesArmy->createInfantry();
    }
    try {
        this->getCreateMediator()->notify(unit, x, y);
        gameMediator->Notify(unit, true);
    } catch (out_of_range& e) {
        throw e;
    }
    catch (invalid_argument& e) {
        throw e;
    }
    units->addUnit(unit);
    unitCount++;
    return unit;
}

void Base::addUnit(Unit *u)
{
    units->addUnit(u);
    unitCount++;
}

void Base::deleteUnit(Subject * unit)
{
    if (units->delUnit(unit)){
        unitCount--;
    }
}

Unit *Base::getCurrUnit()
{
    return units->getUnit(unitCurr);
}


bool Base::getDamage(int numb)
{
    this->health -= numb;
    if (this->health <= 0){
        this->health = 0;
        return true;
    }
    return false;
}

void Base::update(Subject * subject)
{
    deleteUnit(subject);
}

void Base::setGameMediator(GameMediator *val)
{
    gameMediator = val;
}

CompositeUnit *Base::getUnits() const
{
    return units;
}

void Base::setCreateMediator(CreateMediator *value)
{
    createMediator = value;
}

CreateMediator *Base::getCreateMediator() const
{
    return createMediator;
}

int Base::getUnitCurr() const
{
    return unitCurr;
}


