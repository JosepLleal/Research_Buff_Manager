#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Gui.h"
#include <vector>

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

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



private:
	SDL_Texture* debug_tex;

	std::vector <std::string*> StageList;

	Gui_Elements* Health = nullptr;
	Gui_Elements* Strength = nullptr;
	Gui_Elements* Speed = nullptr;
	Gui_Elements* Armor = nullptr;

	Gui_Elements* HUD = nullptr;

	Gui_Elements* NumberEffects = nullptr;
	Gui_Elements* EffectsLoaded = nullptr;

};

#endif // __j1SCENE_H__