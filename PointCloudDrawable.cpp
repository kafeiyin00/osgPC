#include "stdafx.h"
#include "PointCloudDrawable.h"
#include "ColorRamp.h"


using namespace osgPC;


PointCloudGeometry::PointCloudGeometry()
	: _intensities(nullptr), _points(nullptr), _texColors(nullptr), _assignColors(nullptr)
{
}

PointCloudGeometry::PointCloudGeometry(const PointCloudGeometry& pointcloud, const osg::CopyOp& copyop /*= osg::CopyOp::SHALLOW_COPY*/)
{
    _intensities = pointcloud._intensities;
    _points = pointcloud._points;
    _texColors = pointcloud._texColors;
    _bounds = pointcloud._bounds;
	_assignColors = pointcloud._assignColors;
}

void PointCloudGeometry::setPointCloud(osg::Vec3Array* points, const Bounds3d& bounds,
	osg::Vec3 offset, unsigned short* intensities /*= nullptr*/, osg::Vec3Array* texColors /*= nullptr*/, OBJECTCLASS* c)
{
    _points = points;
    _bounds = bounds;
    _texColors = texColors;
    _intensities = intensities;
    _offset = offset;
	_cs = c;
    setVertexArray(_points);
    addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, _points->size()));
	if (_texColors != nullptr)
	{
		int count = _points->size();
		osg::ref_ptr<osg::Vec3Array> currentColors = new osg::Vec3Array(count);
		for (int i = 0; i < count; ++i)
		{
			(*currentColors)[i] = _texColors->at(i);
		}
		setColorArray(currentColors);
	}
	setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    setUseDisplayList(false);
    setUseVertexBufferObjects(true);
}


PointCloudGeometry::~PointCloudGeometry(void)
{
    if (_intensities != nullptr)
        delete _intensities;
	if (_cs != nullptr)
		delete _cs;
}

void PointCloudGeometry::refreshDisplayMode(osgPC::pointColorMode cm)
{
	switch (cm)
	{
	case osgPC::pointColorMode::HEIGHT:
		setColorsByHeight();
		break;
	case osgPC::pointColorMode::INTENSITY:
		setColorsByIntensity();
		break;
	case osgPC::pointColorMode::ASSIGNED:
		setColorsByAssignColor();
		break;
	case osgPC::pointColorMode::RGB:
		setColorsByTexture();
		break;
	case osgPC::pointColorMode::CLASS:
		setColorByClass();
		break;
	default:
		return;
	}
}

void PointCloudGeometry::setColorsByAssignColor()
{
	osg::Vec3 assignColor(0.6,0.6,0.6);
	int count = _points->size();
	osg::ref_ptr<osg::Vec3Array> currentColors = new osg::Vec3Array();
	currentColors->push_back(assignColor);
	_assignColors = currentColors;
	setColorArray(_assignColors);
	setColorBinding(osg::Geometry::BIND_OVERALL);
}
void PointCloudGeometry::setColorsByTexture()
{
	if (_texColors == nullptr)
		return;
	int count = _points->size();
	osg::ref_ptr<osg::Vec3Array> currentColors = new osg::Vec3Array(count);
	for (int i = 0; i < count; ++i)
	{
		(*currentColors)[i] = _texColors->at(i);
	}
	setColorArray(currentColors);
	setColorBinding(osg::Geometry::BIND_PER_VERTEX);
}
void PointCloudGeometry::setColorsByHeight()
{

}
void PointCloudGeometry::setColorByClass()
{

}
void PointCloudGeometry::setColorsByIntensity()
{

}

