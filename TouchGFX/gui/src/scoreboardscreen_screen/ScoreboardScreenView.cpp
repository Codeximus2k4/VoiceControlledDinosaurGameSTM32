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
