#include <expected>
#include <SDL.h>
#include "./utils/ErrorChecker.h"
#include "./utils/Vec2D.h"

struct RGBAlpha { uint8_t red; uint8_t green; uint8_t blue; uint8_t alpha; };
struct BasicConfig { int x{0}; int y{0}; int width{800}; int height{800}; };
static BasicConfig basicConfig;
static int quitApplication = 0;

// Seems like there is another function in math.h being linked in newer GCC compiler
// static inline float lerp(float a, float b, float p) { return ((a*p) + b*(1.0 - p)); };

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

void SDLRenderLine(SDL_Renderer* renderer, Vec2D<int> startPoint, Vec2D<int> endPoint, RGBAlpha rgb)
{
	ErrorChecker::exitOnUnexpected(SDL_SetRenderDrawColor(renderer, rgb.red, rgb.green, rgb.blue, rgb.alpha));
	ErrorChecker::exitOnUnexpected(SDL_RenderDrawLine(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y));
}

int main(int argc, char* argv[])
{
	// Initializing SDL, creating window and renderer
	ErrorChecker::exitOnUnexpected(SDL_Init(SDL_INIT_VIDEO));
	auto window = ErrorChecker::exitOnUnexpected(SDL_CreateWindow("Bezier Curves", basicConfig.x, basicConfig.y, basicConfig.width, basicConfig.height, SDL_WINDOW_RESIZABLE));
	auto renderer = ErrorChecker::exitOnUnexpected(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
	ErrorChecker::exitOnUnexpected(SDL_RenderSetLogicalSize(renderer, basicConfig.width, basicConfig.height));
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
		ErrorChecker::exitOnUnexpected(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));
		ErrorChecker::exitOnUnexpected(SDL_RenderClear(renderer));
		// Drawing a random line... To see if it is possible
		SDLRenderLine(renderer, Vec2D<int>(0, 0), Vec2D<int>(basicConfig.width, basicConfig.height), RGBAlpha{255, 0, 0, 255});
		SDLRenderLine(renderer, Vec2D<int>(basicConfig.width, 0), Vec2D<int>(0, basicConfig.height), RGBAlpha{255, 0, 0, 255});
		// Let us now draw a random Rectangle
		ErrorChecker::exitOnUnexpected(SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255));
		SDL_Rect rect { (basicConfig.width / 2) - 8, (basicConfig.height / 2) - 8, 16, 16 };
		ErrorChecker::exitOnUnexpected(SDL_RenderFillRect(renderer, &rect));
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return 0;
}
