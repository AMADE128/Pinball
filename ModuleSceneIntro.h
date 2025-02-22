#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	update_status PreUpdate();
	update_status PosUpdate();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	char scoreText[10] = { "\0" };
	int score = 0;
	int hiscore = 0;
	int ScoreFont = -1;
	int counter = 0;
	int lifes = 3;
	PhysBody* sensor;
	PhysBody* Deathbox;
	PhysBody* Startbox;
	bool sensed;
	bool Alive = true;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* map;
	SDL_Texture* rightFlipper;
	SDL_Texture* leftFlipper;
	unsigned int backgroundMusic;
	unsigned int flipperMusic;
	p2Point<int> ray;
	bool ray_on;
};
