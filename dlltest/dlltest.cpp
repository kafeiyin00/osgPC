// dlltest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "./../PointCloudDrawable.h"
#include "./../ShareDataSingleton.h"
#include "./..//ColorModeVisitor.h"
#include <osgDB/ReadFile>
#include <string>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
int _tmain(int argc, _TCHAR* argv[])
{
	std::string filename;
	std::cin >> filename;
	osgPC::ShareDataSingleton::Instance()->setColorMode(osgPC::pointColorMode::ASSIGNED);
	osg::ref_ptr<osgPC::PointCloudGeometry> pcg =
		dynamic_cast<osgPC::PointCloudGeometry*>(osgDB::readNodeFile(filename));
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	geode->addChild(pcg.get());
	root->addChild(geode.get());

	osg::ref_ptr<osgPC::ColorModeVisitor> vistor = new osgPC::ColorModeVisitor();
	root->accept(*vistor);

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	viewer->setSceneData(root.get());
	viewer->run();

	return 0;
}

