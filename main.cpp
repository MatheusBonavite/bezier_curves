#include <iostream>
#include <string>
#include <optional>
#include <SDL.h>

struct BasicConfig { int x{0}; int y{0}; int width{800}; int height{800}; };
static BasicConfig basicConfig;
static int quitApplication = 0;

static inline float lerp(float a, float b, float p) { return ((a*p) + b*(1.0 - p)); };

std::optional<int> checkSdlInit(int code)
{
	if (code < 0) return std::nullopt;
	return code;
}

std::optional<void*> checkSdlPointer(void* pointer)
{
	if (!pointer) return std::nullopt;
	return pointer;
}

int main(int argc, char* argv[])
{
	if (!checkSdlInit(SDL_Init(SDL_INIT_VIDEO)).has_value()) { std::cerr << "SDL Error : " << SDL_GetError() << std::endl; exit(1); }
	auto window =  checkSdlPointer(SDL_CreateWindow("Bezier Curves", basicConfig.x, basicConfig.y, basicConfig.width, basicConfig.height, SDL_WINDOW_RESIZABLE));
	if (!window.has_value()) { std::cerr << "SDL Error : " << SDL_GetError() << std::endl; exit(1); }
	auto renderer = checkSdlPointer(SDL_CreateRenderer(static_cast<SDL_Window*>(window.value()), -1, SDL_RENDERER_ACCELERATED));
	if (!renderer.has_value()) { std::cerr << "SDL Error : " << SDL_GetError() << std::endl; exit(1); }
	// Doing main event loop stuff...
	while (!quitApplication)
	{
		// Organizing the event  loop
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					quitApplication = true;
					break;
			}
		}
		// Making sure our window will clean itself up!
		if (!checkSdlInit(SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer.value()), 0, 0, 0, 255)).has_value()) { std::cerr << "SDL Errror : " << SDL_GetError()  << std::endl; exit(1); }
		if (!checkSdlInit(SDL_RenderClear(static_cast<SDL_Renderer*>(renderer.value()))).has_value()) { std::cerr << "SDL Errror : " << SDL_GetError()  << std::endl; exit(1); }
		SDL_RenderPresent(static_cast<SDL_Renderer*>(renderer.value()));
		// Drawing a random line... To see if it is possible
		if (!checkSdlInit(SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer.value()), 255, 0, 0, 255)).has_value()) { std::cerr << "SDL Errror : " << SDL_GetError()  << std::endl; exit(1); }
		if (!checkSdlInit(SDL_RenderDrawLine(static_cast<SDL_Renderer*>(renderer.value()), 0, 0, 1, 100)).has_value()) { std::cerr << "SDL Error : " << SDL_GetError() << std::endl; exit(1); }
		SDL_RenderPresent(static_cast<SDL_Renderer*>(renderer.value()));
	}

	SDL_Quit();
	return 0;
}
