#include "pch.h"
#include "CGCamera.h"
#include <GL/glu.h>
IMPLEMENT_SERIAL(CGCamera, CGTransform, 1)
CGCamera::CGCamera()
{
	mViewport = std::make_shared<Viewport>();
}
CGCamera::~CGCamera()
{
}
void CGCamera::Serialize(CArchive& ar)
{
	CGTransform::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		//ar >> ;
	}
}
void CGCamera::Projection(int mode)
{
	viewport()->activate();
	//����ͶӰ�任
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRenderMode(GL_RENDER); //������Ⱦ����ѡ��
	if (mode == 0) { //��ƽ��ͶӰ������ͶӰ��
		glOrtho(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);
	}
	else if (mode == 1) {//͸��ͶӰ
		glFrustum(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);
		//gluPerspective(45, (wRight- wLeft)/(wTop- wBottom), wNearPlane, wFarPlane);
	}
	else {//����ͶӰ����άЧ����
		gluOrtho2D(mLeft, mRight, mBottom, mTop);
	}
	//ģ����ͼ�任
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //�ӵ㣨������������������ϵ
	gluLookAt(mEye.x, mEye.y, mEye.z, mTarget.x, mTarget.y, mTarget.z, mUp.x, mUp.y, mUp.z); //�����ӵ����
}

IMPLEMENT_SERIAL(Viewport, CGObject, 1)
Viewport::Viewport()
{
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mClearColor = glm::vec4(0, 0, 0, 1);
	mClearDepth = 1.0f;
	mClearStencil = 0;
	mClearFlags = CF_CLEAR_COLOR_DEPTH;
	mScissorEnabled = true;
}
Viewport::Viewport(int x, int y, int w, int h)
{
	mX = x;
	mY = y;
	mWidth = w;
	mHeight = h;
	mClearColor = glm::vec4(0, 0, 0, 1);
	mClearDepth = 1.0f;
	mClearStencil = 0;
	mClearFlags = CF_CLEAR_COLOR_DEPTH;
	mScissorEnabled = true;
}
void Viewport::activate() const
{
	int x = mX;
	int y = mY;
	int w = mWidth;
	int h = mHeight;
	if (w < 1) w = 1;
	if (h < 1) h = 1;
	glViewport(x, y, w, h);
	if (mClearFlags) {
		GLboolean color_write_mask[4] = { 0,0,0,0 };
		glGetBooleanv(GL_COLOR_WRITEMASK, color_write_mask);
		GLboolean depth_write_mask = 0;
		glGetBooleanv(GL_DEPTH_WRITEMASK, &depth_write_mask);
		GLboolean stencil_write_mask = 0;
		glGetBooleanv(GL_STENCIL_WRITEMASK, &stencil_write_mask);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glStencilMask(GL_TRUE);
		if (mScissorEnabled) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(x, y, w, h);
		}
		else {
			glDisable(GL_SCISSOR_TEST);
		}
		glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
		glClearDepth(mClearDepth);
		glClearStencil(mClearStencil);
		glClear(mClearFlags);
		glColorMask(color_write_mask[0], color_write_mask[1], color_write_mask[2],
			color_write_mask[3]);
		glDepthMask(depth_write_mask);
		glStencilMask(stencil_write_mask);
	}
}