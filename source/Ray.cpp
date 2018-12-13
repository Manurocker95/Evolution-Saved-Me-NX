#include "Ray.hpp"
#include "Colors.h"
#include "Settings.h"

#include <random>
#include <ctime>
#include <cstdlib>
#include <cstdio>

Ray::Ray()
{
	this->m_disappear = false;
	this->m_counter = 0;

	// Default Color
	this->m_color = C_RED;
	
	InitialPos();
}


Ray::~Ray()
{

}

void Ray::End(SDL_Helper * _helper)
{

}

void Ray::InitialPos()
{
	this->m_axis = HORIZONTAL;
	MoveToCoord(-CELL_SIZE, -CELL_SIZE);
}

void Ray::LoadData()
{
	this->m_counter = 0;
	this->m_disappear = false;

	// Default Color
	this->m_color = C_RED;

	NewPos();
}

void Ray::NewPos()
{
	this->m_disappear = false;

	// Vertical / Horizontal
	int _type = rand() % 100;
	if (_type % 2 == 0)
	{
		srand(time(NULL));
		this->m_axis = VERTICAL;
		this->m_y = 0;
		int _x = rand() % (8) + 1;
		this->m_x = _x * CELL_SIZE;
	}
	else
	{
		this->m_axis = HORIZONTAL;
		this->m_x = 0;
		srand(time(NULL));
		int _y = rand() % (4) + 1;
		this->m_y = _y * CELL_SIZE;
	}
}
void Ray::Draw(SDL_Helper * _helper)
{
	switch (this->m_axis)
	{
	case VERTICAL:
		_helper->SDL_DrawRect(this->m_x, this->m_y, CELL_SIZE, SWITCH_SCREEN_HEIGHT, this->m_color);
		break;
	case HORIZONTAL:
		_helper->SDL_DrawRect(this->m_x, this->m_y, SWITCH_SCREEN_WIDTH, CELL_SIZE, this->m_color);
		break;
	}
}

void Ray::Update()
{
	if (!this->m_disappear)
	{
		this->m_counter++;

		if (this->m_counter > MIN_LASER_TIME && this->m_counter <= LASER_TIME)
		{
			this->m_color = C_RED;
		}
		if (this->m_counter > LASER_TIME)
		{
			this->m_disappear = true;
			MoveToCoord(-CELL_SIZE, -CELL_SIZE);
		}
	}
}

int Ray::GetCounter()
{
	return m_counter;
}

Ray::RAY_AXIS Ray::GetAxis()
{
	return this->m_axis;
}

void Ray::SetAxis(Ray::RAY_AXIS _value)
{
	this->m_axis = _value;
}

void Ray::SetAlphaColor(int _value)
{
	this->m_color.a = _value;
}

SDL_Color Ray::GetColor()
{
	return this->m_color;
}

void Ray::SetColor(SDL_Color _value)
{
	this->m_color = _value;
}

bool Ray::CheckCollision(Monkey * _player)
{
	if (m_axis == VERTICAL)
	{
		if ((!_player->GetInvincible()) && _player->IsAlive() && this->m_counter > MIN_LASER_TIME && this->m_x == _player->GetX() && (_player->GetY() > this->m_y && _player->GetY() <= SWITCH_SCREEN_HEIGHT))
		{
			return true;
		}
	}
	else
	{
		if ((!_player->GetInvincible()) && _player->IsAlive() && this->m_counter > MIN_LASER_TIME && (_player->GetX() > this->m_x && _player->GetX() <= SWITCH_SCREEN_WIDTH) && this->m_y == _player->GetY())
		{
			return true;
		}
	}

	return false;
}

bool Ray::Out()
{
	return this->m_disappear;
}