#pragma once
#include "CGRenderable.h"
#include <glm/glm.hpp>

class CGSphere : public CGRenderable
{
    DECLARE_SERIAL(CGSphere)
public:
    CGSphere();
    CGSphere(double radius, int latitude, int longitude);
    virtual ~CGSphere();

    // 序列化
    virtual void Serialize(CArchive& ar) override;

    // 绘制对象（在派生类中重写）
    virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera) override;

    // 设置和获取球体参数
    void setRadius(double radius) { mRadius = radius; }
    double getRadius() const { return mRadius; }
    void setLatitude(int latitude) { mLatitude = latitude; }
    int getLatitude() const { return mLatitude; }
    void setLongitude(int longitude) { mLongitude = longitude; }
    int getLongitude() const { return mLongitude; }

protected:
    virtual void buildDisplayList() override; // 重写基类虚函数

private:
    double mRadius; // 半径
    int mLatitude;   // 纬度细分数量
    int mLongitude;  // 经度细分数量
    const double M_PI = 3.1415926;
};