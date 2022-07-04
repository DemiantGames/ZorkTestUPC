#include <iostream>
#include "room.h"
#include "exit.h"
#include "globals.h"
#include "object.h"

// ----------------------------------------------------
Object::Object(const char* title, const char* description, Entity* parent) :
	Entity(title, description, parent)
{
	type = OBJECT;
	captive = NULL;
}

// ----------------------------------------------------
Object::~Object()
{
	type = OBJECT;
}

// ----------------------------------------------------
void Object::Look() const
{
	cout << "\n" << name << "\n";
	cout << description << "\n";

	list<Entity*> stuff;

	if (stuff.size() > 0)
	{
		cout << "It contains: " << "\n";
		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it)
			cout << (*it)->name << "\n";
	}
}
