#include "pch.h"
#include "CGCube.h"
#include "TessellationHints.h"
IMPLEMENT_SERIAL(CGCube, CGRenderable, 1)
void CGCube::setTessellationHints(std::shared_ptr<TessellationHints> hints)
{
	if (mTessellationHints.get() != hints.get())
	{
		mTessellationHints = hints;
		mDisplayListDirty = true;
	}
}
void CGCube::buildDisplayList()
{
	TessellationHints* hints = tessellationHints();
	bool createBody = (hints ? hints->createBody() : true);
	bool createTop = (hints ? hints->createTop() : true);
	bool createBottom = (hints ? hints->createBottom() : true);
	float dx = mHalfLengths.x;
	float dy = mHalfLengths.y;
	float dz = mHalfLengths.z;
	glBegin(GL_QUADS); // ��ʼ���������壬��6���棬����ʱע�ⶥ��˳����ʱ�뷽�򣨴����������ڿ�ʱ��
	if (createBody) { //��Z���4���档
		// - y ��
		glNormal3f(0.0f, -1.0f, 0.0f); //�ⷨ����
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-dx, -dy, dz);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-dx, -dy, -dz);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(dx, -dy, -dz);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(dx, -dy, dz);
		// + y ��
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(dx, dy, dz);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(dx, dy, -dz);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-dx, dy, -dz);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-dx, dy, dz);
		// + x ��
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(dx, -dy, dz);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(dx, -dy, -dz);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(dx, dy, -dz);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(dx, dy, dz);
		// - x ��
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-dx, dy, dz);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-dx, dy, -dz);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-dx, -dy, -dz);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-dx, -dy, dz);
	}
	if (createTop) {
		// + z ��
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-dx, dy, dz);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-dx, -dy, dz);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(dx, -dy, dz);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(dx, dy, dz);
	}
	if (createBottom) {
		// - z ��
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(dx, dy, -dz);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(dx, -dy, -dz);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-dx, -dy, -dz);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-dx, dy, -dz);
	}
	glEnd();
}