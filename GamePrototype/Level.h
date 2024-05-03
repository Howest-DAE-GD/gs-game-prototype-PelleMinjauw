#pragma once
class Level
{
public:
	

	Level(const Rectf& LevelBorders, const Color4f& levelClr, const Rectf& Playerborders, const Color4f& playerClr);
	
	void Draw()const;

private:

	const Rectf m_LevelBorders;
	const Rectf m_PlayerBorders;
	const Color4f m_LevelClr;
	const Color4f m_PlayerClr;

};

