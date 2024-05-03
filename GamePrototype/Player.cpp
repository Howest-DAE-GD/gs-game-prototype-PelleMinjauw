#include "pch.h"
#include "Player.h"
#include <utils.h>

Player::Player(const Point2f& pos, const Color4f& playerClr, const Rectf& borders, const Point2f& posPlatf)
	:m_Pos{pos}
	,m_Color{playerClr}
	,m_Radius{50.f}
	,m_Weapon{Weapon::deflector}
	,m_Speed{150.f}
	,m_Borders{borders}
	,m_Health{5}
	,m_PosCentPlatf{posPlatf.x,posPlatf.y, 10.f,75.f}
{
}

void Player::Update(const Uint8* pStates, float elapsedSec, const Point2f& posMouse)
{
	if (pStates[SDL_SCANCODE_W])
	{
		m_Pos.y += m_Speed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_S])
	{
		m_Pos.y -= m_Speed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_A])
	{
		m_Pos.x -= m_Speed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_D])
	{
		m_Pos.x += m_Speed * elapsedSec;
	}

	if (m_Pos.x + m_Radius > m_Borders.left + m_Borders.width)
	{
		m_Pos.x = m_Borders.left + m_Borders.width - m_Radius;
	}
	else if (m_Pos.x - m_Radius < m_Borders.left)
	{
		m_Pos.x = m_Borders.left + m_Radius;
	}
	if (m_Pos.y + m_Radius > m_Borders.bottom + m_Borders.height)
	{
		m_Pos.y = m_Borders.bottom + m_Borders.height - m_Radius;
	}
	else if (m_Pos.y - m_Radius < m_Borders.bottom)
	{
		m_Pos.y = m_Borders.bottom + m_Radius;
	}

	m_PosCentPlatf.left = posMouse.x;
	m_PosCentPlatf.bottom = posMouse.y;

	if (m_PosCentPlatf.left + m_PosCentPlatf.width/2 > m_Borders.left + m_Borders.width)
	{
		m_PosCentPlatf.left = m_Borders.left + m_Borders.width - m_PosCentPlatf.width / 2;
	}
	else if (m_PosCentPlatf.left + m_PosCentPlatf.width / 2 < m_Borders.left)
	{
		m_PosCentPlatf.left = m_Borders.left + m_PosCentPlatf.width / 2;
	}
	if (m_PosCentPlatf.bottom + m_PosCentPlatf.height / 2 > m_Borders.bottom + m_Borders.height)
	{
		m_PosCentPlatf.bottom = m_Borders.bottom + m_Borders.height - m_PosCentPlatf.height / 2;
	}
	else if (m_PosCentPlatf.bottom - m_PosCentPlatf.height / 2 < m_Borders.bottom)
	{
		m_PosCentPlatf.bottom = m_Borders.bottom + m_PosCentPlatf.height / 2;
	}
}

void Player::Draw() const
{
	utils::SetColor(m_Color);
	utils::FillEllipse(m_Pos, m_Radius, m_Radius);
	utils::FillRect(m_PosCentPlatf.left - m_PosCentPlatf.width / 2, m_PosCentPlatf.bottom - m_PosCentPlatf.height / 2, m_PosCentPlatf.width, m_PosCentPlatf.height);
}

Point2f Player::GetPos() const
{
	return m_Pos;
}

bool Player::CheckCollision(const Circlef& allergyHB, bool isPlayer)
{
	if(!isPlayer)
	{
		if (utils::IsOverlapping(Circlef{ m_Pos,m_Radius }, allergyHB))
		{
			m_Health -= 1;
			return true;
		}
	}
	return false;
}

int Player::GetHealth() const
{
	return m_Health;
}

Rectf Player::GetPlatfromHB() const
{
	return Rectf{ m_PosCentPlatf.left - m_PosCentPlatf.width / 2, m_PosCentPlatf.bottom - m_PosCentPlatf.height / 2, m_PosCentPlatf.width, m_PosCentPlatf.height };
}

