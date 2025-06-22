#include <gui/gamescreen_screen/GameScreenView.hpp>
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
extern osMessageQueueId_t soundInputQueueHandle;
extern int16_t level;
uint32_t static seed = 2463534242;
int16_t level1_highscore = 0;
int16_t level2_highscore = 0;
int16_t level3_highscore = 0;
int16_t score=0;
GameScreenView::GameScreenView()
{
	// Initiate Variable
	//TODO
}

void GameScreenView::setupScreen()
{
    GameScreenViewBase::setupScreen();
}

void GameScreenView::tearDownScreen()
{
    GameScreenViewBase::tearDownScreen();
}

// TODO:  random generator
//TODO :spawn bird and cactus
void GameScreenView::updateObstacle(uint32_t currentTime){
	if (currentTime >= nextSpawnTime){
		uint32_t interval = getRandomInt(100,200);
		nextSpawnTime = currentTime + interval;

		if (obstacleType ==0)
			{
			spawnCactus(obstacle_start_x, obstacle_end_x);
			cactus_running = true;
			specialCactusPresent =false;
			}
		else if (obstacleType ==1){
			spawnCactus(obstacle_start_x, obstacle_end_x);
			uint32_t chooseCactus = getRandomInt(0,1);
			if (chooseCactus==1) specialCactusPresent =true;
			else specialCactusPresent =false;
			cactus_running = true;
		}
		else if (obstacleType ==2) {
			spawnBird(obstacle_start_x, obstacle_end_x,obstacle_start_y,obstacle_end_y);
			bird_flying = true;
		}
		else if (obstacleType ==3){
			spawnCactus(obstacle_start_x, obstacle_end_x);
			uint32_t chooseCactus = getRandomInt(0,1);
			if (chooseCactus==1) specialCactusPresent =true;
			else specialCactusPresent =false;
			spawnBird(obstacle_start_x, obstacle_end_x,obstacle_start_y,obstacle_end_y);
			cactus_running = true;
			bird_flying= true;
		}
	}
}
void GameScreenView::tickEvent()
{

	tickCount++;

	// score :
	

// Obstacle logic:we will need to spawn them based on time
// if it is running then only update its position
	if (!cactus_running &&  !bird_flying){
		obstacleType = getRandomInt(0,obstacleCount);
		updateObstacle(tickCount);
	}
	// Cactus logic
	
	// Game UI update
		// Background
		if (tickCount%10==0) {
			background.moveTo(background.getX()-1, background.getY());
			background2.moveTo(background2.getX()-1,background2.getY());
			if (background.getX() < -background.getWidth()){
				background.moveTo(background2.getX()+background2.getWidth(), background.getY());
			}
			if (background2.getX() < -background.getWidth()){
				background2.moveTo(background.getX()+background.getWidth(), background2.getY());
			}
		}
		// Health
		if (lives ==2) lives_3.setBitmap(touchgfx::Bitmap(HealthLost));
		else if (lives ==1) lives_2.setBitmap(touchgfx::Bitmap(HealthLost));
		else if (lives ==0) {
			lives_1.setBitmap(touchgfx::Bitmap(HealthLost));
			if (level==3 && score >level3_highscore) level3_highscore = score;
			if (level==2 && score >level2_highscore) level2_highscore = score;
			if (level==1 && score >level1_highscore) level1_highscore = score;
			speed_multiplier = 1;
			gotoGameOverScreen();
		}
		lives_3.invalidate();
		lives_2.invalidate();
		lives_1.invalidate();

		// Sound level
		if (osMessageQueueGetCount(soundInputQueueHandle)>0){
			osMessageQueueGet(soundInputQueueHandle, &volumeValue, NULL, 10);
			if (volumeValue >4000) volumeValue =4000;
			volumeLevel.setValue((volumeValue-2000)/20);
		}
	// Dinosaur
// Jump checking

// Hit cooldown:
	
// Dash checking
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET && animation_state== walkState){
	}

// 	Position update
	
// Y_velocity update

		if (animation_state == jumpState){
			if (y_velocity == 0){
				animation_state = fallState;
			}
			else y_velocity --;
		}
		else if (animation_state ==fallState){
			if (tickCount%2==0){
				if (y_velocity <3) y_velocity ++;
			}
		}
//  Animation update

	


}
