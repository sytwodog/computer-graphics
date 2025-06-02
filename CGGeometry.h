#pragma once
#include "CGRenderable.h"
class CGGeometry : public CGRenderable
{
	DECLARE_SERIAL(CGGeometry)
public:
	CGGeometry();
	virtual ~CGGeometry();
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
protected:
};