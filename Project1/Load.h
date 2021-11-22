#pragma once
#include <iostream>
#include "SFML.h"
using namespace std;
class Load
{
	static void LoadAllRoomPrefab();
	static void LoadAllObjectPrefab();
	static void LoadPlayerPerfab();
	static void LoadAllOtherPrefab();
	static void LoadObjectPrefab(const string& name, const string& path, const IntRect& intRect);
	static void LoadOtherPrefab(const string& name, const string& path, const IntRect& intRect);
	static void LoadAllASCII();
	static void LoadScoreboard();
	static void LoadAudio();
	static void LoadMusic();
public:
	static void LoadSingleSoundBuffer(const std::string& name, const std::string& path, const std::string& type,bool isLoop);
	static void SaveScoreboard();
	static void SaveAllRoomPrefab();
	static void RefreshRoomPrefrab();
	static void LoadData();
};

