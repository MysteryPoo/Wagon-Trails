#pragma once

#include <unordered_map>
#include <string>

using namespace std;

class ImageDatabase
{
	unordered_map<string, int> images;
	int setImage(string);
public:
	~ImageDatabase();
	int getImage(string);
	void removeImage(string fileName);
};