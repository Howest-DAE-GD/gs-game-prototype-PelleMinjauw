#pragma once
#include <vector>
#include <Vector2f.h>
class Allergy
{
public:

	Allergy(bool ofPlayer, const Point2f& pos, const Point2f& aimDirec, const Color4f& clr);
	~Allergy() = default;
	void Draw()const;
	void Update(float elapsedSec);
	
	void SetMovement(const Point2f& aimDirec);
	void SetMovement(bool horizontal);
	void SetMovement(const Vector2f& aimDirec);

	Circlef GetHitbox()const;
	bool GetOfPlayer()const;
	Color4f GetClr()const;
	void CheckCollision(const Rectf& levelBorders, std::vector<Point2f> platformHB, std::vector<Vector2f> newDirec);
	void SetOfPlayer(bool ofPlayer);


private:

	bool m_OfPlayer;
	Point2f m_Pos;
	const float m_StartSpeed;
	Point2f m_Speeds;
	Color4f m_Clr;
	const float m_OutRad;
	const float m_InRad;
	float m_Timer;


};

