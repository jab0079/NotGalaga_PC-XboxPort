#include "jsy/jsy.h"
#include "gamedefs.h"
#include "game.h"

bool inited = false;
uint32_t lastTickCount;
bool Initialize()					// Any OpenGL Initialization Goes Here
{
    CGame::CreateInstance();
    CGame::GetInstance()->init();
    lastTickCount = JsyGetTickCount();
    return true;
}

bool gameLoop() {
    if (!inited) {
        Initialize();
        inited = true;
    }
    else {
        uint32_t tickCount = JsyGetTickCount();				// Get The Tick Count
        CGame::GetInstance()->UpdateFrame(tickCount - lastTickCount);	// Update The Counter
        lastTickCount = tickCount;			// Set Last Count To Current Count
        CGame::GetInstance()->DrawScene();			// Draw Our Scene
    }

    return !CGame::GetInstance()->GetQuit();
}

#ifdef _XBOX
//-----------------------------------------------------------------------------
// Name: main()
// Desc: Entry point to the program.
//-----------------------------------------------------------------------------
VOID __cdecl main()
{
    //CXBoxSample xbApp;
    //if( FAILED( xbApp.Create() ) )
    //    return;
    //xbApp.Run();
	JsyAppInit_XBOX(gameLoop);

    CGame::GetInstance()->shutdown();										// User Defined DeInitialization
    CGame::GetInstance()->DestroyGame();

    JsyAppClose();
}

#else
// Program Entry (WinMain)
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    JsyAppInit_Win(hInstance, hPrevInstance, lpCmdLine, nCmdShow, BG_WIDTH, BG_HEIGHT, gameLoop);

    CGame::GetInstance()->shutdown();										// User Defined DeInitialization
    CGame::GetInstance()->DestroyGame();

    JsyAppClose();

	return 0;
}
#endif

