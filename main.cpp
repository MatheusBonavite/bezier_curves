#include <iostream>
#include <string>
#include <expected>
#include <SDL.h>

struct BasicConfig { int x{0}; int y{0}; int width{800}; int height{800}; };
static BasicConfig basicConfig;
static int quitApplication = 0;

// Seems like there is another function in math.h being linked in newer GCC compiler
// static inline float lerp(float a, float b, float p) { return ((a*p) + b*(1.0 - p)); };

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

template <typename T>
T exitOnUnexpected(std::expected<T, const char*> value)
{
	if (!value.has_value())
	{
		std::cerr << " SDL Error : " << value.error() << std::endl;
		exit(1);
	}
	return value.value();
}

class FrameRefresh
{
public:
	FrameRefresh() { m_frameStart = SDL_GetTicks(); }
	~FrameRefresh()
	{
		uint32_t frameTime = SDL_GetTicks() - m_frameStart;
		if (m_frameDelay > frameTime)
		{
			SDL_Delay(m_frameDelay - frameTime);
		}
	}
private:
	uint32_t m_frameStart;
	uint32_t m_frameDelay{100};
};

int main(int argc, char* argv[])
{
	// Initializing SDL, creating window and renderer
	exitOnUnexpected<int>(checkSdlCode(SDL_Init(SDL_INIT_VIDEO)));
	auto window =  exitOnUnexpected<void*>(checkSdlPointer(SDL_CreateWindow("Bezier Curves", basicConfig.x, basicConfig.y, basicConfig.width, basicConfig.height, SDL_WINDOW_RESIZABLE)));
	auto renderer = exitOnUnexpected<void*>(checkSdlPointer(SDL_CreateRenderer(static_cast<SDL_Window*>(window), -1, SDL_RENDERER_ACCELERATED)));
	exitOnUnexpected<int>(checkSdlCode(SDL_RenderSetLogicalSize(static_cast<SDL_Renderer*>(renderer), basicConfig.width, basicConfig.height)));
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
		// In order to delay a little bit between RenderClear and RenderPresent
		FrameRefresh rf;
		// Making sure our window will clean itself up!
		exitOnUnexpected<int>(checkSdlCode(SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer), 0, 0, 0, 255)));
		exitOnUnexpected<int>(checkSdlCode(SDL_RenderClear(static_cast<SDL_Renderer*>(renderer))));
		// Drawing a random line... To see if it is possible
		exitOnUnexpected<int>(checkSdlCode(SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer), 255, 0, 0, 255)));
		exitOnUnexpected<int>(checkSdlCode(SDL_RenderDrawLine(static_cast<SDL_Renderer*>(renderer), 0, 0, basicConfig.width, basicConfig.height)));
		exitOnUnexpected<int>(checkSdlCode(SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer), 255, 0, 0, 255)));
		exitOnUnexpected<int>(checkSdlCode(SDL_RenderDrawLine(static_cast<SDL_Renderer*>(renderer), basicConfig.width, 0, 0, basicConfig.height)));
		SDL_RenderPresent(static_cast<SDL_Renderer*>(renderer));
	}

	SDL_Quit();
	return 0;
}
