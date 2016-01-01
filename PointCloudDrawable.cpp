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
    //_assignColors = new osg::Vec3Array(_points->size());
    setVertexArray(_points);
    addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, _points->size()));
    //setColorArray(texColors);
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

