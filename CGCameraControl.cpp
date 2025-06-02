#include "pch.h"
#include "CGCameraControl.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "resource.h"
#include "CG2022116169��˼��View.h"

CGCameraControl::CGCameraControl(GLFWwindow* window, std::shared_ptr<CGCamera> camera)
    : UIEventHandler(window), m_camera(camera)
{

}

CGCameraControl::~CGCameraControl()
{
}

int CGCameraControl::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (window == nullptr)
        return -1;

    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        bool ctrlPressed = (mods & GLFW_MOD_CONTROL) != 0;
        bool shiftPressed = (mods & GLFW_MOD_SHIFT) != 0;

        // ֱ�ӷ��������Ա����
        auto& cam = *m_camera;
        float& left = cam.mLeft;
        float& right = cam.mRight;
        float& bottom = cam.mBottom;
        float& top = cam.mTop;
        glm::dvec3& eye = glm::dvec3(cam.mEye);
        glm::dvec3& target = glm::dvec3(cam.mTarget);
        glm::dvec3& up = glm::dvec3(cam.mUp);
        int& projMode = cam.mProjectionMode;

        if (!ctrlPressed) {
            switch (key) {
            case GLFW_KEY_EQUAL:  // + �Ŵ�
                cam.mLeft *= 0.8;
                cam.mRight *= 0.8;
                cam.mTop *= 0.8;
                cam.mBottom *= 0.8;
                view->ShowPrompt("�Ŵ���ͼ: " + std::to_string(cam.mLeft) + ", " + std::to_string(cam.mRight));
                break;

            case GLFW_KEY_MINUS:  // - ��С
                cam.mLeft *= 1.25;
                cam.mRight *= 1.25;
                cam.mTop *= 1.25;
                cam.mBottom *= 1.25;
                view->ShowPrompt("��С��ͼ: " + std::to_string(cam.mLeft) + ", " + std::to_string(cam.mRight));
                break;

            case GLFW_KEY_P:  // P �л�͸��ͶӰ
                cam.mProjectionMode = 1;
                view->ShowPrompt("�л���͸��ͶӰ");
                break;

            case GLFW_KEY_O:  // O �л�����ͶӰ
                cam.mProjectionMode = 0;
                view->ShowPrompt("�л�������ͶӰ");
                break;

                // �ӿڱ߽����
            case GLFW_KEY_L: // L
                if (shiftPressed) {
                    cam.mLeft -= 10.0f;  // Shift+L����߽�����
                    view->ShowPrompt("��߽�����: " + std::to_string(cam.mLeft));
                }
                else {
                    cam.mLeft += 10.0f;  // L����߽�����
                    view->ShowPrompt("��߽�����: " + std::to_string(cam.mLeft));
                }
                break;

            case GLFW_KEY_R: // R
                if (shiftPressed) {
                    cam.mRight -= 10.0f; // Shift+R���ұ߽�����
                    view->ShowPrompt("�ұ߽�����: " + std::to_string(cam.mRight));
                }
                else {
                    cam.mRight += 10.0f; // R���ұ߽�����
                    view->ShowPrompt("�ұ߽�����: " + std::to_string(cam.mRight));
                }
                break;

            case GLFW_KEY_B: // B
                if (shiftPressed) {
                    cam.mBottom -= 10.0f; // Shift+B���±߽�����
                    view->ShowPrompt("�±߽�����: " + std::to_string(cam.mBottom));
                }
                else {
                    cam.mBottom += 10.0f; // B���±߽�����
                    view->ShowPrompt("�±߽�����: " + std::to_string(cam.mBottom));
                }
                break;

            case GLFW_KEY_T: // T
                if (shiftPressed) {
                    cam.mTop -= 10.0f; // Shift+T���ϱ߽�����
                    view->ShowPrompt("�ϱ߽�����: " + std::to_string(cam.mTop));
                }
                else {
                    cam.mTop += 10.0f; // T���ϱ߽�����
                    view->ShowPrompt("�ϱ߽�����: " + std::to_string(cam.mTop));
                }
                break;
            }
        }
        else { // Ctrl + key
            // ���������Ŀ��ľ���
            double distance = glm::distance(eye, target);
            if (distance < 1e-5) distance = 200.0; // �������̫С

            switch (key) {
            case GLFW_KEY_A: // Ctrl+A������ͼ
                cam.mEye = target + glm::dvec3(distance, 0, 0);
                cam.mUp = glm::dvec3(0, 1, 0);
                view->ShowPrompt("�л�������ͼ");
                break;

            case GLFW_KEY_D: // Ctrl+D������ͼ
                cam.mEye = target + glm::dvec3(-distance, 0, 0);
                cam.mUp = glm::dvec3(0, 1, 0);
                view->ShowPrompt("�л�������ͼ");
                break;

            case GLFW_KEY_W: // Ctrl+W��ǰ��ͼ
                cam.mEye = target + glm::dvec3(0, 0, distance);
                cam.mUp = glm::dvec3(0, 1, 0);
                view->ShowPrompt("�л���ǰ��ͼ");
                break;

            case GLFW_KEY_B: // Ctrl+B������ͼ
                cam.mEye = target + glm::dvec3(0, 0, -distance);
                cam.mUp = glm::dvec3(0, 1, 0);
                view->ShowPrompt("�л�������ͼ");
                break;

            case GLFW_KEY_Q: // Ctrl+Q������ͼ
                cam.mEye = target + glm::dvec3(0, distance, 0);
                cam.mUp = glm::dvec3(0, 0, 1);
                view->ShowPrompt("�л�������ͼ");
                break;

            case GLFW_KEY_E: // Ctrl+E������ͼ
                cam.mEye = target + glm::dvec3(0, -distance, 0);
                cam.mUp = glm::dvec3(0, 0, -1);
                view->ShowPrompt("�л�������ͼ");
                break;
            }
        }

        // ������ͼ
        view->Invalidate();
        view->UpdateWindow();
        return 1;
    }
    return 0;
}

int CGCameraControl::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (window == nullptr)
        return -1;

    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            m_isLeftButtonDown = true;
            glfwGetCursorPos(window, &m_lastMouseX, &m_lastMouseY);
            mPrev = glm::dvec3(m_lastMouseX, m_lastMouseY, 0);
            return 1;
        }
        else if (action == GLFW_RELEASE) {
            m_isLeftButtonDown = false;
            return 1;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            m_isRightButtonDown = true;
            glfwGetCursorPos(window, &m_lastMouseX, &m_lastMouseY);
            mPrev = glm::dvec3(m_lastMouseX, m_lastMouseY, 0);
            return 1;
        }
        else if (action == GLFW_RELEASE) {
            m_isRightButtonDown = false;
            return 1;
        }
    }
    return 0;
}

int CGCameraControl::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    if (window == nullptr)
        return -1;

    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;

    double dx = xpos - m_lastMouseX;
    double dy = ypos - m_lastMouseY;
    int handled = 0;

    // ���Ctrl���Ƿ���
    bool ctrlPressed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;

    // ֻ��û�а���Ctrl������갴ť����ʱ�Ŵ�������ƶ�
    if (!ctrlPressed && (m_isLeftButtonDown || m_isRightButtonDown)) {
        if (m_isLeftButtonDown) {
            if (fabs(dx) > 1.0 || fabs(dy) > 1.0) {

                float rotationSpeed = 0.5f;
                float verticalRotationFactor = 0.3f; // ��ֱ��ת������ϵ��

                float horizontalAngle = dx * rotationSpeed;
                float verticalAngle = dy * rotationSpeed * verticalRotationFactor; // ���ʹ�ֱ������

                // ��ȡ�������
                glm::vec3& eye = m_camera->mEye;
                glm::vec3& target = m_camera->mTarget;
                glm::vec3& up = m_camera->mUp;

                // ���㵱ǰ����
                glm::dvec3 direction = glm::normalize(target - eye);


                glm::dvec3 worldUp(0.0f, 1.0f, 0.0f);
                glm::dvec3 right = glm::normalize(glm::cross(direction, worldUp));



                glm::mat4 horizontalRot = glm::rotate(
                    static_cast<float>(glm::radians(horizontalAngle)), // �Ƕȣ����ȣ�
                    glm::vec3(worldUp)                                 // ��ת��
                );

                glm::dvec3 newDirection = glm::dvec3(horizontalRot * glm::vec4(direction, 0.0f));



                glm::mat4 verticalRot = glm::rotate(
                    static_cast<float>(glm::radians(-verticalAngle)), // �Ƕȣ����ȣ�
                    glm::vec3(right)                                  // ��ת��
                );

                newDirection = glm::dvec3(verticalRot * glm::vec4(newDirection, 0.0f));


                float dot = glm::dot(glm::normalize(newDirection), worldUp);
                float angle = glm::degrees(glm::acos(dot));

                // ������75�㷶Χ�ڣ�15��~165�㣩
                if (angle < 15.0f || angle > 165.0f) {
                    // �Ƕȳ�����Χ��������ֱ��ת
                    newDirection = glm::dvec3(horizontalRot * glm::vec4(direction, 0.0f));
                }

                // �������λ��
                double distance = glm::distance(eye, target);
                glm::dvec3 newEye = (glm::dvec3)target - newDirection * distance;
                eye = newEye;

                // ����������
                glm::dvec3 newRight = glm::normalize(glm::cross(newDirection, worldUp));
                glm::dvec3 newUp = glm::normalize(glm::cross(newRight, newDirection));
                up = newUp;
                handled = 1;
            }
        }
        else if (m_isRightButtonDown) {
            // ��ס����Ҽ�����
            double scale = 1.0 + dy * 0.01;
            m_camera->mLeft *= scale;
            m_camera->mRight *= scale;
            m_camera->mTop *= scale;
            m_camera->mBottom *= scale;

            view->ShowPrompt("�ӿ�����: " + std::to_string(scale));
            handled = 1;
        }
    }

    if (handled) {
        mPrev = glm::dvec3(xpos, ypos, 0);
        view->Invalidate();
        view->UpdateWindow();
    }

    // ���Ǹ���������λ��
    m_lastMouseX = xpos;
    m_lastMouseY = ypos;
    return handled;
}
int CGCameraControl::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    if (window == nullptr)
        return -1;

    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;

    if (yoffset > 0) {
        // ���Ϲ��� - �Ŵ�
        m_camera->mLeft *= 0.9;
        m_camera->mRight *= 0.9;
        m_camera->mTop *= 0.9;
        m_camera->mBottom *= 0.9;
        view->ShowPrompt("�Ŵ���ͼ");
    }
    else if (yoffset < 0) {
        // ���¹��� - ��С
        m_camera->mLeft *= 1.11;
        m_camera->mRight *= 1.11;
        m_camera->mTop *= 1.11;
        m_camera->mBottom *= 1.11;
        view->ShowPrompt("��С��ͼ");
    }

    view->Invalidate();
    view->UpdateWindow();
    return 1;
}

int CGCameraControl::Cancel(GLFWwindow* window)
{
    if (window == nullptr)
        return -1;

    CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;

    m_isLeftButtonDown = false;
    m_isRightButtonDown = false;

    view->Invalidate();
    view->UpdateWindow();
    view->ShowPrompt("ȡ���������");
    return 1;
}