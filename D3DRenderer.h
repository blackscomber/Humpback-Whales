#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif

#include <d3dx9.h>
#include <string>

#include "sat_utility.h"
#include "mesh.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "DxErr.lib")



class __declspec(novtable) D3DRenderer
{
public:
	void StaticConstructor();
	void StaticDestructor();

	HRESULT CreateDevice(HWND hWnd, int Width, int Height);
	void DestroyDevice();
	//void CreateSurface(BYTE** BufOut, size_t& SizeOut, int& width, int& height);

	void Update(float deltatime);
	void Render();
	void Cleanup();
	//void Quit();

	void DeviceLost();
	void DeviceGained();

	const D3DXVECTOR3 & GetCameraVec() { return m_vecCameraLocation; }

private:
	HWND m_hMainWindow;
	D3DPRESENT_PARAMETERS m_present;

	bool m_bDeviceLost;
	Mesh m_mesh;	
	float m_fAngle;
	UINT WINDOW_WIDTH;
	UINT WINDOW_HEIGHT;

	ID3DXFont* p_mD3DFont;

	D3DXVECTOR3 m_vecCameraLocation;

};

// Global Variables
__declspec(selectany) D3DRenderer g_Renderer;
__declspec(selectany) IDirect3DDevice9* g_pDevice = NULL;
__declspec(selectany) ID3DXSprite*		g_pSprite = NULL;

__declspec(selectany) ID3DXFont*		g_pFont	= NULL;
__declspec(selectany) ID3DXEffect*		g_pEffect = NULL;

inline void GetCurrentWorldMatrix(D3DMATRIX* pOut) { g_pDevice->GetTransform(D3DTS_WORLD, pOut); }
inline void GetCurrentViewMatrix(D3DMATRIX* pOut) { g_pDevice->GetTransform(D3DTS_VIEW, pOut); }
inline void GetCurrentProjectionMatrix(D3DMATRIX* pOut) { g_pDevice->GetTransform(D3DTS_PROJECTION, pOut); }