#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "Level.h"
#include "Human.h"
#include "Timer.h"
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize()
{
	m_pPlayer = new Player{ m_SpawnPos, m_PlayerClr, m_PlayerBorders,Point2f{m_PlayerBorders.left + 300.f, GetViewPort().height / 2}, Point2f{GetViewPort().width - 180.f, GetViewPort().height - 50.f}};
	m_pLevel = new Level{ m_LevelBorders, m_LevelClr, m_PlayerBorders, m_PlayerClr };
	m_pTimer = new Timer{ Point2f{GetViewPort().width / 2 - 50.f, GetViewPort().height - 50.f} };
	m_Humans.reserve(100);
	m_Allergies.reserve(200);
	m_Humans.push_back(new Human{ GetRandomPos(m_HumanBorders), GetRandomClr() });
	//m_Humans.push_back(new Human{ GetRandomPos(m_HumanBorders), GetRandomClr() });
	/*for (int i{}; i < 4; ++i)
	{
		m_Humans.push_back(new Human{ GetRandomPos(m_HumanBorders), GetRandomClr() });

	}*/

}

void Game::Cleanup( )
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
	
	delete m_pLevel;
	m_pLevel = nullptr;

	for (int idx{}; idx < m_Humans.size(); ++idx)
	{
		m_Humans.pop_back();
	}
	for (int idx{}; idx < m_Allergies.size(); ++idx)
	{
		m_Allergies.pop_back();
	}
} 

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	
	m_Timer += elapsedSec;
	if (!m_GameOver)
	{
		UpdatePlayer(pStates, elapsedSec);
		UpdateAllergies(pStates, elapsedSec);
		updateHumans(pStates, elapsedSec);
		m_pTimer->Update(elapsedSec);
		GameOver();
	}
	
	/*if (pStates[SDL_SCANCODE_T])
	{
		m_Humans.push_back(new Human{ GetRandomPos(m_HumanBorders), GetRandomClr() });
	}
	if (pStates[SDL_SCANCODE_UP])
	{
		for (int idx{}; idx < m_Humans.size(); ++idx)
		{
			delete m_Humans[idx];
			m_Humans[idx] = m_Humans[m_Humans.size() - 1];
			m_Humans[m_Humans.size() - 1] = nullptr;
			m_Humans.pop_back();
		}
	}*/
	
	
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );

	m_pPlayer->Draw();
	m_pLevel->Draw();
	m_pPlayer->DrawHealth();
	m_pTimer->Draw();
	for (int idx{}; idx < m_Humans.size();++idx)
	{
		m_Humans[idx]->Draw();
	}
	for (int idx{}; idx < m_Allergies.size(); ++idx)
	{
		m_Allergies[idx]->allergyS.Draw();
	}

	if (m_GameOver)
	{
		m_TextGameOver->Draw(Point2f{ GetViewPort().width / 2 - m_TextGameOver->GetWidth() / 2, GetViewPort().height / 2 });
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_MousePos = Point2f{ float(e.x),float(e.y) };
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.4f, 0.4f, 0.4f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

Point2f Game::GetRandomPos(const Rectf& borders)const
{
	const float x{ rand() % int(borders.width + 1) + borders.left };
	const float y{ rand() % int(borders.height + 1) + borders.bottom };
	return Point2f(x,y);
}

Color4f Game::GetRandomClr(const Color4f& avoidClr) const
{
	const int randClr{ rand() % 3 };
	Color4f clr;
	switch (randClr)
	{
	case 0:
		clr = Color4f(0.8f, 0.f, 0.f, 1.f);
		break;
	case 1:
		clr = Color4f(0.f, 0.8f, 0.f, 1.f);
		break;
	case 2:
		clr = Color4f(0.f, 0.f, 0.8f, 1.f);
		break;
	}
	if (clr.r == avoidClr.r && clr.g == avoidClr.g && clr.b == avoidClr.b)
	{
		return GetRandomClr(avoidClr);
	}
	return clr;
}

void Game::SpawnHumans()
{
	float maxTime{ 3.5f };
	if (m_SpawnTimer > maxTime)
	{
		m_Humans.push_back(new Human{ GetRandomPos(m_HumanBorders), GetRandomClr() });
		m_SpawnTimer = 0.f; 

		/*bool existHuman{ false };
		for (int idx{}; idx < m_Humans.size(); ++idx)
		{
			if (!m_Humans[idx]->GetCanShoot())
			{
				m_Humans[idx]->SetPos(GetRandomPos(m_HumanBorders));
				m_Humans[idx]->SetClr(GetRandomClr());
				m_Humans[idx]->SetCanShoot(true);
				existHuman = true;
				return;
			}
			if (existHuman)return;
		}
		if (!existHuman)
		{	
			m_Humans.push_back(new Human{ GetRandomPos(m_HumanBorders), GetRandomClr() });
			return;
		}
		m_SpawnTimer = 0.f;*/
	}
}

void Game::UpdateAllergies(const Uint8* pStates, float elapsedSec)
{
	const float maxAllergyTime{ 25.f };

	for (int idx{}; idx < m_Allergies.size(); ++idx)
	{
		m_Allergies[idx]->timerS += elapsedSec;
		m_Allergies[idx]->allergyS.Update(elapsedSec);
		m_Allergies[idx]->allergyS.CheckCollision(m_LevelBorders, m_pPlayer->GetPlatfromHB(), m_pPlayer->GetPlatformNormal());
	}
	int idx{};
	while (idx < m_Allergies.size())
	{
		if (m_Allergies[idx]->timerS >= maxAllergyTime)
		{
			/*	delete m_Allergies[idx];
				m_Allergies[idx] = m_Allergies[m_Allergies.size() - 1];
				m_Allergies[m_Allergies.size() - 1] = nullptr;
				m_Allergies.pop_back();*/
			m_Allergies.erase(std::find(m_Allergies.begin(), m_Allergies.end(), m_Allergies[idx]));
		}
		++idx;
	}
			
	
}

void Game::updateHumans(const Uint8* pStates, float elapsedSec)
{
	m_SpawnTimer += elapsedSec;

	SpawnHumans();
	for (int idx{}; idx < m_Humans.size(); ++idx)
	{
		m_Humans[idx]->Update(elapsedSec);
		if (m_Humans[idx]->Shoot())
		{
			m_Allergies.push_back(new AliveAllergy{ Allergy{false, m_Humans[idx]->GetPos(), m_Humans[idx]->GetAimDirection(m_pPlayer->GetPos(),
				GetViewPort().height), GetRandomClr(m_Humans[idx]->GetClr())} });
		}
	}
	int idx{};
	while (idx < m_Humans.size())
	{
		bool humanDeleted{};
		int idx2{};
		while (idx2 < m_Allergies.size())
		{
			if (humanDeleted)return;
			if (m_Humans[idx]->CheckCollision(m_Allergies[idx2]->allergyS.GetHitbox(), m_Allergies[idx2]->allergyS.GetOfPlayer()))
			{
				if (m_Allergies[idx2]->allergyS.GetClr().r == m_Humans[idx]->GetClr().r && m_Allergies[idx2]->allergyS.GetClr().g == m_Humans[idx]->GetClr().g &&
					m_Allergies[idx2]->allergyS.GetClr().b == m_Humans[idx]->GetClr().b)
				{
					m_Allergies.erase(std::find(m_Allergies.begin(), m_Allergies.end(), m_Allergies[idx2]));
					m_Humans.erase(std::find(m_Humans.begin(), m_Humans.end(), m_Humans[idx]));
					humanDeleted = true;
				}
				else
				{
					m_Allergies[idx2]->allergyS.SetMovement(true);
					m_Allergies[idx2]->allergyS.SetOfPlayer(false);

				}
			}
			++idx2;
		}
		++idx;
	}
}

void Game::UpdatePlayer(const Uint8* pStates, float elapsedSec)
{
	m_pPlayer->Update(pStates, elapsedSec, m_MousePos);
	int idx{};
	while (idx < m_Allergies.size())
	{
		if (m_pPlayer->CheckCollision(m_Allergies[idx]->allergyS.GetHitbox(), m_Allergies[idx]->allergyS.GetOfPlayer()))
		{
			/*delete m_Allergies[idx];
			m_Allergies[idx] = m_Allergies[m_Allergies.size() - 1];
			m_Allergies[m_Allergies.size() - 1] = nullptr;
			m_Allergies.pop_back();*/
			m_Allergies.erase(std::find(m_Allergies.begin(), m_Allergies.end(), m_Allergies[idx]));
		}
		++idx;
	}
}

void Game::GameOver()
{
	if (m_pPlayer->GetHealth() <= 0)
	{
		std::cout << "GAME OVER\n";
		m_GameOver = true;
	}
}

Game::AliveAllergy::AliveAllergy(const Allergy& allergy)
	:allergyS{allergy}
	,timerS{0.f}
{
}
