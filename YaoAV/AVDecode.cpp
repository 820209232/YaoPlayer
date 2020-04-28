#include "YaoAV.h"
extern "C"
{
#include <libavformat/avformat.h>
}
Decoder::Decoder() {
	codecContext = avcodec_alloc_context3(null);
}
Decoder::~Decoder() 
{
	if (codecContext != nullptr) {
		avcodec_free_context(&codecContext);
		codecContext = nullptr;
	}
}

int Decoder::init(AVStream* stream)
{
	AVCodec * codec = avcodec_find_decoder(stream->codecpar->codec_id);
	int ret = avcodec_open2(codecContext, codec, nullptr);
	if (ret) {
		printf("Open Decoder Fail\n");
		return -1;
	}
}
