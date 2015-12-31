#pragma once

#include <vector>
#include <osg/Vec3>
#include <osg/Array>

namespace osgPC{//namespace osgPC

template <typename T>
class ColorRamp
{
public:
    ColorRamp(const T& minValue, const T& maxValue);
    ColorRamp(const T& minValue, const T& maxValue, const std::vector<osg::Vec3>& endPointColors);
    ~ColorRamp() {}
    void getColor(const T& val, osg::Vec3& color) const;
    void getColors(const std::vector<T>& vals, osg::Vec3Array* colors);
    void getColors(const T* vals, unsigned int count, osg::Vec3Array* colors);
    static osg::Vec3 getColor(const T& val, const T& sectionLength, const osg::Vec3& stColor,
        const osg::Vec3& endColor);
    static std::vector<osg::Vec3> generateStdEndPtColors();

private:
    T _minValue;
    T _maxValue;
    T _rampLength;
    double _sectionLength;
    std::vector<osg::Vec3> _endPointColors;
};

template <typename T>
osgPC::ColorRamp<T>::ColorRamp(const T& minValue, const T& maxValue)
: _minValue(minValue), _maxValue(maxValue)
{
    _endPointColors = generateStdEndPtColors();
    _rampLength = maxValue - minValue;
    _sectionLength = double(_rampLength) / _endPointColors.size();
}

template <typename T>
osgPC::ColorRamp<T>::ColorRamp(const T& minValue, const T& maxValue, const std::vector<osg::Vec3>& endPointColors)
: _minValue(minValue), _maxValue(maxValue), _endPointColors(endPointColors)
{
    _rampLength = maxValue - minValue;
    _sectionLength = double(_rampLength) / endPointColors.size();
}

template <typename T>
std::vector<osg::Vec3> osgPC::ColorRamp<T>::generateStdEndPtColors()
{
    std::vector<osg::Vec3> endPointColors;
    endPointColors.push_back(osg::Vec3(0.f, 0.f, 1.f));
    endPointColors.push_back(osg::Vec3(0.f, 1.f, 1.f));
    endPointColors.push_back(osg::Vec3(0.f, 1.f, 0.f));
    endPointColors.push_back(osg::Vec3(1.f, 1.f, 0.f));
    endPointColors.push_back(osg::Vec3(1.f, 0.f, 0.f));
    return endPointColors;
}

template <typename T>
void osgPC::ColorRamp<T>::getColors(const T* vals, unsigned int count, osg::Vec3Array* colors)
{
    if (colors->size() != count)
    {
        colors->resize(count);
    }
    for (int i = 0; i < count; i++)
    {
        osg::Vec3 c;
        getColor(vals[i], c);
        (*colors)[i] = c;
    }
}

template <typename T>
void osgPC::ColorRamp<T>::getColors(const std::vector<T>& vals, osg::Vec3Array* colors)
{
    if (colors->size() != vals.size())
    {
        colors->resize(vals.size());
    }
    for (int i = 0, count = vals.size(); i < count; i++)
    {
        osg::Vec3 c;
        getColor(vals[i], c);
        (*colors)[i] = c;
    }
}

template <typename T>
inline osg::Vec3 osgPC::ColorRamp<T>::getColor(const T& val, const T& sectionLength,
    const osg::Vec3& stColor, const osg::Vec3& endColor)
{
    double ratio = (double)val / sectionLength;
    osg::Vec3 c;
    for (int i = 0; i < 3; i++)
    {
        c._v[i] = (endColor._v[i] - stColor._v[i]) * ratio + stColor._v[i];
    }
    return c;
}

template <typename T>
void osgPC::ColorRamp<T>::getColor(const T& val, osg::Vec3& color) const
{
    T relevant_val = val - _minValue;
    int index(relevant_val / _sectionLength);
	int maxIndex = _endPointColors.size() - 1;
    if (index >= maxIndex)
    {
        index = _endPointColors.size() - 1;
        color = _endPointColors[index];
    }
	else if (index < 0)	//考虑噪点小于统计出的最低高程的情况  modified by zhaogang. 2014.09.23
	{
		index = 0;
		color = _endPointColors[index];
	}
    else
    {
        double remainder = relevant_val - _sectionLength * index;
        color = getColor(remainder, _sectionLength, _endPointColors[index], _endPointColors[index + 1]);
    }
}

}//end namespace osgPC