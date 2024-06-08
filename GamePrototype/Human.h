#pragma once
#include "Allergy.h"
class Human
{
public:

	Human(const Point2f& pos, const Color4f& clr);

	void Update(float elapsedSec);
	void Draw()const;
	Point2f GetPos()const;
	float GetSide()const;
	Color4f GetClr()const;
	Point2f GetAimDirection(const Point2f& aimPos, float maxHeight);
	bool Shoot();
	bool CheckCollision(const Circlef& allergyHB, bool isPlayer);
	//void SetPos(const Point2f& newPos);
	//void SetCanShoot(bool newBool);
	//bool GetCanShoot()const;
	//void SetClr(const Color4f& newColor);

private:
	
	Point2f m_Pos;
	Color4f m_Clr;
	const float m_Side;
	bool m_Alive;
	float m_ShootTimer;
	/*bool m_CanShoot;*/
	



};

