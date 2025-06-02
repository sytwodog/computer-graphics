#ifndef _CGObject_H_INCLUDED
#define _CGObject_H_INCLUDED
#include <afx.h>
#include <memory>
#include <string>
#include "glIncludes.h"
/// CGObject����Ϊ�����л������Ļ���
/// ʹ��MFC ��CObject��Ϊ���࣬����֧������ʱ����Ϣ����̬���������л�������������
/// �������ܣ���֧������ʱ����Ϣ�����л�������������ڴ����
/// �������ܼ��϶�����ʱ����Ϣ��֧�֡���DECLARE_DYNAMIC����IMPLEMENT_DYNAMIC�������ʵ���ļ� (.CPP) �У�
/// �������ܼ��϶�����ʱ����Ϣ�Ͷ�̬������֧�֡���DECLARE_DYNCREATE����IMPLEMENT_DYNCREATE �������ʵ���ļ�(.CPP) �У�
/// �������ܼ��϶�����ʱ����Ϣ����̬���������л���֧�֡���DECLARE_SERIAL����IMPLEMENT_SERIAL�������ʵ���ļ�(.CPP) �У�
class CGObject : public CObject
{
	DECLARE_SERIAL(CGObject) //������ʱ����Ϣ����̬���������л���֧�֣�IMPLEMENT_SERIAL�������ʵ���ļ�(.CPP) �У�
public:
	CGObject();
	CGObject(const CString& name);
	CGObject(const CGObject& other);
	virtual ~CGObject() = default; //����������
	//���л��������Ҫ���л�/�����л�֧��������Ӧʹ��DECLARE_SERIAL/IMPLEMENT_SERIA����д���麯����
	virtual void Serialize(CArchive& ar) override;
	const CString& Name() const { return mName; }
	CString& Name() { return mName; }
	void setName(CString name) { this->mName = name; }
protected:
	CString mName; //�������ƣ�Ĭ���ɡ�����+��š����ɣ�������ʾ
	static unsigned long sID; //����ID�������ڸ�����������������Ψһ��ʶ
public:
	const CGObject* userData() const { return mUserData.get(); }
	CGObject* userData() { return mUserData.get(); }
	void setUserData(std::shared_ptr<CGObject> user_data) { mUserData = user_data; }
private:
	std::shared_ptr<CGObject> mUserData = nullptr;
};
//�ص���������Ҫ�����ඨ��ص���Ϊ��ͨ��run���У�
class CGCallback : public CGObject
{
public:
	CGCallback() : mEnabled(true) {}
	//����������дʵ����Ҫ�Ļص�����
	virtual bool run(CGObject* object, void* data)
	{
		if (!mEnabled)
			return false;
		return true;
	}
	void setEnabled(bool enabled) { mEnabled = enabled; }
	bool isEnabled() const { return mEnabled; }
protected:
	virtual ~CGCallback() = default;
	bool mEnabled;
};
#endif //_CGObject_H_INCLUDED