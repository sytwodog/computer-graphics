#pragma once
#include "CGGroup.h"
#include "CGRenderable.h"
class CGRenderable;
class CGGeode : public CGGroup
{
	DECLARE_SERIAL(CGGeode)
public:
	CGGeode();
	virtual ~CGGeode();
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGGeode* asGeode() { return this; }
	virtual const CGGeode* asGeode() const { return this; }

public:
	//��Ϊʵ��Ҷ�ӽڵ㣬��ʾ�¼�Ϊģ�ͽڵ�
	unsigned int GetNumRenderables() const;
	CGRenderable* GetRenderable(unsigned int i);
	const CGRenderable* GetRenderable(unsigned int i) const;
	unsigned int GetRenderableIndex(const CGRenderable* renderable) const;
	bool ContainsRenderable(const CGRenderable* renderable) const;
	virtual bool InsertChild(unsigned int index, std::shared_ptr<CGNode>& child);
};