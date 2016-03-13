#ifndef _JSY_INTERNAL_H_
#define _JSY_INTERNAL_H_

#ifdef _XBOX
#include <stdlib.h>
#include <string.h>
#include <xtl.h>
#include <xgraphics.h>
#include <DSound.h>
#include <dmusicfx.h>

#include "Resource.h"
#else
// Win32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#endif
#include "soil.h"
#include "fmod/fmod.hpp"
#include "jsy.h"

#define NULL 0

#ifdef _XBOX
#else

typedef struct {									// Contains Information Vital To Applications
    HINSTANCE		hInstance;						// Application Instance
    const char*		className;						// Application ClassName
} Application;										// Application

typedef struct {									// Window Creation Info
    Application 		application;				// Application Structure
    int					width;						// Width
    int					height;						// Height
} GL_WindowInit;									// GL_WindowInit

typedef struct {									// Contains Information Vital To A Window
    HWND				hWnd;						// Window Handle
    HDC					hDC;						// Device Context
    HGLRC				hRC;						// Rendering Context
    GL_WindowInit		init;						// Window Init
    BOOL				isVisible;					// Window Visible?
    DWORD				lastTickCount;				// Tick Counter
} GL_Window;// GL_Window

#endif

///////////////
// Input APIs
typedef struct JsyInputInternalS {

} JsyInputInternalT;

typedef struct JsyTextureS
{
#ifdef _XBOX
	unsigned int textureId;
#else
    unsigned int soilTextureId; //Win32
#endif
} JsyTextureT;

///////////////
// Graphic APIs

#ifdef _XBOX

//#define XBOX_WIN_Width 960.0f
//#define XBOX_WIN_Height 720.0f
//
//#define RATIO 0.75f

struct PANELVERTEX
{
    FLOAT x, y, z;
    DWORD color;
    FLOAT u, v;
};

#define D3DFVF_PANELVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#endif


typedef struct JsyGInternalS {
#ifdef _XBOX
	uint32_t                width;
	uint32_t                height;
	float_t					ratio;
	LPDIRECT3D8             g_pD3D;          // Used to create the D3DDevice
	LPDIRECT3DDEVICE8       g_pd3dDevice;          // Our rendering device
	BYTE*                   g_pResourceSysMemData; // Sysmem data for the packed resource
	BYTE*                   g_pResourceVidMemData; // Vidmem data for the packed resource
	LPDIRECT3DTEXTURE8      g_pTexture[256]; // Our texture
	LPDIRECT3DVERTEXBUFFER8 g_pVertices;
#else
    GL_Window * window;
    JsyTextureT texture[256]; // FIXME: Now only support 256 texture, means 256 texture id
#endif
	uint32_t textureCnt;
} JsyGInternalT;

///////////////
// Audio APIs

// node of the sound resources list

#ifdef _XBOX
//
// the WMA decoder will work properly in async mode, with all formats
// only when using a look ahead size of at least 64k. We are using it synchronous mode
// but for good measure we still pass 64k
//

#define WMASTRM_LOOKAHEAD_SIZE (4096*16)

// Define the maximum amount of packets we will ever submit to the renderer
#define WMASTRM_PACKET_COUNT 8




// Define the source packet size:
// This value is hard-coded assuming a WMA file of stereo, 16bit resolution.  If
// this Value can by dynamically set based on the WMA format, keeping in mind
// that WMA needs enough buffer for a minimum of 2048 samples worth of PCM data
#define WMASTRM_SOURCE_PACKET_BYTES (2048*2*2)

DWORD CALLBACK WMAStreamCallback (
    LPVOID pContext,
    DWORD offset,
    DWORD num_bytes,
    LPVOID *ppData);
#endif

#ifdef _XBOX
typedef struct SoundStream_s {
	bool				isValid;
	XMediaObject*       m_pSourceFilter;                         // Source (wave file) filter
    IDirectSoundStream* m_pRenderFilter;                         // Render (DirectSoundStream) filter
    LPVOID              m_pvSourceBuffer;                        // Source filter data buffer
    LPVOID              m_pvRenderBuffer;                        // Render filter data buffer
	DWORD               m_adwPacketStatus[WMASTRM_PACKET_COUNT]; // Packet status array
} SoundStream_t;
#endif

typedef struct SoundNode_s {
    uint32_t id;
#ifdef _XBOX
	XMediaObject*       m_pSourceFilter;                         // Source (wave file) filter
    DWORD               m_dwFileLength;                          // File duration, in bytes
    DWORD               m_dwFileProgress;                        // File progress, in bytes
    PUCHAR              m_pFileBuffer;
    HANDLE              m_hFile;
	SoundStream_t*      streams[256];
	WAVEFORMATEX   wfxSourceFormat;
#else
    FMOD::Sound * sound;
#endif
    struct SoundNode_s * nextSound;
} SoundNode_t;


typedef struct JsyAudioInternalS {
#ifdef _XBOX
	LPDIRECTSOUND8 m_pDSound;
#else
    // FMOD stuff
    FMOD::System *soundSystem;
    FMOD::Channel * channels[32];
#endif
    // the sound resources list
    SoundNode_t * listSounds;
    SoundNode_t * tailSounds;
    uint32_t id_cnt;
} JsyAudioInternalT;

#ifdef _XBOX
HRESULT Process( SoundStream_t * handle);
#endif
#endif