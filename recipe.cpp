#include <iostream>
#include "room.h"
#include "exit.h"
#include "globals.h"
#include "item.h"
#include "recipe.h"


Recipe::Recipe(vector<Entity*> recipe, vector<bool> isDestroyable, Entity* result)
{
	this->ingredients = recipe;
	this->isDestroyable = isDestroyable;
	this->result = result;
}
Recipe::~Recipe()
{
}
