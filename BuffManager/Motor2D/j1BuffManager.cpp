#include "j1App.h"
#include "j1BuffManager.h"



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
	heal.type = BUFF;
	heal.bonus = 50;
	heal.duration = PERMANENT;
	heal.method = ADD;

	return true;
}

bool j1BuffManager::Update(float dt)
{
	return true;
}

void j1BuffManager::ApplyEffect(Effect effect)
{

}

bool j1BuffManager::CleanUp()
{
	return true;
}