#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

class Mesh {
	public:
		Mesh();
		void draw();
	private:
		GLuint VertexArrayID, vertexbuffer, elementbuffer, vertex_size;
};

#endif
