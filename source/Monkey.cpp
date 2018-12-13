#include "Monkey.hpp"
#include "SceneManager.hpp"
#include "Filepaths.h"
#include "Settings.h"

Monkey::Monkey()
{
	SDL_Helper * _helper = SceneManager::Instance()->GetHelper();
	_helper->SDL_LoadImage(&m_normalSprite, IMG_MONKEY_SPRITE);
	_helper->SDL_LoadImage(&m_deadSprite, IMG_MONKEY_SPRITE_DEAD);
	_helper->SDL_LoadImage(&m_dyingSprite, IMG_MONKEY_SPRITE_DYING);
	_helper->SDL_LoadImage(&m_powerUpSprite, IMG_MONKEYFIRE_SPRITE);
	m_sprite = m_normalSprite;

	this->m_x = 200;
	this->m_y = 120;
	this->m_multipleFrames = false;
	this->m_numFrames = 1;
	this->m_sizePerFrameX = MONKEY_SIZE_PER_FRAME;
	this->m_sizePerFrameY = MONKEY_SIZE_PER_FRAME;
	this->m_currentFrame = 0;
	this->m_secondaryCounter = 0;
	this->m_invincible = false;
	this->m_state = ALIVE;
}

Monkey::Monkey(int _x, int _y, SDL_Helper * _helper, bool _multipleFrames, int _numFrames, int _sizePerFrameX, int _sizePerFrameY)
{

	_helper->SDL_LoadImage(&this->m_normalSprite, IMG_MONKEY_SPRITE);
	_helper->SDL_LoadImage(&this->m_deadSprite, IMG_MONKEY_SPRITE_DEAD);
	_helper->SDL_LoadImage(&this->m_dyingSprite, IMG_MONKEY_SPRITE_DYING);
	_helper->SDL_LoadImage(&this->m_powerUpSprite, IMG_MONKEYFIRE_SPRITE);
	m_sprite = m_normalSprite;

	this->m_x = _x;
	this->m_y = _y;
	this->m_multipleFrames = _multipleFrames;
	this->m_numFrames = _numFrames;
	this->m_sizePerFrameY = _sizePerFrameY;
	this->m_sizePerFrameX = _sizePerFrameX;
	this->m_currentFrame = 0;
	this->m_secondaryCounter = 0;
	this->m_invincible = false;
	this->m_state = ALIVE;
}

void Monkey::ChangeState(MONKEY_STATES _state)
{
	this->m_state = _state;

	switch (m_state)
	{
	case MONKEY_STATES::ALIVE:
		m_sprite = m_normalSprite;
		break;
	case MONKEY_STATES::POWERED:
		m_sprite = m_powerUpSprite;
		break;
	case MONKEY_STATES::DYING:
		m_sprite = m_dyingSprite;
		break;
	case MONKEY_STATES::DEAD:
		m_sprite = m_deadSprite;
		break;
	}
}

void Monkey::SetDeadSprite(int _numFrames, int _sizePerFrameX, int _sizePerFrameY)
{
	ChangeState(MONKEY_STATES::DEAD);
	m_currentFrame = 0;
	m_numFrames = _numFrames;
	m_sizePerFrameX = _sizePerFrameX;
	m_sizePerFrameY = _sizePerFrameY;
}


void Monkey::End(SDL_Helper * _helper)
{
	Sprite::End(_helper);
	_helper->SDL_DestroyTexture(this->m_deadSprite);
	_helper->SDL_DestroyTexture(this->m_normalSprite);
	_helper->SDL_DestroyTexture(this->m_dyingSprite);
	_helper->SDL_DestroyTexture(this->m_powerUpSprite);
	delete(this);
}

Monkey::MONKEY_STATES Monkey::GetState()
{
	return this->m_state;
}

void Monkey::SetState(Monkey::MONKEY_STATES _value)
{
	this->m_state = _value;
}

void Monkey::SetInvincible(bool _value)
{
	this->m_invincible = _value;
}

bool Monkey::GetInvincible()
{
	return this->m_invincible;
}

bool Monkey::IsAlive()
{
	return this->m_state == Monkey::ALIVE;
}