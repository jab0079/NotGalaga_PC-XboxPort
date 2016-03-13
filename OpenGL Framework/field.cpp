#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "jsy/jsy.h"
#include "collInfo.h"
#include "object.h"
#include "field.h"
#include "game.h"
#include "gamedefs.h"


void FieldC::moveUp()
{
	int y;
	y=5;
}
FieldC::FieldC(float_t x, float_t y, uint32_t width, uint32_t height, uint32_t initColor, uint32_t initState)
{
    mEnabled = true;
    mFieldColor = initColor;
	mWidth = width;
	mHeight = height;
	mPosition.x = x;
	mPosition.y = y;
	activeState = initState;
};

FieldC::~FieldC()
{
};

void FieldC::update(uint32_t milliseconds)
{
};

void FieldC::render()
{
	float_t left = mPosition.x - (float_t)mWidth/1.0f;
	float_t right = mPosition.x + (float_t)mWidth/1.0f;
	float_t bottom = mPosition.y - (float_t)mHeight/1.0f;
	float_t top = mPosition.y + (float_t)mHeight/1.0f;

	char8_t r = (char8_t)(mFieldColor>>16 & 0xFF);
	char8_t g = (char8_t)(mFieldColor>>8 & 0xFF);
	char8_t b = (char8_t)(mFieldColor>>0 & 0xFF);

    JsyGDrawLine(CGame::GetInstance()->GetJsyGHandle(), left,top,right,top,r,g,b, LINE_WIDTH);
    JsyGDrawLine(CGame::GetInstance()->GetJsyGHandle(), right,top,right,bottom,r,g,b, LINE_WIDTH);
    JsyGDrawLine(CGame::GetInstance()->GetJsyGHandle(), right,bottom,left,bottom,r,g,b, LINE_WIDTH);
    JsyGDrawLine(CGame::GetInstance()->GetJsyGHandle(), left,bottom,left,top,r,g,b, LINE_WIDTH);
};