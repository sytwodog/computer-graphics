#pragma once

#include "CG2022116169��˼��View.h"


// ���Ƶ㼯
void drawPoint();

// �����߶μ��ϣ�����һ�飬�����߶�
void drawLine();

// ������β�������߶�
void drawLineStrip();

// ������β�����߶�
void drawLineLoop();

// ͨ���㼯�ϣ�ÿ���������һ�����һ��������, ������ɫ��� 
void drawTriangles();

// �����㼯�ϣ����ν����������һ�飬����������
void drawTriangStrip();

// �����㼯�ϣ����е�һ����ΪԲ�ģ�ʣ�������������������Σ�����, ������״
void drawTriangFan();

// �����㼯�ϣ������ı��Σ�ÿ�ĸ���һ�����
void drawQuads();

// �����㼯�ϣ������㼯�ϣ����ν��ĸ�������ı��λ���
void drawQuadsStrip();

// �����㼯�ϣ������еĵ㹹�ɵĶ����������������
void drawPolygon();

void drawStar(float cx, float cy, float outerRadius, float innerRadius, glm::vec3 color1, glm::vec3 color2);

std::vector<glm::ivec2> BresenhamCircleWithPoints(int xc, int yc, int r, glm::vec3 color);