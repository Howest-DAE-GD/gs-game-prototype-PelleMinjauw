#pragma once
#include <Texture.h>
#include <vector>
#include <Vector2f.h>

class Player
{
public:

	enum class Weapon
	{
		deflector,
		grabber
	};
	Player(const Point2f& pos, const Color4f& playerClr, const Rectf& border, const Point2f& posPlatf, const Point2f& posText);
	~Player();
	
	void Update(const Uint8* pStates, float elapsedSec, const Point2f& posMouse);
	void Draw()const;
	void DrawHealth()const;
	Point2f GetPos()const;
	bool CheckCollision(const Circlef& allergy, bool isPlayer);
	int GetHealth()const;
	std::vector<Point2f> GetPlatfromHB()const;
	std::vector<Vector2f> GetPlatformNormal()const;
	

private:
	//PLAYER MEMBERS
	Point2f m_Pos;
	const Color4f m_Color;
	const float m_Radius;
	const Rectf m_Borders;
	const Rectf m_MovBorders;
	Point2f m_Speeds;
	float m_TotMoveTime;
	float m_TimeMoved;
	Point2f m_DirecLine;
	
		//ONLY PLATFROM MEMBERS
		std::vector<Point2f>m_Platform;
		std::vector<Point2f> m_StartNorms, m_EndNorms;
		float m_Angle;
		Weapon m_Weapon;
		
	
	//HEALTH MEMBERS
	int m_Health;
	const Point2f m_PosText;
	const int m_SizeText;
	Color4f m_ClrText;
	Texture* m_pText;

	

	
	//PRIVATE FUNCTIONS
	Point2f RandPos(const Rectf& borders);
	
	
	Vector2f test{ 50.f,100.f };
	Vector2f aa{ test.Orthogonal() };
};

