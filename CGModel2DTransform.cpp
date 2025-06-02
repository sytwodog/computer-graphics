#include "pch.h"
#include "CGModel2DTransform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CG2022116169��˼��Doc.h" // ����View֮ǰҪ����Doc
#include "CG2022116169��˼��View.h" // �û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include <iostream>
CGModel2DTransform::CGModel2DTransform(
	CGNode* node,
	GLFWwindow* window,
	bool isScaleX,
	bool isScaleY,
	glm::vec3 pivotPoint,
	bool showPivot
) : UIEventHandler(window),
mNode(node),
mIsScaleX(isScaleX),
mIsScaleY(isScaleY),
mPivotPoint(pivotPoint),
mShowPivot(showPivot),
mIsRotating(false),      // �̶�Ĭ��ֵ
mLastCursorPos(0.0),
mIsDragging(false)
{
	if (window) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		glfwFocusWindow(window);
		mLastCursorPos = glm::dvec2(x, y);
	}
}

CGModel2DTransform::~CGModel2DTransform() = default;

EventType CGModel2DTransform::GetType()
{
	return EventType::Model2DTransform;
}

int CGModel2DTransform::OnMouseButton(GLFWwindow* window, int button, int action, int mods) {
	if (!mNode || !window) return 0;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		if (mods & GLFW_MOD_SHIFT) {
			// Shift+�����������ת���ģ���ת�����꣩
			CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
			if (view) {
				// ת����Ļ���� (DCS) �� �������� (WCS)
				glm::dvec3 pivotDCS(x, y, 0.0);
				mPivotPoint = view->DCS2WCS(pivotDCS); // �洢Ϊ��������
				mShowPivot = true;
				// ǿ��ˢ�½��棨��ʾ��ת���ı�ǣ�
				std::string coordText = "��ת����: (" +
					std::to_string(mPivotPoint.x) + ", " +
					std::to_string(mPivotPoint.y) + ", " +
					std::to_string(mPivotPoint.z) + ")";
				// �ڽ�������ʾ����
				view->ShowPrompt(coordText.c_str());  // ���� ShowPrompt ���� const char*
				view->Invalidate();
				view->UpdateWindow();
			}
		}
	}
	// �����Ҽ�ֱ����ת�߼�
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			mIsRotating = true; // ��ʼ��ת
			glm::dvec3 pivotDCS(x, y, 0.0);
			mLastCursorPos = pivotDCS;
			glfwGetCursorPos(window, &mLastCursorPos.x, &mLastCursorPos.y);
		}
		else if (action == GLFW_RELEASE) {
			mIsRotating = false; // ֹͣ��ת
		}
	}

	return 1;
}



int CGModel2DTransform::OnCursorPos(GLFWwindow* window, double xpos, double ypos) {
	if (!mNode || !window || !mIsRotating) return 0;

	CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
	if (!view) return 0;

	glm::dvec3 currentPosDCS(xpos, ypos, 0.0);
	glm::dvec3 currentPosWCS = view->DCS2WCS(currentPosDCS);
	glm::dvec3 lastPosDCS(mLastCursorPos.x, mLastCursorPos.y, 0.0);
	glm::dvec3 lastPosWCS = view->DCS2WCS(lastPosDCS);


	double currentDx = currentPosWCS.x - mPivotPoint.x;
	double currentDy = currentPosWCS.y - mPivotPoint.y;
	double currentAngle = atan2(currentDy, currentDx);

	double lastDx = lastPosWCS.x - mPivotPoint.x;
	double lastDy = lastPosWCS.y - mPivotPoint.y;
	double lastAngle = atan2(lastDy, lastDx);


	double deltaAngleByPosition = currentAngle - lastAngle;


	if (deltaAngleByPosition > M_PI) {
		deltaAngleByPosition -= 2.0 * M_PI;
	}
	else if (deltaAngleByPosition < -M_PI) {
		deltaAngleByPosition += 2.0 * M_PI;
	}

	//std::string coordText = "��ת�Ƕ�: (" + std::to_string(deltaAngleByPosition) + "�����´νǶ�:( + std::to_string(deltaAngleByDistance) + )";
	//view->ShowPrompt(coordText.c_str());

	// ��Ļ����λ��
	double dx = xpos - mLastCursorPos.x;
	double dy = ypos - mLastCursorPos.y;
	if (deltaAngleByPosition * dx > 0)
		dx = -dx;

	//std::string coordText = "��ת�Ƕ�: (" + std::to_string(deltaAngleByPosition) + "�����´νǶ�:(" + std::to_string(dx) + ")";
	//view->ShowPrompt(coordText.c_str());


	// ���������� dx ������
	const double distanceFactor = 0.5; // ���Ե�
	double deltaAngleByDistance = dx * distanceFactor;

	// �ں�
	double deltaAngle = deltaAngleByPosition + deltaAngleByDistance;

	// ƽ��
	const double smoothingFactor = 0.8;
	deltaAngle *= smoothingFactor;
	deltaAngle = -deltaAngle;
	// ��ʾ
	/*std::string coordText = "��ת�Ƕ�: (" + std::to_string(deltaAngle) + "�����´νǶ�:(" + std::to_string(deltaAngleByDistance) + ")";
	view->ShowPrompt(coordText.c_str());*/
	std::string coordText = "��ת����: (" + std::to_string(mPivotPoint.x) + std::to_string(mPivotPoint.y) + "������ת�Ƕ�:(" + std::to_string(deltaAngle) + ")";
	view->ShowPrompt(coordText.c_str());
	// ��ת
	mNode->Rotate(deltaAngle, mPivotPoint.x, mPivotPoint.y);

	view->Invalidate();
	view->UpdateWindow();

	mLastCursorPos = glm::dvec2(xpos, ypos);

	return 1;
}





int CGModel2DTransform::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	// ����Ƿ��� Ctrl ��
	CCG2022116169��˼��View* view = (CCG2022116169��˼��View*)glfwGetWindowUserPointer(window);
	if (!view) return 0;
	bool isCtrlPressed = (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);
	if (isCtrlPressed && mNode != nullptr)
	{
		// �����������ӣ��������ϷŴ�������С��
		double scaleFactor = (yoffset > 0) ? 1.1 : 0.9; // 10% ����

		// ֱ�ӵ��ýڵ��Scale����
		mNode->Scale(
			mIsScaleX ? scaleFactor : 1.0,
			mIsScaleY ? scaleFactor : 1.0,
			mPivotPoint.x,
			mPivotPoint.y
		);
		view->ShowPrompt("��ʵ�����ţ�");
		view->Invalidate();
		view->UpdateWindow();

		return 1; // �¼��Ѵ���
	}
	return 0; // �¼�δ����
}

int CGModel2DTransform::Cancel(GLFWwindow* window)
{
	mIsRotating = false;
	return 1;
}
