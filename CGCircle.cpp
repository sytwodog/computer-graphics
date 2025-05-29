#include "pch.h"
#include "CGCircle.h"
IMPLEMENT_SERIAL(CGCircle, CGGeometry, 1)
CGCircle::CGCircle()
    : mCenter(glm::dvec3(0.0, 0.0, 0.0)), mRadius(0.0)
{
}
CGCircle::CGCircle(const glm::dvec3& center, double radius)
    : mCenter(center), mRadius(radius)
{
}
CGCircle::~CGCircle()
{
}
void CGCircle::Serialize(CArchive& ar)
{
    CGRenderable::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
    if (ar.IsStoring()) //保存
    {
        ar << mCenter.x << mCenter.y << mCenter.z << mRadius;
    }
    else //读取
    {
        ar >> mCenter.x >> mCenter.y >> mCenter.z >> mRadius;
    }
}
//渲染
bool CGCircle::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
    if (pRC == nullptr || pCamera == nullptr)
        return false;
    glColor3f(1.0f, 1.0f, 1.0f); // 白色
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(mCenter.x, mCenter.y, mCenter.z);
    for (int i = 0; i <= 360; i++) {
        double angle = i * M_PI / 180.0;
        glVertex3f(mCenter.x + mRadius * cos(angle), mCenter.y + mRadius * sin(angle), mCenter.z);
    }
    glEnd();
    return true;
}

void CGCircle::Translate(float tx, float ty)
{
    mCenter.x += tx;
    mCenter.y += ty;
}

void CGCircle::Rotate(double angle, double cx, double cy)
{
    // 将角度转换为弧度（因为三角函数使用弧度）
    double radians = angle * (M_PI / 180.0);

    // 计算旋转矩阵的元素
    double cosTheta = cos(radians);
    double sinTheta = sin(radians);

    // 创建旋转矩阵
    glm::mat2 rotationMatrix(cosTheta, sinTheta, -sinTheta, cosTheta);

    // 对圆心进行旋转
    glm::dvec2 centerRel = glm::dvec2(mCenter.x - cx, mCenter.y - cy);
    glm::dvec2 rotatedCenter = rotationMatrix * centerRel;
    mCenter.x = rotatedCenter.x + cx;
    mCenter.y = rotatedCenter.y + cy;
}

void CGCircle::Scale(double sx, double sy, double cx, double cy)
{
    // 1. 创建平移矩阵（将缩放中心点移动到原点）
    glm::dmat4 translateToOrigin = glm::translate(glm::dmat4(1.0), glm::dvec3(-cx, -cy, 0.0));

    // 2. 创建缩放矩阵
    glm::dmat4 scaleMatrix = glm::scale(glm::dmat4(1.0), glm::dvec3(sx, sy, 1.0));

    // 3. 创建反向平移矩阵（将中心点移回原位置）
    glm::dmat4 translateBack = glm::translate(glm::dmat4(1.0), glm::dvec3(cx, cy, 0.0));

    // 4. 组合变换矩阵：T⁻¹ * S * T
    glm::dmat4 transformMatrix = translateBack * scaleMatrix * translateToOrigin;

    // 5. 对圆心应用变换
    glm::dvec4 transformedCenter = transformMatrix * glm::dvec4(mCenter, 1.0);
    mCenter = glm::dvec3(transformedCenter);

    // 6. 更新半径
    mRadius *= (sx + sy) / 2.0;
}
