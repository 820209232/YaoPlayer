#pragma once

#include <string>

#include "YaoThread/YaoThread.h"
#include "YaoAV/YaoAV.h"
#include "YaoQueue/Queue.h"

enum YaoDecoderType
{
	YAODECODER_TYPE_VIDEO = 0,
	YAODECODER_TYPE_AUDIO = 1
};

class YaoPlayerCtr : public YaoThread
{
public:
	YaoPlayerCtr();
	~YaoPlayerCtr();

	virtual void run();

	int pushVideoFrameQueue(YaoAVFrame* avFrame);
	int pushAudioFrameQueue(YaoAVFrame* avframe);
	int getVideoFrameQueueSize();
	int getAudioFrameQueueSize();
private:
	YaoQueue<YaoAVFrame> videoFrameQueue;
	YaoQueue<YaoAVFrame> audioFrameQueue;

};

class YaoPlayerReaderThread : public YaoThread
{
public:
	YaoPlayerReaderThread(std::string _path, YaoPlayerCtr * ctr);
	~YaoPlayerReaderThread();
	virtual void run();
private:
	std::string path;
	YaoPlayerCtr * ctrThread = nullptr;
};

class YaoDecodeThread : public YaoThread
{
public:
	YaoDecodeThread(YaoPlayerCtr * ctr, YaoDecoderType type);
	~YaoDecodeThread();
	virtual void run();
	int init(YaoAVStream* stream);
	int pushPacket(YaoAVPacket * packet);
	int packetQueueSize();
private:
	Decoder * decode = nullptr;
	YaoQueue<YaoAVPacket> packetQueue;
	YaoPlayerCtr * ctrThread = nullptr;
	YaoDecoderType type;
};

class YaoPlayer
{
public:
	YaoPlayer(std::string path);
	~YaoPlayer();

	int open();
	int stop();
	int play();
	int pause();

	int seek(double time);
private:
	std::string path;
	YaoPlayerCtr * playerCtr = nullptr;
};

