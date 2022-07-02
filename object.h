#ifndef __Object__
#define __Object__

#include <string>
#include "entity.h"

class Room;

using namespace std;

class Object : public Entity
{
public:
	Object(const char* name, const char* description, Entity* parent);
	~Object();
	void Look() const;

public:

};

#endif //__Item__