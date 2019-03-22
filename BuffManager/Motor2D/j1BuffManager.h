#ifndef __j1BuffManager_H__
#define __j1BuffManager_H__

#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

enum Attributes
{
	HEALTH,
	STRENGTH,
	ARMOR,
	SPEED
};

enum EffectType
{
	NONE,
	BUFF,
	DEBUFF
};

enum EffectTime
{
	PERMANENT,
	LIMITED
};

enum EffectMethod
{
	ADD,
	PERCENTAGE
};

	
struct Effect 
{
	EffectType		type;
	EffectTime		duration;
	EffectMethod	method;

	uint			bonus;
	uint			duration_value;

	j1Timer			timer;

};

class j1BuffManager :public j1Module 
{
public:

	j1BuffManager();
	~j1BuffManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	void ApplyEffect(Effect effect);


public:

	Effect heal;	

};

#endif // __j1BuffManager_H__