#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = map = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	map = App->textures->Load("pinball/Background.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	// Pivot 0, 0
	int Background[50] = {
		755, 1109,
		757, 336,
		719, 215,
		667, 142,
		572, 70,
		460, 37,
		300, 48,
		214, 88,
		155, 142,
		111, 223,
		100, 296,
		100, 401,
		116, 510,
		137, 590,
		177, 666,
		160, 692,
		157, 781,
		113, 793,
		93, 831,
		93, 980,
		286, 1109,
		63, 1111,
		62, 0,
		830, 0,
		829, 1111
	}; App->physics->CreateChain(0, 0, Background, 50);

	// Pivot 0, 0
	int Background2[68] = {
		708, 1110,
		704, 331,
		664, 220,
		581, 139,
		476, 97,
		448, 92,
		362, 89,
		291, 112,
		240, 145,
		218, 169,
		286, 136,
		338, 121,
		384, 117,
		458, 128,
		524, 153,
		564, 179,
		601, 215,
		637, 268,
		652, 294,
		665, 393,
		656, 468,
		646, 532,
		625, 600,
		591, 665,
		608, 698,
		610, 778,
		641, 787,
		665, 809,
		672, 854,
		674, 947,
		670, 981,
		641, 1006,
		592, 1037,
		479, 1110
	}; App->physics->CreateChain(0, 0, Background2, 68);

	// Pivot 0, 0
	int FlipperRight[14] = {
		498, 1041,
		623, 954,
		623, 828,
		611, 827,
		607, 922,
		486, 1010,
		499, 1020
	}; App->physics->CreateChain(0, 0, FlipperRight, 14);

	// Pivot 0, 0
	int FlipperLeft[14] = {
		266, 1036,
		146, 954,
		147, 828,
		156, 828,
		161, 925,
		278, 1008,
		267, 1020
	}; App->physics->CreateChain(0, 0, FlipperLeft, 14);

	// Pivot 0, 0
	int TriangleRight[8] = {
		508, 946,
		559, 906,
		557, 834,
		506, 925
	}; App->physics->CreateChain(0, 0, TriangleRight, 8);

	// Pivot 0, 0
	int TriangleLeft[8] = {
		258, 944,
		208, 913,
		206, 834,
		260, 928
	}; App->physics->CreateChain(0, 0, TriangleLeft, 8);

	// Pivot 0, 0
	int PlantRight[44] = {
		523, 581,
		545, 607,
		597, 498,
		604, 455,
		605, 321,
		575, 256,
		531, 213,
		504, 195,
		500, 365,
		499, 395,
		488, 429,
		488, 451,
		482, 468,
		498, 486,
		525, 431,
		530, 394,
		586, 391,
		584, 436,
		572, 482,
		562, 514,
		547, 543,
		530, 566
	}; App->physics->CreateChain(0, 0, PlantRight, 44);
	
	// Pivot 0, 0
	int WallLeft[20] = {
		221, 604,
		245, 578,
		206, 526,
		186, 459,
		175, 400,
		184, 344,
		162, 382,
		162, 447,
		173, 516,
		193, 565
	}; App->physics->CreateChain(0, 0, WallLeft, 20);

	// Pivot 0, 0
	int WallStar[26] = {
		307, 517,
		329, 492,
		327, 459,
		266, 395,
		251, 354,
		253, 317,
		262, 299,
		262, 264,
		237, 324,
		238, 432,
		249, 479,
		268, 510,
		292, 517
	}; App->physics->CreateChain(0, 0, WallStar, 26);

	// Pivot 0, 0
	int StickLeft[8] = {
		333, 255,
		350, 247,
		350, 192,
		331, 192
	}; App->physics->CreateChain(0, 0, StickLeft, 8);

	// Pivot 0, 0
	int StickRight[8] = {
		417, 225,
		439, 225,
		439, 178,
		415, 173
	}; App->physics->CreateChain(0, 0, StickRight, 8);

	App->physics->CreateCircle(427, 304, 35, true);

	App->physics->CreateCircle(327, 346, 35, true);

	App->physics->CreateCircle(404, 420, 35, true);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	App->renderer->Blit(map, 0, 0, NULL);

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}


	/*if(player dies) == true)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}*/

    // Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
