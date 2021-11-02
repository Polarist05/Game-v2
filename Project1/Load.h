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
	static void LoadOtherPrefab(const string& name, const string& path, const IntRect& intRect);
	static void LoadAllASCII();
	static void LoadAllUI();
	static void LoadStartUI();
	static void LoadToolkitUI();
public:
	static void SaveAllRoomPrefab();
	static void RefreshRoomPrefrab();
	static void LoadData();
};

