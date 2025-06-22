#include <gui/scoreboardscreen_screen/ScoreboardScreenView.hpp>
extern int16_t level1_highscore;
extern int16_t level2_highscore;
extern int16_t level3_highscore;
ScoreboardScreenView::ScoreboardScreenView()
{

}

void ScoreboardScreenView::setupScreen()
{
    ScoreboardScreenViewBase::setupScreen();
}

void ScoreboardScreenView::tearDownScreen()
{
    ScoreboardScreenViewBase::tearDownScreen();
}
//TODO: update score
void ScoreboardScreenView::updateScore(){
	Unicode::snprintf(level1_scoreBuffer, sizeof(level1_scoreBuffer)/sizeof(Unicode::UnicodeChar), "%d",level1_highscore);
	level1_score.setWildcard(level1_scoreBuffer);
	level1_score.invalidate();

	Unicode::snprintf(level2_scoreBuffer, sizeof(level2_scoreBuffer)/sizeof(Unicode::UnicodeChar), "%d",level2_highscore);
	level2_score.setWildcard(level2_scoreBuffer);
	level2_score.invalidate();

	Unicode::snprintf(level3_scoreBuffer, sizeof(level3_scoreBuffer)/sizeof(Unicode::UnicodeChar), "%d",level3_highscore);
	level3_score.setWildcard(level3_scoreBuffer);
	level3_score.invalidate();

}
