#pragma once

#ifdef PE_PLATFORM_WINDOWS

#else
#	error Only Windows platform is supported.
#endif

#ifdef PE_ENABLE_ASSERTS
#	define CLIENT_ASSERT(x, ...) {if(!(x))} {LogError("Assertion failed: %s", __VA_ARGS__); __debugbreak();}}
#	define ENGINE_ASSERT(x, ...) {if(!(x))} {LogEngineError("Assertion failed: %s", __VA_ARGS__); __debugbreak();}}
#else
#	define CLIENT_ASSERT(x, ...)
#	define ENGINE_ASSERT(x, ...)
#endif

#define BIT(x)(1 << x)