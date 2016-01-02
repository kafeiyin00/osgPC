#ifndef SHARE_DATA_SINGLETON_H
#define SHARE_DATA_SINGLETON_H
#include <osg/Object>
namespace osgPC{
	enum pointColorMode
	{
		HEIGHT = 0,
		ASSIGNED = 1,
		RGB = 2,
		INTENSITY = 3,
		CLASS = 4
	};
	class OSG_EXPORT ShareDataSingleton
	{
	public:
		static ShareDataSingleton* Instance();
		~ShareDataSingleton();
		void setColorMode(const pointColorMode c);
		void getColorMode(pointColorMode &c);
	protected:
		ShareDataSingleton();
	private:
		static ShareDataSingleton* _instance;
		pointColorMode _colorMode;
	};
}

#endif

