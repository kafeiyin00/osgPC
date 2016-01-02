#include "stdafx.h"
#include "ShareDataSingleton.h"
using namespace osgPC;

ShareDataSingleton* ShareDataSingleton::_instance = nullptr;

ShareDataSingleton::ShareDataSingleton()
{
	_colorMode = pointColorMode::RGB;
}


ShareDataSingleton::~ShareDataSingleton()
{
}

ShareDataSingleton* ShareDataSingleton::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new ShareDataSingleton;
	}
	return _instance;
}

void ShareDataSingleton::setColorMode(const pointColorMode c)
{
	_colorMode = c;
}
void ShareDataSingleton::getColorMode(pointColorMode &c)
{
	c = _colorMode;
}
