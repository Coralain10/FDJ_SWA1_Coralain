#include <SDL\SDL.h>
#include "MainGame.h"
#include "App.h"

int main(int argc,char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	/*MainGame mainge;
	mainge.run();
	system("PAUSE");*/

	App app;
	app.run();

	return 0;
}