#include "pch.h"
#include "CG2DRotateCommand.h"
#include "CG2022116169李思怡Doc.h" // 包含View之前要包含Doc 
#include "CG2022116169李思怡View.h" // 用户交互绘制，并将图形对象通过Doc添加到场景 

// 修改后的构造函数，调用基类构造函数
CG2DRotateCommand::CG2DRotateCommand(GLFWwindow* window)
    : UIEventHandler(window), mCenter(0, 0), mStart(0, 0), mCurrent(0, 0)
{
    mStep = 0;
}

int CG2DRotateCommand::GetType()
{
    return static_cast<int>(CommandType::cmd2dRotateRenderable); // 图形的旋转变换
}

int CG2DRotateCommand::OnLButtonDown(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            mStep++; // 每次单击鼠标左键时操作步骤计数加一 
            if (mStep == 1) // 第一次单击鼠标左键，获取旋转中心
            {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                mCenter = glm::dvec2(xpos, ypos);
                CCG2022116169李思怡View* view = (CCG2022116169李思怡View*)glfwGetWindowUserPointer(window);
                if (view) {
                    view->ShowPrompt(_T("请单击图形的中心")); // 通过处理事件的View显示到状态栏 
                }
            }
            else if (mStep == 2) // 第二次单击鼠标左键，获取图形的中心 
            {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                mStart = glm::dvec2(xpos, ypos);
                mCurrent = mStart;
                CCG2022116169李思怡View* view = (CCG2022116169李思怡View*)glfwGetWindowUserPointer(window);
                if (view) {
                    view->ShowPrompt(_T("请移动鼠标，以旋转图形，单击任意位置结束旋转")); // 状态栏显示 
                }
            }
            else if (mStep == 3) // 第三次单击鼠标左键，结束旋转
            {
                mStep = 0;
                CCG2022116169李思怡View* view = (CCG2022116169李思怡View*)glfwGetWindowUserPointer(window);
                if (view) {
                    view->ShowPrompt(_T("请选择旋转中心")); // 状态栏显示 
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
    CCG2022116169李思怡View* view = (CCG2022116169李思怡View*)glfwGetWindowUserPointer(window);
    if (view) {
        if (mStep == 0) // 现在该获取旋转中心
        {
            view->ShowPrompt(_T("请选择旋转中心")); // 状态栏显示 
        }
        else if (mStep == 1) {  // 现在该获取图形中心
            view->ShowPrompt(_T("请单击图形的中心")); // 状态栏显示 
        }
        else if (mStep == 2) // 进行旋转
        {
            if (glm::dvec2(xpos, ypos) == mStart)
            {
                return -1; // 两点重合，不做处理 
            }
            double angle;  // 定义角度
            mStart = mCurrent;  // 需要更新前一时刻的鼠标的坐标，
            mCurrent = glm::dvec2(xpos, ypos);
            // 现在是视口中的坐标，需要转到世界坐标中
            glm::dvec2 center = view->ViewPorttoWorld(mCenter);
            glm::dvec2 start = view->ViewPorttoWorld(mStart);
            glm::dvec2 cur = view->ViewPorttoWorld(mCurrent);
            // 由向量的点积求偏移的角度
            glm::dvec2 a = glm::dvec2(start.x - center.x, start.y - center.y);
            glm::dvec2 b = glm::dvec2(cur.x - center.x, cur.y - center.y);
            double cosValue = glm::dot(a, b) / glm::length(a) / glm::length(b);
            if (cosValue >= 1.0)  // 按理来说不会超出余弦值的范围，但是浮点数自身精度问题可能使结果在范围之外
                cosValue = 1.0;
            if (cosValue <= -1.0)
                cosValue = -1.0;
            angle = acos(cosValue);  // 算出来的是弧度
            angle = angle * (180.0 / M_PI);  // 转为角度
            if (a.x * b.y - a.y * b.x < 0) // 考虑旋转的方向
                angle = -angle;
            // 进行旋转
            CCG2022116169李思怡Doc* pDoc = view->GetDocument();
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
    CCG2022116169李思怡View* view = (CCG2022116169李思怡View*)glfwGetWindowUserPointer(window);
    if (view) {
        mStep = 0;
        view->ShowPrompt(_T("就绪")); // 状态栏显示 
    }
    return 0;
}