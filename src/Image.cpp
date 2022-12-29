#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(int width, int height)
	: m_Width(width), m_Height(height)
{
	m_Data = new unsigned char[width * height * 3];
	memset(m_Data, 0, width * height * 3);
	stbi_flip_vertically_on_write(1);
}

Image::~Image()
{
	delete[] m_Data;
}

const unsigned char* const Image::GetData() const
{
	return m_Data;
}

Pixel Image::GetPixel(int x, int y) const
{
#ifdef _DEBUG
	if (x > m_Width || y > m_Height || x < 0 || y < 0) {
		printf("Reading from a pixel that is outside the image\n");
		return Pixel();
	}
#endif
	return Pixel(m_Data[y * 3 * m_Width + x * 3], m_Data[y * 3 * m_Width + x * 3 + 1], m_Data[y * 3 * m_Width + x * 3 + 2]);
}

const int Image::GetWidth() const
{
	return m_Width;
}

const int Image::GetHeight() const
{
	return m_Height;
}

void Image::SetPixel(int x, int y, const Pixel& p) const
{
#ifdef _DEBUG
	if (x > m_Width || y > m_Height || x < 0 || y < 0) {
		printf("Writing to a pixel that is outside the image\n");
		return;
	};
#endif
	m_Data[y * 3 * m_Width + x * 3] = p.R;
	m_Data[y * 3 * m_Width + x * 3 + 1] = p.G;
	m_Data[y * 3 * m_Width + x * 3 + 2] = p.B;
}

void Image::Save(const std::string& fileName) const
{
	stbi_write_png(fileName.c_str(), m_Width, m_Height, 3, m_Data, sizeof(unsigned char) * m_Width * 3);
}