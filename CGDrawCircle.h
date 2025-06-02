#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"

class CGDrawCircle : public UIEventHandler
{
public:
    CGDrawCircle(GLFWwindow* window = nullptr);
    ~CGDrawCircle();
    virtual EventType GetType() override; //��������
    //�ٶ�����������ʰȡԲ�ġ�Բ��һ�㣬�ƶ����ʱ����Ƥ��Բ
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
    //ȡ������ִ�е�����簴ESC����
    virtual int Cancel(GLFWwindow* window) override;
protected:
    glm::dvec3 mCenter; // ����ĵ�һ����ΪԲ��
    double mRadius; // ����ĵڶ�����Բ��ȷ���뾶
};