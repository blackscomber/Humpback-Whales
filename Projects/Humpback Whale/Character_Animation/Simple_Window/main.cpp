//////////////////////////////////////////////////////////////
// Our Application Framework								//
// Written by: Claire Lee, 2012							//
//////////////////////////////////////////////////////////////

#include <windows.h>
#include <d3dx9.h>
#include <fstream>


using namespace std;

// Global Variables
IDirect3DDevice9*	g_pDevice = NULL;
ID3DXSprite*		g_pSprite = NULL;
ID3DXFont*			g_pFont = NULL;
ID3DXEffect*		g_pEffect = NULL;
ofstream			g_debug("debug.txt");

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool KeyDown(int vk_code){return (GetAsyncKeyState(vk_code) & 0x8000) ? true : false;}
bool KeyUp(int vk_code){return (GetAsyncKeyState(vk_code) & 0x8000) ? false : true;}

class Application
{
public:
	Application();
	~Application();
	HRESULT Init(HINSTANCE hInstance, bool windowed);
	void Update(float deltatime);
	void Render();
	void CleanUp();
	void Quit();

	void DeviceLost();
	void DeviceGained();

private:
	HWND m_hMainWindow;
	D3DPRESENT_PARAMETERS m_present;
	bool m_bDeviceLost;
	float m_fAngle;
	// mesh variable

	
};

// The Window procedure function
// This function handles all incoming events to the window, and the user can specify 
// what should happend at each event.
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// User specified events
	switch( msg )
	{
	case WM_CREATE:
		// Do some window initalization here
		break;

	case WM_DESTROY:
		// Do some window cleanup here
		PostQuitMessage(0);
		break;
	}

	// Default events
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//WinMain - The application entry point
// It is in this function that the entire application exists and runs its course.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	// Create a new Application object
	Application app;

	// Initialize it
	if(FAILED(app.Init(hInstance, true)))
		return 0;

	// Start the windows message loop
	MSG msg;
	memset(&msg, 0, sizeof(MSG));

	// Keep track of the time
	DWORD startTime = GetTickCount();

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			// If there's a message, deal with it and send it onword
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else	// Otherwise update the game
		{
			// Clacualte the delta time
			DWORD t = GetTickCount();
			float deltaTime = (t - startTime) * 0.001f;

			// Update the application
			//app.Update(deltaTime);

			// Render the application
			//app.Render();

			startTime = t;
		}
	}

	// Release all resources
	//app.CleanUp();

	//... and Quit!
	return (int)msg.wParam;

}

Application::Application()
{
	m_fAngle = 0.0f;
}

Application::~Application()
{
	if(g_debug.good())
	{
		g_debug.close();
	}
}

HRESULT Application::Init(HINSTANCE hInstance, bool windowed)
{
	g_debug << "Application Started \n";

	//Create Window Class
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= (WNDPROC)WndProc;
	wc.hInstance		= hInstance;
	wc.lpszClassName	= "D3DWND";

	RECT rc = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false); // without menu

	//Register Class and Create new Window
	RegisterClass(&wc);

	m_hMainWindow = CreateWindow(	"D3DWND",	//Window class to use
									"Character Animation with Direct3D", //Title
									WS_OVERLAPPEDWINDOW,	//Style
									0,						//X
									0,						//Y
									rc.right - rc.left,		//Width
									rc.bottom - rc.top,		//Height
									NULL,					//Parent Window
									NULL,					//Menu
									hInstance,				//Application Instance
									0);						//Param

	SetCursor(NULL);
	ShowWindow(m_hMainWindow, SW_SHOW); // It sets this window's show state
	UpdateWindow(m_hMainWindow);

	return S_OK;
}

void Application::Quit()
{
	DestroyWindow(m_hMainWindow);
	PostQuitMessage(0);
}