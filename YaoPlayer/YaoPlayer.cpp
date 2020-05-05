#include "YaoPlayer.h"

YaoPlayer::YaoPlayer(std::string _path)
{
	path = _path;
}

YaoPlayer::~YaoPlayer()
{

}

int YaoPlayer::open()
{
	if (readerThread == nullptr) {
		readerThread = new YaoPlayerReaderThread(path);
		readerThread->start();
		return 0;
	}
	return -1;
}

int YaoPlayer::stop()
{
	if (readerThread != nullptr) {
		readerThread->stop();
	}
	return 0;
}

int YaoPlayer::play()
{
	return 0;
}

int YaoPlayer::pause()
{
	return 0;
}

int YaoPlayer::seek(double time)
{
	return 0;
}