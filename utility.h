#pragma once

#include <osg/Export>
#include <fstream>

namespace osgPC{	//namespace osgPC

const int OBJECTCLASS_NUM = 11;

enum OBJECTCLASS
{
	NONE = -1,		//未启用类别
	UNKNOWN = 0,	//未知类别
	GROUND,			//地面;
	BUILDING,       //建筑物;
	UTILITYPOLE,    //电线杆;
	TRAFFICSIGN,    //交通标志牌;
	TREE,           //树;
	STREETLAMP,     //路灯;
	ENCLOSURE,      //围墙;
	CAR,            //汽车;
	CURB,           //路坎;
	ROADMARKING		//交通标线;	
};

struct Point3d
{
	double	x;
	double	y;
	double	z;
	//int	   code;

	Point3d(){ x = y = z = 0.0;}

	Point3d(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	virtual ~Point3d(){}

	virtual void output(std::ostream& out)
	{
		(static_cast<const Point3d*>(this))->output(out);
	}

	virtual void output(std::ostream& out) const
	{
		float fx = x;
		float fy = y;
		float fz = z;
		out.write(reinterpret_cast<const char*>(&fx), sizeof(float));
		out.write(reinterpret_cast<const char*>(&fy), sizeof(float));
		out.write(reinterpret_cast<const char*>(&fz), sizeof(float));
	}

	void relative(const Point3d& offset)
	{
		x -= (int)offset.x;
		y -= (int)offset.y;
		z -= (int)offset.z;
	}
};

struct IntensityPoint3d : Point3d
{
	unsigned short i;

	IntensityPoint3d()
		: Point3d()
	{
		this->i = -1;
	}

	IntensityPoint3d(double x, double y, double z, unsigned short i)
		: Point3d(x, y, z)
	{
		this->i = i;
	}

	virtual ~IntensityPoint3d() {}

	virtual void output(std::ostream& out)
	{
		(static_cast<const IntensityPoint3d*>(this))->output(out);
	}

	virtual void output(std::ostream& out) const
	{
		Point3d::output(out);
		out.write(reinterpret_cast<const char*>(&i), sizeof(unsigned short));
	}
};

//! 带颜色的点云
/*!
  带颜色而不带强度的点云类型
  *注意：没有将ColorPoint3d作为ColorIntensityPoint3d的基类，主要是避免多重继承
  *而且xyzirgb的格式继承自xyzi的格式也更为合理
*/
struct ColorPoint3d : Point3d
{
	unsigned short r;
	unsigned short g;
	unsigned short b;

	ColorPoint3d()
		: Point3d()
	{
		r = g = b = 255;
	}

	ColorPoint3d(double x, double y, double z, unsigned short r,
		unsigned short g, unsigned short b)
		: Point3d(x, y, z)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	virtual ~ColorPoint3d() {}

	virtual void output(std::ostream& out)
	{
		(static_cast<const ColorPoint3d*>(this))->output(out);
	}

	virtual void output(std::ostream& out) const
	{
		Point3d::output(out);
		out.write(reinterpret_cast<const char*>(&r), sizeof(unsigned short));
		out.write(reinterpret_cast<const char*>(&g), sizeof(unsigned short));
		out.write(reinterpret_cast<const char*>(&b), sizeof(unsigned short));
	}
};

struct ColorIntensityPoint3d : IntensityPoint3d
{
	unsigned short r;
	unsigned short g;
	unsigned short b;

	ColorIntensityPoint3d()
		: IntensityPoint3d()
	{
		this->r = this->g = this->b = 255;
	}

	ColorIntensityPoint3d(double x, double y, double z, unsigned short i, unsigned short r, unsigned short g, unsigned short b)
		: IntensityPoint3d(x, y, z, i)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	virtual void output(std::ostream& out)
	{
		(static_cast<const ColorIntensityPoint3d*>(this))->output(out);
	}

	virtual void output(std::ostream& out) const
	{
		IntensityPoint3d::output(out);
		out.write(reinterpret_cast<const char*>(&r), sizeof(unsigned short));
		out.write(reinterpret_cast<const char*>(&g), sizeof(unsigned short));
		out.write(reinterpret_cast<const char*>(&b), sizeof(unsigned short));
	}
};

/**
 * @brief ClassPoint3d	: 具有类别的点云，类别由OBJECTCLASS枚举指定，并在显示时按照类别赋色
 */
struct ClassPoint3d : public Point3d
{
	OBJECTCLASS c;

public:
	ClassPoint3d()
		: Point3d()
	{
		this->c = UNKNOWN;
	}

	ClassPoint3d(double x, double y, double z, OBJECTCLASS c)
		: Point3d(x, y, z)
	{
		this->c = c;
	}

	virtual ~ClassPoint3d() {}

	
	virtual void output(std::ostream& out)
	{
		(static_cast<const ClassPoint3d*>(this))->output(out);
	}

	virtual void output(std::ostream& out) const
	{
		Point3d::output(out);
		out.write(reinterpret_cast<const char*>(&c), sizeof(OBJECTCLASS));
	}
};

// [5/6/2015 jianping]
// --------------TimePoint--------------
struct TimePoint3d : public Point3d
{
	OBJECTCLASS c;
	double gpstime;
	unsigned short r;
	unsigned short g;
	unsigned short b;
	unsigned short i;

public:
	TimePoint3d()
		: Point3d()
	{
		this->gpstime = 0;
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->i = 0;
		this->c = UNKNOWN;
	}

	TimePoint3d(double x, double y, double z, double gpstime, unsigned short r, unsigned short g , unsigned short b, unsigned short i, OBJECTCLASS c)
		: Point3d(x, y, z)
	{
		this->gpstime = gpstime;
		this->r = r;
		this->g = g;
		this->b = b;
		this->i = i;
		this->c = c;
	}

	virtual ~TimePoint3d(){}

	virtual void output(std::ostream& out)
	{
		(static_cast<const TimePoint3d*>(this))->output(out);
	}

	virtual void output(std::ostream& out) const
	{
		float fgpstime = gpstime;
		Point3d::output(out);
		out.write(reinterpret_cast<const char*>(&r), sizeof(unsigned short));
		out.write(reinterpret_cast<const char*>(&g), sizeof(unsigned short));
		out.write(reinterpret_cast<const char*>(&b), sizeof(unsigned short));
		out.write(reinterpret_cast<const char*>(&i), sizeof(unsigned short));
		out.write(reinterpret_cast<const char*>(&fgpstime), sizeof(float));
		out.write(reinterpret_cast<const char*>(&c), sizeof(OBJECTCLASS));
	}
};

struct Point2d
{
	double x;
	double y;

	void relative(const Point2d& offset)
	{
		x -= (int)offset.x;
		y -= (int)offset.y;
	}
};

struct Bounds
{
	double minx;
	double miny;
	double maxx;
	double maxy;

	Bounds()
	{
		minx = miny = DBL_MAX;
		maxx = maxy = -DBL_MAX;
	}

	Bounds(double minx, double miny, double maxx, double maxy)
	{
		this->minx = minx;
		this->maxx = maxx;
		this->miny = miny;
		this->maxy = maxy;
	}

	Point2d center()
	{
		Point2d pt_center = {(minx + maxx) / 2, (miny + maxy) / 2};
		return pt_center;
	}

    double width() const
	{
		return maxx - minx;
	}

    double height() const
	{
		return maxy - miny;
	}

    double area() const
	{
		return width() * height();
	}

	bool contains(const Point3d& pt) const
	{
		return (pt.x >= minx && pt.x <= maxx) && (pt.y >= miny && pt.y <= maxy);
	} 

    bool contains(const Point2d& pt) const
	{
		return (pt.x >= minx && pt.x <= maxx) && (pt.y >= miny && pt.y <= maxy);
	}

    bool contains(double x, double y) const
    {
        return (x >= minx && x <= maxx) && (y >= miny && y <= maxy);
    }
};

struct Bounds3d
{
	double minx;
	double miny;
	double minz;
	double maxx;
	double maxy;
	double maxz;

	Bounds3d()
	{
		reset();
	}

	Bounds3d(double minx, double miny, double minz, double maxx, double maxy, double maxz)
	{
		this->minx = minx;
		this->maxx = maxx;
		this->miny = miny;
		this->maxy = maxy;
		this->minz = minz;
		this->maxz = maxz;
	}

	void reset()
	{
		minx = miny = minz = DBL_MAX;
		maxx = maxy = maxz = -DBL_MAX;
	}

	Point3d center()
	{
		return Point3d((minx + maxx) / 2, (miny + maxy) / 2, (minz +maxz) / 2);
	}

	double length()
	{
		return maxx - minx;
	}

	double width()
	{
		return maxy - miny;
	}

	double height()
	{
		return maxz - minz;
	}

	void expand(const Point3d& pt)
	{
		if(pt.x < minx) minx = pt.x;
		if(pt.x > maxx) maxx = pt.x;
		if(pt.y < miny) miny = pt.y;
		if(pt.y > maxy) maxy = pt.y;
		if(pt.z < minz) minz = pt.z;
		if(pt.z > maxz) maxz = pt.z;
	}

	void expand(double x, double y, double z)
	{
		if(x < minx) minx = x;
		if(x > maxx) maxx = x;
		if(y < miny) miny = y;
		if(y > maxy) maxy = y;
		if(z < minz) minz = z;
		if(z > maxz) maxz = z;
	}

	void combine(const Bounds3d& bound)
	{
		if(minx > bound.minx) minx = bound.minx;
		if(maxx < bound.maxx) maxx = bound.maxx;
		if(miny > bound.miny) miny = bound.miny;
		if(maxy < bound.maxy) maxy = bound.maxy;
		if(minz > bound.minz) minz = bound.minz;
		if(maxz < bound.maxz) maxz = bound.maxz;
	}

	bool contains(const Point3d& pt)
	{
		return (pt.x >= minx && pt.x <= maxx) && (pt.y >= miny && pt.y <= maxy) && (pt.z >= minz && pt.z <= maxz);
	}

	operator Bounds()
	{
		return Bounds(minx, miny, maxx, maxy);
	}
};

//非内联报错
//extern OSG_EXPORT std::ostream& operator <<(std::ostream& fs, const osgPC::Point3d& pt);

}//end namespace osgPC

/**
 *输出点数据
 */
extern OSG_EXPORT std::ostream& operator <<(std::ostream& fs, const osgPC::Point3d& pt);