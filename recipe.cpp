#include <iostream>
#include "room.h"
#include "exit.h"
#include "globals.h"
#include "item.h"
#include "recipe.h"


Recipe::Recipe(list<Entity*> recipe, Entity* result)
{
	this->ingredients = recipe;
	this->result = result;
}
Recipe::~Recipe()
{
}
