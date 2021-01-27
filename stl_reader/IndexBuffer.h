#pragma once

class IndexBuffer {
private:
	unsigned int RendererID_;
	unsigned int Count_;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const {return Count_; }
};