#pragma once
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "Monkey.hpp"

class Object : public Sprite
{
public:
	enum OBJECT_TYPE 
	{ 
		BANANA, 
		FIRE 
	};

private:
	bool m_active;
	OBJECT_TYPE m_type;

public:
	Object();
	Object(OBJECT_TYPE _type, SDL_Texture * _sprite, int  _x, int  _y, int  _numFrames, int  _sizePerFrame, bool  _multipleFrames);
	
	void Update() override;
	void End (SDL_Helper * _helper) override;

	OBJECT_TYPE GetType();
	void SetType(OBJECT_TYPE _value);

	bool CheckCollision (Monkey * _player);
	bool IsActive();
	void SetActive(bool value);



};

#endif