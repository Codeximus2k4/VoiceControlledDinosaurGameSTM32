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
	Unicode::snprintf(player_levelBuffer, sizeof(player_levelBuffer)/sizeof(Unicode::UnicodeChar), "%d", level);
	player_level.setWildcard(player_levelBuffer);
	player_level.invalidate();

	Unicode::snprintf(player_scoreBuffer, sizeof(player_scoreBuffer)/sizeof(Unicode::UnicodeChar), "%d", score);
	player_score.setWildcard(player_scoreBuffer);
	player_score.invalidate();
}
