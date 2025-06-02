#include "pch.h"
#include "homework1.h"
#include "CG2022116169��˼��View.h"
// ���Ƶ㼯��
void drawPoint() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0f);

	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(30, 70);
	glVertex2i(25, 80);
	glVertex2i(50, 70);
	glVertex2i(60, 80);
	glVertex2i(70, 90);
	glEnd();
}

// �����߶μ��ϣ�����һ�飬�����߶�
void drawLine() {
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(200, 40);
	glVertex2i(300, 120);

	glVertex2i(270, 80);
	glVertex2i(400, 60);

	glVertex2i(240, 50);
	glVertex2i(370, 20);

	glVertex2i(220, 10);
	glVertex2i(375, 40);



	glEnd();
}

// ������β�������߶�
void drawLineStrip() {
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(600, 140);
	glVertex2i(800, 30);
	glVertex2i(720, 120);
	glVertex2i(600, 100);
	glVertex2i(570, 70);
	glEnd();
}

// ������β�����߶�
void drawLineLoop() {
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(940, 95);
	glVertex2i(970, 30);
	glVertex2i(1100, 30);
	glVertex2i(1050, 110);
	glVertex2i(1010, 80);
	glVertex2i(990, 120);
	glEnd();
}

// ͨ���㼯�ϣ�ÿ���������һ�����һ��������, ������ɫ��� 
void drawTriangles() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(40, 200);
	glVertex2i(40, 230);
	glVertex2i(100, 200);

	glVertex2i(120, 220);
	glVertex2i(60, 250);
	glVertex2i(180, 250);
	glEnd();
}

// �����㼯�ϣ����ν����������һ�飬����������
void drawTriangStrip() {
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(275, 250);
	glVertex2i(275, 200);
	glVertex2i(320, 250);
	glVertex2i(380, 200);
	glVertex2i(400, 250);
	glVertex2i(420, 170);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(275, 250);
	glVertex2i(275, 200);

	glVertex2i(275, 250);
	glVertex2i(320, 250);

	glVertex2i(320, 250);
	glVertex2i(275, 200);

	glVertex2i(320, 250);
	glVertex2i(400, 250);

	glVertex2i(320, 250);
	glVertex2i(380, 200);

	glVertex2i(380, 200);
	glVertex2i(400, 250);

	glVertex2i(400, 250);
	glVertex2i(420, 170);

	glEnd();
}

// �����㼯�ϣ����е�һ����ΪԲ�ģ�ʣ�������������������Σ�����, ������״
void drawTriangFan() {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(650, 200);
	glVertex2i(650, 250);
	glVertex2i(685, 237);
	glVertex2i(692, 210);
	glVertex2i(685, 185);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(650, 200);
	glVertex2i(685, 237);

	glVertex2i(650, 200);
	glVertex2i(692, 210);

	glEnd();
}

// �����㼯�ϣ������ı��Σ�ÿ�ĸ���һ�����
void drawQuads() {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(850, 200);
	glVertex2i(890, 250);
	glVertex2i(1000, 260);
	glVertex2i(1000, 190);

	glVertex2i(1030, 150);
	glVertex2i(1060, 250);
	glVertex2i(1100, 270);
	glVertex2i(1080, 150);
	glEnd();
}

// �����㼯�ϣ������㼯�ϣ����ν��ĸ�������ı��λ���
void drawQuadsStrip() {
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(50, 300);
	glVertex2i(40, 350);
	glVertex2i(90, 300);
	glVertex2i(90, 357);
	glVertex2i(120, 307);
	glVertex2i(115, 365);
	glVertex2i(140, 315);
	glVertex2i(137, 377);

	glVertex2i(1080, 150);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(90, 300);
	glVertex2i(90, 357);

	glVertex2i(120, 307);
	glVertex2i(115, 365);

	glEnd();

}

// �����㼯�ϣ������еĵ㹹�ɵĶ����������������
void drawPolygon() {
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(347, 355);
	glVertex2i(450, 370);
	glVertex2i(430, 325);
	glVertex2i(340, 315);
	glVertex2i(332, 330);
	glEnd();
}


// �����
void drawStar(float cx, float cy, float outerRadius, float innerRadius, glm::vec3 color1, glm::vec3 color2) {
	//const float cx = 500.0f, cy = 450.0f;
	//const float outerRadius = 100.0f;
	//const float innerRadius = 40.0f;
	const float PI = 3.14159265358979323846f;

	std::vector<GLfloat> vertices;

	for (int i = 0; i < 5; ++i) {

		float outerAngle = (i * 72.0f + 90.0f) * PI / 180.0f;
		vertices.push_back(cx + outerRadius * cos(outerAngle)); // X
		vertices.push_back(cy + outerRadius * sin(outerAngle)); // Y


		float innerAngle = outerAngle + 36.0f * PI / 180.0f;
		vertices.push_back(cx + innerRadius * cos(innerAngle)); // X
		vertices.push_back(cy + innerRadius * sin(innerAngle)); // Y
	}



	// ����˳�����ɫ����
	for (size_t i = 0; i < vertices.size() / 4; ++i) { // +2���ڱջ�

		int index = (i % 5) * 4;

		glBegin(GL_TRIANGLE_STRIP);


		glColor3f(color1.r, color1.g, color1.b);
		glVertex2f(cx, cy);
		glVertex2f(vertices[index], vertices[index + 1]);
		glVertex2f(vertices[index + 2], vertices[index + 3]);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(color2.r, color2.g, color2.b);
		glVertex2f(cx, cy);
		glVertex2f(vertices[index + 2], vertices[index + 3]);
		if (i == vertices.size() / 4 - 1)
			glVertex2f(vertices[0], vertices[1]);
		else {
			glVertex2f(vertices[index + 4], vertices[index + 5]);
		}
		glEnd();
	}


}