#ifndef COLORMODEVISTOR_H
#define COLORMODEVISTOR_H

#include <osg/NodeVisitor>
#include "ShareDataSingleton.h"

namespace osgPC{
	class OSG_EXPORT ColorModeVisitor
		:public osg::NodeVisitor
	{
	public:
		ColorModeVisitor();
		~ColorModeVisitor();

		virtual void apply(osg::Node& node);
	private:
		osgPC::pointColorMode _colormode;
	};
}


#endif