#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"

class CGDrawCircle : public UIEventHandler
{
public:
    CGDrawCircle(GLFWwindow* window = nullptr);
    ~CGDrawCircle();
    virtual EventType GetType() override; //命令类型
    //假定鼠标左键单击拾取圆心、圆上一点，移动鼠标时画橡皮筋圆
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
    //取消正在执行的命令（如按ESC键）
    virtual int Cancel(GLFWwindow* window) override;
protected:
    glm::dvec3 mCenter; // 点击的第一点作为圆心
    double mRadius; // 点击的第二点与圆心确定半径
};