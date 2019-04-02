#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Timer.h"

struct SDL_Texture;

class j1Player :public j1Module
{
public:

	j1Player();
	~j1Player();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


public:

	iPoint position = {0,0};

	int speed, health, armor, strength = 0;
	int og_speed, og_health, og_armor, og_strength = 0;

	SDL_Texture * graphics = nullptr;


	// GHOST --- TEMPORARY --- gain extra movement speed for a limited time

	// TODO 3: 
	// create ghost's j1Timer and a bool ghost_active


};

#endif // __j1Player_H__
