#include "pch.h"
#include "Allergy.h"
#include <utils.h>

Allergy::Allergy(bool ofPlayer, const Point2f& pos, const Point2f& aimDirec, const Color4f& clr)
	:m_OfPlayer{ofPlayer}
	,m_Pos{pos}
	,m_StartSpeed{250.f}
	,m_Speeds{m_StartSpeed,0.f}
	,m_Clr{clr}
	,m_OutRad{7.5f}
	,m_InRad{ m_OutRad - 3.f }
	,m_Timer{}
{
	SetMovement(aimDirec);
}

void Allergy::Draw() const
{
	if (m_OfPlayer)
	{
		utils::SetColor(Color4f{ 0.05f, 0.05f, 0.05f, 1.f });
	}
	else utils::SetColor(Color4f{ 0.95f, 0.95f, 0.95f, 1.f });
	utils::FillEllipse(m_Pos, m_OutRad, m_OutRad);
	utils::SetColor(m_Clr);
	utils::FillEllipse(m_Pos, m_InRad, m_InRad);
}

void Allergy::Update(float elapsedSec)
{
	m_Timer += elapsedSec;
	m_Pos.x += m_Speeds.x * elapsedSec;
	m_Pos.y += m_Speeds.y * elapsedSec;
}

void Allergy::SetMovement(const Point2f& aimDirec)
{
	m_Speeds.y = (aimDirec.y - m_Pos.y) / ((aimDirec.x - m_Pos.x) / m_StartSpeed);
}

void Allergy::SetMovement(bool horizontal)
{
	if (horizontal)
	{
		m_Speeds.x = -m_Speeds.x;
	}
	else
	{
		m_Speeds.y = -m_Speeds.y;
	}
}

void Allergy::SetMovement(const Vector2f& aimDirec)
{
	m_Speeds.x = aimDirec.x / aimDirec.Length() * m_StartSpeed;
	m_Speeds.y = aimDirec.y / aimDirec.Length() * m_StartSpeed;
}

Circlef Allergy::GetHitbox() const
{
	return Circlef(m_Pos,m_OutRad);
}

bool Allergy::GetOfPlayer() const
{
	return m_OfPlayer;
}

Color4f Allergy::GetClr() const
{
	return m_Clr;
}

void Allergy::CheckCollision(const Rectf& levelBorders, std::vector<Point2f> platformHB, std::vector<Vector2f> newDirec)
{
	//levelBorders
	/*if (m_Pos.x + m_OutRad >= levelBorders.left + levelBorders.width)
	{
		m_Pos.x = levelBorders.left + levelBorders.width - m_OutRad;
		m_Speeds.x = -m_Speeds.x;
	}*/
	if (m_Pos.x - m_OutRad <= levelBorders.left)
	{
		m_Pos.x = levelBorders.left + m_OutRad;
		m_Speeds.x = -m_Speeds.x;
	}
	if (m_Pos.y + m_OutRad >= levelBorders.bottom + levelBorders.height)
	{
		m_Pos.y = levelBorders.bottom + levelBorders.height - m_OutRad;
		m_Speeds.y = -m_Speeds.y;
	}
	else if (m_Pos.y - m_OutRad <= levelBorders.bottom)
	{
		m_Pos.y = levelBorders.bottom + m_OutRad;
		m_Speeds.y = -m_Speeds.y;
	}

	//platformHitbox
	for (int idx{}; idx < platformHB.size(); ++idx)
	{
		if (utils::IsOverlapping(platformHB[idx], platformHB[(idx +1) % platformHB.size()], Circlef{m_Pos, m_OutRad}))
		{
			if (m_Timer > 0.1f)
			{
				m_Pos.x -= m_Speeds.x * 0.05f;
				m_Pos.y -= m_Speeds.y * 0.05f;
				SetMovement(newDirec[idx]);
				m_Timer = 0.f;
				m_OfPlayer = true;
			}
		}
	}
}

void Allergy::SetOfPlayer(bool ofPlayer)
{
	m_OfPlayer = ofPlayer;
}

