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

private:
	SDL_Texture * m_background;
	SDL_Texture * m_deadBackground;
	SDL_Texture * m_pauseTexture;
	SDL_Texture * m_bananaTexture;
	SDL_Texture * m_fireTexture;

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
	int m_deadTimer;
	int m_timeToSpawn;

	int m_rayCounter;
	int m_deltaRay;
	bool m_debugMode;
	bool m_pause;
	bool m_ended;
	std::string m_scoreStr;
public:

	GameScreen();								// Constructor
	~GameScreen();								// Destructor
	void Start(SDL_Helper * helper) override;	// initialize
	void Draw() override;						// Draw
	void CheckInputs(u64 kDown, u64 kHeld) override;		// CheckInput
	void Update() override;						// Update
	void NextScene() override;
	void UpdateCollisions();
	void AddScore(int _value);
	void EndGame();
	void BackToMenu();
};

#endif