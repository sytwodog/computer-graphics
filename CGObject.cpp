#include "pch.h"
#include "CGObject.h"
IMPLEMENT_SERIAL(CGObject, CObject, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա��
unsigned long CGObject::sID = 0L;
CGObject::CGObject()
	: CGObject(CString("CGObject"))
{
	mName.Format(_T("CGObject%ld"), sID);
}
CGObject::CGObject(const CString& name)
	: mName(name)
{
	sID++;
}
CGObject::CGObject(const CGObject& other)
	: mName(other.mName)
{
	//�������첻�ı�sID
}
void CGObject::Serialize(CArchive& ar)
{
	CObject::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		ar << mName; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		ar >> mName;
	}
}