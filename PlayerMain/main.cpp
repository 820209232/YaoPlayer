#include "YaoPlayer/YaoPlayer.h"
#include<Windows.h>
int main()
{
	YaoPlayer player("c:/video/the5MP4.mp4");
	int ret = player.open();
	if (ret) {
		printf("file open fail\n");
		return -1;
	}

	Sleep(1000 * 20);

	player.play();

	player.pause();

	player.play();

	player.stop();

	return 0;
}