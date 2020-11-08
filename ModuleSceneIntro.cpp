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
	int Background[86] = {
		756, 1112,
		833, 1112,
		831, 0,
		64, 0,
		64, 1112,
		291, 1112,
		97, 984,
		96, 964,
		96, 830,
		111, 802,
		133, 786,
		160, 781,
		160, 707,
		169, 682,
		179, 673,
		179, 663,
		152, 616,
		130, 543,
		112, 467,
		104, 400,
		104, 260,
		124, 198,
		146, 158,
		157, 142,
		171, 131,
		202, 110,
		236, 86,
		267, 69,
		304, 57,
		328, 51,
		348, 46,
		459, 45,
		520, 57,
		580, 83,
		625, 110,
		648, 126,
		672, 148,
		693, 179,
		716, 215,
		733, 254,
		745, 293,
		755, 340,
		755, 353
	}; App->physics->CreateChain(0, 0, Background, 86);

	// Pivot 0, 0
	int RightWall[118] = {
		479, 1111,
		707, 1111,
		707, 335,
		687, 258,
		656, 202,
		632, 175,
		611, 157,
		585, 138,
		559, 121,
		519, 104,
		491, 96,
		465, 91,
		411, 88,
		369, 88,
		340, 92,
		306, 104,
		268, 124,
		247, 137,
		231, 150,
		215, 172,
		229, 167,
		251, 154,
		281, 142,
		312, 131,
		351, 124,
		424, 124,
		469, 134,
		501, 146,
		540, 164,
		570, 184,
		602, 217,
		627, 252,
		651, 293,
		664, 316,
		663, 397,
		654, 471,
		646, 524,
		635, 563,
		622, 605,
		612, 629,
		600, 647,
		588, 665,
		588, 674,
		598, 682,
		608, 705,
		608, 782,
		634, 788,
		651, 796,
		660, 809,
		666, 820,
		672, 835,
		671, 975,
		663, 989,
		638, 1008,
		614, 1021,
		582, 1043,
		552, 1061,
		514, 1086,
		492, 1101
	}; App->physics->CreateChain(0, 0, Background, 118);

	// Pivot 0, 0
	int Bellsprout[72] = {
		523, 573,
		524, 586,
		546, 606,
		567, 582,
		584, 536,
		601, 482,
		608, 448,
		607, 324,
		582, 264,
		565, 244,
		530, 209,
		512, 197,
		504, 197,
		503, 331,
		499, 337,
		499, 363,
		495, 369,
		495, 374,
		479, 393,
		479, 411,
		483, 414,
		483, 426,
		487, 430,
		487, 445,
		483, 451,
		480, 466,
		496, 487,
		504, 487,
		518, 459,
		527, 427,
		528, 399,
		587, 399,
		587, 421,
		564, 511,
		555, 534,
		539, 554
	}; App->physics->CreateChain(0, 0, Background, 72);

	// Pivot 0, 0
	int TopRightMiniWall[16] = {
		416, 177,
		415, 226,
		421, 231,
		435, 231,
		440, 225,
		440, 176,
		435, 172,
		420, 172
	}; App->physics->CreateChain(0, 0, Background, 16);

	// Pivot 0, 0
	int TopLeftMiniWall[14] = {
		328, 197,
		328, 255,
		335, 259,
		352, 251,
		352, 193,
		347, 188,
		336, 188
	}; App->physics->CreateChain(0, 0, Background, 14);

	// Pivot 0, 0
	int StarmieWall[36] = {
		235, 328,
		235, 433,
		246, 471,
		258, 498,
		278, 515,
		288, 519,
		307, 519,
		331, 493,
		331, 476,
		326, 457,
		291, 421,
		264, 386,
		253, 355,
		252, 329,
		263, 305,
		263, 263,
		248, 288,
		240, 313
	}; App->physics->CreateChain(0, 0, Background, 36);

	// Pivot 0, 0
	int TopLeftBlueWall[38] = {
		222, 607,
		243, 587,
		243, 573,
		229, 554,
		212, 534,
		196, 489,
		184, 442,
		180, 419,
		179, 389,
		187, 365,
		182, 340,
		171, 356,
		161, 386,
		160, 458,
		166, 483,
		175, 520,
		182, 535,
		191, 560,
		208, 593
	}; App->physics->CreateChain(0, 0, Background, 38);

	// Pivot 0, 0
	int BottomLeftLongWall[24] = {
		148, 824,
		144, 830,
		144, 958,
		157, 974,
		266, 1042,
		273, 1044,
		284, 1013,
		270, 1000,
		164, 927,
		160, 918,
		160, 828,
		156, 824
	}; App->physics->CreateChain(0, 0, Background, 24);

	// Pivot 0, 0
	int BottomLeftLittleWall[16] = {
		209, 837,
		204, 841,
		204, 907,
		217, 922,
		254, 947,
		264, 941,
		264, 928,
		216, 837
	}; App->physics->CreateChain(0, 0, Background, 16);

	// Pivot 0, 0
	int BottomRightLittleWall[16] = {
		559, 836,
		564, 842,
		564, 907,
		555, 916,
		514, 947,
		504, 942,
		504, 928,
		553, 837
	}; App->physics->CreateChain(0, 0, Background, 16);

	// Pivot 0, 0
	int BottomRightLongWall[26] = {
		619, 824,
		624, 832,
		624, 957,
		610, 975,
		559, 1006,
		511, 1039,
		500, 1043,
		482, 1012,
		516, 990,
		587, 943,
		608, 918,
		608, 830,
		612, 824
	}; App->physics->CreateChain(0, 0, Background, 26);

	// Pivot 0, 0
	int LeftVoltorb[24] = {
		309, 316,
		319, 313,
		327, 312,
		338, 313,
		347, 317,
		359, 334,
		359, 354,
		345, 371,
		335, 375,
		320, 375,
		297, 354,
		297, 333
	}; App->physics->CreateChain(0, 0, Background, 24);

	// Pivot 0, 0
	int TopVoltorb[24] = {
		416, 274,
		428, 272,
		439, 273,
		459, 293,
		459, 313,
		450, 327,
		437, 335,
		418, 335,
		401, 323,
		396, 311,
		397, 294,
		407, 280
	}; App->physics->CreateChain(0, 0, Background, 24);

	// Pivot 0, 0
	int BottomVoltorb[24] = {
		392, 386,
		404, 384,
		415, 386,
		430, 397,
		435, 405,
		435, 427,
		413, 448,
		395, 447,
		377, 434,
		373, 424,
		373, 405,
		381, 392
	}; App->physics->CreateChain(0, 0, Background, 24);



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
