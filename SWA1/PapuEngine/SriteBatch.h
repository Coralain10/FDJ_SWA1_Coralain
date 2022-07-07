#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class RenderBatch {
public:
	GLuint _offset;
	GLuint _numVertices;
	GLuint _texture;
	RenderBatch(GLuint offset, GLuint numVertices,
		GLuint texture) {
		_offset = offset;
		_numVertices = numVertices;
		_texture = texture;
	}
	
};

struct Glyph {
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class SriteBatch
{
private:
	GLuint _vbo;
	GLuint _vao;
	std::vector<Glyph*> _glyphs;
	std::vector<RenderBatch> _renderBatch;
	GlyphSortType _sortType;
	void createVertexArray();
	void sortGlyph();
	void createRenderBatches();

public:
	SriteBatch();
	~SriteBatch();
	void init();
	void begin(GlyphSortType type= GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRest, const glm::vec4& uvRect,
			GLuint texture, float depth, const Color& color);
	void renderBatch();

};

