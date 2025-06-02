#include "pch.h"
#include "CGRenderable.h"
#include "CGCamera.h"
#include "CGRenderContext.h"
IMPLEMENT_SERIAL(CGRenderable, CGNode, 1)
CGRenderable::CGRenderable()
{
}
CGRenderable::~CGRenderable()
{
}
void CGRenderable::Serialize(CArchive& ar)
{
	CGNode::Serialize(ar);//�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
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
bool CGRenderable::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	//
	if (getRenderStateSet()) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		getRenderStateSet()->apply(pCamera, pRC);
	}
	if (isDisplayListEnabled()) { //ʹ����ʾ�б�
		if (displayListDirty()) {
			if (!displayList()) {
				setDisplayList(glGenLists(1));
			}
			assert(displayList());
			glNewList(displayList(), GL_COMPILE_AND_EXECUTE);
			buildDisplayList();
			glEndList();
			setDisplayListDirty(false);
		}
		else {
			assert(displayList());
			glCallList(displayList());
		}
	}
	else {
	}
	if (getRenderStateSet()) {
		glPopAttrib();
	}
	return true;
}