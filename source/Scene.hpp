#pragma once
#ifndef _SCENE_HPP_
#define _SCENE_HPP_
		
#include "SDL_Helper.hpp"
#include <switch.h>
#include <string>

// Base Class.
class Scene
{

protected:
	SDL_Helper * m_helper;
	bool m_changeScene;
	touchPosition touch;
	bool m_debugMode;

	// FPS
	float m_fps;
	int m_frames;
	u32 prevTime;
	std::string m_fpsStr;

public:
	Scene() {};																	// Constructor
	~Scene() { };																// Destructor
	virtual void Start(SDL_Helper * m_helper) {};													// initialize
	virtual void Draw() { };		// Draw
	virtual void CheckInputs(u64 kDown, u64 kHeld) {};												// CheckInput
	virtual void Update() {};													// Update
	virtual void NextScene() {};													// Update
};

#endif