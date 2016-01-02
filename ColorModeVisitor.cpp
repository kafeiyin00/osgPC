#include "stdafx.h"
#include "ColorModeVisitor.h"
#include "PointCloudDrawable.h"

#include <osg/Geode>
using namespace osgPC;

ColorModeVisitor::ColorModeVisitor() 
	:osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
	osgPC::ShareDataSingleton* ss = osgPC::ShareDataSingleton::Instance();
	ss->getColorMode(_colormode);
}


ColorModeVisitor::~ColorModeVisitor()
{
}

void ColorModeVisitor::apply(osg::Node& node)
{
	osg::Geode* geode = node.asGeode();
	if (geode != nullptr)
	{
		for (int i = 0; i < geode->getNumDrawables(); ++i)
		{
			PointCloudGeometry* pcg = dynamic_cast<PointCloudGeometry*>(geode->getDrawable(i));
			if (pcg != nullptr)
			{
				pcg->refreshDisplayMode(_colormode);
			}
		}
	}
	traverse(node);
}
