#include <gui/levelselectscreen_screen/LevelSelectScreenView.hpp>
int16_t level = 1;
extern int16_t score;
LevelSelectScreenView::LevelSelectScreenView()
{

}

void LevelSelectScreenView::setupScreen()
{
    LevelSelectScreenViewBase::setupScreen();
}

void LevelSelectScreenView::tearDownScreen()
{
    LevelSelectScreenViewBase::tearDownScreen();
}

void LevelSelectScreenView::loadLevel1(){
	level = 1;
	score = 0;
}

void LevelSelectScreenView::loadLevel2(){
	level = 2;
	score = 0;
}
void LevelSelectScreenView::loadLevel3(){
	level = 3;
	score = 0;
}
