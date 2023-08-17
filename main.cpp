#include <iostream>
#include <SDL.h>
#include "mesh.h"
#include "loadShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	Mesh cube;

	GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");

	bool done = false;
	Uint32 lastUpdate = SDL_GetTicks();

	while(!done) {
		Uint32 current = SDL_GetTicks();
		glViewport(0, 0, screen_width, screen_height);

		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT) {
				done = true;
			}
		}
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		float dT = (current - lastUpdate) / 1000.0f;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(50.0f)*dT, glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(60.0f), float(screen_width)/(float)screen_height, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(programID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(programID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projectionLoc = glGetUniformLocation(programID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUseProgram(programID);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		cube.draw();	
		
		SDL_GL_SwapWindow(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
