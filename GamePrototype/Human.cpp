#include "pch.h"
#include "Human.h"
#include <utils.h>

Human::Human(const Point2f& pos, const Color4f& clr)
	:m_Pos{pos}
	,m_Clr{clr}
	,m_Side{30.f}
	,m_Alive{true}
	,m_ShootTimer{}
	//,m_CanShoot{true}
{
}


void Human::Update(float elapsedSec)
{
	m_ShootTimer += elapsedSec;

	/*if (m_CanShoot)
	{
		m_ShootTimer += elapsedSec;
	}*/
}

void Human::Draw() const
{
	if (m_Alive)
	{
		utils::SetColor(m_Clr);
		utils::FillRect(m_Pos, m_Side, m_Side);
		utils::SetColor(Color4f{ 0.95f, 0.95f, 0.95f, 1.f });
		utils::DrawRect(m_Pos, m_Side, m_Side);
	}
}

Point2f Human::GetPos() const
{
	return m_Pos;
}

float Human::GetSide()const
{
	return m_Side;
}

Color4f Human::GetClr() const
{
	return m_Clr;
}

Point2f Human::GetAimDirection(const Point2f& aimPos, float maxHeight)
{
	float randY{ float(rand() % 401 - 200) };
	/*if (randY < 0) randY = 0;
	else if (randY > maxHeight)randY = maxHeight;*/
	return Point2f{ aimPos.x, aimPos.y + randY };
}

bool Human::Shoot() 
{
	const float waitTime{ 5.f };
	if (m_ShootTimer >= waitTime)
	{
		m_ShootTimer = 0.f;
		return true;
	}

	/*if (m_CanShoot)
	{
		const float waitTime{ 5.f };
		if (m_ShootTimer >= waitTime)
		{
			m_ShootTimer = 0.f;
			return true;
		}
	}*/
	return false;
}

bool Human::CheckCollision(const Circlef& allergyHB, bool isPlayer)
{
	if (isPlayer)
	{
		if (utils::IsOverlapping(Rectf{m_Pos.x,m_Pos.y, m_Side, m_Side}, allergyHB))
		{
		return true;
		}
	}
	
	return false;
}

//void Human::SetPos(const Point2f& newPos)
//{
//	m_Pos = newPos;
//}

//void Human::SetCanShoot(bool newBool)
//{
//	m_CanShoot = newBool;
//}
//
//bool Human::GetCanShoot() const
//{
//	return m_CanShoot;
//}

//void Human::SetClr(const Color4f& newColor)
//{
//	m_Clr = newColor;
//}
