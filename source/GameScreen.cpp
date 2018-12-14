#include "GameScreen.hpp"
#include "SceneManager.hpp"
#include "Colors.h"
#include "Filepaths.h"
#include "Settings.h"
#include <cmath>

GameScreen::GameScreen() : Scene()
{
	this->m_score = 0;
	this->m_bananaTimer = 0;
	this->m_fireTimer = 0;
	this->m_deadTimer = 0;
	this->m_dyingTimer = 0;
	this->m_activeBananas = 0;
	this->m_rayCounter = 0;
	this->m_deltaRay = 0;
	this->m_invincibleTimer = 0;
	this->m_ended = false;
	this->m_pause = false;
	this->m_debugMode = false;
	this->m_changeScene = false;
	this->m_scoreStr = "Score: 0";
	this->m_timeToSpawn = rand() % ((MAX_TIME_TO_SPAWN_RAYS - MIN_TIME_TO_SPAWN_RAYS) + 1) + MIN_TIME_TO_SPAWN_RAYS;
}

GameScreen::~GameScreen()
{
	this->m_helper->SDL_DestroyTexture(this->m_background);
	this->m_helper->SDL_DestroyTexture(this->m_deadBackground);
	this->m_helper->SDL_DestroyTexture(this->m_pauseTexture);
	this->m_helper->SDL_DestroyTexture(this->m_bananaTexture);
	this->m_helper->SDL_DestroyTexture(this->m_fireTexture);

	//this->m_helper->SDL_DestroyFont(this->m_font);

	this->m_player->End(this->m_helper);
	delete(this->m_player);

	for (auto & ray : m_rays)
	{
		ray->End(this->m_helper);
		delete(ray);
	}
		
	for (auto & banana : m_bananas)
	{
		banana->End(this->m_helper);
		delete(banana);
	}
	
	this->m_fire->End(this->m_helper);
	delete(m_fire);
}

void GameScreen::Start(SDL_Helper * helper)
{

	this->m_helper = helper;
	this->m_helper->SDL_LoadImage(&this->m_background, IMG_BG_GAME);
	this->m_helper->SDL_LoadImage(&this->m_deadBackground, IMG_BG_GAMEOVER);
	this->m_player = new Monkey(CELL_SIZE * 2, CELL_SIZE * 2, helper, true, 4, MONKEY_SIZE_PER_FRAME, MONKEY_SIZE_PER_FRAME);
	
	this->m_helper->SDL_LoadImage(&this->m_pauseTexture, IMG_BG_PAUSE);

	this->m_helper->SDL_LoadImage(&this->m_bananaTexture, IMG_BANANA_SPRITE);

	for (int i = 0; i < MAX_BANANAS; i++)
	{
		this->m_bananas[i] = new Object(Object::BANANA, this->m_bananaTexture, -CELL_SIZE, -CELL_SIZE, 4, BANANA_SIZE_PER_FRAME, BANANA_SIZE_PER_FRAME, true);
	}
	
	this->m_helper->SDL_LoadImage(&this->m_fireTexture, IMG_FIRE_SPRITE);
	this->m_fire = new Object(Object::FIRE, this->m_fireTexture, -CELL_SIZE, -CELL_SIZE, 4, FIRE_SIZE_PER_FRAME, FIRE_SIZE_PER_FRAME, true);

	for (int i = 0; i < MAX_RAYS; i++)
	{
		m_rays[i] = new Ray();
		m_rays[i]->InitialPos();
	}
}

void GameScreen::EndGame()
{
	this->m_changeScene = true;
}

void GameScreen::BackToMenu()
{
	this->m_changeScene = true;
}


void GameScreen::Draw()
{
	
	if (this->m_ended)
	{
		this->m_helper->SDL_DrawImage(this->m_deadBackground, 0, 0);
		return;
	}
		

	this->m_helper->SDL_DrawImage(this->m_background, 0, 0);

	for (auto & banana : m_bananas)
	{
		banana->Draw(this->m_helper);
	}

	this->m_fire->Draw(this->m_helper);
	this->m_player->Draw(this->m_helper);

	for (int i = 0; i < this->m_rayCounter; i++)
		this->m_rays[i]->Draw(this->m_helper);

	if (this->m_pause)
	{
		this->m_helper->SDL_DrawImage(this->m_pauseTexture, 0, 0);
	}

	this->m_helper->SDL_DrawText(600, 670, 4, BLACK, this->m_scoreStr.c_str());
}

void GameScreen::Update()
{
	
	if (!m_ended && !m_pause)
	{

		m_player->Update();

		for (auto & banana : m_bananas)
			banana->Update();

		m_fire->Update();

		for (int i = 0; i < m_rayCounter; i++)
			m_rays[i]->Update();
		
		UpdateCollisions();
	}
	
	if (m_changeScene)
		NextScene();
}

void GameScreen::AddScore(int _value)
{
	m_score += _value;
	m_scoreStr = "Score: " + std::to_string(this->m_score);
}

void GameScreen::UpdateCollisions()
{
	if (m_bananaTimer >= BANANATIMER)
	{
		m_bananaTimer = 0;

		if (m_activeBananas < MAX_BANANAS)
		{
			int x = rand() % (8) + 1; //
			int y = rand() % (4) + 1;

			m_activeBananas++;
			m_bananas[m_activeBananas - 1]->SetActive(true);
			m_bananas[m_activeBananas - 1]->SetX(x*CELL_SIZE);
			m_bananas[m_activeBananas - 1]->SetY(y*CELL_SIZE);
		}
		else
		{
			int bananaN = rand() % 3;

			int x = rand() % (8) + 1; //
			int y = rand() % (4) + 1;

			m_bananas[bananaN]->SetActive(true);
			m_bananas[bananaN]->SetX(x*CELL_SIZE);
			m_bananas[bananaN]->SetY(y*CELL_SIZE);

		}
	}
	else
	{
		m_bananaTimer++;
	}

	for (auto & banana : m_bananas)
	{
		if (banana->CheckCollision(m_player))
		{
			m_activeBananas--;
			banana->SetActive(false);
			AddScore(SCORE_TO_ADD);
			banana->MoveToCoord(-CELL_SIZE, -CELL_SIZE);
		}
	}

	if (m_player->GetInvincible())
	{
		if (m_invincibleTimer >= POWERUPTIME)
		{
			m_fireTimer = 0;
			m_invincibleTimer = 0;
			m_player->SetInvincible(false);
			m_player->ChangeState(Monkey::MONKEY_STATES::ALIVE);
			m_player->SetFrameSize(MONKEY_SIZE_PER_FRAME, true);
		}
		else
		{
			m_invincibleTimer++;
		}
	}
	else
	{
		if (m_player->IsDying())
		{
			if (m_dyingTimer >= DYINGTIME)
			{
				m_dyingTimer = 0;
				m_player->SetInvincible(false);
				m_player->ChangeState(Monkey::MONKEY_STATES::DEAD);
				m_player->SetFrameSize(MONKEY_SIZE_PER_FRAME, true);
				return;
			}
			else
			{
				m_dyingTimer++;
			}		
		}
		else if (m_player->IsDead())
		{
			if (m_deadTimer >= DEADTIME)
			{
				m_ended = true;
				return;
			}
			else
			{
				m_deadTimer++;
			}
		}
		
		
		if (m_fireTimer >= FIRETIMER)
		{
			m_fireTimer = 0;
			int x = CELL_SIZE;
			int y = CELL_SIZE;
			do
			{
				x = rand() % (8) + 1; //
				y = rand() % (4) + 1;

			} while ((x*CELL_SIZE == m_player->GetX() && y*CELL_SIZE == m_player->GetY()) || (x*CELL_SIZE == m_bananas[0]->GetX() && y*CELL_SIZE == m_player->GetY()) || (x*CELL_SIZE == m_bananas[1]->GetX() && y*CELL_SIZE == m_player->GetY()) || (x*CELL_SIZE == m_bananas[2]->GetX() && y*CELL_SIZE == m_player->GetY()));

			m_fire->SetActive(true);
			m_fire->SetX(x*CELL_SIZE);
			m_fire->SetY(y*CELL_SIZE);
		}
		else
		{
			m_fireTimer++;
		}

		if (m_fire->IsActive())
		{
			if (m_fire->CheckCollision(m_player))
			{
				m_fire->MoveToCoord(-CELL_SIZE, -CELL_SIZE);
				m_fireTimer = 0;
				m_invincibleTimer = 0;
				m_player->SetInvincible(true);
				m_player->ChangeState(Monkey::MONKEY_STATES::POWERED);
				m_player->SetFrameSize(120, true);
				m_player->SetFrameSize(120, false);
			}
		}
	}

	// RAYOS:

	m_deltaRay++;

	if (m_deltaRay >= m_timeToSpawn)
	{
		m_rayCounter = rand() % (MAX_RAYS-1);
		for (int i = 0; i < m_rayCounter; i++)
		{
			m_rays[i]->LoadData();
		}		
		m_deltaRay = 0;
		m_timeToSpawn = rand() % ((MAX_TIME_TO_SPAWN_RAYS - MIN_TIME_TO_SPAWN_RAYS) + 1) + MIN_TIME_TO_SPAWN_RAYS;
	}
	else if (m_player->IsAlive())
	{
		for (int i = 0; i < m_rayCounter; i++)
		{
			if (m_rays[i]->CheckCollision(m_player))
			{
				m_player->ChangeState(Monkey::MONKEY_STATES::DYING);
				m_player->SetFrameSize(MONKEY_SIZE_PER_FRAME, true);
				m_player->SetNumFrames(8);
				m_rayCounter = 0;
				m_deltaRay = 0;
			}
		}
	}
}

void GameScreen::CheckInputs(u64 kDown, u64 kHeld)
{
	if (m_ended)
	{
		if (kDown & KEY_TOUCH || kDown & KEY_MINUS || kDown & KEY_B || kDown & KEY_A || kDown & KEY_MINUS)
		{
			EndGame();
		}
		return;
	}
		

	if (kDown & KEY_PLUS)
	{
		m_ended = true;
	}
		
	if (kDown & KEY_R && kDown & KEY_L)
		m_debugMode = !m_debugMode;

	if (m_pause)
	{
		if (kDown & KEY_TOUCH || kDown & KEY_MINUS || kDown & KEY_B)
		{
			m_pause = false;
			return;
		}
	}
	else
	{
		if (kDown & KEY_LEFT)
		{
			m_player->MoveX(-CELL_SIZE);
		}

		if (kDown & KEY_RIGHT)
		{
			m_player->MoveX(CELL_SIZE);
		}

		if (kDown & KEY_UP)
		{
			m_player->MoveY(-CELL_SIZE);
		}

		if (kDown & KEY_DOWN)
		{
			m_player->MoveY(CELL_SIZE);
		}

		if (kDown & KEY_MINUS)
		{
			m_pause = true;
			return;
		}
	}
}

// * We go to the next scene = GameScreen
void GameScreen::NextScene()
{	
	SceneManager::Instance()->LoadScene(SceneManager::TITLE);
}
