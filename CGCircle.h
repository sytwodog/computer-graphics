#pragma once
#include "CGGeometry.h"
class CGCircle : public CGGeometry
{
    DECLARE_SERIAL(CGCircle)
public:
    CGCircle();
    CGCircle(const glm::dvec3& center, double radius);
    virtual ~CGCircle();
    //序列化
    virtual void Serialize(CArchive& ar) override;
    //绘制对象（在派生类中重写）
    virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
    //变换
    void Translate(float tx, float ty); //平移
    virtual void Rotate(double angle, double cx, double cy);
    virtual void Scale(double sx, double sy, double cx, double cy);
protected:
    glm::dvec3 mCenter;
    double mRadius;
    const double M_PI = 3.1415926;
};
