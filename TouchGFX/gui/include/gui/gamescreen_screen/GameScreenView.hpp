#ifndef GAMESCREENVIEW_HPP
#define GAMESCREENVIEW_HPP

#include <gui_generated/gamescreen_screen/GameScreenViewBase.hpp>
#include <gui/gamescreen_screen/GameScreenPresenter.hpp>
#include <images/BitmapDatabase.hpp>
extern int16_t level1_highscore;
extern int16_t level2_highscore;
extern int16_t level3_highscore;
extern int16_t score;
class GameScreenView : public GameScreenViewBase
{
public:
    GameScreenView();
    virtual ~GameScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void tickEvent();
    void spawnCactus(int x1, int x2);
    void spawnBird(int x1, int x2, int y1, int y2);
    void updateObstacle(uint32_t currentTime);

protected:
    uint32_t tickCount = 0;
    uint32_t nextSpawnTime = 0;
    uint32_t ground_pos =  212;
    uint16_t volumeValue = 0;
    uint16_t lowJumpValue = 2800;
    uint16_t highJumpValue = 3500;
    uint16_t obstacleCount = 3;
    //Obstacle properties
    bool cactus_running = false;
    bool bird_flying = false;
    bool specialCactusPresent=false;
    int16_t speed_multiplier = 1;
    int16_t cactus_running_speed = 2;
    int16_t bird_speed = 4;
    int16_t obstacle_start_x = 250;
    int16_t obstacle_end_x =  350;
    int16_t obstacle_start_y = 100;
    int16_t obstacle_end_y =  150;
    int16_t obstacleType = 0; // 0 : only normal cactus, 1: special cactus and normal cactus, 2: only bird

    // Define character properties
    int16_t y_velocity = 0 ;
    int16_t low_jump_velocity = 13;
    int16_t high_jump_velocity = 17;
    int16_t lives = 3;
    int16_t hit_cooldown=0;
    int16_t hit_cooldown_limit = 7;
    int16_t dinosaurHitBox[4] = {16,16, 20, 20}; // start_x, start_y , width , height of hitbox
    int16_t flickering_duration =6;
    int16_t flickering = 7;
    // Define character states
    uint8_t animation_state = 0; // walk = 0, jump = 1, fall = 3;
    const uint8_t walkState =0;
    const uint8_t jumpState =1;
    const uint8_t fallState =2;

    uint8_t animation_frame_num[3] = {6,3,3};
	uint8_t animation_frame = 0;
	// Define character animation
		//Walk animation-------------------------------------------------------------
	uint16_t DinosaurWalk[6] = {BITMAP_MOVE_1_ID,BITMAP_MOVE_2_ID,BITMAP_MOVE_3_ID,BITMAP_MOVE_4_ID,BITMAP_MOVE_5_ID,BITMAP_MOVE_6_ID };
		//---------------------------------------------------------------------------
		// Jump animation------------------------------------------------------------
	uint16_t DinosaurJump[3] = {BITMAP_JUMP_1_ID,BITMAP_JUMP_2_ID,BITMAP_JUMP_3_ID};
		// Fall animation------------------------------------------------------------
	uint16_t DinosaurFall[3] = {BITMAP_JUMP_3_ID,BITMAP_JUMP_2_ID,BITMAP_JUMP_1_ID};

	// Define UI elements:
	uint16_t  HealthFull = BITMAP_HEART_FULL_ID;
	uint16_t  HealthLost = BITMAP_HEART_LOST_ID;
	uint16_t  level1_bg = BITMAP_DESERT_BACKGROUND_ID;
	uint16_t  level2_bg = BITMAP_FOREST_1_ID;
	uint16_t  level3_bg =  BITMAP_OASIS_ID;
};

#endif // GAMESCREENVIEW_HPP
