#pragma once
#include "CGObject.h"
#include <vector>
class CGCamera; //Ԥ����
class CGRenderContext;//Ԥ����
class CGNode; //Ԥ����
class CGScene : public CGObject
{
	DECLARE_SERIAL(CGScene)
public:
	CGScene();
	virtual ~CGScene();
	virtual void Serialize(CArchive& ar) override;
	//��Ⱦ����
	bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	void SetMainCamera(std::shared_ptr<CGCamera> camera) { mCamera = camera; }
	CGCamera* GetMainCamera() { return mCamera.get(); }
	//�����е�ͼ�ζ���һ����Group��Transform
	void SetSceneData(std::shared_ptr<CGNode> root);
	CGNode* GetSceneData() { return mRoot.get(); }
protected:
	std::shared_ptr<CGCamera> mCamera = nullptr;//���������
	std::shared_ptr<CGNode> mRoot = nullptr; //���������ڵ�
	void DrawWCS(CGCamera* pCamera);
};