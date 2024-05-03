#pragma once
class Allergy
{
public:

	Allergy(bool ofPlayer, const Point2f& pos, const Point2f& aimDirec, const Color4f& clr);
	~Allergy() = default;
	void Draw()const;
	void Update(float elapsedSec);
	
	void SetMovement(const Point2f& aimDirec);
	void SetMovement(bool horizontal);
	Circlef GetHitbox()const;
	bool GetOfPlayer()const;
	Color4f GetClr()const;
	void CheckCollision(const Rectf& levelBorders, const Rectf& platformHB);


private:

	bool m_OfPlayer;
	Point2f m_Pos;
	const float m_StartSpeed;
	Point2f m_Speeds;
	Color4f m_Clr;
	const float m_Rad;
	float m_Timer;


};

