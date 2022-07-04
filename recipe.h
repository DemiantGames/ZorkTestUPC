#ifndef __Recipe__
#define __Recipe__

#include <string>
#include "entity.h"

class Entity;

using namespace std;

class Recipe 
{
public:
	Recipe(vector<Entity*> recipe, vector<bool> isDestroyable, Entity* result);
	~Recipe();

public:
	vector<Entity*> ingredients;
	vector<bool> isDestroyable;
	Entity* result;
};

#endif //__Item__