#include "Object.hpp"
#include "SceneManager.hpp"
#include "Filepaths.h"
#include "Settings.h"

Object::Object()
{
	SDL_Helper * _helper = SceneManager::Instance()->GetHelper();
	_helper->SDL_LoadImage(&m_sprite, IMG_BANANA_SPRITE);

	this->m_type = BANANA;
	this->m_x = 200;
	this->m_y = 120;
	this->m_multipleFrames = false;
	this->m_numFrames = 1;
	this->m_sizePerFrameX = BANANA_SIZE_PER_FRAME;
	this->m_sizePerFrameY = BANANA_SIZE_PER_FRAME;

	this->m_currentFrame = 0;
	this->m_secondaryCounter = 0;
}

Object::Object(Object::OBJECT_TYPE _type, SDL_Texture * _sprite, int _x, int _y, int _numFrames, int _sizePerFrameX, int _sizePerFrameY, bool _multipleFrames)
{
	this->m_type = _type;
	this->m_sprite = _sprite;
	this->m_x = _x;
	this->m_y = _y;
	this->m_numFrames = _numFrames;
	this->m_sizePerFrameX = _sizePerFrameX;
	this->m_sizePerFrameY = _sizePerFrameY;
	this->m_multipleFrames = _multipleFrames;
	this->m_active = false;
	this->m_secondaryCounter = 0;
}

void Object::SetActive(bool _value)
{
	this->m_active = _value;
}

bool Object::IsActive()
{
	return this->m_active;
}

void Object::Update()
{
	Sprite::Update();
}

void Object::End(SDL_Helper * _helper)
{
	Sprite::End(_helper);
}

Object::OBJECT_TYPE Object::GetType()
{
	return this->m_type;
}

void Object::SetType(Object::OBJECT_TYPE value)
{
	this->m_type = value;
}
//this game is based on a grid, so just checking x,y we can know if this object is colliding with the plaeyr
bool Object::CheckCollision(Monkey * player)
{
	return (this->m_x == player->GetX() && this->m_y == player->GetY());
}