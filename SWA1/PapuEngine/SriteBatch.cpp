#include "SriteBatch.h"



SriteBatch::SriteBatch()
{
}

void SriteBatch::createVertexArray() {

}
void SriteBatch::sortGlyph() {
}
void SriteBatch::createRenderBatches() {
	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);
	if (_glyphs.empty()) {
		return;
	}
	int cv = 0;
	int offset = 0;
	_renderBatch.emplace_back(0, 6, _glyphs[0]->texture);
	vertices[cv++] = _glyphs[0]->topLeft;
	vertices[cv++] = _glyphs[0]->bottomLeft;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->topRight;
	vertices[cv++] = _glyphs[0]->topLeft;

	offset += 6;

	for (int i = 1; i < _glyphs.size(); i++)
	{
		if (_glyphs[i]->texture != _glyphs[i-1]->texture) {
			_renderBatch.emplace_back
					(offset, 6, _glyphs[i]->texture);
		}
		else {
			_renderBatch.back()._numVertices = 6;
		}
		vertices[cv++] = _glyphs[i]->topLeft;
		vertices[cv++] = _glyphs[i]->bottomLeft;
		vertices[cv++] = _glyphs[i]->bottomRight;
		vertices[cv++] = _glyphs[i]->bottomRight;
		vertices[cv++] = _glyphs[i]->topRight;
		vertices[cv++] = _glyphs[i]->topLeft;
		offset += 6;
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, 
		vertices.size() * sizeof(Vertex),
		nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,
		vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

void SriteBatch::init() {
	createVertexArray();
}
void SriteBatch::begin(GlyphSortType type) {
	_sortType = type;
	_renderBatch.clear();
	_glyphs.clear();
}

void SriteBatch::end() {
	sortGlyph();
	createRenderBatches();
}
void SriteBatch::draw(const glm::vec4& destRest, 
	const glm::vec4& uvRect,
	GLuint texture, float depth, const Color& color) {

	Glyph* glyph = new Glyph;
	glyph->texture = texture;
	glyph->depth = depth;
	glyph->topLeft.color = color;
	glyph->bottomLeft.color = color;
	glyph->topRight.color = color;
	glyph->bottomRight.color = color;

	glyph->topLeft.setPosition(destRest.x, 
								destRest.y + destRest.w);
	glyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	glyph->bottomLeft.setPosition(destRest.x, destRest.y);
	glyph->bottomLeft.setUV(uvRect.x, uvRect.y);


	glyph->topRight.setPosition(destRest.x + destRest.z, 
								destRest.y + destRest.w);
	glyph->topRight.setUV(uvRect.x + uvRect.z, 
							uvRect.y + uvRect.w);

	glyph->bottomRight.setPosition(destRest.x + destRest.z,
		destRest.y);
	glyph->bottomRight.setUV(uvRect.x + uvRect.z,
		uvRect.y);
}
void SriteBatch::renderBatch() {

	glBindVertexArray(_vao);
	for (int i = 0; i < _renderBatch.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatch[i]._texture);
		glDrawArrays(GL_TRIANGLES, _renderBatch[i]._offset,
			_renderBatch[i]._numVertices);
	}
	glBindVertexArray(0);
}


SriteBatch::~SriteBatch()
{
}
