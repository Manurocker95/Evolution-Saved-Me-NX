#pragma once
#ifndef _MONKEY_HPP_
#define _MONKEY_HPP_

#include "SDL_Helper.hpp"
#include "Sprite.hpp"

class Monkey : public Sprite
{
public:
	// States of the monkey. In each state, the monkey has a different animation.
	enum MONKEY_STATES 
	{ 
		ALIVE, 
		POWERED, 
		DYING, 
		DEAD 
	};


private:
	SDL_Texture * m_normalSprite;
	SDL_Texture * m_deadSprite;
	SDL_Texture * m_dyingSprite;
	SDL_Texture * m_powerUpSprite;

	MONKEY_STATES m_state;

	bool m_invincible;

public:
	Monkey();	// Basic Constructor
	Monkey(int _x, int _y, SDL_Helper * _helper, bool _multipleFrames, int _numFrames, int _sizePerFrameX, int _sizePerFrameY);
	~Monkey();	// Destructor

public:

	void End(SDL_Helper * _helper) override;

	MONKEY_STATES GetState();
	void SetState(MONKEY_STATES value);

	void SetInvincible(bool value);
	bool GetInvincible();

	void SetDeadSprite(int _numFrames, int _sizePerFrameX, int _sizePerFrameY);
	void ChangeState(MONKEY_STATES state);

	bool IsAlive();
	bool IsDead();
	bool IsDying();
	bool IsPowered();
};

#endif