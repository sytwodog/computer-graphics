#include "pch.h"
#include "CGSphere.h"
#include <cmath>

IMPLEMENT_SERIAL(CGSphere, CGRenderable, 1)

CGSphere::CGSphere()
{
}

CGSphere::CGSphere(double radius, int latitude, int longitude)
    : mRadius(radius), mLatitude(latitude), mLongitude(longitude)
{
}

CGSphere::~CGSphere()
{
}

void CGSphere::Serialize(CArchive& ar)
{
    CGRenderable::Serialize(ar);
    ar << mRadius << mLatitude << mLongitude;
}

bool CGSphere::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
    if (mDisplayListEnabled && mDisplayListDirty)
    {
        deleteDisplayList();
        buildDisplayList();
    }
    if (mDisplayList)
    {
        glCallList(mDisplayList);
    }
    return true;
}

void CGSphere::buildDisplayList()
{
    deleteDisplayList();
    mDisplayList = glGenLists(1);
    glNewList(mDisplayList, GL_COMPILE);

    
    const double PI = 3.14159265358979323846;
    double stackDelta = 2.0 * PI / mLongitude;  // ����ϸ�֣���Z�ᣩ
    double sliceDelta = PI / mLatitude;         // γ��ϸ�֣���Z�ᣩ

    glColor3f(0.0f, 1.0f, 0.0f); // �����߿���ɫΪ��ɫ

    for (int stack = 0; stack < mLongitude; ++stack) {
        double theta1 = stack * stackDelta;
        double theta2 = (stack + 1) * stackDelta;

        glBegin(GL_QUAD_STRIP);
        for (int slice = 0; slice <= mLatitude; ++slice) {
            double phi = slice * sliceDelta;
            double sinPhi = sin(phi);
            double cosPhi = cos(phi);

            // ���㷨�ߺͶ�������
            for (int i = 0; i < 2; ++i) {
                double theta = (i == 0) ? theta1 : theta2;
                double x = cos(theta) * sinPhi * mRadius;
                double y = sin(theta) * sinPhi * mRadius;
                double z = cosPhi * mRadius;

                glNormal3d(x / mRadius, y / mRadius, z / mRadius);
                glVertex3d(x, y, z);
            }
        }
        glEnd();
    }

    // �������γ�Ȼ�
    for (int slice = 0; slice < mLatitude; ++slice) {
        double phi = slice * sliceDelta;
        double sinPhi = sin(phi);
        double cosPhi = cos(phi);

        glBegin(GL_LINE_LOOP);
        for (int stack = 0; stack <= mLongitude; ++stack) {
            double theta = stack * stackDelta;
            double x = cos(theta) * sinPhi * mRadius;
            double y = sin(theta) * sinPhi * mRadius;
            double z = cosPhi * mRadius;

            glNormal3d(x / mRadius, y / mRadius, z / mRadius);
            glVertex3d(x, y, z);
        }
        glEnd();
    }

    glEndList();
}