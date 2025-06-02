#ifndef _UIEventHandler_H_INCLUDED
#define _UIEventHandler_H_INCLUDED
#include "CGObject.h"
struct GLFWwindow; //Ԥ���������ļ���ֻ�õ�GLFWwindow*��
enum class EventType : int //�����������ͣ��ο����¶��壬�ɸ�����Ҫ�޸�
{
	EventNone = 0, //�ޣ���ʾ���ָ�룬��������ͼ
	//��άͼ�λ��ƣ��൱��ֱ���ڻ����ϻ��ƣ�
	//��
	Draw2DPoint = 1, //���Ƶ�����
	Draw2DStroke = 2, //�ʻ������ߣ� 
	Draw2DSeedFill = 3, //ʰȡ���ӵ�
	//�ߣ��߶Ρ������߶Ρ�ֱ�ߡ����ߡ����ߡ������
	Draw2DLineSeg = 10, //������㡢�յ����ֱ�߶�
	Draw2DLineLen = 11, //������㡢�յ㣨ȷ�����򣩡����볤�Ȼ���ֱ�߶�
	Draw2DLineX = 12, //��������������޳�ֱ��
	Draw2DLineRay = 13, //������㡢�յ㣨�ڶ���ȷ�����򣩻�������
	Draw2DLineStrip = 14, //���ߣ�����������ֱ�߶��γ�
	Draw2DLineLoop = 15, //����ߣ���������
	Draw2DCircle = 16,
	// ����Σ�����Ρ��������
	Draw2DPolygon = 20, //�������Σ��������õ����㣬�Ҽ�������һ�������
	Draw2DPolygonNC = 21, //������Σ�������ǰ����ȷ��һ�߳�����������������ڱ����������õ�������Σ�
	Draw2DPolygonNR = 22, //������Σ������һ��õ����ġ��ڶ���õ��뾶�������������������ƶ���תȷ���������λ�ã�
	Draw2DRectangle = 23, //�������Σ������һ�㣬�ڶ��㣩
	Draw2DSquare = 24, //����������Σ������һ�㣬�ڶ��㣬���ϳ��ķ���
	Draw2DDiamond = 25, //���Σ������һ�㣬�ڶ����γ������ߣ���������ȣ�
	Draw2DTriangle = 26, //�����Σ����ȱ�scalene, �ȱ�equilateral,����isosceles����ֱ��������
	
	Draw3DSphere = 27,
	CameraControl=28,
	EventUnknown = 2000,
	Model2DTransform=120,
	
	PickOne=121

};
//���ͼ�ͻ����Ľ�����ʹ������ģʽ����CView�������м��̡�����¼��Ĵ���
class UIEventHandler
{
public:
	UIEventHandler(GLFWwindow* window = nullptr);
	virtual ~UIEventHandler();
	//�������ͣ�����������������д
	virtual EventType GetType() { return EventType::EventNone; }
	//ȡ�������ESC���жϵ�ǰ�����ִ�У�������������������д
	virtual int Cancel(GLFWwindow* window) { return 0; }
	//����¼�����ֻ����Ĭ��ʵ�֣������������Ҫ��д��Ӧ�ĺ�����
	virtual int OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) { return 0; }
	virtual int OnChar(GLFWwindow* window, unsigned int codepoint) { return 0; }
	virtual int OnCharMods(GLFWwindow* window, unsigned int codepoint, int mods) { return 0; }
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) { return 0; }
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) { return 0; }
	virtual int OnCursorEnter(GLFWwindow* window, int entered) { return 0; }
	virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) { return 0; }
	//GLFW������꽻���ص�����
	//��������
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//�ַ�����
	static void CharCallback(GLFWwindow* window, unsigned int codepoint);
	//��ϼ����룬�ַ�Ҳ�ɴ����������η���������codepoint�ǰ��µļ���unicode�룬mods�ǰ��µ����η���
	static void CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
	//��갴��
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	//����ƶ�
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	//��������뿪
	static void CursorEnterCallback(GLFWwindow* window, int entered);
	//������
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	//�ϷŲ���
	static void DropCallback(GLFWwindow* window, int path_count, const char* paths[]);
	//�����Ҫ�����������ݣ����������٣�
	void SetOwnerData(std::shared_ptr<CGObject> owner, std::shared_ptr<CGObject> data)
	{
		mOwnder = owner;
		mData = data;
	}
	//ֻʹ��һ���������
	static UIEventHandler* CurCommand();
	static void DelCommand();
	static void SetCommand(UIEventHandler* cmd);
protected:
	int mStep = 0; // �����������
	GLFWwindow* mGLFWwindow = nullptr; //GLFWͼ�λ��ƴ���
	std::shared_ptr<CGObject> mOwnder = nullptr; //�¼�ӵ����
	std::shared_ptr<CGObject> mData = nullptr; //�¼��������� 
	static UIEventHandler* sCommand; //��������
};
#endif //_UIEventHandler_H_INCLUDED