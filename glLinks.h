// glLinks.h ���ļ����������������ڵ�cpp�ļ�����Ŀ��ֻ����һ��
#ifndef _GLLINKS_H_INCLUDED_ 
#define _GLLINKS_H_INCLUDED_ 1
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glm.lib")
#pragma comment(lib,"soil2.lib")
#if defined(NDEBUG) || !defined(_DEBUG) //Releaseģʽ
#if defined(_USE_GLEW)
#pragma comment(lib,"glew32.lib")
#else
#pragma comment(lib,"glad.lib")
#endif
#else //Debugģʽ
#if defined(_USE_GLEW)
#pragma comment(lib,"glew32d.lib")
#else
#pragma comment(lib,"glad.lib")
#endif
#endif
#endif //_GLLINKS_H_INCLUDED_