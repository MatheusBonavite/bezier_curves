#include <expected>

namespace ErrorChecker
{
template <typename T>
T exitOnUnexpected(T value);
};

template<> int ErrorChecker::exitOnUnexpected(int code);
template<> SDL_Window* ErrorChecker::exitOnUnexpected(SDL_Window* code);
template<> SDL_Renderer* ErrorChecker::exitOnUnexpected(SDL_Renderer* code);
