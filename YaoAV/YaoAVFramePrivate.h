#pragma once
extern "C"
{
#include <libavformat/avformat.h>
}

class YaoAVFramePrivate {
public:
	AVFrame* frame = nullptr;
};