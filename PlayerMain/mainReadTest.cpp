#include <stdio.h>
#include <vector>

#include "YaoThread/YaoThread.h"
#include "YaoAV/YaoAV.h"
#include "YaoQueue/Queue.h"

class MyThread : public YaoThread
{
private:
	int a;
public:
	MyThread(int _a)
	{
		a = _a;
	}
	virtual void run() 
	{
		printf("in yaoThread %d \n", a);
	}
};

int main_thread()
{
	int a = 10;
	MyThread * t = new MyThread(a);
	t->start();
	std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}

int main()
{
	YaoQueue<YaoAVPacket> packetQueue;
	YaoAVReader reader;
	FILE* fout;
	fout = fopen("C://video/the5MP4.yuv", "wb");
	int ret = reader.Open("C://video/the5MP4.mp4");
	if (ret) {
		printf("open file fail \n");
		return -1;
	}
	
	int videoStreamIndex = reader.getVideoStreamIndex();
	int audioStreamIndex = reader.getAudioStreamIndex();

	std::vector<Decoder*> DecoderList;

	int streamCount = reader.getStreamCount();
	for (int i = 0; i < streamCount; i++) {
		YaoAVStream stream;
		reader.getStream(&stream, i);
		//printf("streamIndex:%d \n", stream.streamIndex);
		Decoder* decode = new Decoder();
		int ret = decode->init(&stream);
		if (ret) {
			printf("decode init fail:%d \n", ret);
		}
		DecoderList.push_back(decode);
	}

	while (1)
	{
		YaoAVPacket * packet = new YaoAVPacket();
		ret = reader.Read(packet);
		if (ret) {
			break;
		}

		packetQueue.push(packet);

		int packetIndex = packet->getIndex();
		Decoder* decoder = DecoderList[packetIndex];

		ret = decoder->sendPacket(packet);
		if (ret) {
			continue;
		}
		while (1) {
			YaoAVFrame frame;
			ret = decoder->receiveFrame(&frame);
			if (ret) {
				break;
			}

			//receive success

			if (packetIndex == videoStreamIndex) {
				//frame.videoPrint();
				//fout
				int width = frame.getW();
				int height = frame.getH();

				unsigned char* y;
				unsigned char* u;
				unsigned char* v;

				y = (unsigned char*)malloc(width * height);
				u = (unsigned char*)malloc(width / 2 * height / 2);
				v = (unsigned char*)malloc(width / 2 * height / 2);

				frame.getY(y);
				frame.getU(u);
				frame.getV(v);

				fwrite(y, width * height, 1, fout);
				fwrite(u, width / 2 * height / 2, 1, fout);
				fwrite(v, width / 2 * height / 2, 1, fout);

				free(y);
				free(u);
				free(v);
			}

			if (packetIndex == audioStreamIndex) {
				//frame.audioPrint();
			}
		}

	}

	for (int i = 0; i < DecoderList.size(); i++) {
		Decoder* decoder = DecoderList[i];
		decoder->sendPacket(nullptr);
		while (1) {
			YaoAVFrame frame;
			ret = decoder->receiveFrame(&frame);
			if (ret) {
				break;
			}

			//receive success
		}
	}

	//for (int i = 0; i < packetQueue.queueSize(); i++) {
	while (packetQueue.queueSize() > 0){
		YaoAVPacket* packet = nullptr;
		packetQueue.pop(&packet);

		printf("packetQueue size:%d \n", packetQueue.queueSize());

		if (packet != nullptr) {
			delete packet;
		}
	}

	reader.Close();
	fclose(fout);

	for (int i = 0; i < DecoderList.size(); i++) {
		Decoder * decoder = DecoderList[i];
		if (decoder != nullptr) {
			decoder->close();
			delete decoder;
			decoder = nullptr;
		}
	}
	DecoderList.clear();
	return 0;
}