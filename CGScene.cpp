#include "pch.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGRenderContext.h"
#include "CGNode.h"
IMPLEMENT_SERIAL(CGScene, CGObject, 1)
CGScene::CGScene()
{
	SetMainCamera(std::make_shared<CGCamera>());
	SetSceneData(std::make_shared<CGTransform>());
}
CGScene::~CGScene()
{
}
void CGScene::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		//ar >> ;
	}
}
void CGScene::SetSceneData(std::shared_ptr<CGNode> root)
{
	if (!root->asGroup()) //�˴�Ҫ��Group���������������Ϊͼ�γ���ʵ�������ڵ�
		return;
	mRoot = root;
}

//��Ⱦ����
//��Ⱦ����
bool CGScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (mRoot == nullptr || pRC == nullptr || pCamera == nullptr)
		return false;
	//�������
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//�����ڵ����
	mRoot->update();
	//���ͶӰ
	pCamera->Projection(pCamera->ProjectionMode());
	//����
	mRoot->Render(pRC, pCamera);
	//+2���Ƴ�����������ϵ
	DrawWCS(pCamera);
	return true;
}

void CGScene::DrawWCS(CGCamera* pCamera)
{
	//�����Զ��壬��ʹ�ù淶������ʱ���轫���������(-1��1)
	glm::vec3 xs(-100, 0, 0), xe(100, 0, 0);
	glm::vec3 ys(0, -100, 0), ye(0, 100, 0);
	glm::vec3 zs(0, 0, -100), ze(0, 0, 100);
	//X���ɫ��Y����ɫ��Z����ɫ
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(glm::value_ptr(xs));
	glVertex3fv(glm::value_ptr(xe));
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(glm::value_ptr(ys));
	glVertex3fv(glm::value_ptr(ye));
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(glm::value_ptr(zs));
	glVertex3fv(glm::value_ptr(ze));
	glEnd();
}