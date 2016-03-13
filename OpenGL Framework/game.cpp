#define GAME_CPP
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "jsy/jsy.h"
#include "gamedefs.h"
#include "collInfo.h"
#include "object.h"
#include "Sprite.h"
#include "field.h"
#include "random.h"
#include "SpriteManager.h"
#include "FieldManager.h"
#include "GameManager.h"
#include "game.h"

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";
CGame* CGame::sInstance=NULL;

CGame::CGame(){
	//move from .h
	jsyGHandle = NULL;
    jsyInputHandle = NULL;
    jsyAudioHandle = NULL;
	mQuit = false;
    mRatio = 1.0f;
}

void CGame::init()
{
    JsyGOpen(&jsyGHandle, mBitsPerPixel);
    JsyInputOpen(&jsyInputHandle);
    JsyAudioOpen(&jsyAudioHandle);

	SpriteManager::CreateInstance();
	FieldManagerC::CreateInstance();
	GameManager::CreateInstance();

	GameManager::GetInstance()->init(BG_WIDTH, BG_HEIGHT);
	FieldManagerC::GetInstance()->init();
	SpriteManager::GetInstance()->init();
}

void CGame::UpdateFrame(uint32_t milliseconds)
{
    uint32_t scaledMillseconds = mRatio * (float_t)milliseconds;

    float_t quit;
    JsyInputGetInput(jsyInputHandle, JSY_INPUT_BACK, &quit);
    if (quit > 0.0f)
    {
        mQuit = true;
    }

	GameManager::GetInstance()->update(scaledMillseconds);
	SpriteManager::GetInstance()->updateSprites(scaledMillseconds);
}

void CGame::DrawScene(void)											
{
    JsyGClear(jsyGHandle);
	GameManager::GetInstance()->render();
	FieldManagerC::GetInstance()->renderField();
	SpriteManager::GetInstance()->renderSprites();
    JsyGSwapBuffer(jsyGHandle);
}

CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}

void CGame::shutdown()
{
	SpriteManager::GetInstance()->shutdown();
	FieldManagerC::GetInstance()->shutdown();
	GameManager::GetInstance()->shutdown();
}

void CGame::DestroyGame(void)
{
	JsyAudioClose(jsyAudioHandle);
	JsyInputClose(jsyInputHandle);
	JsyGClose(jsyGHandle);

	delete SpriteManager::GetInstance();
	delete FieldManagerC::GetInstance();	
	delete GameManager::GetInstance();	
}
