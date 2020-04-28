#include "YaoAV.h"
#include "YaoAVReaderPrivate.h"
#include "YaoAVPacketPrivate.h"

YaoAVReader::YaoAVReader()
{
	av_register_all();
	avformat_network_init();
	formatContextPrivate = new YaoAVReaderPrivate();
	formatContextPrivate->formatContext = avformat_alloc_context();
}

YaoAVReader::~YaoAVReader()
{
	if (formatContextPrivate->formatContext != nullptr) {
		avformat_free_context(formatContextPrivate->formatContext);
		formatContextPrivate->formatContext = nullptr;
	}
}

int YaoAVReader::Open(const char* path)
{
	if (formatContextPrivate->formatContext == nullptr) {
		return -1;
	}
	int ret = avformat_open_input(&formatContextPrivate->formatContext, path, nullptr, nullptr);
	if (!ret) {
		avformat_find_stream_info(formatContextPrivate->formatContext, nullptr);
	}
	return ret;
}

int YaoAVReader::Close()
{
	if (formatContextPrivate->formatContext == nullptr) {
		return -1;
	}
	avformat_close_input(&formatContextPrivate->formatContext);
	return 0;
}

int YaoAVReader::Read(YaoAVPacket* packet)
{
	if (formatContextPrivate->formatContext == nullptr) {
		return -1;
	}
	int ret = av_read_frame(formatContextPrivate->formatContext, packet->packetPrivate->packet);
	return ret;
}