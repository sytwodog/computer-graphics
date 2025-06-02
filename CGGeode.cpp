#include "pch.h"
#include "CGGeode.h"
#include "CGRenderable.h"
IMPLEMENT_SERIAL(CGGeode, CGGroup, 1)
CGGeode::CGGeode()
{
}
CGGeode::~CGGeode()
{
}
void CGGeode::Serialize(CArchive& ar)
{
	CGGroup::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		//ar >> ;
	}
}

bool CGGeode::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	if (getRenderStateSet()) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		getRenderStateSet()->apply(pCamera, pRC);
	}
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->Render(pRC, pCamera);
	}
	if (getRenderStateSet()) {
		glPopAttrib();
	}
	return true;
}

unsigned int CGGeode::GetNumRenderables() const
{
	return GetNumChildren();
}
CGRenderable* CGGeode::GetRenderable(unsigned int i)
{
	return mChildren[i] != nullptr ? mChildren[i]->asRenderable() : 0;
}
const CGRenderable* CGGeode::GetRenderable(unsigned int i) const
{
	return mChildren[i] != nullptr ? mChildren[i]->asRenderable() : 0;
}
unsigned int CGGeode::GetRenderableIndex(const CGRenderable* renderable) const
{
	return GetChildIndex(renderable);
}
bool CGGeode::ContainsRenderable(const CGRenderable* renderable) const
{
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		if (itr->get() == renderable) return true;
	}
	return false;
}
bool CGGeode::InsertChild(unsigned int index, std::shared_ptr<CGNode>& child)
{
	//�����ӽڵ�����ΪCGRenderable������
	if (!child) return false;
	if (!child->asRenderable()) return false;
	return CGGroup::InsertChild(index, child);
}