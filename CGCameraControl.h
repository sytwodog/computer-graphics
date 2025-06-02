#pragma once

#include "UIEventHandler.h"
#include "CGCamera.h"
#include <memory>
#include <string>

class CGCameraControl : public UIEventHandler
{
public:
    CGCameraControl(GLFWwindow* window, std::shared_ptr<CGCamera> camera);
    ~CGCameraControl();

    virtual EventType GetType() const { return EventType::CameraControl; }

    virtual int OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
    virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;
    virtual int Cancel(GLFWwindow* window) override;

private:
    std::shared_ptr<CGCamera> m_camera;
    bool m_isLeftButtonDown = false;
    bool m_isRightButtonDown = false;
    double m_lastMouseX = 0.0;
    double m_lastMouseY = 0.0;
    glm::dvec3 mPrev = glm::dvec3(0.0); // 用于存储上一次鼠标位置
};