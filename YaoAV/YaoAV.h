#pragma once

class YaoAVPacketPrivate;
class YaoAVReaderPrivate;
class YaoAVStreamPrivate;
class YaoAVDecodePrivate;
class YaoAVFramePrivate;

class YaoAVPacket
{
public:
	YaoAVPacket();
	~YaoAVPacket();
public:
	YaoAVPacketPrivate * packetPrivate = nullptr;
};

class YaoAVStream
{
public:
	YaoAVStream();
	~YaoAVStream();
public:
	YaoAVStreamPrivate* imp = nullptr;

};

class YaoAVReader
{
public:
	YaoAVReader();
	~YaoAVReader();

	int Open(const char * path);
	int Close();
	int Read(YaoAVPacket * packet);

private:
	YaoAVReaderPrivate * formatContextPrivate = nullptr;
};

class YaoAVFrame
{
public:
	YaoAVFrame();
	~YaoAVFrame();
public:
	YaoAVFramePrivate* imp = nullptr;
};

class Decoder
{
public:
	YaoAVDecodePrivate* imp = nullptr;
public:
	Decoder();
	~Decoder();

	int init(YaoAVStream* stream);
	int sendPacket(YaoAVPacket * packet);
	int receiveFrame(YaoAVFrame * frame);
	int close();
};

