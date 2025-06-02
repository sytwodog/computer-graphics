#pragma once
#include "CGNode.h"
class CGRenderContext;//Ԥ����
class CGCamera; //Ԥ����
class CGRenderable : public CGNode
{
	DECLARE_SERIAL(CGRenderable)
public:
	CGRenderable();
	virtual ~CGRenderable();
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGRenderable* asRenderable() { return this; }
	virtual const CGRenderable* asRenderable() const { return this; }
protected:
	bool mDisplayListEnabled = false;
	bool mDisplayListDirty = true;
	GLuint mDisplayList = 0;
protected:
	CGRenderable(const CGRenderable& other) : CGNode(other)
	{
	}
	CGRenderable& operator=(const CGRenderable&) = default;
	virtual void buildDisplayList() {} //����������д
public:
	bool isDisplayListEnabled() const { return mDisplayListEnabled; }
	void setDisplayListEnabled(bool enabled) { mDisplayListEnabled = enabled; }
	bool displayListDirty() const { return mDisplayListDirty; }
	void setDisplayListDirty(bool dirty) { mDisplayListDirty = dirty; }
	GLuint displayList() const { return mDisplayList; }
	void setDisplayList(unsigned int disp_list) { mDisplayList = disp_list; }
	void deleteDisplayList()
	{
		if (displayList())
			glDeleteLists(displayList(), 1);
		mDisplayList = 0;
	}
};