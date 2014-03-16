#include "global.h"
#include "XInput.h"
#include "StaticGraphic.h"

#include <ctime>

#include "Girly.h"
#include "Bouncer.h"
#include "Fan.h"
#include "Bullet.h"
#include "Box.h"
#include "Prince.h"
#include "HealthUp.h"
#include "SuperUp.h"
#include "TempGraphic.h"

std::vector <Player*> players;
std::vector <Enemy*> enemies;
std::vector <Entity *> entities;
std::vector <hgeRectExt>		tempBoundingBoxes;
std::vector <Bullet *> bullets;
std::vector <PowerUp *> powerups;
std::vector <TempGraphic *> tempGraphics;

StaticGraphic * titleScreen;
StaticGraphic * background;
StaticGraphic * loseScreen;
StaticGraphic * winScreen;
StaticGraphic * riotScreen;
StaticGraphic * obscenityScreen;
StaticGraphic * gust;
StaticGraphic * options;

Prince * prince;


int currentRound = 0;
int currentStorm = 0;

float timeToFinish = 0;

bool Intro();
bool FrameFunc();
bool RenderFunc();
bool TitleFrame();
bool TitleRender();
bool MenuFrame();
bool MenuRender();
bool CreditsFrame();
bool CreditsRender();
bool PauseFrame();
bool PauseRender();

float levelTime = 50;
int currentLevel = 0;
int spawned = 0;
void Reset()
{
	hge->System_SetState(HGE_FRAMEFUNC, TitleFrame);
	hge->System_SetState(HGE_RENDERFUNC, TitleRender);
	currentLevel = 1;
	levelTime = 0;
	spawned = 0;


	for (unsigned int i = 0; i < entities.size(); ++i)
		delete entities[i];
	entities.clear();

		entities.push_back(new Box("poops.png", 0, 350, 150, S_HEIGHT, 0x00FFFFFF));
		entities.push_back(new Box("poops.png", 0, 0, S_WIDTH, 200, 0x00FFFFFF));
		entities.push_back(new Box("poops.png", 0, S_HEIGHT-70, S_WIDTH, 70, 0x00FFFFFF));
		entities.push_back(new Box("poops.png", 150, 360, 178, 156, 0x00FFFFFF));
		//entities.push_back(new Box("poops.png", S_WIDTH, 0, 20, S_HEIGHT, 0x00FFFFFF));

		//entities.push_back(new StaticGraphic("plant.png", 200, 40, 107, 163, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*2, 40, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*4, 40, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*6, 40, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*8, 40, 130, 184, 0));

		entities.push_back(new StaticGraphic("plant.png", 200, S_HEIGHT-163, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*2, S_HEIGHT-163, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*4, S_HEIGHT-163, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*6, S_HEIGHT-163, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*8, S_HEIGHT-163, 130, 184, 0));

		delete gust;
		gust = new StaticGraphic("gust.png", S_WIDTH + 500, S_HEIGHT/2, 826, 688, 0, true);

		prince = new Prince("prince.png", 70, 160, 96, 96);
		entities.push_back(prince);


	enemies.clear();

	players.clear();

	tempGraphics.clear();

	bullets.clear();

	powerups.clear();

}

bool GetXKey(DWORD key)
{
	PLUGGED_IN = 0;
	for (unsigned int i = 0; i < NUMBER_PLAYERS; ++i )
	{
		DWORD dwResult;   
		XINPUT_STATE state;  
		ZeroMemory( &state, sizeof(XINPUT_STATE) );
		dwResult = XInputGetState( i, &state );
		if (dwResult == ERROR_SUCCESS)
			PLUGGED_IN++;
		else
			break;

		//if (state.Gamepad.sThumbLX > 10276 || state.Gamepad.sThumbLX < -10276 || state.Gamepad.sThumbLY > 10000 || state.Gamepad.sThumbLY < -10000)
		//players[i]->Move(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, dt);
		//if (state.Gamepad.bRightTrigger > 100)
		//	players[i]->AttackC();
		//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		//{
		//	sheep[i]->HoldKeyA();
		//}

		XINPUT_KEYSTROKE keystroke;
		ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
		for (dwResult = XInputGetKeystroke(i, XINPUT_FLAG_GAMEPAD, &keystroke); dwResult == ERROR_SUCCESS; dwResult = XInputGetKeystroke(i, XINPUT_FLAG_GAMEPAD, &keystroke))
		{
			if (keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN)
			{
				if (keystroke.VirtualKey == key)
					return true;
				//if (keystroke.VirtualKey == VK_PAD_B)
				//	players[i]->AttackB();
				//if (keystroke.VirtualKey == VK_PAD_X)
				//	sheep[i]->PressKeyC();
			}
			ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
		}
	}
	return false;
}

bool obscenityFrame()
{
	float dt = hge->Timer_GetDelta();
	GENERIC_COUNTDOWN -= dt;
	if (GENERIC_COUNTDOWN < 0)
	{
		hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	}
	return false;
}

bool obscenityRender()
{
	hge->Gfx_BeginScene();
		obscenityScreen->Render();
	hge->Gfx_EndScene();
	return false;
}

bool riotFrame()
{
	float dt = hge->Timer_GetDelta();
	GENERIC_COUNTDOWN -= dt;
	if (GENERIC_COUNTDOWN < 0)
	{
		hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	}
	return false;
}

bool riotRender()
{
	hge->Gfx_BeginScene();
		riotScreen->Render();
	hge->Gfx_EndScene();
	return false;
}

bool lastFrame()
{
	if (hge->Input_GetKeyState(HGEK_ENTER) || GetXKey(VK_PAD_START))
	{
		hge->Channel_StopAll();
		Reset();
		//hge->System_SetState(HGE_FRAMEFUNC, CreditsFrame);
		//hge->System_SetState(HGE_RENDERFUNC, CreditsRender);
		//fnt->SetColor(0xFFFFFFFF);
	}
	return false;
}

bool winRender()
{
	//player sound
	//show text
	static StaticGraphic fade("nofilehere.png", 0, 0, S_WIDTH, S_HEIGHT, 0);
	static DWORD color = 0x00000000;
	static short alpha = 0;
	if (alpha < 255 * 2)
	{
		alpha++;
		color = 0 | (alpha/2 << 24);
		fade.GetSprite().SetColor(color);
	}

	hge->Gfx_BeginScene();
		fade.Render();
		winScreen->Render();
	hge->Gfx_EndScene();
	return false;
}

bool loseRender()
{
	//player sound
	//show text
	static StaticGraphic fade("nofilehere.png", 0, 0, S_WIDTH, S_HEIGHT, 0);
	static DWORD color = 0x00000000;
	static short alpha = 0;
	if (alpha < 255 * 2)
	{
		alpha++;
		color = 0 | (alpha/2 << 24);
		fade.GetSprite().SetColor(color);
	}

	hge->Gfx_BeginScene();
		fade.Render();
		loseScreen->Render();
	hge->Gfx_EndScene();
	return false;
}

float creditsPosition = S_HEIGHT;
bool CreditsFrame()
{
	creditsPosition -= 0.5f;
	if (creditsPosition < -800)
		creditsPosition = S_HEIGHT;
	if (hge->Input_GetKey())
		return true;
	return false;
}

bool CreditsRender()
{
	hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		fnt->printf(S_WIDTH/2, creditsPosition, HGETEXT_CENTER, "%s%s%s%s%s",
			"Credits (Alphabetical)\n\n\n",
			"*Design*\n----\nKrystal Condren\nNathan Perry\nPaul Fox\nWilliam Goddard\nYing Luo", "\n\n\n*Programming*\n----\nWilliam Goddard",
			"\n\n\n*Art Work*\n----\nKrystal Condren\nNathan Perry\nYing Luo", "\n\n\n*Tools*\n----\nPaul Fox");
	hge->Gfx_EndScene();
	return false;
}


int pauseOption = 0;
bool PauseFrame()
{
	if (hge->Input_KeyDown(HGEK_ESCAPE))
	{
		hge->Channel_ResumeAll();
		hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
		return false;
	}




	bool start = false;
	bool up = false;
	bool down = false;

	PLUGGED_IN = 0;
	for (unsigned int i = 0; i < NUMBER_PLAYERS; ++i )
	{
		DWORD dwResult;   
		XINPUT_STATE state;  
		ZeroMemory( &state, sizeof(XINPUT_STATE) );
		dwResult = XInputGetState( i, &state );
		if (dwResult == ERROR_SUCCESS)
			PLUGGED_IN++;
		else
			break;

		//if (state.Gamepad.sThumbLX > 10276 || state.Gamepad.sThumbLX < -10276 || state.Gamepad.sThumbLY > 10000 || state.Gamepad.sThumbLY < -10000)
		//players[i]->Move(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, dt);
		//if (state.Gamepad.bRightTrigger > 100)
		//	players[i]->AttackC();
		//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		//{
		//	sheep[i]->HoldKeyA();
		//}

		XINPUT_KEYSTROKE keystroke;
		ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
		for (dwResult = XInputGetKeystroke(i, XINPUT_FLAG_GAMEPAD, &keystroke); dwResult == ERROR_SUCCESS; dwResult = XInputGetKeystroke(i, XINPUT_FLAG_GAMEPAD, &keystroke))
		{
			if (keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN)
			{
				if (keystroke.VirtualKey == VK_PAD_START)
					start = true;
				if (keystroke.VirtualKey == VK_PAD_LTHUMB_UP)
					up = true;
				if (keystroke.VirtualKey == VK_PAD_LTHUMB_DOWN)
					down = true;

				//if (keystroke.VirtualKey == VK_PAD_B)
				//	players[i]->AttackB();
				//if (keystroke.VirtualKey == VK_PAD_X)
				//	sheep[i]->PressKeyC();
			}
			ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
		}
	}





	if (hge->Input_KeyDown(HGEK_DOWN) || down)
		pauseOption++;
	if (hge->Input_KeyDown(HGEK_UP) || up)
		pauseOption--;

	if (pauseOption < 0) pauseOption = 2;
	if (pauseOption > 2) pauseOption = 0;

	if (hge->Input_KeyDown(HGEK_ENTER) || start)
	{
		switch(pauseOption)
		{
		case 0:
			hge->Channel_ResumeAll();
			hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
			hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
			return false;
			break;
		case 1:
			hge->Channel_StopAll();
			Reset();
			return false;
			break;
		case 2:
			/////////////////
			hge->System_SetState(HGE_FRAMEFUNC, CreditsFrame);
			hge->System_SetState(HGE_RENDERFUNC, CreditsRender);
			return false;
			break;
		}
	}

	return false;
}

bool PauseRender()
{
	hge->Gfx_BeginScene();
		//hge->Gfx_Clear(0);
		static StaticGraphic temp("sss", S_WIDTH/2 - 100, 100, 300, 450, 0);
		temp.GetSprite().SetColor(0x88000000);
		temp.Render();
		fnt->printf(S_WIDTH/2, 200, HGETEXT_LEFT, "Resume");
		fnt->printf(S_WIDTH/2, 300, HGETEXT_LEFT, "Restart");
		fnt->printf(S_WIDTH/2, 400, HGETEXT_LEFT, "Exit");
		int selection = 0;
		switch(pauseOption)
		{
		case 0:
			selection = 200;
			break;
		case 1:
			selection = 300;
			break;
		case 2:
			selection = 400;
			break;
		default:
			break;
		}
		fnt->printf(S_WIDTH/2 - 50, selection, HGETEXT_LEFT, "*");
	hge->Gfx_EndScene();
	return false;
}

bool TitleFrame()
{
	if (hge->Input_GetKeyState(HGEK_ENTER) || GetXKey(VK_PAD_START))
	{
		hge->System_SetState(HGE_FRAMEFUNC, MenuFrame);
		hge->System_SetState(HGE_RENDERFUNC, MenuRender);
		fnt->SetColor(0xFFFFFFFF);
	}
	return false;
}

bool TitleRender()
{
	static BYTE alpha = 0;
	static bool up = true;
	if (up)
		alpha++;
	else
		alpha--;

	if (alpha >= 255) up = false;
	else if (alpha <= 0) up = true;

	hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		titleScreen->Render();
		fnt->SetColor((alpha << 24) + 0xFFFFFF);
		fnt->printf(S_WIDTH/2, 680, HGETEXT_CENTER, "Press START to continue.");
	hge->Gfx_EndScene();
	return false;
}

bool MenuFrame()
{
	PLUGGED_IN = 0;
	for (unsigned int i = 0; i < MAX_CONTROLLERS; ++i )
	{
		DWORD dwResult;   
		XINPUT_STATE state;  
		ZeroMemory( &state, sizeof(XINPUT_STATE) );
		dwResult = XInputGetState( i, &state );
		if (dwResult == ERROR_SUCCESS)
			PLUGGED_IN++;

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			std::cout << "Controller " << i << " x " << state.Gamepad.sThumbLX << " y " << state.Gamepad.sThumbLY << '\n';
	}

	if (hge->Input_KeyDown(HGEK_ENTER) || GetXKey(VK_PAD_START))
	{
		hge->System_SetState(HGE_FRAMEFUNC, Intro);
		hge->System_SetState(HGE_RENDERFUNC, RenderFunc);

		hge->Stream_Play(music, true);

		timeToFinish = 60.0f;
		currentRound = 1;
		currentStorm = 1;

		players.push_back(new Girly("girl real.png", 500, 500, 96, 96));
		//players.push_back(new Girly("girl2.png", 700, 500, 96, 96));
		players.push_back(new Bouncer("bouncer.png", 700, 500, 96, 96));
		//enemies.push_back(new Fan("Boss.png", S_WIDTH - 400, hge->Random_Int(300, S_HEIGHT-100), 288, 288, 1, 1, 50 + 10 * currentLevel, 5, true));

		for (int i = 0; i < players.size(); ++i)
		{
			entities.push_back(players[i]);
		}

	}
	return false;
}

bool MenuRender()
{
	hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		options->Render();
		//fnt->printf(S_WIDTH/2, 300, HGETEXT_CENTER, "%d players selected.", NUMBER_PLAYERS);
		fnt->printf(S_WIDTH/2, 500, HGETEXT_CENTER, "%d controllers plugged in.", PLUGGED_IN);
	hge->Gfx_EndScene();
	return false;
}

bool Intro()
{
	/////////////////////
	///Skip this shit
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	return false;
	////////////////

}


bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();

	int size = entities.size();
	for (unsigned int i = 0; i < size; ++i)
		entities[i]->Update(dt);
	size = bullets.size();
	for (unsigned int i = 0; i < size; ++i)
		bullets[i]->Update(dt);


	for (unsigned int i = 0; i < tempGraphics.size(); ++i)
	{
		tempGraphics[i]->Update(dt);
		if (tempGraphics[i]->IsAlive() == false)
		{
			delete tempGraphics[i];
			tempGraphics.erase(tempGraphics.begin() + i);
		}
	}


	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i]->IsAlive() == false)
		{
			Entity * temp = enemies[i];
			delete enemies[i];
			enemies.erase(enemies.begin() + i );

			for (unsigned int j = 0; j < entities.size(); ++j)
			{
				if (entities[j] == temp)
				{
					entities.erase(entities.begin() + j);
					break;
				}
			}
			//enemies[i] = NULL;
			--i;
		}
	}

	for (unsigned int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i]->IsAlive() == false)
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
	
	gust->MoveLeft(dt);

	int fps = hge->Timer_GetFPS();
	if (fps < 5)
		fps = 5;

	//int lucky = hge->Random_Int(0, fps*50);
	int lucky = rand() % (fps*50);
	//std::cout << lucky << '\n';

	if (lucky == fps*50 - 1)
		powerups.push_back(new HealthUp("Health.png", hge->Random_Int(200, 500), hge->Random_Int(200, S_HEIGHT-100), 96, 96));
	
	lucky = hge->Random_Int(0, fps*50);

	if (lucky == fps*50)
		powerups.push_back(new SuperUp("Power.png", hge->Random_Int(200, 500), hge->Random_Int(200, S_HEIGHT-100), 96, 96));


	static float time = 0;
	time += dt;
	levelTime += dt;
	if (currentLevel % 3 == 0 && spawned == 0 && currentLevel > 0)
	{
		Enemy * temp = new Fan("girl.png", S_WIDTH - 400, hge->Random_Int(300, S_HEIGHT-100), 48, 48, 8, 8, 50 + 10 * currentLevel, 5, true);
		while ( temp->Collide() )
		{
			temp->SetPosition(hge->Random_Int(S_WIDTH - 200, S_WIDTH + 600), hge->Random_Int(300, S_HEIGHT-100));
		}
		enemies.push_back(temp);
		entities.push_back(temp);
		spawned++;
	}
	else if (time > 0.1 && enemies.size() < 100 && spawned < 100)
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			Enemy * temp = new Fan("girl.png", hge->Random_Int(S_WIDTH-50, S_WIDTH+500), hge->Random_Int(250, S_HEIGHT-100), 48, 48, 1, 1, 1, currentLevel/2 + 1);
			while (temp->Collide())
			{
				float tempx = temp->GetX();
				temp->SetPosition(tempx + 50, hge->Random_Int(200, S_HEIGHT-100));
			}
			enemies.push_back(temp);
			entities.push_back(temp);
		}
		time = 0;
		spawned++;
	}
	if (levelTime >= 30 && currentLevel < 7)
	{
		levelTime = 0;
		time = 0;
		spawned = 0;
		currentLevel++;
		for (unsigned int i = 0; i < 30; ++i)
		{
			Enemy * temp = new Fan("girl.png", hge->Random_Int(S_WIDTH-50, S_WIDTH+500), hge->Random_Int(250, S_HEIGHT-100), 48, 48, 1, 1, 1, currentLevel/2 + 1);
			while (temp->Collide())
			{
				float tempx = temp->GetX();
				temp->SetPosition(tempx + 50, rand() % (S_HEIGHT-100) + 200);
			}
			enemies.push_back(temp);
			entities.push_back(temp);
		}
		gust->SetPosition(S_WIDTH+500, S_HEIGHT/2);

	}
	if (currentLevel == 7)
	{
		hge->System_SetState(HGE_FRAMEFUNC, lastFrame);
		hge->System_SetState(HGE_RENDERFUNC, winRender);
	}

	PLUGGED_IN = 0;
	for (unsigned int i = 0; i < NUMBER_PLAYERS; ++i )
	{
		DWORD dwResult;   
		XINPUT_STATE state;  
		ZeroMemory( &state, sizeof(XINPUT_STATE) );
		dwResult = XInputGetState( i, &state );
		if (dwResult == ERROR_SUCCESS)
			PLUGGED_IN++;
		else
			break;

		//if (state.Gamepad.sThumbLX > 10276 || state.Gamepad.sThumbLX < -10276 || state.Gamepad.sThumbLY > 10000 || state.Gamepad.sThumbLY < -10000)
		
		players[i]->Move(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, dt);
		if (state.Gamepad.bRightTrigger > 100)
			players[i]->AttackC();
		//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		//{
		//	sheep[i]->HoldKeyA();
		//}

		XINPUT_KEYSTROKE keystroke;
		ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
		for (dwResult = XInputGetKeystroke(i, XINPUT_FLAG_GAMEPAD, &keystroke); dwResult == ERROR_SUCCESS; dwResult = XInputGetKeystroke(i, XINPUT_FLAG_GAMEPAD, &keystroke))
		{
			if (keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN)
			{
				if (keystroke.VirtualKey == VK_PAD_A)
					players[i]->AttackA();
				if (keystroke.VirtualKey == VK_PAD_B)
					players[i]->AttackB();
				if (keystroke.VirtualKey == VK_PAD_START)
				{
					hge->System_SetState(HGE_FRAMEFUNC, PauseFrame);
					hge->System_SetState(HGE_RENDERFUNC, PauseRender);
					hge->Channel_PauseAll();
				}
				//if (keystroke.VirtualKey == VK_PAD_X)
				//	sheep[i]->PressKeyC();
			}
			ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
		}
	}

	if (PLUGGED_IN == 0)
	{
		int xm = 0, ym = 0;
		if (hge->Input_GetKeyState(HGEK_LEFT))
			xm = -32767;
		else if (hge->Input_GetKeyState(HGEK_RIGHT))
			xm = 32767;
		if (hge->Input_GetKeyState(HGEK_UP))
			ym = 32767;
		else if (hge->Input_GetKeyState(HGEK_DOWN))
			ym = -32767;
		players[0]->Move(xm, ym, dt);

		if (hge->Input_GetKeyState(HGEK_Z))
		{
			players[0]->AttackA();
		}

		if (hge->Input_GetKeyState(HGEK_X))
		{
			players[0]->AttackB();
		}

		if (hge->Input_GetKeyState(HGEK_C))
		{
			players[0]->AttackC();
		}
	}



		if (hge->Input_KeyDown(HGEK_D))
		{
			DEBUG = !DEBUG;
			hge->System_SetState(HGE_HIDEMOUSE, !DEBUG);
		}

	if (DEBUG)
	{
		//std::cout << "Boxes size: " << tempBoundingBoxes.size() << '\n';
		for (unsigned int i = 0; i < tempBoundingBoxes.size(); ++i)
		{
			if (tempBoundingBoxes[i].Update(dt))
			{
				tempBoundingBoxes.erase(tempBoundingBoxes.begin() + i);
				--i;
			}
		}

	}




	if (hge->Input_KeyDown(HGEK_ESCAPE))
	{
		hge->Channel_PauseAll();
		hge->System_SetState(HGE_FRAMEFUNC, PauseFrame);
		hge->System_SetState(HGE_RENDERFUNC, PauseRender);
		return false;
	}

	return false;
}


bool RenderFunc()
{
	hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		//for (unsigned int i = 0; i < graphics.size(); ++i)
		//	graphics[i]->Render();
		background->Render();

		int size = tempGraphics.size();
		for (unsigned int i = 0; i < size; ++i)
			tempGraphics[i]->Render();

		size = entities.size();
		for (unsigned int i = size - 1; i > 0; --i)
			entities[i]->Render();

		for (unsigned int i = 0; i < bullets.size(); ++i)
			bullets[i]->Render();

		for (unsigned int i = 0; i < powerups.size(); ++i)
			powerups[i]->Render();


		//fnt->printf(20, 20, HGETEXT_LEFT, "%d FPS", hge->Timer_GetFPS());

		if (PLUGGED_IN < NUMBER_PLAYERS)
			fnt->printf(S_WIDTH/2, 100, HGETEXT_CENTER, "Please enable %d controllers.", NUMBER_PLAYERS-PLUGGED_IN); 

		for (unsigned int i = 0; i < NUMBER_PLAYERS; ++i)
		{
			fnt->printf(10, S_HEIGHT/2 + i * 35, HGETEXT_LEFT, "Score %d", players[i]->GetScore());
		}

		if (currentLevel < 6)
		{
			fnt->printf(S_WIDTH/2, 20, HGETEXT_CENTER, "%.2f seconds until storm worsens.", (30-levelTime));
			fnt->printf(S_WIDTH/2, 50, HGETEXT_CENTER, "Storm Category %d", currentLevel);
		}
		else
			fnt->printf(S_WIDTH/2, 50, HGETEXT_CENTER, "Eye of the storm!");


		if (DEBUG)
		{

			fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
			for (unsigned int i = 0; i < tempBoundingBoxes.size(); ++i)
				tempBoundingBoxes[i].Render();
		}

		//hge->Gfx_RenderLine(0,500,500,501);

		gust->Render();

		static StaticGraphic redfade ("nopoops.png", 0, 0, S_WIDTH, S_HEIGHT, 0);
		RED_FADE_ALPHA-=2;
		if (RED_FADE_ALPHA < 0)
			RED_FADE_ALPHA = 0;
		redfade.GetSprite().SetColor(0x00FF0000 | (RED_FADE_ALPHA << 24));
		redfade.Render();

	hge->Gfx_EndScene();

	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//int main (int argc, char * argv[])
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, LOGFILE.c_str());
	hge->System_SetState(HGE_FRAMEFUNC, TitleFrame);
	hge->System_SetState(HGE_RENDERFUNC, TitleRender);
//	hge->System_SetState(HGE_EXITFUNC, ExitFunc);
	hge->System_SetState(HGE_TITLE, NAME.c_str());
	hge->System_SetState(HGE_FPS, 100);
	hge->System_SetState(HGE_WINDOWED, S_WINDOWED);
	hge->System_SetState(HGE_SCREENWIDTH, S_WIDTH);
	hge->System_SetState(HGE_SCREENHEIGHT, S_HEIGHT);
	hge->System_SetState(HGE_SCREENBPP, S_BPP);
	hge->System_SetState(HGE_ZBUFFER, true);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	if (DEBUG)
		hge->System_SetState(HGE_HIDEMOUSE, !DEBUG);


	if(hge->System_Initiate()) 
	{
		hge->Resource_AttachPack("resource.pak");

		DWORD dwResult;    
		for (DWORD i=0; i< MAX_CONTROLLERS; i++ )
		{
			XINPUT_STATE state;
			ZeroMemory( &state, sizeof(XINPUT_STATE) );

			// Simply get the state of the controller from XInput.
			dwResult = XInputGetState( i, &state );

			if( dwResult == ERROR_SUCCESS )
			{ 
				std::cout << "Controller " << i << " connected\n";
			}
			else
			{
				std::cout << "Controller " << i << " not conntected\n";	// Controller is not connected 
			}
		}

		// Load a font
		fnt=new hgeFont("font1.fnt");
		fnt->SetZ(0.0f);

		particles = new hgeSprite(resource.GetTexture("particles.png"), 32, 0, 32, 32);

		titleScreen = new StaticGraphic(TITLE_GRAPHIC, 0, 0, S_WIDTH, S_HEIGHT, 1.0f, false);
		background = new StaticGraphic("Map copy.png", 0, 0, S_WIDTH, S_HEIGHT, 1.0f, false);
		loseScreen = new StaticGraphic("lose.png", 0, 0, S_WIDTH, S_HEIGHT, 0.0f, false);
		winScreen = new StaticGraphic("win.png", 0, 0, S_WIDTH, S_HEIGHT, 0.0f, false);
		riotScreen = new StaticGraphic("RIOT.png", 0, 0, S_WIDTH, S_HEIGHT, 0, false);
		options = new StaticGraphic("options.png", 0, 0, S_WIDTH, S_HEIGHT, 0, false);
		obscenityScreen = new StaticGraphic("OBSCENITY.png", 0, 0, S_WIDTH, S_HEIGHT, 0.0f, false);
		gust = new StaticGraphic("gust.png", S_WIDTH + 500, S_HEIGHT/2, 826, 688, 0, true);
		bar = hge->Texture_Load("bar.png");
		punch = hge->Effect_Load("punch.wav");
		music = hge->Stream_Load("Knife Fight.mp3");

		entities.push_back(new Box("poops.png", 0, 350, 150, S_HEIGHT, 0x00FFFFFF));
		entities.push_back(new Box("poops.png", 0, 0, S_WIDTH, 200, 0x00FFFFFF));
		entities.push_back(new Box("poops.png", 0, S_HEIGHT-70, S_WIDTH, 70, 0x00FFFFFF));
		entities.push_back(new Box("poops.png", 150, 360, 178, 156, 0x00FFFFFF));
		//entities.push_back(new Box("poops.png", S_WIDTH, 0, 20, S_HEIGHT, 0x00FFFFFF));

		//entities.push_back(new StaticGraphic("plant.png", 200, 40, 107, 163, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*2, 40, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*4, 40, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*6, 40, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*8, 40, 130, 184, 0));

		entities.push_back(new StaticGraphic("plant.png", 200, S_HEIGHT-163, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*2, S_HEIGHT-163, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*4, S_HEIGHT-163, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*6, S_HEIGHT-163, 130, 184, 0));
		entities.push_back(new StaticGraphic("plant.png", 200+107*8, S_HEIGHT-163, 130, 184, 0));

		prince = new Prince("prince.png", 70, 160, 96, 96);
		entities.push_back(prince);

		hge->Random_Seed();
		srand(time(NULL));

		hge->System_Start();

	for (unsigned int i = 0; i < entities.size(); ++i)
		delete (entities[i]);
	delete fnt;
	delete titleScreen;
	delete background;
	delete loseScreen;
	delete riotScreen;
	delete obscenityScreen;
	delete particles;
	delete options;
	resource.Purge();
	hge->Texture_Free(bar);
	hge->Effect_Free(punch);
	hge->Stream_Free(music);

	}

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();

	//exit(0);
	return 0;
}
