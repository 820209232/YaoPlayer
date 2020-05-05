#pragma once

#include <string>

#include "YaoThread/YaoThread.h"
#include "YaoAV/YaoAV.h"
#include "YaoQueue/Queue.h"

class YaoPlayerReaderThread : public YaoThread
{
public:
	YaoPlayerReaderThread(std::string _path);
	~YaoPlayerReaderThread();
	virtual void run();
private:
	std::string path;
};

class YaoDecodeThread : public YaoThread
{
public:
	YaoDecodeThread();
	~YaoDecodeThread();
	virtual void run();
	int init(YaoAVStream* stream);
	int pushPacket(YaoAVPacket * packet);
	int packetQueueSize();
private:
	Decoder * decode = nullptr;
	YaoQueue<YaoAVPacket> packetQueue;
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
	YaoPlayerReaderThread * readerThread = nullptr;
};

