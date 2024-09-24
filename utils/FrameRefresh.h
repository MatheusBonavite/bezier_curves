#include <SDL.h>

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
