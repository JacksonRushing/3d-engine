#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cassert>
#include <iostream>



Texture::Texture(const std::string filename)
{
	int width, 
				 height, 
				 numComponents;
	//load the data
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << filename << std::endl;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
										//texture wrapping, what to do when beyond dimensions of texture, repeat this texture. other options are clamp for black, etc.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
										//what to do when texture  isn't shown as exactly native resolution. min = taking up fewer than resolution. linear = linearly interpolate between pixels
										//other options are nearest, etc. 
										//mag is for when it's taking up more pixels than resolution.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//target, level(for mip mapping (scaled textures, uses higher when nearer, lower when further, etc))
				//internalformat, width, height, border, format, type (data type, how are the pixels sorted)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	//free the data
	stbi_image_free(imageData);
}


Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);
	//ordered sequentially, selecting active texture. 
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}
