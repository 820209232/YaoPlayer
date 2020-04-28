#pragma once

class YaoAVPacketPrivate;
class YaoAVReaderPrivate;

class YaoAVPacket
{
public:
	YaoAVPacket();
	~YaoAVPacket();
public:
	YaoAVPacketPrivate * packetPrivate = nullptr;
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

//class Decoder
//{
//public:
//	AVCodecContext* codecContext = nullptr;
//public:
//	Decoder();
//	~Decoder();
//
//	int init(AVStream * stream);
//};
