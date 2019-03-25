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
	heal.duration_type = TEMPORARY;
	heal.duration_value = 5;
	heal.method = ADD;
	heal.attribute_to_change = HEALTH;

	

	return true;
}

bool j1BuffManager::Update(float dt)
{

	LOG("START: %i", App->player->healing.started_at);
	LOG("TIME: %f", App->player->healing.ReadSec());
	LOG("OG: %i", App->player->og_health);

	RestartAttribute(&heal, App->player);

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
			if(entity->heal_active == false)
				DoMath(entity->health, effect->bonus, effect->method, effect->type);
			entity->healing.Start();
			entity->heal_active = true;
			
			break;

		case STRENGTH:
			effect->original_value = entity->strength;
			DoMath(entity->strength, effect->bonus, effect->method, effect->type);
			
			break;

		case ARMOR:
			effect->original_value = entity->armor;
			DoMath(entity->armor, effect->bonus, effect->method, effect->type);
			
			break;

		case SPEED:
			effect->original_value = entity->speed;
			DoMath(entity->speed, effect->bonus, effect->method, effect->type);
			
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