#pragma once

#include <sstream>
#include <DXErr.h>
#include <fstream>



using namespace std;
__declspec(selectany) ofstream			g_debug("debug.txt");

//Only support assertions in debug builds
#ifdef _DEBUG
# include "assert.h"
#else
# define assert(x) { }
#endif

#ifndef HR
#if defined(DEBUG) || defined(_DEBUG)
#define HR(x) {\
	HRESULT hr = (x);\
	if( FAILED(hr) )\
	{\
		std::wostringstream os;\
		os << DXGetErrorString(hr) << " - " << DXGetErrorDescription(hr);\
		::MessageBox(0, os.str().c_str(), L"D3D Failed", 0);\
		throw hr;\
	}\
}
#else
#define	HR(x) x
#endif
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if(x) { delete (x); (x) = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) { if(x) { delete [] (x); (x) = NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }
#endif


