#pragma once
class Player
{
public:

	enum class Weapon
	{
		deflector,
		grabber
	};
	Player(const Point2f& pos, const Color4f& playerClr, const Rectf& border, const Point2f& posPlatf);
	
	void Update(const Uint8* pStates, float elapsedSec, const Point2f& posMouse);
	void Draw()const;
	Point2f GetPos()const;
	bool CheckCollision(const Circlef& allergy, bool isPlayer);
	int GetHealth()const;
	Rectf GetPlatfromHB()const;

private:
	Point2f m_Pos;
	const Color4f m_Color;
	const float m_Radius;
	Weapon m_Weapon;
	const float m_Speed;
	const Rectf m_Borders;
	int m_Health;
	Rectf m_PosCentPlatf;
};

