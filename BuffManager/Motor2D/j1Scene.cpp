#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "j1Gui_Elements.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1BuffManager.h"

j1Scene::j1Scene() : j1Module()
{
	name.assign("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	for (pugi::xml_node stage = config.child("map_name"); stage; stage = stage.next_sibling("map_name"))
	{
		std::string* StageName = new std::string(stage.attribute("path").as_string());
		StageList.push_back(StageName);
	}

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	// --- Loading map ---

	App->map->Load(StageList.front()->data());

	debug_tex = App->tex->Load("maps/path2.png");

	HUD = App->gui->Create_Image(Element_type::IMAGE, { 350, 655 }, { 0, 0, 278, 112 }, true, false, false, App->gui->GetAtlas(), nullptr);

	Health = App->gui->Create_Label(Element_type::LABEL, { 415, 670 }, true, false, "0%%", { 0,255, 0,0 }, App->font->smaller);
	Strength = App->gui->Create_Label(Element_type::LABEL, { 555, 670 }, true, false, "0%%", { 255,0, 0,0 }, App->font->smaller);
	Armor = App->gui->Create_Label(Element_type::LABEL, { 425, 710 }, true, false, "0%%", { 200,0, 0,0 }, App->font->smaller);
	Speed = App->gui->Create_Label(Element_type::LABEL, { 565, 710 }, true, false, "0%%", { 200,0, 0,0 }, App->font->smaller);

	NumberEffects = App->gui->Create_Label(Element_type::LABEL, { 230, 5 }, true, false, "0%%", { 0,255, 0,0 }, App->font->smaller);
	EffectsLoaded = App->gui->Create_Label(Element_type::LABEL, { 20, 10 }, true, false, "Loaded effects:", { 255,255, 255,0 }, App->font->Credits);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	Health->ValuetoString(App->player->health, Health->text);
	Strength->ValuetoString(App->player->strength, Strength->text);
	Armor->ValuetoString(App->player->armor, Armor->text);
	Speed->ValuetoString(App->player->speed, Speed->text);
	NumberEffects->ValuetoString(App->buff->CreatedEffects, NumberEffects->text);

	if (App->buff->CreatedEffects > 0)
	{
		NumberEffects->color = { 0,255, 0,0 };
	}
	else
	{
		NumberEffects->color = { 255,0, 0,0 };
	}

	
	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += ceil(150.0*dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= ceil(150.0*dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += ceil(150.0*dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= ceil(150.0*dt);



	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->buff->ApplyEffect(&App->buff->effects[HEAL], App->player);
	}
	else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->buff->ApplyEffect(&App->buff->effects[POISON], App->player);
	}
	else if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		App->buff->ApplyEffect(&App->buff->effects[WAR_CRY], App->player);
	}


	App->map->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	std::vector<std::string*>().swap(StageList);

	return true;
}

