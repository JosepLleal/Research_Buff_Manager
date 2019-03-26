#include "j1App.h"
#include "j1Player.h"
#include "j1Input.h"
#include "j1Timer.h"
#include "j1BuffManager.h"
#include "p2Log.h"



j1BuffManager::j1BuffManager(): j1Module()
{
	name.assign("BuffManager");
}

j1BuffManager::~j1BuffManager() 
{

}


bool j1BuffManager::Awake()
{
	return true;
}


bool j1BuffManager::Start()
{
	heal.name = "healing";
	heal.type = BUFF;
	heal.bonus = 20;
	heal.duration_type = PERMANENT;
	heal.duration_value = 5;
	heal.method = ADD;
	heal.attribute_to_change = HEALTH;

	health.name = "hp_tick";
	health.type = DEBUFF;
	health.bonus = 2;
	health.duration_type = PER_TICK;
	health.duration_value = 10;
	health.method = ADD;
	health.attribute_to_change = HEALTH;

	return true;
}

bool j1BuffManager::Update(float dt)
{
	// TEMPORARY EFFECT
	RestartAttribute(&heal, App->player);

	// PER TICK
	ApplyByTick(&health, App->player);

	// LIMIT THE ATTRIBUTES OF Entities
	LimitAttributes(App->player);
	

	return true;
}

bool j1BuffManager::CleanUp()
{


	return true;
}

void j1BuffManager::ApplyEffect(Effect* effect, j1Player *entity)
{
	
	if (effect->duration_type == PERMANENT)
	{
		switch (effect->attribute_to_change)
		{
		case HEALTH:
			DoMath(entity->health, effect->bonus, effect->method, effect->type);
			DoMath(entity->og_health, effect->bonus, effect->method, effect->type);
			break;

		case STRENGTH:
			DoMath(entity->strength, effect->bonus, effect->method, effect->type);
			DoMath(entity->og_strength, effect->bonus, effect->method, effect->type);
			break;

		case ARMOR:
			DoMath(entity->armor, effect->bonus, effect->method, effect->type);
			DoMath(entity->og_armor, effect->bonus, effect->method, effect->type);
			break;

		case SPEED:
			DoMath(entity->speed, effect->bonus, effect->method, effect->type);
			DoMath(entity->og_speed, effect->bonus, effect->method, effect->type);
			break;
					
		}
	}
	else if (effect->duration_type == TEMPORARY) // we have to put manually every NEW EFFECT that has a TIMER (and create the timer in entity.h or in this case Player.h)
	{
		switch (effect->attribute_to_change)
		{
		case HEALTH:
			if (effect->name == heal.name)
			{
				if (entity->heal_active == false)
				{
					DoMath(entity->health, effect->bonus, effect->method, effect->type);
					entity->heal_active = true;
				}
				entity->healing.Start();
			}
			break;

		case STRENGTH:
			DoMath(entity->strength, effect->bonus, effect->method, effect->type);
			
			break;

		case ARMOR:
			DoMath(entity->armor, effect->bonus, effect->method, effect->type);
			
			break;

		case SPEED:
			DoMath(entity->speed, effect->bonus, effect->method, effect->type);
			
			break;
		}
	}
	else if (effect->duration_type == PER_TICK)// we have to put manually every NEW EFFECT that has a TIMER (and create the timer in entity.h or in this case Player.h)
	{
		switch (effect->attribute_to_change)
		{
		case HEALTH:
			if (effect->name == health.name)
			{
				if (entity->hp_tick_active == false)
				{
					entity->hp_tick_active = true;
				}
				entity->hp_tick.Start();
			}
			break;

		case STRENGTH:
			
			break;

		case ARMOR:
			
			break;

		case SPEED:
			
			break;

		}
	}
	

}

void j1BuffManager::DoMath(uint &att_value, float bonus, EffectMethod method, EffectType eff_type)
{
	if (eff_type == BUFF)
	{
		if (method == ADD)
		{
			att_value += bonus;
		}
		else if (method == MULTIPLY)
		{
			att_value *= bonus;
		}
		else if (method == PERCENTAGE)
		{
			att_value += att_value * (bonus / 100);
		}
	}
	else if (eff_type == DEBUFF)
	{
		if (method == ADD)
		{
			att_value -= bonus;
		}
		else if (method == MULTIPLY)
		{
			att_value /= bonus;
		}
		else if (method == PERCENTAGE)
		{
			att_value -= att_value * (bonus / 100);
		}
	}
	
}

void j1BuffManager::RestartAttribute(Effect *effect, j1Player *entity)
{
	if (effect->name == "healing")
	{
		if (entity->healing.ReadSec() > effect->duration_value && entity->heal_active == true)
		{
			entity->health = entity->og_health;
			entity->heal_active = false;
		}
	}
	
}

void j1BuffManager::ApplyByTick(Effect * effect, j1Player * entity)
{
	if (entity->hp_tick_active == true)
	{
		if (entity->hp_tick.ReadSec() > effect->duration_value)
		{
			entity->hp_tick_active = false;
			entity->hp_tick_iterator = 0;

		}
		if (entity->hp_tick.ReadSec() > entity->hp_tick_iterator)
		{
			DoMath(entity->health, effect->bonus, effect->method, effect->type);
			DoMath(entity->og_health, effect->bonus, effect->method, effect->type);
			entity->hp_tick_iterator++;
		}
	}
}

void j1BuffManager::LimitAttributes(j1Player * entity)
{
	// HEALTH ATT
	if (entity->og_health > MAX_HEALTH)
		entity->og_health = MAX_HEALTH;

	if (entity->health > MAX_HEALTH)
		entity->health = MAX_HEALTH;

	// STRENGTH ATT
	if (entity->og_strength > MAX_STRENGTH)
		entity->og_strength = MAX_STRENGTH;

	if (entity->strength > MAX_STRENGTH)
		entity->strength = MAX_STRENGTH;

	// ARMOR ATT
	if (entity->og_armor > MAX_ARMOR)
		entity->og_armor = MAX_ARMOR;

	if (entity->armor > MAX_ARMOR)
		entity->armor = MAX_ARMOR;

	// SPEED ATT
	if (entity->og_speed > MAX_SPEED)
		entity->og_speed = MAX_SPEED;

	if (entity->speed > MAX_SPEED)
		entity->speed = MAX_SPEED;
}