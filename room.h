#ifndef __Room__
#define __Room__

#include <string>
#include <list>
#include "entity.h"
class Exit;
class Creature;
class Object;
class Item;

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	~Room();

	void Look() const;

	Exit* GetExit(const string& direction) const;
	Creature* GetCreature(const string& args) const;
	Object* GetObject(const string& name) const;


public :
};

#endif