#include "GameScreen.hpp"
#include "SceneManager.hpp"
#include "Colors.h"
#include "Filepaths.h"
#include "Settings.h"

GameScreen::GameScreen() : Scene()
{

}

GameScreen::~GameScreen()
{
	m_helper->SDL_DestroyTexture(m_bananaTexture);
	m_helper->SDL_DestroyTexture(m_fireTexture);
	m_player->End(m_helper);

	for (auto & ray : m_rays)
		delete(ray);

	for (auto & banana : m_bananas)
		delete(banana);
}

void GameScreen::Start(SDL_Helper * helper)
{
	m_changeScene = false;
	m_helper = helper;
	m_helper->SDL_LoadImage(&m_background, IMG_BG_GAME);
	m_player = new Monkey(200, 120, helper, true, 4, MONKEY_SIZE_PER_FRAME, MONKEY_SIZE_PER_FRAME);
	
	m_helper->SDL_LoadImage(&m_pauseTexture, IMG_BG_PAUSE);

	m_helper->SDL_LoadImage(&m_bananaTexture, IMG_BANANA_SPRITE);

	for (int i = 0; i < MAX_BANANAS; i++)
	{
		m_bananas[i] = new Object(Object::BANANA, m_bananaTexture, -CELL_SIZE, -CELL_SIZE, 4, BANANA_SIZE_PER_FRAME, BANANA_SIZE_PER_FRAME, true);
	}
	
	m_helper->SDL_LoadImage(&m_bananaTexture, IMG_BANANA_SPRITE);
	m_fire = new Object(Object::FIRE, m_fireTexture, -CELL_SIZE, -CELL_SIZE, 4, FIRE_SIZE_PER_FRAME, FIRE_SIZE_PER_FRAME, true);

	m_rays[0]->InitialPos();
	m_rays[1]->InitialPos();
	m_rays[2]->InitialPos();

	m_score = 0;

	m_timeToSpawn = TIME_TO_SPAWN_RAYS;
	m_bananaTimer = 0;
	m_fireTimer = 0;
	m_activeBananas = 0;
	m_rayCounter = 0;
	m_deltaRay = 0;
	m_invincibleTimer = 0;

	m_pause = false;
	m_debugMode = DEBUG_MODE;
}

void GameScreen::Draw()
{
	m_helper->SDL_DrawImage(m_background, 0, 0);

	for (auto & banana : m_bananas)
	{
		banana->Draw(m_helper);
	}

	m_fire->Draw(m_helper);
	m_player->Draw(m_helper);

	for (int i = 0; i < m_rayCounter; i++)
		m_rays[i]->Draw(m_helper);

	if (m_pause)
	{
		m_helper->SDL_DrawImage(m_pauseTexture, 0, 0);
	}
}

void GameScreen::Update()
{
	if (!m_pause)
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
				m_player->SetFrameSize(MONKEY_SIZE_PER_FRAME, true);
			}
		}
	}

	// RAYOS:

	m_deltaRay++;

	if (m_deltaRay >= m_timeToSpawn)
	{
		int numraystospawn = rand() % 3;
		if (numraystospawn == 0)
		{
			m_rays[0]->LoadData();
			m_rayCounter = 1;
		}
		else if (numraystospawn == 1)
		{
			m_rays[0]->LoadData();
			m_rays[1]->LoadData();
			if (m_rays[1]->GetX() == m_rays[0]->GetX())
			{
				m_rays[1]->NewPos();
			}
			m_rayCounter = 2;
		}
		else if (numraystospawn == 2)
		{
			m_rays[0]->LoadData();
			m_rays[1]->LoadData();
			m_rays[2]->LoadData();

			if (m_rays[1]->GetX() == m_rays[0]->GetX() || m_rays[2]->GetX() == m_rays[1]->GetX())
			{
				m_rays[1]->NewPos();
				m_rays[2]->NewPos();
			}

			if (m_rays[2]->GetX() == m_rays[0]->GetX())
			{
				m_rays[0]->NewPos();
				m_rays[0]->NewPos();
			}

			m_rayCounter = 3;
		}

		m_deltaRay = 0;
	}

	if (m_rays[0]->CheckCollision(m_player))
	{
		m_player->ChangeState(Monkey::MONKEY_STATES::DYING);
		m_player->SetFrameSize(MONKEY_SIZE_PER_FRAME, true);
		m_player->SetNumFrames(8);
		m_rayCounter = 0;
		m_deltaRay = 0;
	}
	else if (m_rayCounter > 1 && m_rays[1]->CheckCollision(m_player))
	{
		m_player->ChangeState(Monkey::MONKEY_STATES::DYING);
		m_player->SetFrameSize(MONKEY_SIZE_PER_FRAME, true);
		m_player->SetNumFrames(8);
		m_rayCounter = 0;
		m_deltaRay = 0;
	}
	else if (m_rayCounter > 2 && m_rays[2]->CheckCollision(m_player))
	{
		m_player->ChangeState(Monkey::MONKEY_STATES::DYING);
		m_player->SetFrameSize(MONKEY_SIZE_PER_FRAME, true);
		m_player->SetNumFrames(8);
		m_rayCounter = 0;
		m_deltaRay = 0;
	}
}

void GameScreen::CheckInputs(u64 kDown, u64 kHeld)
{

	if (kDown & KEY_PLUS)
	{
		m_changeScene = true;
		return;
	}
		
	if (kDown & KEY_R && kHeld & KEY_L)
		m_debugMode != m_debugMode;

	if (m_pause)
	{
		if (kDown & KEY_TOUCH)
		{
			m_pause = false;
			return;
		}
	}
	else
	{
		if (kHeld & KEY_LEFT)
		{
			m_player->MoveX(-CELL_SIZE);
		}

		if (kHeld & KEY_RIGHT)
		{
			m_player->MoveX(CELL_SIZE);
		}

		if (kHeld & KEY_UP)
		{
			m_player->MoveY(-CELL_SIZE);
		}

		if (kHeld & KEY_DOWN)
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
	SceneManager::Instance()->SetActualScene(SceneManager::TITLE);
	delete(this);
}
