#include "pch.h"
#include "CG2DRotateCommand.h"
#include "CG2022116169��˼��Doc.h" // ����View֮ǰҪ����Doc 
#include "CG2022116169��˼��View.h" // �û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ����� 

// �޸ĺ�Ĺ��캯�������û��๹�캯��
CG2DRotateCommand::CG2DRotateCommand(GLFWwindow* window)
    : UIEventHandler(window), mCenter(0, 0), mStart(0, 0), mCurrent(0, 0)
{
    mStep = 0;
}

int CG2DRotateCommand::GetType()
{
    return static_cast<int>(CommandType::cmd2dRotateRenderable); // ͼ�ε���ת�任
}

int CG2DRotateCommand::OnLButtonDown(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            mStep++; // ÿ�ε���������ʱ�������������һ 
            if (mStep == 1) // ��һ�ε�������������ȡ��ת����
            {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                mCenter = glm::dvec2(xpos, ypos);
                CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
                if (view) {
                    view->ShowPrompt(_T("�뵥��ͼ�ε�����")); // ͨ�������¼���View��ʾ��״̬�� 
                }
            }
            else if (mStep == 2) // �ڶ��ε�������������ȡͼ�ε����� 
            {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                mStart = glm::dvec2(xpos, ypos);
                mCurrent = mStart;
                CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
                if (view) {
                    view->ShowPrompt(_T("���ƶ���꣬����תͼ�Σ���������λ�ý�����ת")); // ״̬����ʾ 
                }
            }
            else if (mStep == 3) // �����ε�����������������ת
            {
                mStep = 0;
                CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
                if (view) {
                    view->ShowPrompt(_T("��ѡ����ת����")); // ״̬����ʾ 
                }
            }
            else
            {
            }
        }
    }
    return 0;
}

int CG2DRotateCommand::OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view) {
        if (mStep == 0) // ���ڸû�ȡ��ת����
        {
            view->ShowPrompt(_T("��ѡ����ת����")); // ״̬����ʾ 
        }
        else if (mStep == 1) {  // ���ڸû�ȡͼ������
            view->ShowPrompt(_T("�뵥��ͼ�ε�����")); // ״̬����ʾ 
        }
        else if (mStep == 2) // ������ת
        {
            if (glm::dvec2(xpos, ypos) == mStart)
            {
                return -1; // �����غϣ��������� 
            }
            double angle;  // ����Ƕ�
            mStart = mCurrent;  // ��Ҫ����ǰһʱ�̵��������꣬
            mCurrent = glm::dvec2(xpos, ypos);
            // �������ӿ��е����꣬��Ҫת������������
            glm::dvec2 center = view->ViewPorttoWorld(mCenter);
            glm::dvec2 start = view->ViewPorttoWorld(mStart);
            glm::dvec2 cur = view->ViewPorttoWorld(mCurrent);
            // �������ĵ����ƫ�ƵĽǶ�
            glm::dvec2 a = glm::dvec2(start.x - center.x, start.y - center.y);
            glm::dvec2 b = glm::dvec2(cur.x - center.x, cur.y - center.y);
            double cosValue = glm::dot(a, b) / glm::length(a) / glm::length(b);
            if (cosValue >= 1.0)  // ������˵���ᳬ������ֵ�ķ�Χ�����Ǹ������������������ʹ����ڷ�Χ֮��
                cosValue = 1.0;
            if (cosValue <= -1.0)
                cosValue = -1.0;
            angle = acos(cosValue);  // ��������ǻ���
            angle = angle * (180.0 / M_PI);  // תΪ�Ƕ�
            if (a.x * b.y - a.y * b.x < 0) // ������ת�ķ���
                angle = -angle;
            // ������ת
            CCG2022116169��˼��Doc* pDoc = view->GetDocument();
            if (pDoc) {
                pDoc->Rotate(angle, center.x, center.y);
                view->Invalidate(true);
                view->UpdateWindow();
                Sleep(30);
            }
        }
        else
        {
        }
    }
    return 0;
}

int CG2DRotateCommand::Cancel(GLFWwindow* window)
{
    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view) {
        mStep = 0;
        view->ShowPrompt(_T("����")); // ״̬����ʾ 
    }
    return 0;
}