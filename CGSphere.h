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

    // ���л�
    virtual void Serialize(CArchive& ar) override;

    // ���ƶ���������������д��
    virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera) override;

    // ���úͻ�ȡ�������
    void setRadius(double radius) { mRadius = radius; }
    double getRadius() const { return mRadius; }
    void setLatitude(int latitude) { mLatitude = latitude; }
    int getLatitude() const { return mLatitude; }
    void setLongitude(int longitude) { mLongitude = longitude; }
    int getLongitude() const { return mLongitude; }

protected:
    virtual void buildDisplayList() override; // ��д�����麯��

private:
    double mRadius; // �뾶
    int mLatitude;   // γ��ϸ������
    int mLongitude;  // ����ϸ������
    const double M_PI = 3.1415926;
};