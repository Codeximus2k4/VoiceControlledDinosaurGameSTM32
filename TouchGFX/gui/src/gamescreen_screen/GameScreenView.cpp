#include <gui/gamescreen_screen/GameScreenView.hpp>
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
extern osMessageQueueId_t soundInputQueueHandle;
extern int16_t level;
uint32_t static seed = 2463534242;
int16_t level1_highscore = 0;
int16_t level2_highscore = 0;
int16_t level3_highscore = 0;
int16_t score = 0;
GameScreenView::GameScreenView() {
	// Initiate Variable
	//TODO
	tickCount = 0;
	lives_3.setBitmap(touchgfx::Bitmap(HealthFull));
	lives_2.setBitmap(touchgfx::Bitmap(HealthFull));
	lives_1.setBitmap(touchgfx::Bitmap(HealthFull));
	if (level == 1) {
		background.setBitmap(touchgfx::Bitmap(level1_bg));
		background.moveTo(0, 0);
		background2.setBitmap(touchgfx::Bitmap(level1_bg));
		background2.moveTo(background.getX() + background.getWidth(),
				background2.getY());
		obstacleCount = 0;
	} else if (level == 2) {
		background.setBitmap(touchgfx::Bitmap(level2_bg));
		background.moveTo(0, 0);
		background2.setBitmap(touchgfx::Bitmap(level2_bg));
		background2.moveTo(background.getX() + background.getWidth(),
				background2.getY());
		obstacleCount = 1;
	} else {
		background.setBitmap(touchgfx::Bitmap(level3_bg));
		background.moveTo(0, 0);
		background2.setBitmap(touchgfx::Bitmap(level3_bg));
		background2.moveTo(background.getX() + background.getWidth(),
				background2.getY());
		obstacleCount = 3;
	}
	background.invalidate();
	background2.invalidate();
	Unicode::snprintf(scoreAreaBuffer,
			sizeof(scoreAreaBuffer) / sizeof(Unicode::UnicodeChar), "%d",
			score);
	scoreArea.setWildcard(scoreAreaBuffer);
	scoreArea.invalidate();
}

void GameScreenView::setupScreen() {
	GameScreenViewBase::setupScreen();
}

void GameScreenView::tearDownScreen() {
	GameScreenViewBase::tearDownScreen();
}

// TODO:  random generator using xorshift32
uint32_t xorshift32() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
int getRandomInt(int min, int max) {
	return min + (xorshift32() % (max - min + 1));
}

bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2,
		int h2) {
	return (x1 < x2 + w2) && (x1 + w1 > x2) && (y1 < y2 + h2) && (y1 + h1 > y2);
}

//TODO :spawn bird and cactus

void GameScreenView::spawnBird(int x1, int x2, int y1, int y2) {
	int16_t coordX = getRandomInt(x1, x2);
	int16_t coordY = getRandomInt(y1, y2);
	bird.moveTo(coordX, coordY);
}
void GameScreenView::spawnCactus(int x1, int x2) {
	int16_t coordX = getRandomInt(x1, x2);
	cactus.moveTo(coordX, cactus.getY());
}

void GameScreenView::updateObstacle(uint32_t currentTime) {
	if (currentTime >= nextSpawnTime) {
		uint32_t interval = getRandomInt(100, 200);
		nextSpawnTime = currentTime + interval;

		if (obstacleType == 0) {
			spawnCactus(obstacle_start_x, obstacle_end_x);
			cactus_running = true;
			specialCactusPresent = false;
		} else if (obstacleType == 1) {
			spawnCactus(obstacle_start_x, obstacle_end_x);
			uint32_t chooseCactus = getRandomInt(0, 1);
			if (chooseCactus == 1)
				specialCactusPresent = true;
			else
				specialCactusPresent = false;
			cactus_running = true;
		} else if (obstacleType == 2) {
			spawnBird(obstacle_start_x, obstacle_end_x, obstacle_start_y,
					obstacle_end_y);
			bird_flying = true;
		} else if (obstacleType == 3) {
			spawnCactus(obstacle_start_x, obstacle_end_x);
			uint32_t chooseCactus = getRandomInt(0, 1);
			if (chooseCactus == 1)
				specialCactusPresent = true;
			else
				specialCactusPresent = false;
			spawnBird(obstacle_start_x, obstacle_end_x, obstacle_start_y,
					obstacle_end_y);
			cactus_running = true;
			bird_flying = true;
		}
	}
}
void GameScreenView::tickEvent() {

	tickCount++;

	// score :
	score += speed_multiplier;
	Unicode::snprintf(scoreAreaBuffer,
			sizeof(scoreAreaBuffer) / sizeof(Unicode::UnicodeChar), "%d",
			score);
	scoreArea.setWildcard(scoreAreaBuffer);
	scoreArea.invalidate();
	if (score > 2000)
		speed_multiplier = 2;
	if (score > 4000)
		speed_multiplier = 3;

// Obstacle logic:we will need to spawn them based on time
// if it is running then only update its position
	if (!cactus_running && !bird_flying) {
		obstacleType = getRandomInt(0, obstacleCount);
		updateObstacle(tickCount);
	}

	// Cactus logic
	if (cactus_running) {
		cactus.moveTo(cactus.getX() - cactus_running_speed * speed_multiplier,
				cactus.getY());
		if (specialCactusPresent)
			special_cactus.moveTo(cactus.getX() + cactus.getWidth(),
					special_cactus.getY());
		if (cactus.getX() < -70)
			cactus_running = false;
	}

	if (bird_flying) {
		bird.moveTo(bird.getX() - bird_speed * speed_multiplier, bird.getY());
		if (bird.getX() < -32)
			bird_flying = false;
	}

	//collision logic

	bool hit = checkCollision(dinosaur.getX() + dinosaurHitBox[0],
			dinosaur.getY() + dinosaurHitBox[1], dinosaurHitBox[2],
			dinosaurHitBox[3], cactus.getX(), cactus.getY(), cactus.getWidth(),
			cactus.getHeight());
	hit = hit
			|| checkCollision(dinosaur.getX() + dinosaurHitBox[0],
					dinosaur.getY() + dinosaurHitBox[1], dinosaurHitBox[2],
					dinosaurHitBox[3], special_cactus.getX(),
					special_cactus.getY(), special_cactus.getWidth(),
					special_cactus.getHeight());
	hit = hit
			|| checkCollision(dinosaur.getX() + dinosaurHitBox[0],
					dinosaur.getY() + dinosaurHitBox[1], dinosaurHitBox[2],
					dinosaurHitBox[3], bird.getX(), bird.getY(),
					bird.getWidth(), bird.getHeight());
	if (hit) {
		if (hit_cooldown > hit_cooldown_limit) {
			lives--;
			flickering = 0;
			hit_cooldown = 0;
		}
	}

	// Game UI update
	// Background
	if (tickCount % 10 == 0) {
		background.moveTo(background.getX() - 1, background.getY());
		background2.moveTo(background2.getX() - 1, background2.getY());
		if (background.getX() < -background.getWidth()) {
			background.moveTo(background2.getX() + background2.getWidth(),
					background.getY());
		}
		if (background2.getX() < -background.getWidth()) {
			background2.moveTo(background.getX() + background.getWidth(),
					background2.getY());
		}
	}
	// Health
	if (lives == 2)
		lives_3.setBitmap(touchgfx::Bitmap(HealthLost));
	else if (lives == 1)
		lives_2.setBitmap(touchgfx::Bitmap(HealthLost));
	else if (lives == 0) {
		lives_1.setBitmap(touchgfx::Bitmap(HealthLost));
		if (level == 3 && score > level3_highscore)
			level3_highscore = score;
		if (level == 2 && score > level2_highscore)
			level2_highscore = score;
		if (level == 1 && score > level1_highscore)
			level1_highscore = score;
		speed_multiplier = 1;
		gotoGameOverScreen();
	}
	lives_3.invalidate();
	lives_2.invalidate();
	lives_1.invalidate();

	// Sound level
	if (osMessageQueueGetCount(soundInputQueueHandle) > 0) {
		osMessageQueueGet(soundInputQueueHandle, &volumeValue, NULL, 10);
		if (volumeValue > 4000)
			volumeValue = 4000;
		volumeLevel.setValue((volumeValue - 2000) / 20);
	}
	// Dinosaur
	// Jump checking
	if (volumeValue >= lowJumpValue && animation_state == walkState) {
		animation_state = jumpState;
		animation_frame = 0;
		if (volumeValue >= lowJumpValue && volumeValue <= highJumpValue)
			y_velocity = low_jump_velocity;
		else if (volumeValue >= highJumpValue)
			y_velocity = high_jump_velocity;
	}
	// Hit cooldown:
	if (tickCount % 7 == 0) {
		if (hit_cooldown + 1 > hit_cooldown_limit)
			hit_cooldown = hit_cooldown_limit + 1;
		else
			hit_cooldown++;
	}

	// Dash checking
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET
			&& animation_state == walkState) {
	}

	// 	Position update
	if (animation_state == jumpState) {
		dinosaur.moveTo(dinosaur.getX(), dinosaur.getY() - y_velocity);
	} else if (animation_state == fallState) {
		uint16_t future_pos = dinosaur.getY() + y_velocity;
		if (ground_pos > future_pos) {
			dinosaur.moveTo(dinosaur.getX(), future_pos);
		} else {
			dinosaur.moveTo(dinosaur.getX(), ground_pos);
			animation_state = walkState;
			animation_frame = 0;

		}
	}

	// Y_velocity update

	if (animation_state == jumpState) {
		if (y_velocity == 0) {
			animation_state = fallState;
		} else
			y_velocity--;
	} else if (animation_state == fallState) {
		if (tickCount % 2 == 0) {
			if (y_velocity < 3)
				y_velocity++;
		}
	}

	// Animation update
	if (flickering <= flickering_duration) {
		if (tickCount % 3 == 0) {
			flickering++;
			if (dinosaur.isVisible()) {
				dinosaur.setVisible(false);
			} else
				dinosaur.setVisible(true);
		}
	} else
		dinosaur.setVisible(true);

	if (tickCount % 3 == 0) {
		if (animation_state == walkState) {
			animation_frame = (animation_frame + 1)
					% animation_frame_num[walkState];
			dinosaur.setBitmap(touchgfx::Bitmap(DinosaurWalk[animation_frame]));
		} else if (animation_state == jumpState) {
			if (animation_frame < animation_frame_num[jumpState] - 1) {
				animation_frame++;
			}
			dinosaur.setBitmap(touchgfx::Bitmap(DinosaurJump[animation_frame]));
		} else if (animation_state == fallState) {
			if (animation_frame < animation_frame_num[fallState] - 1) {
				animation_frame++;
			}
			dinosaur.setBitmap(touchgfx::Bitmap(DinosaurFall[animation_frame]));
		}
		dinosaur.invalidate();
	}
}
