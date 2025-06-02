#pragma once
#include "CGObject.h"
#include <vector>
#include "CGRenderState.h"
//Ԥ���������ļ���ֻ�õ������ָ�룬Ϊ���⽻�������
class CGNode;
class CGCamera;
class CGRenderContext;
class CGGroup;
class CGTransform;
class CGGeode;
class CGRenderable;
class CGGeometry;
class CGNode : public CGObject
{
	DECLARE_SERIAL(CGNode)
public:
	CGNode();
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGNode* asNode() { return this; }
	virtual const CGNode* asNode() const { return this; }
	virtual CGGroup* asGroup() { return 0; }
	virtual const CGGroup* asGroup() const { return 0; }
	virtual CGTransform* asTransform() { return 0; }
	virtual const CGTransform* asTransform() const { return 0; }
	virtual CGRenderable* asRenderable() { return 0; }
	virtual const CGRenderable* asRenderable() const { return 0; }
	virtual CGGeode* asGeode() { return 0; }
	virtual const CGGeode* asGeode() const { return 0; }
	virtual CGGeometry* asGeometry() { return 0; }
	virtual const CGGeometry* asGeometry() const { return 0; }
	void SetUpdateCallback(std::shared_ptr<CGCallback> uc) { mUpdateCallback = uc; }
	inline CGCallback* GetUpdateCallback() { return mUpdateCallback.get(); }
	//��άͼ�α任
	virtual void Translate(float dx, float dy) {}
	virtual void Rotate(double angle, double cx, double cy) {}
	virtual void Scale(double sx, double sy, double cx, double cy) {}
public:
	//֧�ֹ����ӽڵ㣨�磬ʵ���ڵ㹲����ģ�ͣ�
	typedef std::vector<CGGroup*> ParentList;
	CGGroup* GetParent(unsigned int i);
	const CGGroup* GetParent(unsigned int i) const;
	inline const ParentList& GetParents() const { return mParents; }
	inline ParentList GetParents() { return mParents; }
	inline unsigned int GetNumParents() const { return static_cast<unsigned int>(mParents.size()); }
	bool boundDirty() const { return mBoundsDirty; } //�����Χ���Ƿ���Ҫ���¼���
	void dirtyBound(); //���ð�Χ�б仯��Ҫ���¼���
	//���㵽��������ϵ���󣨵��������ڵ㣩
	virtual glm::mat4 worldMatrix();
	CGRenderStateSet* gocRenderStateSet() {
		if (!mRenderStateSet)
			mRenderStateSet = std::make_shared<CGRenderStateSet>();
		return mRenderStateSet.get();
	}
	CGRenderStateSet* getRenderStateSet() { return mRenderStateSet.get(); }
	const CGRenderStateSet* getRenderStateSet() const { return mRenderStateSet.get(); }

protected:
	//֧�ֹ����ӽڵ�
	ParentList mParents; //һ��ģ�͹��������ͼ�νڵ㣨�������ʵ���ڵ㣩
	void AddParent(CGGroup* parent);
	void RemoveParent(CGGroup* parent);
protected:
	bool mBoundsDirty = true; //�����Χ���Ƿ���Ҫ���¼���
	std::shared_ptr<CGRenderStateSet> mRenderStateSet;

protected:
	virtual ~CGNode();
	std::shared_ptr<CGCallback> mUpdateCallback = nullptr;
	friend class CGGroup;
	friend class CGRenderable;
public:
	virtual void update() { if (mUpdateCallback) mUpdateCallback->run(this, userData()); }
};