#pragma once
#include "glIncludes.h"
#include <vector>
#include <utility>

class CCGRenderContext
{
public:
	CCGRenderContext();
	virtual ~CCGRenderContext();

	void drawTest(void);
	//// �����߶�
	//void DDALine(int xStart, int yStart, int xEnd, int yEnd, glm::vec3 color);

	//// ���Ƶ㼯��
	//void drawPoint(std::vector<std::pair<int,int>> Points, glm::vec3 color);

	//// �����߶μ��ϣ�����һ�飬�����߶�
	//void drawLine(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// ������β�������߶�
	//void drawLineStrip(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// ������β�����߶�
	//void drawLineLoop(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// ͨ���㼯�ϣ�ÿ���������һ�����һ��������, ������ɫ��� 
	//void drawTriangles(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// �����㼯�ϣ����ν����������һ�飬����������
	//void drawTriangStrip(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// �����㼯�ϣ����е�һ����ΪԲ�ģ�ʣ�������������������Σ�����, ������״
	//void drawTriangFan(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// �����㼯�ϣ������ı��Σ�ÿ�ĸ���һ�����
	//void drawQuads(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// �����㼯�ϣ������㼯�ϣ����ν��ĸ�������ı��λ���
	//void drawQuadsStrip(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// �����㼯�ϣ������еĵ㹹�ɵĶ����������������
	//void drawPolygon(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	// ��
	void DRAWPoint(int x, int y, glm::vec3 color);
	// ��
	void DRAWLine(int xStart, int yStart, int xEnd, int yEnd, glm::vec3 color);
	// ��
	void DRAWSurface(std::vector<std::pair<int, int>> Points, glm::vec3 color);
};



