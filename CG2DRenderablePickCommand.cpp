#include "pch.h"
#include "CG2DRenderablePickCommand.h"
#include "CG2022116169��˼��Doc.h"
#include "CG2022116169��˼��View.h"

CG2DRenderablePickCommand::CG2DRenderablePickCommand(GLFWwindow* window /*= nullptr*/)
    : UIEventHandler(window)
{
    mStep = 0;
}

EventType CG2DRenderablePickCommand::GetType()
{
    return EventType::Draw2DSeedFill; // ����ʰȡ��������Ϊ Draw2DSeedFill
}

// ����¼�����������������ʰȡ��
int CG2DRenderablePickCommand::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS)
        return 0;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // ����Ļ����ת��Ϊ��������
    Vec2d p = ViewPorttoWorld(Vec2i(xpos, ypos));

    // ������һ�����������жϵ��λ���Ƿ���ĳ��ͼ�ζ�����
    if (IsPointInRenderable(p))
    {
        // ѡ�и�ͼ�ζ���
        SelectRenderable(p);
    }

    return 0;
}

int CG2DRenderablePickCommand::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    // ����ƶ�ʱ�Ĵ���
    return 0;
}

// ȡ�� Esc
int CG2DRenderablePickCommand::Cancel(GLFWwindow* window)
{
    mStep = 0;
    // ���ѡ�е�ͼ�ζ���
    ClearSelection();
    return 0;
}

// �������������ӿ�����ת��Ϊ��������
Vec2d CG2DRenderablePickCommand::ViewPorttoWorld(Vec2i pos)
{
    // ������Ҫ������ľ���ʵ�������
    return Vec2d(pos.x, pos.y);
}

// �����������жϵ��Ƿ���ĳ��ͼ�ζ�����
bool CG2DRenderablePickCommand::IsPointInRenderable(const Vec2d& point)
{
    // ������Ҫ������ľ���ʵ�������
    return true;
}

// ����������ѡ��ͼ�ζ���
void CG2DRenderablePickCommand::SelectRenderable(const Vec2d& point)
{
    // ������Ҫ������ľ���ʵ�������
}

// �������������ѡ�е�ͼ�ζ���
void CG2DRenderablePickCommand::ClearSelection()
{
    // ������Ҫ������ľ���ʵ�������
}