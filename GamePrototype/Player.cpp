#include "pch.h"
#include "Player.h"
#include <utils.h>
#include <Texture.h>
#include <Matrix2x3.h>

Player::Player(const Point2f& pos, const Color4f& playerClr, const Rectf& borders, const Point2f& posPlatf, const Point2f& posText)
	: m_Pos{ pos }
	, m_Color{ playerClr }
	, m_Radius{ 50.f }
	, m_Borders{ borders }
	, m_MovBorders{borders.left + borders.width / 2 + m_Radius,borders.bottom + m_Radius, borders.width/2 - m_Radius * 2, borders.height- m_Radius *2}
	, m_Speeds{}
	, m_TotMoveTime{}
	, m_TimeMoved{}
	, m_DirecLine{}
	, m_Platform{}
	, m_StartNorms{}
	, m_EndNorms{}
	, m_Angle{}
	, m_Weapon{ Weapon::deflector }
	, m_Health{ 5 }
	, m_PosText{posText}
	, m_SizeText{35}
	, m_ClrText{ Color4f(0.3f,0.8f,0.3f,1.f)}
{
	m_pText = new Texture{ "Health: " + std::to_string(m_Health)  , "DIN-Light.otf", m_SizeText, m_ClrText };
	const int sides{ 4 };
	m_Platform.reserve(sides);
	m_StartNorms.reserve(sides);
	m_EndNorms.reserve(sides);
}

Player::~Player()
{
	delete m_pText;
	m_pText = nullptr;
	for (int idx{}; m_Platform.size(); ++idx)
	{
		m_Platform.pop_back();
	}
}

void Player::Update(const Uint8* pStates, float elapsedSec, const Point2f& posMouse)
{
	/*const float speed{ 100.f };

	if (pStates[SDL_SCANCODE_W])
	{
		m_Pos.y += speed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_S])
	{
		m_Pos.y -= speed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_A])
	{
		m_Pos.x -= speed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_D])
	{
		m_Pos.x += speed * elapsedSec;
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
	}*/

	const float restTime{1.f};
	if (m_TimeMoved - restTime >= m_TotMoveTime)
	{
		const float speed{ 100.f };
		Vector2f vectorMov{ m_Pos, RandPos(m_MovBorders) };
		m_TotMoveTime = vectorMov.Length() / speed;
		m_Speeds.x = vectorMov.x / m_TotMoveTime;
		m_Speeds.y = vectorMov.y / m_TotMoveTime;
		
		m_TimeMoved = 0.f;

		m_DirecLine.x = vectorMov.x / vectorMov.Length() * m_Radius;
		m_DirecLine.y = vectorMov.y / vectorMov.Length() * m_Radius;

		// length / speed = sec to reach end --> distance x & y / totsec = speeds --> speeds * elapsedSec
	}
	else
	{
		if (m_TimeMoved >= restTime)
		{
			m_Pos.x += m_Speeds.x * elapsedSec;
			m_Pos.y += m_Speeds.y * elapsedSec;
		}
		m_TimeMoved += elapsedSec;
	}

	const float angleConst{ 100.f };
	if (pStates[SDL_SCANCODE_X])
	{
		m_Angle += angleConst * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_C])
	{
		m_Angle -= angleConst * elapsedSec;
	}
	
	const float minAngle{ -45.f }, maxAngle{ 45.f };
	if (m_Angle < minAngle)
	{
		m_Angle = minAngle;
	}
	else if (m_Angle > maxAngle)
	{
		m_Angle = maxAngle;
	}

	for (int idx{}; m_StartNorms.size();++idx)
	{
		m_StartNorms.pop_back();
	}
	for (int idx{}; m_EndNorms.size(); ++idx)
	{
		m_EndNorms.pop_back();
	}

	Matrix2x3 rotM{};
	rotM.SetAsRotate(m_Angle);
	Matrix2x3 translM{};
	translM.SetAsTranslate(posMouse.x,posMouse.y);
	Matrix2x3 transformM{translM * rotM};
	
	Rectf oriPltf{ -5.f, -37.f, 10.f, 75.f };
	m_Platform = transformM.Transform(oriPltf);

	const float distNorm{ 10.f };
	std::vector<Point2f> orStartNorm{ Point2f{ oriPltf.left,  oriPltf.bottom + oriPltf.height / 2}, Point2f{oriPltf.left + oriPltf.width/2, oriPltf.bottom +oriPltf.height},
	Point2f{oriPltf.left+oriPltf.width, oriPltf.bottom + oriPltf.height/2},Point2f{oriPltf.left + oriPltf.width / 2, oriPltf.bottom} },
	orEndNorm{ Point2f{-distNorm + oriPltf.left,oriPltf.left + oriPltf.width / 2}, Point2f{oriPltf.left + oriPltf.width / 2, oriPltf.bottom + oriPltf.height + distNorm},
	Point2f{oriPltf.left + oriPltf.width + distNorm, oriPltf.bottom + oriPltf.height / 2},Point2f{oriPltf.left + oriPltf.width / 2, oriPltf.bottom-distNorm} };
	
	for (int idx{}; idx < orStartNorm.size(); ++idx)
	{
		m_StartNorms.push_back(transformM.Transform(orStartNorm[idx]));
	}
	for (int idx{}; idx < orEndNorm.size(); ++idx)
	{
		m_EndNorms.push_back(transformM.Transform(orEndNorm[idx]));
	}


	//PLATFORM borders
	for (int idx{}; idx < m_Platform.size(); ++idx)
	{
		//Platfrom idx 0-1 front(left) side, 1-2 top, 2-3 back(right) side, 3-1 bottom sides
		if (idx < 2 && m_Platform[idx].x < m_Borders.left)
		{
			const float difference{ m_Borders.left - m_Platform[idx].x };
			for (int idx2{}; idx2 < m_Platform.size(); ++idx2)
			{
				m_Platform[idx2].x += difference;
			}
		}
		else if (idx > 1 && m_Platform[idx].x > m_Borders.left + m_Borders.width)
		{
			const float difference{ m_Platform[idx].x - (m_Borders.left + m_Borders.width) };
			for (int idx2{}; idx2 < m_Platform.size(); ++idx2)
			{
				m_Platform[idx2].x -= difference;
			}
		}
		if ((idx == 0 || idx == 3)	&& m_Platform[idx].y < m_Borders.bottom)
		{
			const float difference{ m_Borders.bottom - m_Platform[idx].y };
			for (int idx2{}; idx2 < m_Platform.size(); ++idx2)
			{
				m_Platform[idx2].y += difference;
			}
		}
		else if ((idx == 1 || idx == 2) && m_Platform[idx].y > m_Borders.bottom + m_Borders.height)
		{
			const float difference{ m_Platform[idx].y - (m_Borders.bottom + m_Borders.height) };
			for (int idx2{}; idx2 < m_Platform.size(); ++idx2)
			{
				m_Platform[idx2].y -= difference;
			}
		}
	}
	
}

void Player::Draw() const
{
	utils::SetColor(m_Color);
	utils::FillEllipse(m_Pos, m_Radius, m_Radius);
	utils::FillPolygon(m_Platform);
	utils::SetColor(Color4f{ 0.6f,0.8f,0.6f,1.f });
	utils::DrawLine(m_Pos, Point2f{m_Pos.x + m_DirecLine.x, m_Pos.y + m_DirecLine.y}, 4.f);
	
	//Testing normals
	/*for (int idx{}; idx < 4; ++idx)
	{
		utils::DrawLine(m_StartNorms[idx], m_EndNorms[idx]);
	}*/
	
}

void Player::DrawHealth() const
{
	m_pText->Draw(m_PosText);
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
			switch (m_Health)
			{
			case 4:
				m_ClrText = Color4f(0.5f, 0.7f, 0.3f, 1.f);
				break;
			case 3:
				m_ClrText = Color4f(0.6f, 0.5f, 0.3f, 1.f);
					break;
			case 2:
				m_ClrText = Color4f(0.8f, 0.3f, 0.3f, 1.f);
				break;
			case 1:
				m_ClrText = Color4f(1.f, 0.3f, 0.3f, 1.f);
				break;
			default:
				m_ClrText = Color4f(0.1f, 0.1f, 0.1f, 1.f);
				break;
			}
			delete m_pText;
			m_pText = new Texture{ "Health: " + std::to_string(m_Health)  , "DIN-Light.otf", m_SizeText, m_ClrText };
			return true;
		}
	}
	return false;
}

int Player::GetHealth() const
{
	return m_Health;
}

std::vector<Point2f> Player::GetPlatfromHB() const
{
	return m_Platform;
}

std::vector<Vector2f> Player::GetPlatformNormal() const
{
	std::vector<Vector2f>normals{};
	for (int idx{}; idx < m_StartNorms.size(); ++idx)
	{
		normals.push_back(Vector2f{ m_StartNorms[idx], m_EndNorms[idx] });
	}
	return normals;
}

Point2f Player::RandPos(const Rectf& borders)
{
	return Point2f{rand() % int(borders.width +1) + borders.left, rand() % int(borders.height +1) + borders.bottom};
}

