#pragma once

#include <DxErr.h>

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)														\
		{                                                           \
			HRESULT hr = (x);                                       \
			if(FAILED(hr))                                          \
			{                                                       \
				DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true);  \
			}                                                       \
		}
#endif
#else
#ifndef HR
#define HR(x) (x)
#endif
#endif