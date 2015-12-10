#include "ImageDatabase.h"
#include "agk.h"

using namespace std;
using namespace AGK;

int ImageDatabase::setImage(string fileName)
{
	int index = agk::LoadImage(fileName.c_str());
	images[fileName] = index;
	return index;
}

ImageDatabase::~ImageDatabase()
{
	for (auto i = images.begin(); i != images.end(); ++i)
	{
		agk::DeleteImage(i->second);
		i->second = 0;
	}
}

int ImageDatabase::getImage(string fileName)
{
	int index = images[fileName];
	if (index == 0)
		return setImage(fileName);
	else
		return index;
}

void ImageDatabase::removeImage(string fileName)
{
	int index = images[fileName];
	if (index != 0)
	{
		if (agk::GetImageExists(index))
		{
			agk::DeleteImage(index);
		}
		images[fileName] = 0;
	}
}
