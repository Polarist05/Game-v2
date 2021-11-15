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
public:
	
	static void SaveScoreboard();
	static void SaveAllRoomPrefab();
	static void RefreshRoomPrefrab();
	static void LoadData();
};

