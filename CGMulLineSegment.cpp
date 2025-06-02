﻿#include "pch.h" // 如果你的项目使用了预编译头文件
#include "CGMulLineSegment.h"
#include <gl/GL.h> // 包含 OpenGL 头文件

// 将实现序列化宏中的类名修改为 CGMulLineSegment
IMPLEMENT_SERIAL(CGMulLineSegment, CGGeometry, 1)

CGMulLineSegment::CGMulLineSegment()
	: mClosed(false)
{
}

CGMulLineSegment::CGMulLineSegment(const std::vector<glm::dvec3>& points)
	: mPoints(points), mClosed(false)
{
}

CGMulLineSegment::CGMulLineSegment(const std::vector<glm::dvec3>& points, bool closed)
	: mPoints(points), mClosed(closed)
{
}

CGMulLineSegment::~CGMulLineSegment()
{
}

void CGMulLineSegment::Serialize(CArchive& ar)
{
	CGGeometry::Serialize(ar); // 调用基类的序列化方法

	if (ar.IsStoring())
	{
		// 保存数据
		ar << (int)mPoints.size(); // 保存点的数量
		for (const auto& point : mPoints)
		{
			// 使用 << 运算符序列化每个点的分量
			ar << point.x << point.y << point.z;
		}
		ar << mClosed; // 保存闭合状态
	}
	else
	{
		// 加载数据
		int numPoints;
		ar >> numPoints; // 加载点的数量
		mPoints.resize(numPoints); // 调整点列表大小
		for (int i = 0; i < numPoints; ++i)
		{
			// 使用 >> 运算符反序列化每个点的分量
			ar >> mPoints[i].x >> mPoints[i].y >> mPoints[i].z;
		}
		ar >> mClosed; // 加载闭合状态
	}
}

// 渲染
bool CGMulLineSegment::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;

	// 检查是否有足够的点来绘制线段
	if (mPoints.size() < 2)
	{
		return false; // 少于两个点无法形成线段
	}

	// 设置绘制颜色 (仿照 CGLineSegment 使用白色)
	glColor3f(1.0f, 1.0f, 1.0f); // 白色

	// 使用 GL_LINE_STRIP 绘制连续的线段
	glBegin(GL_LINE_STRIP);
	for (const auto& point : mPoints)
	{
		glVertex3f(point.x, point.y, point.z); // 添加点到线段序列
	}
	glEnd();

	// 如果折线闭合，需要单独绘制从最后一个点到第一个点的线段
	if (mClosed && mPoints.size() >= 2)
	{
		glBegin(GL_LINES);
		glVertex3f(mPoints.back().x, mPoints.back().y, mPoints.back().z); // 最后一个点
		glVertex3f(mPoints.front().x, mPoints.front().y, mPoints.front().z); // 第一个点
		glEnd();
	}

	return true;
}

void CGMulLineSegment::AddPoint(const glm::dvec3& point)
{
	mPoints.push_back(point);
}

void CGMulLineSegment::Translate(float tx, float ty) {
	// 遍历所有点并应用平移
	for (auto& point : mPoints) {
		point.x += tx; // x 坐标平移
		point.y += ty; // y 坐标平移
		// z 坐标保持不变（如果是 2D 折线）
	}
}

void CGMulLineSegment::Rotate(double angle, double cx, double cy)
{
	// 如果点列表为空，直接返回
	if (mPoints.empty()) {
		return;
	}

	// 创建变换矩阵
	glm::dmat4 transform(1.0); // 初始化为单位矩阵

	// 1. 平移到原点 (将旋转中心移到原点)
	transform = glm::translate(transform, glm::dvec3(-cx, -cy, 0.0));

	// 2. 绕Z轴旋转 (逆时针为正)
	transform = glm::rotate(transform, glm::radians(angle), glm::dvec3(0.0, 0.0, 1.0));

	// 3. 平移回原位置
	transform = glm::translate(transform, glm::dvec3(cx, cy, 0.0));

	// 应用变换到所有点
	for (auto& point : mPoints) {
		// 将点转换为齐次坐标 (w=1)
		glm::dvec4 transformed = transform * glm::dvec4(point, 1.0);

		// 更新点坐标 (除以w分量，虽然这里w=1不需要除)
		point = glm::dvec3(transformed.x, transformed.y, point.z);
	}
}


void CGMulLineSegment::Scale(double sx, double sy, double cx, double cy)
{
	// 1. 创建平移矩阵（将中心点移动到原点）
	glm::dmat4 translateToOrigin = glm::translate(glm::dmat4(1.0), glm::dvec3(-cx, -cy, 0.0));

	// 2. 创建缩放矩阵
	glm::dmat4 scaleMatrix = glm::scale(glm::dmat4(1.0), glm::dvec3(sx, sy, 1.0));

	// 3. 创建反向平移矩阵（将中心点移回原位置）
	glm::dmat4 translateBack = glm::translate(glm::dmat4(1.0), glm::dvec3(cx, cy, 0.0));

	// 4. 组合变换矩阵：T⁻¹ * S * T
	glm::dmat4 transformMatrix = translateBack * scaleMatrix * translateToOrigin;

	// 5. 应用变换到所有点
	for (auto& point : mPoints) {
		glm::dvec4 transformedPoint = transformMatrix * glm::dvec4(point, 1.0);
		point = glm::dvec3(transformedPoint);
	}
}
