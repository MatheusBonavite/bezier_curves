#include <SDL.h>

static float elapsedTime{0.0f};

class FrameRefresh
{
public:
	FrameRefresh(float delaySeconds, uint32_t delay) : m_frameDelayInSeconds(delaySeconds), m_frameDelay(delay) {};
	float getElapsedTime() { return elapsedTime; }
	~FrameRefresh()
	{
		SDL_Delay(m_frameDelay);
		elapsedTime += m_frameDelayInSeconds;
	}
private:

	float m_frameDelayInSeconds{0.1f};
	uint32_t m_frameDelay{static_cast<uint32_t>(m_frameDelayInSeconds*1000.0f)};
};
