#define FIELD_MANAGER_CPP

#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
 
#include "jsy/jsy.h"
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "stateManager.h"
#include "field.h"
#include "FieldManager.h"
#include "GameManager.h"

FieldManagerC* FieldManagerC::sInstance=NULL;


FieldManagerC *FieldManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new FieldManagerC();
	return sInstance;
}
void FieldManagerC::init()
{
	uint32_t width = GameManager::GetInstance()->getBackgroundWidth();
	uint32_t height = GameManager::GetInstance()->getBackgroundHeight();
	border = new FieldC(0.0f, 0.0f, width, height, 0x00FF0000, StateManagerC::SPACE);
}
FieldC *FieldManagerC::getFieldPtr()
{
	return border;
}
void FieldManagerC::renderField()
{
	border->render();
}
void FieldManagerC::shutdown()
{
	delete border;
}