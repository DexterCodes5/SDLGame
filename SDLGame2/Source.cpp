#include <stdio.h>

#include <string>

#include <math.h>

using namespace std;

#ifdef __APPLE__

#include <SDL2/sdl.h>

#else

#include <SDL.h>

#endif

#pragma comment( lib, "SDL2.lib" )

#pragma comment( lib, "SDL2main.lib" )

// If there is a fatal error the program exits w/ message

inline void fatalError(const char* msg)

{

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", msg, NULL);

	printf("Fatal error: %s, (%s)", msg, SDL_GetError());

	exit(1);

}

class SDL

{

public:

	// The SDL_Window represents the Window on the underlying O/S.

	// SDL_Window can construct a Window equally well on Windows, Mac, & Linux.

	// You must realize how much work SDL is doing for you!

	SDL_Window* window;

	// An SDL_Surface is just a collection of pixels. Pixels have a format, like R8G8B8A8.

	// This surface is to represent the SCREEN. Images could be stored in other surfaces,

	// and you can copy from one surface to another.

	SDL_Surface* surface;

	// The SDL_Renderer takes care of draw-state information, like whether translucency is on or not

	SDL_Renderer* renderer;

	// Initializes an SDL window to desired width

	// and height, initializes video subsystem,

	// screen surface & renderer

	SDL(int windowWidth, int windowHeight) :window(0), surface(0), renderer(0)

	{

		if (SDL_Init(SDL_INIT_VIDEO) < 0)

		{

			fatalError("Couldn't init SDL Video!");

		}

		window = SDL_CreateWindow("SDL 2.0 app", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,

			windowWidth, windowHeight, SDL_WINDOW_SHOWN);

		if (!window)

		{

			fatalError("SDL Window could not be created!");

		}

		// Grab the surface (collection of pixels) of the window

		surface = SDL_GetWindowSurface(window);

		// Create a renderer ("paintbrush") to draw to the window's surface.

		// Turn on HARDWARE ACCELERATION and VSYNC

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		// Turn on alpha blending on the renderer, so translucent stuff displays correctly.

		// Translucency is expensive but worth adding!

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	}

	~SDL()

	{

		SDL_DestroyRenderer(renderer);

		SDL_FreeSurface(surface);

		SDL_DestroyWindow(window);

		SDL_Quit();

	}

	int getScreenWidth()

	{

		return surface->w;

	}

	int getScreenHeight()

	{

		return surface->h;

	}

};

// Draw the scene using the SDL object

void draw(SDL& sdl)

{

	// Clear to a dark blue.

	SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 40, 255);

	// Actually clear the screen.

	SDL_RenderClear(sdl.renderer);

	// +-------------+

	// | |

	// | |

	// +-------------+

	// SDL_RenderDrawRect, SDL_RenderFillRect

	SDL_Rect rectangle;

	rectangle.x = 0;

	rectangle.y = 0; // TOP LEFT CORNER

	rectangle.w = 100;

	rectangle.h = 100;

	SDL_SetRenderDrawColor(sdl.renderer, 255, 0, 0, 255);

	SDL_RenderDrawRect(sdl.renderer, &rectangle);

	rectangle.x = 101;

	SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 255, 255);

	SDL_RenderFillRect(sdl.renderer, &rectangle);

	// +--------------+

	// SDL_RenderDrawLine

	int startX = 0, startY = 0, endX = 200, endY = 200;

	SDL_SetRenderDrawColor(sdl.renderer, 0, 255, 0, 255);

	SDL_RenderDrawLine(sdl.renderer, startX, startY, endX, endY);

	// .

	// SDL_RenderDrawPoint

	SDL_SetRenderDrawColor(sdl.renderer, 255, 255, 0, 255);

	SDL_RenderDrawPoint(sdl.renderer, 100, 100);

	SDL_RenderPresent(sdl.renderer);

}

// All C++ apps start at the first line of main()

int main(int argc, char* args[])

{

	// Initialize an SDL window. See ctor of SDL object for details.

	SDL sdl(800, 600);

	// Keep running the game until the user presses esc

	bool gameRunning = true;

	while (gameRunning)

	{

		// CONTROLLER INPUT

		SDL_Event e;

		// SDL_PollEvent returns 0 when there are no more events

		// we continue to poll for events until there aren't any more

		while (SDL_PollEvent(&e))

		{

			if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)

			{

				gameRunning = false;

			}

		}

		// DRAW: We simply draw here

		draw(sdl);

	}

	return 0;

}