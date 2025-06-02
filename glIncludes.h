//glIncludes.h ����OpenGL��Ҫ��ͷ�ļ���

#ifndef _GLINCLUDES_H_INCLUDED_
#define _GLINCLUDES_H_INCLUDED_ 1
#if defined(_USE_GLEW)
#include <GL/glew.h>
#else
#include <GLAD/glad.h>
#include <GL/glext.h>
#endif
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#define GLM_ENABLE_EXPERIMENTAL
//�����õ���OpenGL��ѧ�⡢ͼ����ؿ�
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SOIL2/SOIL2.h>
#endif //_GLINCLUDES_H_INCLUDED_