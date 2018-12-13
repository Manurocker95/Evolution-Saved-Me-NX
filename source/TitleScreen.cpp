#include "TitleScreen.hpp"
#include "SceneManager.hpp"
#include "Filepaths.h"
#include "Settings.h"
#include "Colors.h"

TitleScreen::TitleScreen() : Scene()
{

}

TitleScreen::~TitleScreen()
{
	//m_helper->
}

void TitleScreen::Start(SDL_Helper * helper)
{
	m_changeScene = false;
	m_helper = helper;
	m_helper->SDL_LoadImage(&m_background, IMG_BG_TITLE);
	m_helper->SDL_LoadImage(&m_logo, IMG_LOGO);
	m_helper->SDL_LoadImage(&m_playButton, IMG_BT_PLAY);
	m_debugMode = DEBUG_MODE;
	prevTime = SDL_GetTicks(); // Get ticks
	m_fps = 0;
	m_frames = 0;
	m_fpsStr = "FPS: 0";
}

void TitleScreen::Draw()
{
	m_helper->SDL_DrawImage(m_background, 0, 0);
	m_helper->SDL_DrawImage(m_logo, 250, 70);
	m_helper->SDL_DrawImage(m_playButton, 460, 450);
	this->m_helper->SDL_DrawText(600, 670, 4, BLACK, "Manurocker95 (C) 2018");

	if (m_debugMode)
		this->m_helper->SDL_DrawText(10, 5, 4, BLACK, m_fpsStr.c_str());
}

void TitleScreen::Update()
{
	if (m_debugMode)
	{
		++m_frames; //increase frames counter
		u32 currTime = SDL_GetTicks(); //current time since last tick
		float elapsed = (currTime - prevTime); //elapsed time

		if (elapsed > 100) { //if elapsed time id greater than 100

			m_fps = round(m_frames / (elapsed / 1000.0f)); //round fps
			m_frames = 0; //reset frames
			prevTime = currTime; //set previous time to current time
		}

		m_fpsStr = "FPS: " + (int)m_fps;
	}

	if (m_changeScene)
		NextScene();
}

void TitleScreen::CheckInputs(u64 kDown, u64 kHeld)
{
	// If we touched  play
	if (kDown & KEY_TOUCH)
	{
		u32 i;
		hidTouchRead(&touch, i);
		
		if (touch.px >= 460 && touch.px < 820 && touch.py >= 450 && touch.py <= 576)//360x126
		{
			// We touched play ;)
			m_changeScene = true;
			return;
		}
	}

	if (kDown & KEY_A)
		m_changeScene = true;

	if (kDown & KEY_R && kHeld & KEY_L)
		m_debugMode = !m_debugMode;

	if (kDown & KEY_PLUS)
	{
		SceneManager::Instance()->ExitGame();
	}
}

// * We go to the next scene = GameScreen
void TitleScreen::NextScene()
{
	/*
	m_helper->SDL_DestroyTexture(m_background);
	m_helper->SDL_DestroyTexture(m_logo);
	m_helper->SDL_DestroyTexture(m_playButton);
	*/

	SceneManager::Instance()->SetActualScene(SceneManager::GAME);
	delete(this);
}

