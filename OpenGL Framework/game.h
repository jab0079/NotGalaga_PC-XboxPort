#ifndef _GAME_H_
#define _GAME_H_

#include "jsy\jsy.h"

class CGame
{
public:
	const char8_t *GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene();
	void UpdateFrame(uint32_t milliseconds);
	void DestroyGame();
	void init();
	void shutdown();

    JSYGHandle GetJsyGHandle() {
        return jsyGHandle;
    };

    JSYInputHandle GetJsyInputHandle() {
        return jsyInputHandle;
    };

    JSYInputHandle GetJsyAudioHandle() {
        return jsyAudioHandle;
    };

    bool GetQuit() { return mQuit; };
    float_t getFrameRatio() { return mRatio; }
    void setFrameRatio(float_t ratio) { mRatio = ratio; }

	static const uint32_t mBitsPerPixel = 32;
private:
	static const char8_t mGameTitle[20];
	static CGame *sInstance;

    JSYGHandle jsyGHandle;
    JSYInputHandle jsyInputHandle;
    JSYAudioHandle jsyAudioHandle;

    float_t mRatio;

    bool mQuit;

	CGame();
};

#endif