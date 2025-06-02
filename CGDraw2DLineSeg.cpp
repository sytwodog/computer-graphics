#include "pch.h"
#include "CGDraw2DLineSeg.h"
#include "CG2022116169��˼��Doc.h" //����View֮ǰҪ����Doc
#include "CG2022116169��˼��View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CGLineSegment.h"
// ���ƶ�ά��
static void draw2dline(glm::dvec3& s, glm::dvec3& e)
{
	glBegin(GL_LINES);
	glVertex2d(s.x, s.y);
	glVertex2d(e.x, e.y);
	glEnd();
}
CGDraw2DLineSeg::CGDraw2DLineSeg(GLFWwindow* window)
	:UIEventHandler(window), mStart(0.0, 0.0, 0.0), mEnd(0.0, 0.0, 0.0)
{
}
CGDraw2DLineSeg::~CGDraw2DLineSeg()
{
}
EventType CGDraw2DLineSeg::GetType() //��������
{
	//UIEventHandler.h�ж��壬Ҫ���ݲ�ͬ�������������޸ģ��˴��ǻ���ֱ�߶�
	return EventType::Draw2DLineSeg;
}
//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
int CGDraw2DLineSeg::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
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
			if (mStep == 1) { //��һ�ε�������������¼�����λ����Ϊ�������߶ε����
				mStart.x = xpos;
				mStart.y = ypos;
				mEnd = mStart;
				mPrePos1 = mEnd;
				mPrePos2 = mEnd;
				view->ShowPrompt("����������������ֱ�߶ε��յ�"); //ͨ�������¼���View��ʾ��״̬��
			}
			else if (mStep == 2) {//�ڶ��ε�������������¼�����λ����Ϊ�������߶ε��յ�
				if (xpos == mStart.x && ypos == mStart.y) {
					mStep = 1;
					view->ShowPrompt("������غϣ���������������������ֱ�߶ε��յ�");
					return -1;
				}
				//�ж��Ƿ���SHIFT��������ǣ������X��Y�����������С��������ˮƽ�߻�ֱ��
				int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS) {
					if (abs(xpos - mStart.x) <= abs(ypos - mStart.y)) { //x����仯С����ֱ��
						mEnd.x = mStart.x; //X���ֲ���
						mEnd.y = ypos;
					}
					else { //x����仯��ˮƽ��
						mEnd.x = xpos;
						mEnd.y = mStart.y; //Y���ֲ���
					}
				}
				else { //һ��ֱ�߶Σ���ˮƽ����ֱ������¼�յ㡣
					mEnd.x = xpos;
					mEnd.y = ypos;
				}
				glm::dvec3 start = view->DCS2WCS(mStart);
				glm::dvec3 pre2 = view->DCS2WCS(mPrePos2);
				glm::dvec3 end = view->DCS2WCS(mEnd);
				//���������Ƥ��
				glEnable(GL_COLOR_LOGIC_OP);
				glLogicOp(GL_XOR); // ʹ�����ģʽʵ����Ƥ��Ч��GL_XOR
				glColor3f(0.0f, 0.0f, 1.0f);
				if (mMoveCount == 0) {//��һ���ƶ�
					draw2dline(start, end); // ��������
					mPrePos1 = mEnd;
					mPrePos2 = mEnd;
				}
				else if (mMoveCount == 1) { //�ڶ����ƶ�
					draw2dline(start, end); // ��������
					mPrePos2 = mPrePos1;
					mPrePos1 = mEnd;
				}
				else {
					draw2dline(start, pre2);// ��������
					draw2dline(start, end); // ��������
					mPrePos2 = mPrePos1;
					mPrePos1 = mEnd;
				}
				glDisable(GL_COLOR_LOGIC_OP);
				glfwSwapBuffers(window);
				//�������ڶ��ε�����ֱ�߶δ�������㡢�յ��ѻ�ȡ��
					//��������Ҫע������ת������������������Ӧ�����ԡ�
					//��ȡ��㡢�յ��Ӧ�ĳ����������ڴ���ֱ�߶ζ���
				view->AddRenderable(std::make_shared<CGLineSegment>(start, end)); //������ӵ�����
				view->Invalidate(); //�ͻ�����Ҫ�ػ�
				view->UpdateWindow(); //�ͻ���ִ���ػ�
				mStep = 0; //��Ϊ0����д��ʼ�����߶ζ����õ����������ϵ��߶ΰ�ť
				mStart.x = mStart.y = mEnd.x = mEnd.y = 0;
				view->ShowPrompt("������ֱ�߶ε����"); //״̬����ʾ
			}
			else {
			}
		}
	}
	return 0;
}
int CGDraw2DLineSeg::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (window == nullptr)
		return -1;
	CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mStep == 0) { //��û�����һ���㣨��ȡ�߶���㣩
		view->ShowPrompt("����������������ֱ�߶ε����"); //״̬����ʾ
	}
	else if (mStep == 1) {//�Ѿ����������󣬵�ǰ����ƶ���λ��������γ���Ƥ��
		if (xpos == mStart.x && ypos == mStart.y) {
			return -1; //�����غϣ���������
		}
		//�ж��Ƿ���SHIFT��������ǣ������X��Y�����������С��������ˮƽ�߻�ֱ��
		int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
		if (state == GLFW_PRESS) {
			if (abs(xpos - mStart.x) <= abs(ypos - mStart.y)) { //x����仯С����ֱ��
				mEnd.x = mStart.x;
				mEnd.y = ypos;
			}
			else {
				mEnd.x = xpos;
				mEnd.y = mStart.y;
			}
		}
		else {
			mEnd.x = xpos;
			mEnd.y = ypos;
		}
		glm::dvec3 start = view->DCS2WCS(mStart);
		glm::dvec3 pre2 = view->DCS2WCS(mPrePos2);
		glm::dvec3 end = view->DCS2WCS(mEnd);
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR); // ʹ�����ģʽʵ����Ƥ��Ч��GL_XOR
		glColor3f(0.0f, 0.0f, 1.0f);
		if (mMoveCount == 0) {//��һ���ƶ�
			draw2dline(start, end); // ��������
			mPrePos1 = mEnd;
			mPrePos2 = mEnd;
			mMoveCount++;
		}
		else if (mMoveCount == 1) { //�ڶ����ƶ�
			draw2dline(start, end); // ��������
			mPrePos2 = mPrePos1;
			mPrePos1 = mEnd;
			mMoveCount++;
		}
		else {
			draw2dline(start, pre2);// ��������
			draw2dline(start, end); // ��������
			mPrePos2 = mPrePos1;
			mPrePos1 = mEnd;
			mMoveCount++;
		}
		glDisable(GL_COLOR_LOGIC_OP);
		glfwSwapBuffers(window);
	}
	else {
	}
	return 0;
}
//ȡ������ִ�е�����簴ESC����
int CGDraw2DLineSeg::Cancel(GLFWwindow* window)
{
	if (window == nullptr)
		return -1;
	CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mStep == 1) { //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
		glm::dvec3 start = view->DCS2WCS(mStart);
		glm::dvec3 pre2 = view->DCS2WCS(mPrePos2);
		//���������Ƥ��
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR); // ʹ�����ģʽʵ����Ƥ��Ч��GL_XOR
		glColor3f(0.0f, 0.0f, 1.0f);
		draw2dline(start, pre2);// ��������
		glDisable(GL_COLOR_LOGIC_OP);
		glfwSwapBuffers(window);
	}
	mStep = 0;
	mStart.x = mStart.y = mEnd.x = mEnd.y = 0.0f;
	view->ShowPrompt("����"); //״̬����ʾ
	return 0;
}