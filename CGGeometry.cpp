#include "pch.h"
#include "CGGeometry.h"
#include "CGCamera.h"
#include "CGRenderContext.h"
IMPLEMENT_SERIAL(CGGeometry, CGRenderable, 1)
CGGeometry::CGGeometry()
{
}
CGGeometry::~CGGeometry()
{
}
void CGGeometry::Serialize(CArchive& ar)
{
	CGRenderable::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		//ar >> ;
	}
}
//��Ⱦ
bool CGGeometry::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	return true;
}