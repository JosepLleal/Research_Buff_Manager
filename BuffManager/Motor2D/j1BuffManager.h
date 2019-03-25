#ifndef __j1BuffManager_H__
#define __j1BuffManager_H__

#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

enum Attribute
{
	HEALTH,
	STRENGTH,
	ARMOR,
	SPEED
};

enum EffectType
{
	BUFF,
	DEBUFF
};

enum EffectTime
{
	PERMANENT,
	TEMPORARY,
	PER_TICK
};

enum EffectMethod
{
	ADD,
	MULTIPLY,
	PERCENTAGE
};

	
struct Effect 
{
	std::string		name;

	EffectType		type;
	EffectTime		duration_type;
	EffectMethod	method;
	Attribute		attribute_to_change;

	float			bonus;
	uint			duration_value;
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

	void ApplyEffect(Effect* effect, j1Player *entity);
	void DoMath(uint &att_value, float bonus, EffectMethod method, EffectType eff_type);
	void RestartAttribute(Effect* effect, j1Player *entity);


public:

	Effect			heal;

	Effect			health;
	


};

#endif // __j1BuffManager_H__