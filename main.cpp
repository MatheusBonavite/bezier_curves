#include <expected>
#include <math.h>
#include <SDL.h>
#include "./utils/ErrorChecker.h"
#include "./utils/Vec2D.h"
#include "./utils/FrameRefresh.h"

struct RGBAlpha { uint8_t red; uint8_t green; uint8_t blue; uint8_t alpha; };
struct BasicConfig { 
	int x{0};
	int y{0};
	int width{800};
	int height{800};
	int screenFps{60};
	float delaySeconds{1.0f/screenFps};
	uint32_t delayMilliseconds{static_cast<uint32_t>(delaySeconds * 1000.0f)};
};
static BasicConfig basicConfig;
static int quitApplication = 0;

// Seems like there is another function in math.h being linked in newer GCC compiler
// static inline float lerp(float a, float b, float p) { return ((a*p) + b*(1.0 - p)); };
// However, I still need to do lerp for 2D vectors
template <typename T>
static inline Vec2D<T> lerpVec2D(Vec2D<T> a, Vec2D<T> b, float p) { return (a*p) + b*(1.0 - p); }

void SDLRenderLine(SDL_Renderer* renderer, Vec2D<int> startPoint, Vec2D<int> endPoint, RGBAlpha rgb)
{
	ErrorChecker::exitOnUnexpected(SDL_SetRenderDrawColor(renderer, rgb.red, rgb.green, rgb.blue, rgb.alpha));
	ErrorChecker::exitOnUnexpected(SDL_RenderDrawLine(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y));
}

void SDLRenderRect(SDL_Renderer* renderer, Vec2D<int> position, Vec2D<int> size, RGBAlpha rgb)
{
	ErrorChecker::exitOnUnexpected(SDL_SetRenderDrawColor(renderer,rgb.red, rgb.green, rgb.blue, rgb.alpha));
	SDL_Rect rect { position.x, position.y, size.x, size.y };
	ErrorChecker::exitOnUnexpected(SDL_RenderFillRect(renderer, &rect));
}

void renderMarker(SDL_Renderer* renderer, Vec2D<int> position, RGBAlpha color)
{
	constexpr int MARKER_SIZE = 16;
	// Let us now draw a random Rectangle
	SDLRenderRect(renderer, position - (MARKER_SIZE/2), Vec2D<int>(MARKER_SIZE, MARKER_SIZE), color);
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
		FrameRefresh rf(basicConfig.delaySeconds, basicConfig.delayMilliseconds);
		// Making sure our window will clean itself up!
		ErrorChecker::exitOnUnexpected(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));
		ErrorChecker::exitOnUnexpected(SDL_RenderClear(renderer));
		// Drawing a random line... To see if it is possible
		SDLRenderLine(renderer, Vec2D<int>(0, 0), Vec2D<int>(basicConfig.width, basicConfig.height), RGBAlpha{255, 0, 0, 255});
		SDLRenderLine(renderer, Vec2D<int>(basicConfig.width, 0), Vec2D<int>(0, basicConfig.height), RGBAlpha{255, 0, 0, 255});
		// Doing some lerping operations...
		auto lerpResult = lerpVec2D(Vec2D<float>(0.0, 0.0), Vec2D<float>(basicConfig.width, basicConfig.height), (sin(rf.getElapsedTime()) + 1.0)/2.0 );
		renderMarker(renderer, Vec2D<int>(lerpResult.x, lerpResult.y), {0, 255, 0, 255});
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return 0;
}
