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
	if (playerCtr == nullptr) {
		playerCtr = new YaoPlayerCtr();
		playerCtr->start();
		return 0;
	}
	return -1;
}

int YaoPlayer::stop()
{
	if (playerCtr != nullptr) {
		playerCtr->stop();
		delete playerCtr;
		playerCtr = nullptr;
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