#include <iostream>
#include "globals.h"
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "world.h"

// ----------------------------------------------------
World::World()
{
	tick_timer = clock();

	// Rooms ----
	Room* mainentrance = new Room("Hogwarts main entrance", "\nGlorious and imposing entrance to the castle with all the magician houses flags waving\n");
	Room* forestpath = new Room("Forbidden Forest Path", "\nThere's a warning notice:'Forbidden to enter without a broom'.\n"
		"You hear people screaming from the north\n.");
	Room* thestadiumbridge = new Room("Quidditch Stadium Bridge", "\nYou can hear people cheering on their teams with a lot of euphoria.\n"
		"There's a Quidditch match of Hufflepuff against Slytherin.\n");
	Room* thehogwartshills = new Room("Hogwarts Hills", "\nThe lonely Whomping Willow still being as agressive as always.\n");
	Room* dumbledoresoffice = new Room("Dumbledore's office", "Dumbledore: Hi Harry, how are you doing? I hope you were able to enjoy your vacation.\n"
		"Harry: Hi Professor Dumbledore!! Glad to see you again sir.\n"
		"Dumbledore: The Gryffindor Common room has changed its access password this year. However, I think you should already know that. If you don't, I can give it to you.\n");
	Room* gryffindorcommonroom = new Room("Gryffindor Common Room", "There are all your Gryffindor mates and your suitcase is right in the entrance near you.\n");
	Room* dinningroom = new Room("The Great Dinning Room", "This is a huge room to practice new spells.\n");
	Room* hagridshut = new Room("Hagrid's Hut", "Hagrid is lying in the bed looking very bad.\n");
	Room* whompingwillow = new Room("Whomping Willow", "Watch out!! Whomping Willow's branches are too fast, they can hurt you");
	Room* forbiddenforest = new Room("Forbidden Forest", "You are surrounded by a huge dark forest.\n"
		"and you are not alone... There's a plantation of mandragora right there. Don't waste a lot of time here...\n");
	Room* quidditwarehouse = new Room("Quiddich Stadium Warehouse", "This warehouse should have a lot of brooms.\n");

	//Main entrance 
	Exit* ex1 = new Exit("south", "north", "Hagrid's Hut", mainentrance, hagridshut);
	Exit* ex2 = new Exit("north", "south", "The Great Dinning Room", mainentrance, dinningroom);	
	Exit* ex3 = new Exit("west", "east", "Forbidden Forest Path", mainentrance, forestpath);

	//Forbidden Forest Path
	Exit* ex4 = new Exit("west", "east", "Forbidden Forest", forestpath, forbiddenforest);
	Exit* ex5 = new Exit("north", "south", "Quiddich Stadium Bridge", forestpath, thestadiumbridge);

	//Quidditch Stadium Bridge
	Exit* ex6 = new Exit("north", "south", "Quiddich Stadium Warehouse", thestadiumbridge, quidditwarehouse);
	Exit* ex7 = new Exit("east", "west", "The Hogwarts Hills", thestadiumbridge, thehogwartshills);

	//Whomping Willow
	Exit* ex8 = new Exit("east", "west", "Whomping Willow", thehogwartshills, whompingwillow);

	//Inside the castle
	Exit* ex9 = new Exit("north", "south", "Dumbledore's Office", dinningroom, dumbledoresoffice);
	Exit* ex10 = new Exit("up", "down", "Gryffindor Common Room", dinningroom, gryffindorcommonroom);

	ex1->locked = true;
	ex4->locked = true;
	ex6->locked = true;
	ex8->locked = true;
	ex10->locked = true;


	entities.push_back(mainentrance);
	entities.push_back(forestpath);
	entities.push_back(thestadiumbridge);
	entities.push_back(dumbledoresoffice);
	entities.push_back(gryffindorcommonroom);
	entities.push_back(dinningroom);
	entities.push_back(hagridshut);
	entities.push_back(whompingwillow);
	entities.push_back(forbiddenforest);
	entities.push_back(quidditwarehouse);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);
	entities.push_back(ex8);
	entities.push_back(ex9);
	entities.push_back(ex10);

	// Creatures ----
	Creature* dumbledore = new Creature("Dumbledore", "Hogwarts Director.", dumbledoresoffice);
	Creature* hagrid = new Creature("Hagrid", "Hogwarts Guardian.", hagridshut);
	Creature* fatlady = new Creature("Fat Lady", "Gryffindor Common Room Guardian.", dinningroom);
	Creature* hermione = new Creature("Hermione", "Your firend.", dinningroom);
	Creature* ron = new Creature("Ron", "Your firend.", dinningroom);

	entities.push_back(dumbledore);
	entities.push_back(hagrid);
	entities.push_back(fatlady);
	entities.push_back(hermione);
	entities.push_back(ron);

	// Items -----

	Item* password = new Item("Password", "Fortuna Major", dumbledore);
	Item* suitcase = new Item("Suitcase", "Your suitcase.", gryffindorcommonroom);
	Item* wand = new Item(" Wand", "Your magic wand, use it to spell objects or creatures.", suitcase/*, MAGICOBJECT*/);
	Item* inmobilus = new Item("Inmobilus", "Note with the spell written. You can immobilize the Whomping Willow with this spell.", ron/*, SPELL*/);
	Item* note = new Item("Note", "There are not more mandragoras here, you can find them into the forbidden forest.", whompingwillow);
	Item* alohomora = new Item("Alohomora", "Note with the spell written. You can open locked doors with this spell", hermione/*, SPELL*/);
	Item* broom = new Item("Broom", "You can move faster with this item.", quidditwarehouse/*, MAGICOBJECT*/);
	Item* mandragora = new Item("Mandragora", "Its salvia can heal sick people.", forbiddenforest);

	ex1->key = mandragora;
	ex4->key = broom;
	ex6->key = alohomora;
	ex8->key = inmobilus;
	ex10->key = password;

	entities.push_back(password);
	entities.push_back(suitcase);
	entities.push_back(wand);
	entities.push_back(inmobilus);
	entities.push_back(note);
	entities.push_back(alohomora);
	entities.push_back(broom);
	entities.push_back(mandragora);

	// Player -----

	player = new Player("Harry Potter", "You are a magnificent magician!", mainentrance);

	entities.push_back(player);
}

// ----------------------------------------------------
World::~World()
{
	for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

// ----------------------------------------------------
bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if(args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

// ----------------------------------------------------
void World::GameLoop()
{
	clock_t now = clock();

	if((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			(*it)->Tick();

		tick_timer = now;
	}
}

// ----------------------------------------------------
bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch(args.size())
	{
		case 1: // commands with no arguments ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "north") || Same(args[0], "n"))
			{
				(args.size() == 1) ? args.push_back("north") : args[1] = "north";
				player->Go(args);
			}
			else if(Same(args[0], "south") || Same(args[0], "s"))
			{
				(args.size() == 1) ? args.push_back("south") : args[1] = "south";
				player->Go(args);
			}
			else if(Same(args[0], "east") || Same(args[0], "e"))
			{
				(args.size() == 1) ? args.push_back("east") : args[1] = "east";
				player->Go(args);
			}
			else if(Same(args[0], "west") || Same(args[0], "w"))
			{
				(args.size() == 1) ? args.push_back("west") : args[1] = "west";
				player->Go(args);
			}
			else if(Same(args[0], "up") || Same(args[0], "u"))
			{
				(args.size() == 1) ? args.push_back("up") : args[1] = "up";
				player->Go(args);
			}
			else if(Same(args[0], "down") || Same(args[0], "d"))
			{
				(args.size() == 1) ? args.push_back("down") : args[1] = "down";
				player->Go(args);
			}
			else if(Same(args[0], "stats") || Same(args[0], "st"))
			{
				player->Stats();
			}
			else if(Same(args[0], "inventory") || Same(args[0], "i"))
			{
				player->Inventory();
			}
			else
				ret = false;
			break;
		}
		case 2: // commands with one argument ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "go"))
			{
				player->Go(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else if(Same(args[0], "equip") || Same(args[0], "eq"))
			{
				player->Equip(args);
			}
			else if(Same(args[0], "unequip") || Same(args[0], "uneq"))
			{
				player->UnEquip(args);
			}			
			else
				ret = false;
			break;
		}
		case 3: // commands with two arguments ------------------------------
		{
			if (Same(args[0], "talk") || Same(args[0], "tk"))
			{
				player->Talk(args);
			}
			else
				ret = false;
			break;
		}
		case 4: // commands with three arguments ------------------------------
		{
			if(Same(args[0], "unlock") || Same(args[0], "unlk"))
			{
				player->UnLock(args);
			}			
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else
				ret = false;
			break;
		}
		default:
		ret =  false;
	}

	return ret;
}