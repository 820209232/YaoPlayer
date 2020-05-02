#include "YaoAV.h"
#include "YaoAVFramePrivate.h"

YaoAVFrame::YaoAVFrame() 
{
	imp = new YaoAVFramePrivate();
	imp->frame = av_frame_alloc();
}

YaoAVFrame::~YaoAVFrame()
{
	if (imp->frame != nullptr) {
		av_frame_free(&imp->frame);
		imp->frame = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}