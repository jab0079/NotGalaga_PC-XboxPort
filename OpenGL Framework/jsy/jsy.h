#ifndef _JSY_H_
#define _JSY_H_

#ifdef _XBOX
#include <XBApp.h>
#include <XBFont.h>
#include <XBMesh.h>
#include <XBUtil.h>
#include <XBResource.h>
#include <xgraphics.h>
#include "Resource.h"
#else
#include <Windows.h>
#endif
#include "types.h"

// This is JSY virtual platform library for PC and XBOX

// Error codes for JSY functions
typedef enum JSY_ERROR_S {
    JSY_SUCCEED = 0,
    JSY_ERROR_OOM = -100,
    JSY_ERROR_INITED = -101,
    JSY_ERROR_INTERNAL = -102,
} JSY_ERROR_T;

///////////////////////
// Init library
typedef bool(*AppLoop)();
#ifdef _XBOX
JSY_ERROR_T JsyAppInit_XBOX(AppLoop func);

#define nullptr 0

#else
JSY_ERROR_T JsyAppInit_Win(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int width, int height, AppLoop func);
#endif

JSY_ERROR_T JsyAppClose();

///////////////////////
// Audio APIs

typedef void * JSYAudioHandle;

JSY_ERROR_T JsyAudioOpen(JSYAudioHandle * pHandle);

JSY_ERROR_T JsyAudioClose(JSYAudioHandle handle);

uint32_t JsyAudioLoad(JSYAudioHandle handle, const char8_t * fileName);

JSY_ERROR_T JsyAudioPlaySound(JSYAudioHandle handle, uint32_t resourceId);

///////////////////////
// Platform APIs

uint32_t JsyGetTickCount();

///////////////////////
// Input APIs

typedef enum JSY_INPUT_S {
    JSY_INPUT_UP = 100,
    JSY_INPUT_DOWN = 101,
    JSY_INPUT_LEFT = 102,
    JSY_INPUT_RIGHT = 103,
    JSY_INPUT_A = 104,
    JSY_INPUT_B = 105,
    JSY_INPUT_START = 106,
    JSY_INPUT_BACK = 107,
} JSY_INPUT_T;

typedef void * JSYInputHandle;

JSY_ERROR_T JsyInputOpen(JSYInputHandle * pHandle);

JSY_ERROR_T JsyInputClose(JSYInputHandle handle);

JSY_ERROR_T JsyInputGetInput(JSYInputHandle handle, JSY_INPUT_T input, float_t * value);

///////////////////////
// Simple Graphic APIs

// The Graphic handle
typedef void * JSYGHandle;

// Invalid handle
#define JSYG_INVALID_HANDLE 0

JSY_ERROR_T JsyGOpen(JSYGHandle * pHandle, int32_t colorDepth);

JSY_ERROR_T JsyGClose(JSYGHandle handle);

#ifdef _XBOX
JSY_ERROR_T JStGLoadTexture(JSYGHandle handle, uint32_t fileID, uint32_t * pTextureId);
#else
JSY_ERROR_T JStGLoadTexture(JSYGHandle handle, const char * fileName, uint32_t * pTextureId);
#endif

JSY_ERROR_T JsyGClear(JSYGHandle handle);

JSY_ERROR_T JsyGSwapBuffer(JSYGHandle handle);

JSY_ERROR_T JsyGDrawBackGround(JSYGHandle handle, uint32_t textureId, float_t width, float_t height,
    float_t yTexCoord, uint32_t numSprites);

JSY_ERROR_T JsyGDrawLine(JSYGHandle handle, float_t startX, float_t startY, float_t endX, float_t endY,
    char8_t r, char8_t g, char8_t b, float_t lineWidth);

JSY_ERROR_T JsyGDrawSprite(JSYGHandle handle, uint32_t textureId, bool8_t isFlipped, float_t xPosLeft, float_t xPosRight,
    float_t yPosTop, float_t yPosBot, float_t xTexCoord, uint32_t numSprites);

#endif // include guard