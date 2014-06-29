#pragma once

#ifdef DEDICATED
#	ifdef _WIN32
#		include <windows.h>
#		define Sys_LoadLibrary(f) (void*)LoadLibrary(f)
#		define Sys_UnloadLibrary(h) FreeLibrary((HMODULE)h)
#		define Sys_LoadFunction(h,fn) (void*)GetProcAddress((HMODULE)h,fn)
#		define Sys_LibraryError() "unknown"
#	else
#	include <dlfcn.h>
#		define Sys_LoadLibrary(f) dlopen(f,RTLD_NOW)
#		define Sys_UnloadLibrary(h) dlclose(h)
#		define Sys_LoadFunction(h,fn) dlsym(h,fn)
#		define Sys_LibraryError() dlerror()
#	endif
#elif __pnacl__
// no dynamic linking in pnacl, so the libs must be statically linked.
// should be uh, interesting to say the least to get that to link lol.
#	define Sys_LoadLibrary(f) NULL
#	define Sys_UnloadLibrary(h) NULL
#	define Sys_LoadFunction(h,fn) NULL
#	define Sys_LibraryError() "unknown"
#else
#	include <SDL.h>
#	include <SDL_loadso.h>
#	define Sys_LoadLibrary(f) SDL_LoadObject(f)
#	define Sys_UnloadLibrary(h) SDL_UnloadObject(h)
#	define Sys_LoadFunction(h,fn) SDL_LoadFunction(h,fn)
#	define Sys_LibraryError() SDL_GetError()
#endif

void * QDECL Sys_LoadDll(const char *name, qboolean useSystemLib);
