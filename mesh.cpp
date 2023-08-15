#include <vector>
#include "mesh.h"
#include <SDL.h>
#include <iostream>

Mesh::Mesh() {
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLfloat verticies[] = {
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f
	};

	GLint triangles[] = {0, 2, 3, 0, 3, 1};
	
	std::vector<GLfloat> g_vertex_buffer_data;

	for (int i = 0; i < sizeof(triangles) / sizeof(GLint); i++) {
		g_vertex_buffer_data.push_back(verticies[(3*triangles[i])]);
		g_vertex_buffer_data.push_back(verticies[(3*triangles[i])+1]);
		g_vertex_buffer_data.push_back(verticies[(3*triangles[i])+2]);
	}

	vertex_size = g_vertex_buffer_data.size() / 3;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(GLfloat), 			g_vertex_buffer_data.data(), GL_STATIC_DRAW);
}

void Mesh::draw(){
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, vertex_size);
	glDisableVertexAttribArray(0);
}
