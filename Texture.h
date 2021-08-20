#pragma once
class Texture
{
public:
	unsigned int m_id;
	int m_width;
	int m_height;

	static Texture* loadTexture(const char*);
	void bindTexture();

protected:
	Texture(int, int, int);

};

