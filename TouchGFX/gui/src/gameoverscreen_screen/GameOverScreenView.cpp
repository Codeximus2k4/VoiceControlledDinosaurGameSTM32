#include <gui/gameoverscreen_screen/GameOverScreenView.hpp>
extern  int16_t level;
extern  int16_t score;
GameOverScreenView::GameOverScreenView()
{

}

void GameOverScreenView::setupScreen()
{
    GameOverScreenViewBase::setupScreen();
}

void GameOverScreenView::tearDownScreen()
{
    GameOverScreenViewBase::tearDownScreen();
}
void GameOverScreenView::showPlayerStat(){
	// redraw the player's recent level and score

	//TODO
}
