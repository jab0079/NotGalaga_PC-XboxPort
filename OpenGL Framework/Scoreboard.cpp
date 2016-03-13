#include "Scoreboard.h"
#include "SpriteManager.h"


Scoreboard::Scoreboard()
{
	//moved from .h
	for(int i = 0; i < NUM_LINES; i++){
		lines[i] = nullptr;
	}

	label = new Sprite(HIGH_SCORE_X, HIGH_SCORE_Y, HIGH_SCORE_WIDTH, HIGH_SCORE_HEIGHT, SpriteManager::LABEL);
	score = 0;

	for (int32_t i = 0; i < NUM_LINES / 7; i++) {
		lines[0 + i * 7] = new Sprite(SCOREBOARD_X + SCOREBOARD_HORIZONTAL_WIDTH / 2 - DIGIT_SEPARATION * i + 2, SCOREBOARD_Y - SCOREBOARD_HORIZONTAL_HEIGHT / 2, SCOREBOARD_HORIZONTAL_WIDTH, SCOREBOARD_HORIZONTAL_HEIGHT, SpriteManager::HLINE);
		lines[1 + i * 7] = new Sprite(SCOREBOARD_X + SCOREBOARD_VERTICAL_WIDTH / 2 - DIGIT_SEPARATION * i, SCOREBOARD_Y - SCOREBOARD_VERTICAL_HEIGHT / 2, SCOREBOARD_VERTICAL_WIDTH, SCOREBOARD_VERTICAL_HEIGHT, SpriteManager::VLINE);
		lines[2 + i * 7] = new Sprite(SCOREBOARD_X + SCOREBOARD_VERTICAL_WIDTH / 2 + SCOREBOARD_HORIZONTAL_WIDTH - DIGIT_SEPARATION * i, SCOREBOARD_Y - SCOREBOARD_VERTICAL_HEIGHT / 2, SCOREBOARD_VERTICAL_WIDTH, SCOREBOARD_VERTICAL_HEIGHT, SpriteManager::VLINE);
		lines[3 + i * 7] = new Sprite(SCOREBOARD_X + SCOREBOARD_HORIZONTAL_WIDTH / 2 - DIGIT_SEPARATION * i + 2, SCOREBOARD_Y - SCOREBOARD_HORIZONTAL_HEIGHT / 2 - SCOREBOARD_VERTICAL_HEIGHT, SCOREBOARD_HORIZONTAL_WIDTH, SCOREBOARD_HORIZONTAL_HEIGHT, SpriteManager::HLINE);
		lines[4 + i * 7] = new Sprite(SCOREBOARD_X + SCOREBOARD_VERTICAL_WIDTH / 2 - DIGIT_SEPARATION * i, SCOREBOARD_Y - SCOREBOARD_VERTICAL_HEIGHT / 2 - SCOREBOARD_VERTICAL_HEIGHT, SCOREBOARD_VERTICAL_WIDTH, SCOREBOARD_VERTICAL_HEIGHT, SpriteManager::VLINE);
		lines[5 + i * 7] = new Sprite(SCOREBOARD_X + SCOREBOARD_VERTICAL_WIDTH / 2 + SCOREBOARD_HORIZONTAL_WIDTH - DIGIT_SEPARATION * i, SCOREBOARD_Y - SCOREBOARD_VERTICAL_HEIGHT / 2 - SCOREBOARD_VERTICAL_HEIGHT, SCOREBOARD_VERTICAL_WIDTH, SCOREBOARD_VERTICAL_HEIGHT, SpriteManager::VLINE);
		lines[6 + i * 7] = new Sprite(SCOREBOARD_X + SCOREBOARD_HORIZONTAL_WIDTH / 2 - DIGIT_SEPARATION * i + 2, SCOREBOARD_Y - SCOREBOARD_HORIZONTAL_HEIGHT / 2 - SCOREBOARD_VERTICAL_HEIGHT * 2, SCOREBOARD_HORIZONTAL_WIDTH, SCOREBOARD_HORIZONTAL_HEIGHT, SpriteManager::HLINE);
	}	
}

Scoreboard::~Scoreboard()
{
	for (int32_t i = 0; i < NUM_LINES; i++)
	{
		delete lines[i];
	}

	delete label;
}

void Scoreboard::Reset()
{
	score = 0;
	for (int32_t i = 0; i < NUM_LINES; i++)
	{
		lines[i]->disable();
	}
}

void Scoreboard::Render() {
	for (int32_t i = 0, scoreValue = score; scoreValue >= 0 && i < NUM_LINES / 7; ++i, scoreValue /= 16) {
		int32_t digit = scoreValue % 16;
		switch (digit) {
		case 0x0000:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->disable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->enable();
			break;
		case 0x0001:
			lines[0 + i * 7]->disable();
			lines[1 + i * 7]->disable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->disable();
			lines[4 + i * 7]->disable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->disable();
		case 0x0002:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->disable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->disable();
			lines[6 + i * 7]->enable();
			break;
		case 0x0003:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->disable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->disable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->enable();
			break;
		case 0x0004:
			lines[0 + i * 7]->disable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->disable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->disable();
			break;
		case 0x0005:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->disable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->disable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->enable();
			break;
		case 0x0006:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->disable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->enable();
			break;
		case 0x0007:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->disable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->disable();
			lines[4 + i * 7]->disable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->disable();
			break;
		case 0x0008:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->enable();
			break;
		case 0x0009:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->disable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->disable();
			break;
		case 0x000a:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->disable();
			break;
		case 0x000b:
			lines[0 + i * 7]->disable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->disable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->enable();
			break;
		case 0x000c:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->disable();
			lines[3 + i * 7]->disable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->disable();
			lines[6 + i * 7]->enable();
			break;
		case 0x000d:
			lines[0 + i * 7]->disable();
			lines[1 + i * 7]->disable();
			lines[2 + i * 7]->enable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->enable();
			lines[6 + i * 7]->enable();
			break;
		case 0x000e:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->disable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->disable();
			lines[6 + i * 7]->enable();
			break;
		case 0x000f:
			lines[0 + i * 7]->enable();
			lines[1 + i * 7]->enable();
			lines[2 + i * 7]->disable();
			lines[3 + i * 7]->enable();
			lines[4 + i * 7]->enable();
			lines[5 + i * 7]->disable();
			lines[6 + i * 7]->disable();
			break;
		default:
			lines[0 + i * 7]->disable();
			lines[1 + i * 7]->disable();
			lines[2 + i * 7]->disable();
			lines[3 + i * 7]->disable();
			lines[4 + i * 7]->disable();
			lines[5 + i * 7]->disable();
			lines[6 + i * 7]->disable();
			break;
		}
	}
	for (int i = 0; i < NUM_LINES; i++) {
		lines[i]->render();
	}
	label->render();
}