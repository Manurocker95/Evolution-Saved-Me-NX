#pragma once
#ifndef _RAY_H_
#define _RAY_H_

#include "Monkey.hpp"


class Ray : public Sprite
{
public:
	enum RAY_AXIS 
	{ 
		VERTICAL, 
		HORIZONTAL 
	};

private:

	int m_counter;
	bool m_disappear;
	SDL_Color m_color;
	RAY_AXIS m_axis;

public:

	Ray();
	~Ray();

	bool CheckCollision(Monkey * _player);

	int GetCounter();

	void SetAxis(RAY_AXIS value);
	RAY_AXIS GetAxis();

	SDL_Color GetColor();
	void SetColor(SDL_Color _value);
	void SetAlphaColor(int _value);

	void LoadData();


	void Draw(SDL_Helper * _helper) override;
	void Update() override;
	void End(SDL_Helper * _helper) override;
	bool Out();

	void InitialPos();
	void NewPos();

};


#endif