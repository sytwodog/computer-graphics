#pragma once
#include "CGGeometry.h"
#include <vector>

// ���߼������ࣨ�̳���CGGeometry��
class CGMulLineSegment : public CGGeometry
{
    DECLARE_SERIAL(CGMulLineSegment)
public:
	// ���캯��
	CGMulLineSegment();
	// ���캯��������һ�����б�
	CGMulLineSegment(const std::vector<glm::dvec3>& points);
	// ���캯��������ָ���Ƿ�պ�
	CGMulLineSegment(const std::vector<glm::dvec3>& points, bool closed);

	// ��������
	virtual ~CGMulLineSegment();

	// ���л�
	virtual void Serialize(CArchive& ar) override;

	// ���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);

	// ���һ���㵽����
	void AddPoint(const glm::dvec3& point);

	// ��ȡ�����ϵ����е�
	const std::vector<glm::dvec3>& GetPoints() const { return mPoints; }

	// ���������Ƿ�պ�
	void SetClosed(bool closed) { mClosed = closed; }

	// ��ȡ�����Ƿ�պ�
	bool IsClosed() const { return mClosed; }

	void Translate(float tx, float ty); //ƽ��

	virtual void Rotate(double angle, double cx, double cy);

	virtual void Scale(double sx, double sy, double cx, double cy);

protected:
	std::vector<glm::dvec3> mPoints; // �洢�����ϵĵ�
	bool mClosed; // ��������Ƿ�պϣ���β������
};
