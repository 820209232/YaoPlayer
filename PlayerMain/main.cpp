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
	player.play();

	Sleep(1000 * 2);

	player.seek(10);
	/*player.pause();
	Sleep(1000 * 2);*/


	player.play();
	Sleep(1000 * 5);

	player.stop();

	return 0;
}