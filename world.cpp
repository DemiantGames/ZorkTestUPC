#include <iostream>
#include "globals.h"
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "object.h"
#include "world.h"
#include "recipe.h"
// ----------------------------------------------------
//TODO READ ME
//TODO CHANGE DIALOGUES
//TODO HELP AND COMMANDS INSTRUCTIONS 
//TODO COMPLETE THE MAIN FLOW OF THE GAME
//TODO BATTLE SYSTEM


World::World()
{
	tick_timer = clock();

	// Rooms ----
	Room* demonRoom = new Room("Demon Room", "You are in a room with a demon");
	Room* darkRoom = new Room("Dark Room", "You are inside a dark room");
	Room* fireRoom = new Room("Fire Room", "This is room is completely red and hot");
	Room* iceRoom = new Room("Ice Room", "You are in a freezer, you're going to get a flue");
	Room* cosyRoom = new Room("Cosy Room", "It's a cosy place, The carpet has something extrange");
	Room* wizardRoom = new Room("Wizard Room", "You are in a cage but there is magic in the air");

	//Exits
	Exit* ex1 = new Exit("west", "east", "Door", demonRoom, darkRoom);
	Exit* ex2FireDoor = new Exit("north", "south", "Hot door", demonRoom, fireRoom);
	Exit* ex3Ice = new Exit("south", "north", "Ice", demonRoom, iceRoom);
	Exit* ex4LuxuryDoor = new Exit("east", "west", "Luxury door", demonRoom, cosyRoom);
	Exit* ex5SecretStairs = new Exit("down", "up", "Secret Stairs", cosyRoom, wizardRoom);
	ex1->description = "An open door";
	ex2FireDoor->description = "It's a hot door with a fire icon on it";
	ex3Ice->description = "There is a ice bloking the way, I have to melt it. It would be nice to have a Fire Sword";
	ex4LuxuryDoor->description = "It's a cosy luxury door";
	ex5SecretStairs->description = "There are some stairs under the carpet";

	ex2FireDoor->locked = true;
	ex3Ice->locked = true;
	ex4LuxuryDoor->locked = true;
	ex5SecretStairs->locked = true;

	entities.push_back(demonRoom);
	entities.push_back(darkRoom);
	entities.push_back(fireRoom);
	entities.push_back(iceRoom);
	entities.push_back(cosyRoom);
	entities.push_back(wizardRoom);

	entities.push_back(ex1);
	entities.push_back(ex2FireDoor);
	entities.push_back(ex3Ice);
	entities.push_back(ex4LuxuryDoor);
	entities.push_back(ex5SecretStairs);

	// Creatures ----
	Creature* demon = new Creature("Demon", "It's a Demon, I need to defeat him in order to scape.", demonRoom);
	demon->hit_points = 50;
	demon->max_damage = 5;
	demon->min_damage = 2;
	demon->isLocked = true;
	demon->dialogues = { "I'm in this cage","If you help me out I help you to scape out of this place" };
	Creature* wizard = new Creature("Wizard", "It's little Wizard.", wizardRoom);
	wizard->hit_points = 1000000000;
	wizard->max_damage = 1;
	wizard->min_damage = 1;
	wizard->isLocked = true;
	wizard->dialogues = { "Help me! And then I'll give you my magical Sword","You will need this powerfull sword","The demon is weak to ice, maybe you should attack him with an ice sword" };
	
	entities.push_back(demon);
	entities.push_back(wizard);

	//Static Objects
	Object* fire = new Object("Fire", "It's fire and there is a gem in it", fireRoom);
	Object* waterTab = new Object("WaterTab", "It's fire and there is a gem in it", demonRoom);
	Object* carpet = new Object("Carpet", "There is a scratches, it look's like something is hidden", cosyRoom);
	Object* cage = new Object("Cage", "A cage with a demon in it", demonRoom);
	Object* rope = new Object("Rope", "A rope too tied, I would need to cut it", wizardRoom);

	// Items -----
	Item* woodSword = new Item("WoodSword", "A wood sword", darkRoom, WEAPON);
	Item* fireSword = new Item("FireSword", "A fire sword", NULL, WEAPON);
	Item* steelSword = new Item("SteelSword", "A wood sword", wizard, WEAPON);
	Item* iceSword = new Item("IceSword", "A ice sword", NULL, WEAPON);
	Item* fireGem = new Item("FireGem", "A fire gem", NULL);
	Item* iceGem = new Item("IceGem", "An ice gem", iceRoom);
	Item* firekey = new Item("FireKey", "A red hot key", cosyRoom);
	Item* luxurykey = new Item("LuxuryKey", "A luxury key", darkRoom);
	Item* demonicKey = new Item("DemonicKey", "It looks like a demonic key", wizardRoom);
	Item* knife = new Item("Knife", "A sharp knife", iceRoom);
	Item* bucket = new Item("Bucket", "A bucket", cosyRoom);
	Item* waterBucket = new Item("WaterBucket", "A bucket with water", NULL);
	
	//TEST
	//Item* knife = new Item("Knife", "A sharp knife", wizardRoom);

	ex2FireDoor->key = firekey;
	ex2FireDoor->destroyKey = true;
	ex3Ice->key = fireSword;
	ex3Ice->destroyKey = true;
	ex4LuxuryDoor->key = luxurykey;
	ex4LuxuryDoor->destroyKey = true;
	ex5SecretStairs->key = knife;
	ex5SecretStairs->destroyKey = false;

	cage->key = demonicKey;
	cage->destroyKey = true;
	rope->key = knife;
	rope->captive = wizard;
	cage->destroyKey = true;
	cage->captive = demon;
	fire->key = bucket;
	fire->destroyKey = true;


	woodSword->min_value = 1;
	woodSword->max_value = 1;
	fireSword->min_value = 10;
	fireSword->max_value = 15;
	steelSword->min_value = 10;
	steelSword->max_value = 15;
	iceSword->min_value = 20;
	iceSword->max_value = 30;

	entities.push_back(woodSword);
	entities.push_back(fireSword);
	entities.push_back(steelSword);
	entities.push_back(iceSword);
	entities.push_back(fireGem);
	entities.push_back(iceGem);
	entities.push_back(firekey);
	entities.push_back(luxurykey);
	entities.push_back(knife);
	entities.push_back(bucket);

	//Recipes
	Recipe* recipe1 = new Recipe({ woodSword,fireGem }, { true,true }, fireSword);
	Recipe* recipe2 = new Recipe({ bucket,waterTab }, { true,false }, waterBucket);
	Recipe* recipe3 = new Recipe({ iceGem,steelSword }, { true,true }, iceSword);
	Recipe* recipe4 = new Recipe({ fire,waterBucket }, { true,true }, fireGem);
	Recipe* recipe5 = new Recipe({ rope,knife }, { true,true }, steelSword);
	Recipe* recipe6 = new Recipe({ cage,demonicKey }, { true,true }, NULL);

	recipes.push_back(recipe1);
	recipes.push_back(recipe2);
	recipes.push_back(recipe3);
	recipes.push_back(recipe4);
	recipes.push_back(recipe5);
	recipes.push_back(recipe6);
	// Player ----
	//player = new Player("Hero", "You woke up in a dungeon", demonRoom);
	player = new Player("Hero", "You woke up in a dungeon", demonRoom);
	player->hit_points = 25;

	entities.push_back(player);


}

// ----------------------------------------------------
World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete* it;

	entities.clear();
}

// ----------------------------------------------------
bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if (args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

// ----------------------------------------------------
void World::GameLoop()
{
	clock_t now = clock();

	if ((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			(*it)->Tick();

		tick_timer = now;
	}
}

// ----------------------------------------------------
bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch (args.size())
	{
	case 1: // commands with no arguments ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l"))
		{
			player->Look(args);
		}
		else if (Same(args[0], "north") || Same(args[0], "n"))
		{
			(args.size() == 1) ? args.push_back("north") : args[1] = "north";
			player->Go(args);
		}
		else if (Same(args[0], "south") || Same(args[0], "s"))
		{
			(args.size() == 1) ? args.push_back("south") : args[1] = "south";
			player->Go(args);
		}
		else if (Same(args[0], "east") || Same(args[0], "e"))
		{
			(args.size() == 1) ? args.push_back("east") : args[1] = "east";
			player->Go(args);
		}
		else if (Same(args[0], "west") || Same(args[0], "w"))
		{
			(args.size() == 1) ? args.push_back("west") : args[1] = "west";
			player->Go(args);
		}
		else if (Same(args[0], "up") || Same(args[0], "u"))
		{
			(args.size() == 1) ? args.push_back("up") : args[1] = "up";
			player->Go(args);
		}
		else if (Same(args[0], "down") || Same(args[0], "d"))
		{
			(args.size() == 1) ? args.push_back("down") : args[1] = "down";
			player->Go(args);
		}
		else if (Same(args[0], "stats") || Same(args[0], "st"))
		{
			player->Stats();
		}
		else if (Same(args[0], "inventory") || Same(args[0], "i"))
		{
			player->Inventory();
		}
		else
			ret = false;
		break;
	}
	case 2: // commands with one argument ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l"))
		{
			player->Look(args);
		}
		else if (Same(args[0], "go"))
		{
			player->Go(args);
		}
		else if (Same(args[0], "take") || Same(args[0], "pick"))
		{
			player->Take(args);
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
			player->Drop(args);
		}
		else if (Same(args[0], "equip") || Same(args[0], "eq"))
		{
			player->Equip(args);
		}
		else if (Same(args[0], "unequip") || Same(args[0], "uneq"))
		{
			player->UnEquip(args);
		}
		else if (Same(args[0], "examine") || Same(args[0], "ex"))
		{
			player->Examine(args);
		}
		else if (Same(args[0], "attack") || Same(args[0], "at"))
		{
			player->Attack(args);
		}
		else if (Same(args[0], "loot") || Same(args[0], "lt"))
		{
			player->Loot(args);
		}
		else if (Same(args[0], "talk") || Same(args[0], "t"))
		{
			player->Talk(args);
		}
		else
			ret = false;
		break;
	}
	case 3: // commands with two arguments ------------------------------
	{

		if (Same(args[0], "talk") || Same(args[0], "t"))
		{
			player->Talk(args);
		}
		break;
	}
	case 4: // commands with three arguments ------------------------------
	{
		if (Same(args[0], "unlock") || Same(args[0], "unlk"))
		{
			player->UnLock(args);
		}
		else if (Same(args[0], "lock") || Same(args[0], "lk"))
		{
			player->Lock(args);
		}
		else if (Same(args[0], "take") || Same(args[0], "pick"))
		{
			player->Take(args);
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
			player->Drop(args);
		}
		else if (Same(args[0], "notch") || Same(args[0], "combine") || Same(args[0], "use"))
		{
			player->Combine(args, recipes);
		}
		else
			ret = false;
		break;
	}
	default:
		ret = false;
	}

	return ret;
}