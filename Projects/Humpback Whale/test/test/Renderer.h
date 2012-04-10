#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif

#include <d3dx9.h>
#include <string>
#include "sat_utility.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "DxErr.lib")

class __declspec(novtable) Renderer
{
public:
	void StaticConstructor();
	void StaticDestructor();
	void CreateDevice(HWND Wnd, int Width, int Height);
	void DestroyDevice();
	void DoRender();
	void CreateSurface(BYTE** BufOut, size_t& SizeOut, int& width, int& height);

private:
	ID3DXMesh* m_PreviewMesh;
	D3DPRESENT_PARAMETERS m_PresentParams;
	int m_WindowWidth;
	int m_WindowHeight;
};

__declspec(selectany) Renderer theRenderer;
__declspec(selectany) IDirect3DDevice9* theDevice = NULL;