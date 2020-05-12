#include "YaoPlayer.h"

YaoPlayerCtr::YaoPlayerCtr()
{

}

YaoPlayerCtr::~YaoPlayerCtr()
{

}

void YaoPlayerCtr::run()
{
	YaoPlayerReaderThread readerThread("c:/video/the5MP4.mp4", this);
	readerThread.start();

	//获取线程启动时的时间 startTime
	long long startTime = YaoTime::getTime();
	YaoAVFrame* videoFrame = nullptr;
	YaoAVFrame* audioFrame = nullptr;
	while (!stopFlag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		//获取当前时间 nowTime
		long long nowTime = YaoTime::getTime();
		//获取当前时间和开始时间的差 dTime
		long long dTime = nowTime - startTime;
		//printf("dTime:%lld\n", dTime);

		//-------视频
		//从视频frame缓存队列中获取一帧视频 framePts
		if (videoFrame == nullptr) {
			videoFrameQueue.pop(&videoFrame);
		} 
		if (videoFrame != nullptr) {
			//如果 framePts <= dTime
			if (videoFrame->getPts() <= dTime) {
				//该帧立即播放
				printf("video frame videoFrame->getPts():%lld\n", videoFrame->getPts());
				delete videoFrame;
				videoFrame = nullptr;
			}
			else {
				//还不到播放的时间，程序自悬，或者去处理音频
			}
		}

		//------音频
		//从音频frame缓存队列中获取一帧音频 framePts
		if (audioFrame == nullptr) {
			audioFrameQueue.pop(&audioFrame);
		}
		if (audioFrame != nullptr) {
			//如果 framePts <= dTime，
			if (audioFrame->getPts() <= dTime) {
				//该帧立即播放
				//printf("audio frame audioFrame->getPts():%lld\n", audioFrame->getPts());

				delete audioFrame;
				audioFrame = nullptr;
			}
			else
			{
				//还不到播放的时间，程序自悬
			}
		}

	}

	readerThread.stop();
}

int YaoPlayerCtr::pushVideoFrameQueue(YaoAVFrame* avFrame)
{
	return videoFrameQueue.push(avFrame);
}

int YaoPlayerCtr::pushAudioFrameQueue(YaoAVFrame* avframe)
{
	return audioFrameQueue.push(avframe);
}

int YaoPlayerCtr::getVideoFrameQueueSize()
{
	return videoFrameQueue.queueSize();
}

int YaoPlayerCtr::getAudioFrameQueueSize()
{
	return audioFrameQueue.queueSize();
}