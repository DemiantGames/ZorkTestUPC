#include <iostream>
#include "globals.h"
#include "exit.h"
#include "item.h"
#include "creature.h"
#include "room.h"
#include "object.h"

// ----------------------------------------------------
Room::Room(const char* title, const char* description) :
Entity(title, description, NULL)
{
	type = ROOM;
}

// ----------------------------------------------------
Room::~Room()
{
}

// ----------------------------------------------------
void Room::Look() const
{
	cout << "\n" << name << "\n";
	cout << description;

	// List exits --
	for(list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name;
		}
	}

	// List items --
	for(list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if((*it)->type == ITEM)
		{
			Item* item = (Item*)*it;
			cout << "\nThere is an item here: " << item->name;
		}
	}

	// List creatures --
	for(list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if((*it)->type == CREATURE)
		{
			Creature* cr = (Creature*)*it;
			cout << "\nThere is someone else here: " << cr->name;
			if(cr->IsAlive() == false)
				cout << " (dead)";
		}
	}

	// List objects --
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == OBJECT)
		{
			Object* cr = (Object*)*it;
			cout << "\nThere is : " << cr->name;
			/*if (cr->IsAlive() == false)
				cout << " (dead)";*/
		}
	}

	cout << "\n";
}

// ----------------------------------------------------
Exit* Room::GetExit(const string& direction) const
{
	for(list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if((*it)->type == EXIT)
		{
			Exit* ex = (Exit*) *it;
			if(Same(ex->GetNameFrom(this), direction))
				return ex;
		}
	}

	return NULL;
}

Creature* Room::GetCreature(const string& name) const
{
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == CREATURE)
		{
			Creature* creature = (Creature*)*it;
			if (Same(creature->name, name))
				return creature;
		}
	}

	return NULL;
}

Object* Room::GetObject(const string& name) const
{
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == OBJECT)
		{
			Object* object = (Object*)*it;
			if (Same(object->name, name))
				return object;
		}
	}
	return NULL;
}
