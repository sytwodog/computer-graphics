#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"
class CGDraw2DLineSeg : public UIEventHandler
{
public:
	CGDraw2DLineSeg(GLFWwindow* window = nullptr);
	~CGDraw2DLineSeg();
	virtual EventType GetType() override; //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel(GLFWwindow* window) override;
protected:
	glm::dvec3 mStart; //����ĵ�һ����Ϊ�߶����
	glm::dvec3 mEnd; //����ĵڶ�����Ϊ�߶��յ�
	//��ʱ��ŵ�ǰλ�õ�ǰһ�������λ�ã���Ϊ˫�����ԭ����Ƥ�߿��ܻ��Ƶ���ǰ��֡��
	glm::dvec3 mPrePos1, mPrePos2;
	int mMoveCount = 0;
};