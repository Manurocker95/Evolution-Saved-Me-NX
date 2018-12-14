#include "TitleScreen.hpp"
#include "SceneManager.hpp"
#include "Filepaths.h"
#include "Settings.h"
#include "Colors.h"

TitleScreen::TitleScreen() : Scene()
{
	this->m_changeScene = false;
}

TitleScreen::~TitleScreen()
{
	m_helper->SDL_DestroyTexture(m_background);
	m_helper->SDL_DestroyTexture(m_logo);
	m_helper->SDL_DestroyTexture(m_playButton);
	m_helper->SDL_DestroyFont(m_font);
}

void TitleScreen::Start(SDL_Helper * helper)
{

	this->m_helper = helper;
	this->m_helper->SDL_LoadImage(&this->m_background, IMG_BG_TITLE);
	this->m_helper->SDL_LoadImage(&this->m_logo, IMG_LOGO);
	this->m_helper->SDL_LoadImage(&this->m_playButton, IMG_BT_PLAY);
	this->m_helper->SDL_LoadCustomFont(&this->m_font, FONT_NORMAL, 15, BLACK);
}

void TitleScreen::Draw()
{
	this->m_helper->SDL_DrawImage(this->m_background, 0, 0);
	this->m_helper->SDL_DrawImage(this->m_logo, 250, 70);
	this->m_helper->SDL_DrawImage(this->m_playButton, 460, 450);
	this->m_helper->SDL_DrawTextWithFont(this->m_font, 525, 670, BLACK, "Manurocker95 (C) 2018");
}

void TitleScreen::Update()
{
	if (this->m_changeScene)
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
			this->m_changeScene = true;
			return;
		}
	}

	if (kDown & KEY_A)
		this->m_changeScene = true;

	if (kDown & KEY_PLUS)
	{
		SceneManager::Instance()->ExitGame();
	}
}

// * We go to the next scene = GameScreen
void TitleScreen::NextScene()
{
	SceneManager::Instance()->LoadScene(SceneManager::GAME);
}

