#pragma once

#ifdef PE_PLATFORM_WINDOWS

#else
#	error Only Windows platform is supported.
#endif

#define BIT(x)(1 << x)