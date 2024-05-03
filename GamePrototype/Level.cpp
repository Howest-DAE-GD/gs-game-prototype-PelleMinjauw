#include "pch.h"
#include "Level.h"
#include <utils.h>

Level::Level(const Rectf& LevelBorders, const Color4f& levelClr, const Rectf& Playerborders, const Color4f& playerClr)
	:m_LevelBorders{ LevelBorders }
	,m_LevelClr{levelClr}
	,m_PlayerBorders{Playerborders}
	,m_PlayerClr{playerClr}
{
}

void Level::Draw() const
{
	const float	borderWidth{ 5.f };
	
	utils::SetColor(m_PlayerClr);
	utils::DrawRect(m_PlayerBorders, borderWidth);
	utils::SetColor(m_LevelClr);
	utils::DrawRect(m_LevelBorders,borderWidth );
}
