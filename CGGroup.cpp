#include "pch.h"
#include "CGGroup.h"
#include <algorithm>
#include "CGGeometry.h"
IMPLEMENT_SERIAL(CGGroup, CGNode, 1)

CGGroup::CGGroup()
{
}
CGGroup::~CGGroup()
{
	//���븸�ڵ�
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr) {
		(*itr)->RemoveParent(this);
	}
}
void CGGroup::Serialize(CArchive& ar)
{
	CGNode::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		//ar >> ;
	}
}
bool CGGroup::Render(CGRenderContext* pRC, CGCamera* pCamera)
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
bool CGGroup::AddChild(std::shared_ptr<CGNode> child)
{
	return CGGroup::InsertChild(mChildren.size(), child);
}

bool CGGroup::InsertChild(unsigned int index, std::shared_ptr<CGNode>& child)
{
	if (!child) return false;
	if (index >= mChildren.size())
	{
		index = mChildren.size();
		mChildren.push_back(child);
	}
	else
	{
		mChildren.insert(mChildren.begin() + index, child);
	}
	child->AddParent(this);
	return true;
}

//�ӽڵ����
unsigned int CGGroup::GetNumChildren() const
{
	return static_cast<unsigned int>(mChildren.size());
}
CGNode* CGGroup::GetChild(unsigned int i)
{
	if (i >= mChildren.size())
		return nullptr;
	return mChildren[i].get();
}
const CGNode* CGGroup::GetChild(unsigned int i) const
{
	if (i >= mChildren.size())
		return nullptr;
	return mChildren[i].get();
}
bool CGGroup::ContainsNode(const CGNode* node) const
{
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr) {
		if (itr->get() == node)
			return true;
	}
	return false;
}
unsigned int CGGroup::GetChildIndex(const CGNode* node) const
{
	for (unsigned int childNum = 0; childNum < mChildren.size(); ++childNum) {
		if (mChildren[childNum].get() == node) return childNum;
	}
	return static_cast<unsigned int>(mChildren.size()); //û�ҵ��������ӽڵ����
}
void CGGroup::update()
{
	if (mUpdateCallback)
		mUpdateCallback->run(this, userData());
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		if ((*itr)->GetUpdateCallback()) {
			(*itr)->GetUpdateCallback()->run((*itr).get(), (*itr)->userData());
		}
	}
}