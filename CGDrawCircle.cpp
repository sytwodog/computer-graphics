#include "pch.h"
#include "CGDrawCircle.h"
#include "CG2022116169��˼��Doc.h" //����View֮ǰҪ����Doc
#include "CG2022116169��˼��View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CGCircle.h"

// ���ƶ�άԲ
static void draw2dcircle(glm::dvec3& center, double radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(center.x, center.y);
    for (int i = 0; i <= 360; ++i) {
        double angle = i * 3.1415926 / 180.0;
        glVertex2d(center.x + radius * cos(angle), center.y + radius * sin(angle));
    }
    glEnd();
}

CGDrawCircle::CGDrawCircle(GLFWwindow* window)
    : UIEventHandler(window), mCenter(0.0, 0.0, 0.0), mRadius(0.0)
{
}

CGDrawCircle::~CGDrawCircle()
{
}

EventType CGDrawCircle::GetType() //��������
{
    //UIEventHandler.h�ж��壬Ҫ���ݲ�ͬ�������������޸ģ��˴��ǻ���Բ
    return EventType::Draw2DCircle;
}

//�ٶ�����������ʰȡԲ�ġ�Բ��һ�㣬�ƶ����ʱ����Ƥ��Բ
int CGDrawCircle::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (window == nullptr)
        return -1;
    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mStep++; //ÿ�ε���������ʱ�������������һ
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (mStep == 1) { //��һ�ε�������������¼�����λ����Ϊ������Բ��Բ��
                mCenter.x = xpos;
                mCenter.y = ypos;
                mRadius = 0.0;
                view->ShowPrompt("����������������Բ�ϵ�һ����ȷ���뾶"); //ͨ�������¼���View��ʾ��״̬��
            }
            else if (mStep == 2) { //�ڶ��ε�������������¼�����λ����Ϊ������Բ�İ뾶
                if (xpos == mCenter.x && ypos == mCenter.y) {
                    mStep = 1;
                    view->ShowPrompt("��Բ���غϣ���������������������Բ�ϵ�һ��");
                    return -1;
                }
                // ����뾶
                mRadius = std::sqrt((xpos - mCenter.x) * (xpos - mCenter.x) + (ypos - mCenter.y) * (ypos - mCenter.y));
                glm::dvec3 center = view->DCS2WCS(mCenter);
                glm::dvec3 end = view->DCS2WCS(glm::dvec3(xpos, ypos, 0.0));
                //���������Ƥ��
                glEnable(GL_COLOR_LOGIC_OP);
                glLogicOp(GL_XOR); // ʹ�����ģʽʵ����Ƥ��Ч��GL_XOR
                glColor3f(0.0f, 0.0f, 1.0f);
                draw2dcircle(center, mRadius);
                glDisable(GL_COLOR_LOGIC_OP);
                glfwSwapBuffers(window);
                //�������ڶ��ε�����Բ��Բ�ĺͰ뾶�ѻ�ȡ��
                //��������Ҫע������ת������������������Ӧ�����ԡ�
                glm::dvec3 circleCenter = view->DCS2WCS(mCenter);
                view->AddRenderable(std::make_shared<CGCircle>(circleCenter, mRadius)); //������ӵ�����
                view->Invalidate(); //�ͻ�����Ҫ�ػ�
                view->UpdateWindow(); //�ͻ���ִ���ػ�
                mStep = 0; //��Ϊ0����д��ʼ����Բ�����õ����������ϵ�Բ��ť
                mCenter.x = mCenter.y = mRadius = 0.0;
                view->ShowPrompt("������Բ��Բ��"); //״̬����ʾ
            }
            else {
            }
        }
    }
    return 0;
}

int CGDrawCircle::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    if (window == nullptr)
        return -1;
    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    if (mStep == 0) { //��û�����һ���㣨��ȡԲ�ģ�
        view->ShowPrompt("����������������Բ��Բ��"); //״̬����ʾ
    }
    else if (mStep == 1) { //�Ѿ�������Բ�ĺ󣬵�ǰ����ƶ���λ����Բ���γ���ƤԲ
        if (xpos == mCenter.x && ypos == mCenter.y) {
            return -1; //�����غϣ���������
        }
        double preRadius, curRadius;
        preRadius = mRadius;
        // ����뾶
        mRadius = std::sqrt((xpos - mCenter.x) * (xpos - mCenter.x) + (ypos - mCenter.y) * (ypos - mCenter.y));
        curRadius = mRadius;

        glm::dvec3 center = view->DCS2WCS(mCenter);
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR); // ʹ�����ģʽʵ����Ƥ��Ч��GL_XOR
        glColor3f(0.0f, 0.0f, 1.0f);
        draw2dcircle(center, preRadius); // ��������ƤԲ
        draw2dcircle(center, curRadius); // ��������ƤԲ
        glDisable(GL_COLOR_LOGIC_OP);
        glfwSwapBuffers(window);

        mRadius = curRadius; //��¼����λ�ã���Ϊȷ���뾶�ĵ�
    }
    else {
    }
    return 0;
}

//ȡ������ִ�е�����簴ESC����
int CGDrawCircle::Cancel(GLFWwindow* window)
{
    if (window == nullptr)
        return -1;
    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    if (mStep == 1) { //����Ѿ��������һ�Σ����������ǰɾ����ƤԲ
        glm::dvec3 center = view->DCS2WCS(mCenter);
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR); // ʹ�����ģʽʵ����Ƥ��Ч��GL_XOR
        glColor3f(0.0f, 0.0f, 1.0f);
        draw2dcircle(center, mRadius); // ��������ƤԲ
        glDisable(GL_COLOR_LOGIC_OP);
        glfwSwapBuffers(window);
    }
    mStep = 0;
    mCenter.x = mCenter.y = mRadius = 0.0f;
    view->ShowPrompt("����"); //״̬����ʾ
    return 0;
}