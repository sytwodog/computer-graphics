#pragma once
#include "CGGroup.h"
class CGTransform : public CGGroup
{
	DECLARE_SERIAL(CGTransform)
public:
	CGTransform();
	virtual ~CGTransform();
	virtual void Serialize(CArchive& ar) override;
	//��Ⱦ����
	bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGTransform* asTransform() { return this; }
	virtual const CGTransform* asTransform() const { return this; }
protected:
	bool mWorldMatrixDirty = true; //
	glm::mat4 mLocalMatrix = glm::mat4(1.0f); //�ֲ������ϼ��ľ���
	glm::mat4 mWorldMatrix = glm::mat4(1.0f); //ȫ�֣�����������ϵ��
protected:
	void dirtyWorldMatrix();
public:
	//ģ������ϵ�ڸ��ڵ��еĶ�λ
	const glm::mat4& localMatrix() const { return mLocalMatrix; }
	glm::mat4& localMatrix() { return mLocalMatrix; }
	void setLocalMatrix(const glm::mat4& m);
	//��Ը��ڵ�ı任
	void translate(float tx, float ty, float tz); //ƽ��
	void translate(const glm::vec3& t); //ƽ��
	void scale(float sx, float sy, float sz); //����
	void rotate(float degrees, float x, float y, float z); //��ת
	void preMultiply(const glm::mat4& m); //��˾���m
	void postMultiply(const glm::mat4& m); //�ҳ˾��� m
};