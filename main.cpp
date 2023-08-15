#include <iostream>
#include <glad/glad.h>
#include <SDL.h>

int main(int argc, char* argv[]){
	SDL_Window* window = nullptr;
	
	int screen_width = 1000;
	int screen_height = 800;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL failed initialization. " << SDL_GetError();
		return -1;
	} else {
		std::cout << "SDL successfully initialized.";
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow("C++ SDL2 Window | OpenGL", 
			0, 
			0, 
			screen_width, 
			screen_height, 
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext context;
	context = SDL_GL_CreateContext(window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	bool done = false;

	while(!done) {
		glViewport(0, 0, screen_width, screen_height);

		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT) {
				done = true;
			}
		}
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}
