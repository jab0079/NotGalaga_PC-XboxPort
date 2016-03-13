
#define GAME_SPEED 10000

// ***** Backgrond Images *****
#define BG_WIDTH		640
#define BG_HEIGHT		960
#define NUM_BACKGROUNDS	2
#define LINE_WIDTH	1

// Title Screen
#define TITLE_NUM_SPRITES	1

// Space (in-game)
#define SPACE_NUM_SPRITES	2
#define SCROLL_RATE			0.10f

// ***** Sprite Images *****

// Player
#define PLAYER_WIDTH		48
#define PLAYER_HEIGHT		48
#define PLAYER_NUM_SPRITES	1
#define MOVE_FORCE			3
#define STARTING_LIVES		3
#define MAX_PLAYER_LIVES	5
#define PLAYER_LIVES		10
#define PLAYER_BULLETTIME	3.0f
#define PLAYER_BULLETTIME_RATIO 0.1f
#define INVINCIBILITY_TIME	1000

// Weapons
#define WEAPON_DURATION_MS	20000	
#define SHOT_FORCE			6
#define QUICK_SHOT_FORCE	8
#define SPREAD_SHOT_FORCE	4
#define SPREAD_SHOT_ANGLE	5
#define HOMING_ABILITY		0.1f
#define HOMING_FORCE		2
#define NORMAL_SHOT_RATE	250
#define QUICK_SHOT_RATE		100
#define SPREAD_SHOT_RATE	350
#define HOMING_SHOT_RATE	220

#define WEAPON_DROP_WIDTH		16
#define WEAPON_DROP_HEIGHT		64
#define WEAPON_DROP_NUM_SPRITES 1
#define MAX_WEAPON_DROPS		5
#define WEAPON_DROP_SPEED		0.5f

// Enemies
#define ENEMY_WIDTH					42
#define ENEMY_HEIGHT				38
#define ENEMY_NUM_SPRITES			1
#define ENEMY_BASE_HP				1
#define ENEMY_SHIP_HP				5

#define ENEMY_MAX_ENEMIES			30
#define ENEMY_RESPAWN_TIME_MILLISEC 500
#define ENEMY_SHOOT_TIME_MILLISEC	600
#define BASE_ENEMIES_PER_WAVE		5
#define SHIP_SPAWN					15
#define WAVE_DELAY_MS				5000

// FallTrajectory
#define FALL_TRAJECTORY_SPEED 100.0f

// SideTrajectory
#define SIDE_TRAJECTORY_SPEED 100.0f

// Projectiles
#define MISSILE_WIDTH		12
#define MISSILE_HEIGHT		20
#define MISSILE_NUM_SPRITES 1
#define MAX_NUM_MISSILES	1000

// Explosions
#define EXPLOSION_PLAYER_WIDTH			80
#define EXPLOSION_PLAYER_HEIGHT			72
#define EXPLOSION_ENEMY_WIDTH			56
#define EXPLOSION_ENEMY_HEIGHT			56
#define EXPLOSION_NUM_SPRITES			4
#define MAX_EXPLOSIONS					ENEMY_MAX_ENEMIES+1
#define EXPLOSION_RATE_MS				100

// Scoring Points
#define POINTS_WIDTH		36
#define POINTS_HEIGHT		16
#define POINTS_NUM_SPRITES	8
#define POINTS_RATE_MS		500

// Labels

#define GAMEOVER_WIDTH		500
#define GAMEOVER_HEIGHT		140

#define HIGH_SCORE_WIDTH	236
#define HIGH_SCORE_HEIGHT	16
#define HIGH_SCORE_X		-HIGH_SCORE_WIDTH / 2.0f
#define HIGH_SCORE_Y		(BG_HEIGHT / 2.0f) - (3.0f * HIGH_SCORE_HEIGHT)
#define NUMBER_WIDTH		24
#define NUMBER_HEIGHT		24
#define NUMBER_NUM_SPRITES	10

// Scoreboard
#define DIGIT_SEPARATION 24
#define SCOREBOARD_HORIZONTAL_WIDTH 16
#define SCOREBOARD_HORIZONTAL_HEIGHT 4
#define SCOREBOARD_VERTICAL_WIDTH 4
#define SCOREBOARD_VERTICAL_HEIGHT 16
#define NUM_LINES 63
#define SCOREBOARD_X	(BG_WIDTH / 3.0f)
#define SCOREBOARD_Y	(BG_HEIGHT / 2.0f) - 4 * (SCOREBOARD_VERTICAL_HEIGHT / 2.0f)

#define LEVEL_X				(BG_WIDTH / 2.0f) - NUMBER_WIDTH
#define LEVEL_Y				-(BG_HEIGHT / 2.0f) + (2.0f * NUMBER_HEIGHT)
#define MAX_LEVEL_DIGITS	3

#ifdef _XBOX
#define ENEMY_SPRITE_GREEN	resource_ENEMY_SPRITE_GREEN_OFFSET
#define ENEMY_SPRITE_PURPLE resource_ENEMY_SPRITE_PURPLE_OFFSET
#define ENEMY_SPRITE_RED	resource_ENEMY_SPRITE_RED_OFFSET
#define ENEMY_SPRITE_YELLOW resource_ENEMY_SPRITE_YELLOW_OFFSET
#define ENEMY_SPRITE_SHIP	resource_ENEMY_SPRITE_SHIP_OFFSET
#define FAST_SHOT_WEAPON	resource_FAST_SHOT_WEAPON_OFFSET
#define SPREAD_SHOT_WEAPON	resource_SPREAD_SHOT_WEAPON_OFFSET
#define HOMING_SHOT_WEAPON	resource_HOMING_SHOT_WEAPON_OFFSET
#define MISSILE_SPRITE		resource_MISSILE_SPRITE_OFFSET
#define EXPLOSION_PLAYER_SPRITE resource_EXPLOSION_PLAYER_SPRITE_OFFSET
#define EXPLOSION_ENEMY_SPRITE	resource_EXPLOSION_ENEMY_SPRITE_OFFSET
#define POINTS_SPRITES		resource_POINTS_SPRITES_OFFSET
#define GAMEOVER_SPRITE		resource_GAMEOVER_SPRITE_OFFSET
#define HIGH_SCORE_SPRITE	resource_HIGH_SCORE_SPRITE_OFFSET
#define HORIZONTAL_LINE resource_HORIZONTAL_LINE_OFFSET
#define VERTICAL_LINE	resource_VERTICAL_LINE_OFFSET
#define BG_TITLE_SCREEN		resource_BG_TITLE_SCREEN_OFFSET
#define BG_SPACE			resource_BG_SPACE_OFFSET
#define BG_SLOW_SPACE       resource_BG_SLOW_SPACE_OFFSET
#define PLAYER_SPRITE	resource_PLAYER_SPRITE_OFFSET
#define NUMBER_SPRITES		resource_NUMBER_SPRITES_OFFSET

#define PLAYER_SFX_FIRE	"D:\\Media\\sfx\\fire.wma"
#define PLAYER_SFX_HIT	"D:\\Media\\sfx\\hit.wma"
#define START_SFX			"D:\\Media\\sfx\\start.wma"
#define ENEMY_SFX_KILL		"D:\\Media\\sfx\\kill.wma"

#else
#define ENEMY_SPRITE_GREEN	"assets/enemy_green.png"
#define ENEMY_SPRITE_PURPLE "assets/enemy_purple.png"
#define ENEMY_SPRITE_RED	"assets/enemy_red.png"
#define ENEMY_SPRITE_YELLOW "assets/enemy_yellow.png"
#define ENEMY_SPRITE_SHIP	"assets/enemy_ship.png"
#define FAST_SHOT_WEAPON	"assets/sprites/weapons/fast_weapon.png"
#define SPREAD_SHOT_WEAPON	"assets/sprites/weapons/spread_weapon.png"
#define HOMING_SHOT_WEAPON	"assets/sprites/weapons/homing_weapon.png"
#define MISSILE_SPRITE		"assets/missile.png"
#define EXPLOSION_PLAYER_SPRITE "assets/explosion_player.png"
#define EXPLOSION_ENEMY_SPRITE	"assets/explosion_enemy.png"
#define POINTS_SPRITES		"assets/scores.png"
#define GAMEOVER_SPRITE		"assets/gameover.png"
#define HIGH_SCORE_SPRITE	"assets/label.png"
#define HORIZONTAL_LINE "assets/sprites/lines/horizontal_line.png"
#define VERTICAL_LINE	"assets/sprites/lines/vertical_line.png"
#define BG_TITLE_SCREEN		"assets/title_screen.png"
#define BG_SPACE			"assets/background2.png"
#define BG_SLOW_SPACE       "assets/background3.png"
#define PLAYER_SPRITE	"assets/player.png"
#define NUMBER_SPRITES		"assets/numbers.png"


#define PLAYER_SFX_FIRE	".\\assets\\sfx\\fire.wma"
#define PLAYER_SFX_HIT	".\\assets\\sfx\\hit.wma"
#define START_SFX			".\\assets\\sfx\\start.wma"
#define ENEMY_SFX_KILL		".\\assets\\sfx\\kill.wma"
#endif