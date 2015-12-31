// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <osgViewer\View>
#include <osgViewer\Viewer>
#include <osgDB\ReadFile>
#include <osg\Point>
#include "..\osgPC\PointCloudProtocal.h"
#include "..\osgPC\DisplayModeNodeVisitor.h"
#include <osgViewer\ViewerEventHandlers>
#include "..\osgPC\SwitchNodeVisitor.h"


using namespace osgGA;

class ColorHandler : public osgGA::GUIEventHandler
{
public:
    ColorHandler(osg::Node* node)
    : _node(node){}

    virtual bool handle(const GUIEventAdapter& ea, GUIActionAdapter& ga)
    {
        if (ea.getEventType() == GUIEventAdapter::KEYDOWN)
        {
            switch (ea.getKey())
            {
            case osgGA::GUIEventAdapter::KEY_T:
                {
                    osgPC::ShareData shareData;
                    shareData.displayMode = osgPC::ShareData::HEIGHT;
                    shareData.minHeight = 13.075;
                    shareData.maxHeight = 31.795;
                    osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
                    pcp.writeShareBuffer(shareData);
                    osgPC::DisplayModeNodeVisitor dmnv;
                    dmnv.updateShareData();
                    _node->accept(dmnv);
                    //osgPC::PointCloudGeometry* pcg = dynamic_cast<osgPC::PointCloudGeometry*>(_node->asGroup()->getChild(0)->asGeode()->getDrawable(0));
                    break;
                }
			case osgGA::GUIEventAdapter::KEY_P:
				{
					osg::Vec3d color(1.f, 1.f, 0.f);
					osgPC::ShareData shareData;
					shareData.displayMode = osgPC::ShareData::ASSIGNCOLOR;
					shareData.assignColor = color;
					osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
					pcp.writeShareBuffer(shareData);
					osgPC::DisplayModeNodeVisitor dmnv;
					dmnv.updateShareData();
					_node->accept(dmnv);
					break;
				}
			case osgGA::GUIEventAdapter::KEY_O:
				{
					osgPC::ShareData shareData;
					shareData.displayMode = osgPC::ShareData::INTENSITY;
					shareData.minIntensity = 1;
					shareData.maxIntensity = 2047;
					osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
					pcp.writeShareBuffer(shareData);
					osgPC::DisplayModeNodeVisitor dmnv;
					dmnv.updateShareData();
					_node->accept(dmnv);
					break;
				}
			case osgGA::GUIEventAdapter::KEY_8:
				{
					osgPC::ShareData shareData;
					shareData.displayMode = osgPC::ShareData::CLASS;
					shareData.switchMode[5] = FALSE;
					shareData.switchMode[1] = false;
					const osgPC::ShareData & sd = shareData;
					osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
					pcp.writeShareBuffer(shareData);
					osgPC::SwitchNodeVisitor dmnv;
					dmnv.updateShareData();
					_node->accept(dmnv);
					//osgPC::DisplayModeNodeVisitor dmnv;
					//dmnv.updateShareData();
					//_node->accept(dmnv);

					break;
				}
            default:
                break;
            }
            return false;
        }
        else
            return false;
    }

private:
    osg::Node*  _node;

};

int _tmain(int argc, _TCHAR* argv[])
{
    //std::string filename = "E:\\Works\\lidar\\osg\\hd\\cache\\00656.lasdb";
    //std::string filename = "E:\\Works\\lidar\\osg\\hd\\cache\\035.lasdb";
    //std::string filename = "E:\\Works\\lidar\\osg\\testdata3_cache\\cache\\0.lasdb";
    //std::string filename = "E:\\Works\\lidar\\osg\\testdata5_cache\\cache\\0311.lasdb";
    //osgDB::ReaderWriter::ReadResult rs = rw->readNode(filename);
    //osg::Object* obj = rs.getObject();	//getObject是返回rs中的_object，并且没有增加引用计数，因此rs内存释放后obj所指向的便是不确定的内容
    //osg::Object* obj = rs.takeObject();		//取出rs中的_object，增加引用计数，并将rs中的_object赋值为NULL，再减少一次引用级数（unref_nodelete）
    //osg::Geode* geode = dynamic_cast<osg::Geode*>(obj);	//通过这种方式获得的节点，setSceneData时报错，可能无法直接用getNode得到节点
    osgViewer::Viewer viewer;
    osg::Group* group = new osg::Group;
    //group->addChild(osgDB::readNodeFile("E:\\Works\\lidar\\osg\\hd\\cache\\00656.lasdb"));
    //osg::Node* geode = osgDB::readNodeFile("E:\\Dev\\Labs\\Point2Model安装包\\data\\tt_c2\\cache\\0.lasdb");
	osg::Node* geode = osgDB::readNodeFile("E:\\result_cache\\cache\\07507.lasdb");
    group->addChild(geode);
    group->getOrCreateStateSet()->setAttributeAndModes(new osg::Point(1.f), osg::StateAttribute::ON);
    osg::Light* light = new osg::Light;
    light->setAmbient(osg::Vec4(0.f, 0.f, 0.f, 1.f));
    group->getOrCreateStateSet()->setAttributeAndModes(light, osg::StateAttribute::ON);
	viewer.getDatabasePager()->registerPagedLODs(geode);
    viewer.setSceneData(group);
	//viewer.addEventHandler(new osgViewer::WindowSizeHandler);

	viewer.setUpViewInWindow(100, 100, 800, 600);
	//viewer.getEventQueue()->windowResize(100, 100, 400, 300); //没起作用
	viewer.addEventHandler(new osgViewer::StatsHandler);

    viewer.realize();



    osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
    bool rs = pcp.createShareBuffer();


	/*osgPC::ShareData shareData;
	shareData.displayMode = osgPC::ShareData::HEIGHT;
	shareData.minHeight = -63.227;
	shareData.maxHeight = 378.997;
	pcp.writeShareBuffer(shareData);
	osgPC::DisplayModeNodeVisitor dmnv;
	dmnv.updateShareData();
	group->accept(dmnv);
	osgPC::PointCloudGeometry* pcg = dynamic_cast<osgPC::PointCloudGeometry*>(group->asGroup()->getChild(0)->asGeode()->getDrawable(0));*/
	std::vector<int > a(5);
	rs = (a.size() - 1) <= -6 ;


    viewer.addEventHandler(new ColorHandler(group));
    viewer.run();

	return 0;
}

