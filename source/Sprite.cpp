#include "Sprite.hpp"
#include "Filepaths.h"
#include "Settings.h"

void Sprite::Draw(SDL_Helper * _helper)
{
	if (this->m_multipleFrames)
		_helper->SDL_DrawImageRect(this->m_sprite, m_x, m_y, m_currentFrame * m_sizePerFrame, 0, m_sizePerFrame, m_sizePerFrame);
	else
		_helper->SDL_DrawImage(this->m_sprite, m_x, m_y);
}

void Sprite::Update()
{
	Uint32 ticks = SDL_GetTicks();
	this->m_currentFrame = (ticks / 100) % this->m_numFrames;

	/*
	this->m_secondaryCounter++;

	if (this->m_secondaryCounter > FRAME_COUNTER_MONKEY)
	{
		this->m_currentFrame++;
		this->m_secondaryCounter = 0;
	}

	if (this->m_currentFrame >= this->m_numFrames)
	{
		this->m_currentFrame = 0;
	}
	*/
}

void Sprite::MoveToCoord(int _x, int _y)
{
	this->m_x = _x;
	this->m_y = _y;
}

void Sprite::MoveX(int _value)
{
	if ((_value > 0 && m_x + _value <= SWITCH_SCREEN_WIDTH - CELL_SIZE - CELL_SIZE) || (_value < 0 && m_x + _value >= 0 + CELL_SIZE))
		this->m_x += _value;
}

void Sprite::MoveY(int _value)
{
	if ((_value > 0 && m_y + _value <= SWITCH_SCREEN_HEIGHT - CELL_SIZE - CELL_SIZE) || (_value < 0 && m_y + _value >= 0 + CELL_SIZE))
		this->m_y += _value;
}

SDL_Texture * Sprite::GetSprite()
{
	return this->m_sprite;
}

void Sprite::SetSprite(SDL_Texture * _sprite)
{
	m_sprite = _sprite;
}


void Sprite::SetX(int _value)
{
	this->m_x = _value;
}

int Sprite::GetX()
{
	return this->m_x;
}

void Sprite::SetY(int _value)
{
	this->m_y = _value;
}

int Sprite::GetY()
{
	return this->m_y;
}

void Sprite::End(SDL_Helper * _helper)
{
	_helper->SDL_DestroyTexture(this->m_sprite);
}


void Sprite::SetNumFrames(int _value)
{
	this->m_numFrames = _value;
	this->m_currentFrame = 0;
}

int Sprite::GetNumFrames()
{
	return this->m_numFrames;
}

void Sprite::SetFrameSize(int _value)
{
	this->m_sizePerFrame = _value;
}

int Sprite::GetFrameSize()
{
	return this->m_sizePerFrame;
}