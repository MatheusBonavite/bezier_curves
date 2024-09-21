#include <SDL.h>
#include <iostream>
#include "ErrorChecker.h"

namespace
{
std::expected<int, const char*> checkSdlCode(int code)
{
	if (code < 0) return std::unexpected(SDL_GetError());
	return code;
}

std::expected<void*, const char*> checkSdlPointer(void* pointer)
{
	if (!pointer) return std::unexpected(SDL_GetError());
	return pointer;
}
};

template<> int ErrorChecker::exitOnUnexpected(int code)
{
	if (auto value = checkSdlCode(code); !value.has_value())
	{
		std::cerr << " SDL Error : " << value.error() << std::endl;
		exit(1);
	}
	return code;
}

template<> SDL_Window* ErrorChecker::exitOnUnexpected(SDL_Window* pointer)
{
	if (auto value = checkSdlPointer(pointer); !value.has_value())

	{
		std::cerr << " SDL Error : " << value.error() << std::endl;
		exit(1);
	}
	return pointer;
}

template<> SDL_Renderer* ErrorChecker::exitOnUnexpected(SDL_Renderer* pointer)
{
	if (auto value = checkSdlPointer(pointer); !value.has_value())

	{
		std::cerr << " SDL Error : " << value.error() << std::endl;
		exit(1);
	}
	return pointer;
}
