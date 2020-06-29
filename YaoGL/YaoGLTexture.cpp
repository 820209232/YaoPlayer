#include "YaoGL.h"
#include "YaoImg/stb_image.h"

YaoGLTexture::YaoGLTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//����һ�ֽڶ���
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

YaoGLTexture::~YaoGLTexture()
{

}
int YaoGLTexture::loadImg(char* imgPath)
{
	stbi_set_flip_vertically_on_load(true);
	imgData = stbi_load(imgPath, &width, &height, &nrChannels, 0);
	printf("width %d, height %d, nrChannels %d \n", width, height, nrChannels);
	if (width <= 0 && height <= 0) {
		return -1;
	}
	return 0;
}

int YaoGLTexture::createTexImage2D()
{
	if (imgData == nullptr) {
		printf("Failed to load texture\n");
		return -1;
	};
	//��ͼƬ��������
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
	//����������֮�����glGenerateMipmap����Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
	glGenerateMipmap(GL_TEXTURE_2D);
	//����������ͷ�ͼ����ڴ�
	//stbi_image_free(imgData);

	return 0;
}

int YaoGLTexture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	return 0;
}

int YaoGLTexture::setImgData(unsigned char* _imgData)
{
	/*for (int i = 0; i < 10; i++)
	{
		printf(" %d ", _imgData[i]);
	}*/
	int _strLen = 12 + 1;
	printf("strLen:%d\n", _strLen);
	imgData = (unsigned char *)malloc(_strLen);
	memcpy(imgData, _imgData, _strLen);
	return 0;
}

