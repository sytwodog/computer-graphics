#pragma once
#include "CGObject.h"
#include "CGTransform.h"
//�ڵ�任�Զ�����������Ը��ݸ�����Ҫ������� 
class RobotBodyTransformParam : public CGObject
{
public:
	void setRotateDegree(float degree) { mRotateDegree = degree; }
	float rotateDegree() const { return mRotateDegree; }
protected:
	float mRotateDegree = 1.0f;
};

//��ת���»ص�ʾ�� 
class RobotBodyRotate : public CGCallback
{
public:
	virtual bool run(CGObject* object, void* data) override
	{
		if (!mEnabled || !object)
			return false;
		CGTransform* body = dynamic_cast<CGTransform*>(object);  //Ҫ��任�ڵ� 
		if (body) {
			RobotBodyTransformParam* d = nullptr;
			if (data) { //�Ƿ����Զ������ 
				d = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
			}
			if (d) {
				body->rotate(d->rotateDegree(), 0.0f, 1.0f, 0.0f);
			}
			else { //���û�����Զ���������Ĭ�ϲ������� 
				body->rotate(1.0f, 0.0f, 1.0f, 0.0f);
			}
			return true;
		}
		return false;
	}
};

class RotateParam : public CGObject
{
public:
	void setAngle(float angle) { mAngle = angle; }
	float armAngle() const { return mAngle; }

	void setStep(float s) { mStep = s; }
	float step() const { return mStep; }

	void setMaxAngle(float angel) { mMaxAngle = angel; }
	float maxAngle()const { return mMaxAngle; }

	void setAxis(glm::vec3 axis) { mAxis = axis; }
	glm::vec3 Axis() { return mAxis; }
protected:
	float mAngle = -45.0f; // ��ʼ�Ƕ�
	float mStep = 2.0f;
	float mMaxAngle = 45.0f;
	// Ĭ��z��
	glm::vec3 mAxis = glm::vec3(0.0f, 0.0f, 1.0f);
};

class RotateCallback : public CGCallback {
public:
	virtual bool run(CGObject* object, void* data) override {



		auto node = dynamic_cast<CGTransform*>(object);
		if (!node) {

			return false;
		}
		// ֱ��ת�� data �� ArmSwingParam*
		RotateParam* param = nullptr;
		if (data) {
			param = static_cast<RotateParam*>(data); // ���� data ָ����� ArmSwingParam
		}

		float angle = param ? param->armAngle() : -45.0f; // Ĭ�ϽǶ�

		// ���½Ƕ�
		if (param) { // ȷ�� param ��Ϊ nullptr
			float currentStep = param->step();
			float newAngle = angle + currentStep;

			if (newAngle >= param->maxAngle()) {
				newAngle = param->maxAngle();
				param->setStep(-param->step());
			}
			else if (newAngle <= -param->maxAngle()) {
				newAngle = -param->maxAngle();
				param->setStep(-param->step());
			}
			//param->setStep(currentStep);
			param->setAngle(newAngle);
		}
		// ��� param Ϊ nullptr��ʹ��Ĭ�ϽǶ� -45.0f
		glm::vec3 axis = param ? param->Axis() : glm::vec3(0.0f, 0.0f, 1.0f); // ��� param Ϊ nullptr��ʹ��Ĭ����
		node->rotate(glm::radians(param ? param->armAngle() : 2.0f), axis.x, axis.y, axis.z);
		//node->rotate(glm::radians( param->armAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
		return true;
	}
};
