#include "stdafx.h"
#include "utility.h"

using namespace osgPC;

std::ostream& operator <<(std::ostream& fs, const Point3d& pt)
{
	pt.output(fs);
	return fs;
}