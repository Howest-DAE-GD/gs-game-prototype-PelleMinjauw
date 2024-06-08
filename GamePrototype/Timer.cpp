#include "pch.h"
#include "Timer.h"

Timer::Timer(const Point2f& pos)
	:m_Timer{}
	,m_pos{pos}
	,m_Size{35}
	,m_Clr{Color4f{0.2f,0.2f,0.8f,1.f}}
{
	m_pText = new Texture{ "Time: " + std::to_string(m_Timer), "DIN-Light.otf",  m_Size,m_Clr };
}

Timer::~Timer()
{
	delete m_pText;
	m_pText = nullptr;
}

void Timer::Update(float elapsedSec)
{
	m_Timer += elapsedSec;
	delete m_pText;
	m_pText = new Texture{ "Time: " + std::to_string(int(m_Timer)), "DIN-Light.otf",  m_Size,m_Clr };
}

void Timer::Draw() const
{
	m_pText->Draw(m_pos);
}
