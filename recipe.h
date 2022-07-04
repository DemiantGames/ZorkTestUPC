#ifndef __Recipe__
#define __Recipe__

#include <string>
#include "entity.h"

class Entity;

using namespace std;

class Recipe 
{
public:
	Recipe(list<Entity*> recipe, Entity* result);
	~Recipe();

public:
	list<Entity*> ingredients;
	Entity* result;
};

#endif //__Item__