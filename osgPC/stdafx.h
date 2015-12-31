// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>



#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "openThreadsd.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#else
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#endif