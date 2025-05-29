#pragma once
#include "CGGeometry.h"
#include <vector>

// 折线几何体类（继承自CGGeometry）
class CGMulLineSegment : public CGGeometry
{
    DECLARE_SERIAL(CGMulLineSegment)
public:
	// 构造函数
	CGMulLineSegment();
	// 构造函数，接受一个点列表
	CGMulLineSegment(const std::vector<glm::dvec3>& points);
	// 构造函数，可以指定是否闭合
	CGMulLineSegment(const std::vector<glm::dvec3>& points, bool closed);

	// 析构函数
	virtual ~CGMulLineSegment();

	// 序列化
	virtual void Serialize(CArchive& ar) override;

	// 绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);

	// 添加一个点到折线
	void AddPoint(const glm::dvec3& point);

	// 获取折线上的所有点
	const std::vector<glm::dvec3>& GetPoints() const { return mPoints; }

	// 设置折线是否闭合
	void SetClosed(bool closed) { mClosed = closed; }

	// 获取折线是否闭合
	bool IsClosed() const { return mClosed; }

	void Translate(float tx, float ty); //平移

	virtual void Rotate(double angle, double cx, double cy);

	virtual void Scale(double sx, double sy, double cx, double cy);

protected:
	std::vector<glm::dvec3> mPoints; // 存储折线上的点
	bool mClosed; // 标记折线是否闭合（首尾相连）
};
