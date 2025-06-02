#pragma once
#include "CGGeometry.h"
class CGCircle : public CGGeometry
{
    DECLARE_SERIAL(CGCircle)
public:
    CGCircle();
    CGCircle(const glm::dvec3& center, double radius);
    virtual ~CGCircle();
    //���л�
    virtual void Serialize(CArchive& ar) override;
    //���ƶ���������������д��
    virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
    //�任
    void Translate(float tx, float ty); //ƽ��
    virtual void Rotate(double angle, double cx, double cy);
    virtual void Scale(double sx, double sy, double cx, double cy);
protected:
    glm::dvec3 mCenter;
    double mRadius;
    const double M_PI = 3.1415926;
};
