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
}

void TitleScreen::Draw()
{
	m_helper->SDL_DrawImage(m_background, 0, 0);
	m_helper->SDL_DrawImage(m_logo, 250, 70);
	m_helper->SDL_DrawImage(m_playButton, 460, 450);
	this->m_helper->SDL_DrawText(600, 680, VERSION_TEXT_SIZE, BLACK, "Manurocker95 (C) 2018");
}

void TitleScreen::Update()
{
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

	if (kDown & KEY_PLUS)
	{
		SceneManager::Instance()->ExitGame();
	}
}

// * We go to the next scene = GameScreen
void TitleScreen::NextScene()
{
	SceneManager::Instance()->SetActualScene(SceneManager::GAME);
	delete(this);
}

