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
	pugi::xml_parse_result res = buffmanager_xml.load_file("buff_manager.xml");;
	node = buffmanager_xml.document_element();

	LoadEffects(node);

	return true;
}

bool j1BuffManager::Update(float dt)
{
	// better optimization if this is done on the update of every entity --> (&effect, this)

	// TEMPORARY EFFECT
	RestartAttribute(&effects[WAR_CRY], App->player);

	// PER TICK
	ApplyEachTick(&effects[POISON], App->player);

	// LIMIT THE ATTRIBUTES OF Entities  
	LimitAttributes(App->player);
	

	return true;
}

bool j1BuffManager::CleanUp()
{

	delete effects;

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
	else if (effect->duration_type == TEMPORARY) // we have to put manually every NEW EFFECT that has a TIMER (and create the timer in entity.h or in this case in Player.h)
	{
		switch (effect->attribute_to_change)
		{
		case HEALTH:
			if (effect->name == effects[HEAL].name)
			{
				if (entity->heal_active == false)
				{
					DoMath(entity->health, effect->bonus, effect->method, effect->type);
					entity->heal_active = true;
				}
				entity->healing.Start(); // timer starts
			}
			break;

		case STRENGTH:

			if (effect->name == effects[WAR_CRY].name)
			{
				if (entity->war_cry_active == false)
				{
					DoMath(entity->strength, effect->bonus, effect->method, effect->type);
					entity->war_cry_active = true;
				}
				entity->war_cry.Start();
			}			
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
			if (effect->name == effects[POISON].name)
			{
				if (entity->poison_tick_active == false)
				{
					entity->poison_tick_active = true;
				}
				entity->poison_tick.Start(); // start or restart timer
				entity->poison_tick_iterator = 0; //restart iterator
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

void j1BuffManager::DoMath(int &att_value, float bonus, EffectMethod method, EffectType eff_type)
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

void j1BuffManager::RestartAttribute(Effect *effect, j1Player *entity) //Check all the TEMPORAY effects of an entity and 
{
	if (effect->name == effects[HEAL].name)
	{
		if (entity->heal_active == true && entity->healing.ReadSec() > effect->duration_value)
		{
			entity->health = entity->og_health;
			entity->heal_active = false;
		}
	}
	else if (effect->name == effects[WAR_CRY].name)
	{
		if (entity->war_cry_active == true && entity->war_cry.ReadSec() > effect->duration_value)
		{
			entity->strength = entity->og_strength;
			entity->war_cry_active = false;
		}
	}
	
}

void j1BuffManager::ApplyEachTick(Effect * effect, j1Player * entity) //Check all the PER_TICK effects of an entity
{
	if (effect->name == effects[POISON].name)
	{
		if (entity->poison_tick_active == true)
		{
			if (entity->poison_tick.ReadSec() > effect->duration_value)
			{
				entity->poison_tick_active = false;
				entity->poison_tick_iterator = 0;

			}
			if (entity->poison_tick.ReadSec() > entity->poison_tick_iterator)
			{
				DoMath(entity->health, effect->bonus, effect->method, effect->type);
				DoMath(entity->og_health, effect->bonus, effect->method, effect->type);
				entity->poison_tick_iterator++;
			}
		}
	}
	
}

void j1BuffManager::LimitAttributes(j1Player * entity)
{
	// HEALTH ATT
	if (entity->og_health > MAX_HEALTH)
		entity->og_health = MAX_HEALTH;
	else if (entity->og_health < MIN_HEALTH)
		entity->og_health = MIN_HEALTH;

	if (entity->health > MAX_HEALTH)
		entity->health = MAX_HEALTH;
	else if (entity->health < MIN_HEALTH)
		entity->health = MIN_HEALTH;

	// STRENGTH ATT
	if (entity->og_strength > MAX_STRENGTH)
		entity->og_strength = MAX_STRENGTH;
	else if (entity->og_strength < MIN_STRENGTH)
		entity->og_strength = MIN_STRENGTH;

	if (entity->strength > MAX_STRENGTH)
		entity->strength = MAX_STRENGTH;
	else if (entity->strength < MIN_STRENGTH)
		entity->strength = MIN_STRENGTH;

	// ARMOR ATT
	if (entity->og_armor > MAX_ARMOR)
		entity->og_armor = MAX_ARMOR;
	else if (entity->og_armor < MIN_ARMOR)
		entity->og_armor = MIN_ARMOR;

	if (entity->armor > MAX_ARMOR)
		entity->armor = MAX_ARMOR;
	else if (entity->armor < MIN_ARMOR)
		entity->armor = MIN_ARMOR;

	// SPEED ATT
	if (entity->og_speed > MAX_SPEED)
		entity->og_speed = MAX_SPEED;
	else if (entity->og_speed < MIN_SPEED)
		entity->og_speed = MIN_SPEED;

	if (entity->speed > MAX_SPEED)
		entity->speed = MAX_SPEED;
	else if (entity->speed < MIN_SPEED)
		entity->speed = MIN_SPEED;
}

void j1BuffManager::LoadEffects(pugi::xml_node & data)
{
	pugi::xml_node iterator;
	Effect effect;
	
	for (iterator = data.child("effect"); iterator; iterator = iterator.next_sibling("effect"))
	{
		effect.name = iterator.attribute("name").as_string();
		SetValue(effect, iterator.attribute("type").as_string());
		SetValue(effect, iterator.attribute("duration_type").as_string());
		SetValue(effect, iterator.attribute("method").as_string());
		SetValue(effect, iterator.attribute("att_to_change").as_string());
		effect.bonus = iterator.attribute("bonus").as_int();
		effect.duration_value = iterator.attribute("duration_value").as_int();

		effects[iterator.attribute("id").as_int()] = effect;
		CreatedEffects++;
	}
	
}

void j1BuffManager::SetValue(Effect &effect, std::string string)
{
	if (string == "BUFF" )
	{
		effect.type = BUFF;
	}
	else if (string == "DEBUFF")
	{
		effect.type = DEBUFF;
	}
	else if (string == "PERMANENT")
	{
		effect.duration_type = PERMANENT;
	}
	else if (string == "TEMPORARY")
	{
		effect.duration_type = TEMPORARY;
	}
	else if (string == "PER_TICK")
	{
		effect.duration_type = PER_TICK;
	}
	else if (string == "ADD")
	{
		effect.method = ADD;
	}
	else if (string == "MULTIPLY")
	{
		effect.method = MULTIPLY;
	}
	else if (string == "PERCENTAGE")
	{
		effect.method = PERCENTAGE;
	}
	else if (string == "HEALTH")
	{
		effect.attribute_to_change = HEALTH;
	}
	else if (string == "ARMOR")
	{
		effect.attribute_to_change = ARMOR;
	}
	else if (string == "STRENGTH")
	{
		effect.attribute_to_change = STRENGTH;
	}
	else if (string == "SPEED")
	{
		effect.attribute_to_change = SPEED;
	}
	
	
}
