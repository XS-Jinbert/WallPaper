#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <vlc/vlc.h>
#include <string>
#include "CharsRain.h"

#define ssize_t SSIZE_H

HWND workerw;
BOOL CALLBACK EnumWindowProFindDesktopWindow(HWND hwnd, LPARAM lparam) {
	HWND p = FindWindowEx(hwnd, NULL,"SHELLDLL_DefView", NULL);
	if (p == NULL)return 1;
	std::cout << "Yes, is work!" << std::endl;
	workerw = FindWindowEx(NULL, hwnd, "WorkerW", NULL);
}

int main() {
	HWND hwnd_progman = FindWindow("Progman", NULL);
	if (hwnd_progman == NULL) {
		std::cout << "canot get handle of Progman" << std::endl;
		return 1;
	}
	DWORD_PTR result = 0;
	SendMessageTimeout(hwnd_progman, 0x052c, NULL, NULL, SMTO_NORMAL, 1000, &result);
	EnumWindows(EnumWindowProFindDesktopWindow, NULL);

	std::cout << "Yes, you get it!" << std::endl;
	charsrain(workerw);
}

void SetVideo(void* drawbale){
	char* videopath = new char[256];
	std::string path;
	std::cout << "please enter the video path:" << std::endl;
	std::cin >> path;
	std::cin.get();		// 去掉输入行最后的\n

	// 转化string为LPCWSTR，并存在buf上
	int len;
	int slength = (int)path.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, buf, len);

	WideCharToMultiByte(CP_UTF8, 0, buf, -1, videopath, 128, NULL, 0);

	// 播放设置
	libvlc_instance_t* inst = libvlc_new(0, NULL);
	libvlc_media_t* m = libvlc_media_new_path(inst, videopath);
	libvlc_media_list_t* ml = libvlc_media_list_new(inst);
	libvlc_media_player_t* mp = libvlc_media_player_new_from_media(m);
	libvlc_media_list_player_t* mlp = libvlc_media_list_player_new(inst);

	libvlc_media_list_add_media(ml, m);
	libvlc_media_release(m);

	libvlc_media_list_player_set_media_list(mlp, ml);
	libvlc_media_list_player_set_media_player(mlp, mp);
	libvlc_media_list_player_set_playback_mode(mlp, libvlc_playback_mode_loop);	// 循环播放
	libvlc_media_player_set_hwnd(mp, drawbale);
	libvlc_audio_set_volume(mp, 100);
	libvlc_media_list_player_play(mlp);
	std::cin.get();
}