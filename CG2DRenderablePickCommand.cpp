#include "pch.h"
#include "CG2DRenderablePickCommand.h"
#include "CG2022116169李思怡Doc.h"
#include "CG2022116169李思怡View.h"

CG2DRenderablePickCommand::CG2DRenderablePickCommand(GLFWwindow* window /*= nullptr*/)
    : UIEventHandler(window)
{
    mStep = 0;
}

EventType CG2DRenderablePickCommand::GetType()
{
    return EventType::Draw2DSeedFill; // 假设拾取命令类型为 Draw2DSeedFill
}

// 鼠标事件（鼠标左键单击用于拾取）
int CG2DRenderablePickCommand::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS)
        return 0;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // 将屏幕坐标转换为世界坐标
    Vec2d p = ViewPorttoWorld(Vec2i(xpos, ypos));

    // 假设有一个方法可以判断点击位置是否在某个图形对象上
    if (IsPointInRenderable(p))
    {
        // 选中该图形对象
        SelectRenderable(p);
    }

    return 0;
}

int CG2DRenderablePickCommand::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    // 鼠标移动时的处理
    return 0;
}

// 取消 Esc
int CG2DRenderablePickCommand::Cancel(GLFWwindow* window)
{
    mStep = 0;
    // 清除选中的图形对象
    ClearSelection();
    return 0;
}

// 辅助方法：将视口坐标转换为世界坐标
Vec2d CG2DRenderablePickCommand::ViewPorttoWorld(Vec2i pos)
{
    // 这里需要根据你的具体实现来完成
    return Vec2d(pos.x, pos.y);
}

// 辅助方法：判断点是否在某个图形对象上
bool CG2DRenderablePickCommand::IsPointInRenderable(const Vec2d& point)
{
    // 这里需要根据你的具体实现来完成
    return true;
}

// 辅助方法：选中图形对象
void CG2DRenderablePickCommand::SelectRenderable(const Vec2d& point)
{
    // 这里需要根据你的具体实现来完成
}

// 辅助方法：清除选中的图形对象
void CG2DRenderablePickCommand::ClearSelection()
{
    // 这里需要根据你的具体实现来完成
}