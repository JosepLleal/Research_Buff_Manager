#include "j1Player.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1BuffManager.h"

j1Player::j1Player(): j1Module()
{
	name.assign("player");
}

j1Player::~j1Player()
{
}

bool j1Player::Awake()
{
	

	return true;
}

bool j1Player::Start()
{

	graphics = App->tex->Load("textures/character.png");

	position.x = 0;
	position.y = 600;

	health = og_health = 200;
	strength = og_strength = 50;
	speed = og_speed = 3;
	armor = og_armor = 10;
	
	return true;
}

bool j1Player::PreUpdate()
{



	return true;
}


bool j1Player::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		position.y -= speed ;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		position.y += speed;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		position.x -= speed;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		position.x += speed;

	
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		// TODO 7:
		// Apply the GHOST effect to the player
	}

	
	// TODO 6:
	// Call the necessary function to, when the effect finishes, restart the upgraded attribute. 
	

	
	App->buff->LimitAttributes(this);

	
	return true;
}

bool j1Player::PostUpdate()
{

	App->render->Blit(graphics, position.x, position.y);

	return true;
}

bool j1Player::CleanUp()
{

	App->tex->UnLoad(graphics);

	return true;
}
