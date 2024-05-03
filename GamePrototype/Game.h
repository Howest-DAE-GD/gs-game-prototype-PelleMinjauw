#pragma once
#include "BaseGame.h"
#include <vector>
#include "Allergy.h"
class Player;
class Level;
class Human;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	struct AliveAllergy
	{
		AliveAllergy(const Allergy& allergy);

		Allergy allergyS;
		float timerS;
	};
	
	Point2f m_MousePos{};

	Player* m_pPlayer{};
	Level* m_pLevel{};
	const float m_MaxSideHum{ 60.f };
	const Point2f m_SpawnPos{ 1200.f, GetViewPort().height / 2 };
	const Rectf	m_PlayerBorders{1000.f + 1, 0.f + 1, GetViewPort().width - 1000.f -2, GetViewPort().height-2};
	const Rectf	m_LevelBorders{1.f, 1.f, GetViewPort().width -2, GetViewPort().height -2};
	const Rectf m_HumanBorders{ 20.f + m_MaxSideHum, 20.f + m_MaxSideHum, GetViewPort().width / 3, GetViewPort().height - 2*(20.f + m_MaxSideHum)};
	const Color4f m_PlayerClr{ 0.05f,0.05f,0.05f,1.f };
	const Color4f m_LevelClr{ 0.95f, 0.5f, 0.5f, 1.f };

	float m_Timer{}; 
	float m_SpawnTimer{};

	std::vector<Human*>m_Humans;
	std::vector<AliveAllergy*> m_Allergies;

	bool m_GameOver{ false };

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	Point2f GetRandomPos(const Rectf& borders)const;
	Color4f GetRandomClr(const Color4f& avoidClr = Color4f{0.f,0.f,0.f,0.f})const;
	void SpawnHumans();
	void UpdateAllergies(const Uint8* pStates, float elapsedSec);
	void updateHumans(const Uint8* pStates, float elapsedSec);
	void UpdatePlayer(const Uint8* pStates, float elapsedSec);
	void GameOver();

};