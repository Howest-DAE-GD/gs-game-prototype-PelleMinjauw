#pragma once
#include <Texture.h>
class Timer
{
public:
	
	Timer(const Point2f& pos);
	~Timer();

	void Update(float elapsedSec);
	void Draw()const;

private:

	float m_Timer;
	const Point2f m_pos;
	const int m_Size;
	Color4f m_Clr;
	Texture* m_pText;
};

