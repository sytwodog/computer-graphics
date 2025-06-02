#include "pch.h"
#include "UIEventHandler.h"
#include "CGRenderContext.h"
#include "CG2022116169��˼��Doc.h"
#include "CG2022116169��˼��View.h" //����Viewǰ�������Doc
UIEventHandler* UIEventHandler::sCommand = nullptr; //��������
UIEventHandler::UIEventHandler(GLFWwindow* window)
	:mStep(0), mGLFWwindow(window)
{
}
UIEventHandler::~UIEventHandler()
{
	if (mGLFWwindow) {
		Cancel(mGLFWwindow);
	}
}
//��������
void UIEventHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//CCG20XX110001����View* pCtx = (CCG20XX110001����View*)glfwGetWindowUserPointer(window);
	//if (pCtx) {
	//}
	//if (mods == GLFW_MOD_CONTROL) {
	// //����ctrl��ͬʱ��������key
	//}
	//if (mods == GLFW_MOD_SHIFT) {
	// //����shift��ͬʱ��������key
	//}
	if (action == GLFW_PRESS) { //��λ����
		if (key == GLFW_KEY_ESCAPE) { //������ESC��ȡ����ǰ����ִ�е�����
			if (sCommand) {
				sCommand->Cancel(window);
				DelCommand();
			}
			else { //�����ѡ�е�ͼ�ζ��󣬴˴�����ʰȡ״̬��
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		//��λ̧��
	}
	else { //action == GLFW_REPEAT
	}
	if (sCommand) {//����ģʽ��ת������Ӧ�������ȥ������¼�
		sCommand->OnKey(window, key, scancode, action, mods);
	}
}
//�ַ�����
void UIEventHandler::CharCallback(GLFWwindow* window, unsigned int codepoint)
{
	//δʵ��
}
//��ϼ����룬�ַ�Ҳ�ɴ����������η���������codepoint�ǰ��µļ���unicode�룬mods�ǰ��µ����η���
void UIEventHandler::CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
{
	//δʵ��
}
//��갴��
void UIEventHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//CCG20XX110001����View* pCtx = (CCG20XX110001����View*)glfwGetWindowUserPointer(window);
	//if (pCtx) {
	//}
	if (sCommand) {//����ģʽ��ת������Ӧ�������ȥ������¼�
		sCommand->OnMouseButton(window, button, action, mods);
	}
}
//����ƶ�
void UIEventHandler::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	CCG2022116169��˼��View* pCtx = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
	if (pCtx) {
		pCtx->ShowCoord(xpos, ypos);
	}
	if (sCommand) {//����ģʽ��ת������Ӧ�������ȥ������¼�
		sCommand->OnCursorPos(window, xpos, ypos);
	}
}
//��������뿪
void UIEventHandler::CursorEnterCallback(GLFWwindow* window, int entered)
{
	//δʵ��
}
//������
void UIEventHandler::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	//CCG20XX110001����View* pCtx = (CCG20XX110001����View*)glfwGetWindowUserPointer(window);
	//if (pCtx) {
	//}
	if (sCommand) {//����ģʽ��ת������Ӧ�������ȥ������¼�
		sCommand->OnMouseScroll(window, xoffset, yoffset);
	}
}
//�ϷŲ���
void UIEventHandler::DropCallback(GLFWwindow* window, int path_count, const char* paths[])
{
	//δʵ��
}
UIEventHandler* UIEventHandler::CurCommand()
{
	return sCommand;
}
void UIEventHandler::DelCommand()
{
	delete sCommand;
	sCommand = nullptr;
}
void UIEventHandler::SetCommand(UIEventHandler* cmd)
{
	sCommand = cmd;
}