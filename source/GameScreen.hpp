#pragma once
#ifndef _GAME_SCREEN_HPP_
#define _GAME_SCREEN_HPP_
#include <string>
#include "Scene.hpp"
#include "Object.hpp"
#include "Monkey.hpp"
#include "Ray.hpp"

#include "Settings.h"

class GameScreen : public Scene
{

public:
	enum GAME_STATES 
	{ 
		PLAYING, 
		PAUSE, 
		DYING, 
		DEAD, 
		OUT, 
		NONE 
	};

private:

	SDL_Texture * m_background;
	Monkey * m_player;
	Object * m_bananas[MAX_BANANAS];
	Object * m_fire;
	Ray * m_rays[MAX_RAYS]; //8x4

	int m_score;
	int m_maxScore;

	int m_activeBananas;
	int m_bananaTimer;
	int m_fireTimer;
	int m_invincibleTimer;
	int m_dyingTimer;
	int m_timeToSpawn;

	int m_rayCounter;
	int m_deltaRay;

	std::string m_fps;
	u32 held;
	touchPosition touch;
	
public:

	GameScreen();								// Constructor
	~GameScreen();								// Destructor
	void Start(SDL_Helper * helper) override;	// initialize
	void Draw() override;						// Draw
	void CheckInputs(u64 kDown) override;		// CheckInput
	void Update() override;						// Update
	void NextScene() override;

};

#endif