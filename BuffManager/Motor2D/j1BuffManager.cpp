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
	heal.type = DEBUFF;
	heal.bonus = 20;
	heal.duration_type = TEMPORARY;
	heal.duration_value = 5;
	heal.method = ADD;
	heal.attribute_to_change = HEALTH;

	health.name = "hp_tick";
	health.type = BUFF;
	health.bonus = 2;
	health.duration_type = PER_TICK;
	health.duration_value = 10;
	health.method = ADD;
	health.attribute_to_change = HEALTH;

	

	return true;
}

bool j1BuffManager::Update(float dt)
{

	RestartAttribute(&heal, App->player);

	//PER TICK (NEEDS FUNCTION)
	if (App->player->hp_tick_active == true)
	{
		if (App->player->hp_tick.ReadSec() > health.duration_value)
		{
			App->player->hp_tick_active = false;
			App->player->hp_tick_iterator = 0;

		}
		if (App->player->hp_tick.ReadSec() > App->player->hp_tick_iterator)
		{
			DoMath(App->player->health, health.bonus, health.method, health.type);
			DoMath(App->player->og_health, health.bonus, health.method, health.type);
			App->player->hp_tick_iterator++;
		}		
	}
	

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
	else if (effect->duration_type == TEMPORARY)
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
	else if (effect->duration_type == PER_TICK)
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


bool j1BuffManager::CleanUp()
{
	return true;
}