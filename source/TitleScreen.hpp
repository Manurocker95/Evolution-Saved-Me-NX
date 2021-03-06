#pragma once
#ifndef _TITLE_SCREEN_HPP_
#define _TITLE_SCREEN_HPP_

#include "Scene.hpp"

class TitleScreen : public Scene
{
private:
	SDL_Texture * m_background;
	SDL_Texture * m_logo;
	SDL_Texture * m_playButton;
	FC_Font * m_font;
	Mix_Music * m_music;
	Mix_Chunk * m_buttonTapSFX;

public:

	TitleScreen();				// Constructor
	~TitleScreen();				// Destructor
	void Start(SDL_Helper * helper) override;				// initialize
	void Draw() override;				// Draw
	void CheckInputs(u64 kDown, u64 kHeld) override;			// CheckInput
	void Update() override;				// Update
	void NextScene() override;

};

#endif