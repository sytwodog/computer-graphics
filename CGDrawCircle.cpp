#include "pch.h"
#include "CGDrawCircle.h"
#include "CG2022116169李思怡Doc.h" //包含View之前要包含Doc
#include "CG2022116169李思怡View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CGCircle.h"

// 绘制二维圆
static void draw2dcircle(glm::dvec3& center, double radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(center.x, center.y);
    for (int i = 0; i <= 360; ++i) {
        double angle = i * 3.1415926 / 180.0;
        glVertex2d(center.x + radius * cos(angle), center.y + radius * sin(angle));
    }
    glEnd();
}

CGDrawCircle::CGDrawCircle(GLFWwindow* window)
    : UIEventHandler(window), mCenter(0.0, 0.0, 0.0), mRadius(0.0)
{
}

CGDrawCircle::~CGDrawCircle()
{
}

EventType CGDrawCircle::GetType() //命令类型
{
    //UIEventHandler.h中定义，要根据不同的命令对象进行修改，此处是绘制圆
    return EventType::Draw2DCircle;
}

//假定鼠标左键单击拾取圆心、圆上一点，移动鼠标时画橡皮筋圆
int CGDrawCircle::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (window == nullptr)
        return -1;
    CCG2022116169李思怡View* view = (CCG2022116169李思怡View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mStep++; //每次单击鼠标左键时操作步骤计数加一
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (mStep == 1) { //第一次单击鼠标左键，记录鼠标点击位置作为将创建圆的圆心
                mCenter.x = xpos;
                mCenter.y = ypos;
                mRadius = 0.0;
                view->ShowPrompt("请鼠标左键单击输入圆上的一点以确定半径"); //通过处理事件的View显示到状态栏
            }
            else if (mStep == 2) { //第二次单击鼠标左键，记录鼠标点击位置作为将创建圆的半径
                if (xpos == mCenter.x && ypos == mCenter.y) {
                    mStep = 1;
                    view->ShowPrompt("与圆心重合，请鼠标左键单击重新输入圆上的一点");
                    return -1;
                }
                // 计算半径
                mRadius = std::sqrt((xpos - mCenter.x) * (xpos - mCenter.x) + (ypos - mCenter.y) * (ypos - mCenter.y));
                glm::dvec3 center = view->DCS2WCS(mCenter);
                glm::dvec3 end = view->DCS2WCS(glm::dvec3(xpos, ypos, 0.0));
                //擦除最后橡皮线
                glEnable(GL_COLOR_LOGIC_OP);
                glLogicOp(GL_XOR); // 使用异或模式实现橡皮线效果GL_XOR
                glColor3f(0.0f, 0.0f, 1.0f);
                draw2dcircle(center, mRadius);
                glDisable(GL_COLOR_LOGIC_OP);
                glfwSwapBuffers(window);
                //鼠标左键第二次单击，圆的圆心和半径已获取。
                //创建对象要注意坐标转换到场景，并设置相应的属性。
                glm::dvec3 circleCenter = view->DCS2WCS(mCenter);
                view->AddRenderable(std::make_shared<CGCircle>(circleCenter, mRadius)); //创建添加到场景
                view->Invalidate(); //客户区需要重绘
                view->UpdateWindow(); //客户区执行重绘
                mStep = 0; //设为0可重写开始绘制圆而不用点击命令面板上的圆按钮
                mCenter.x = mCenter.y = mRadius = 0.0;
                view->ShowPrompt("请输入圆的圆心"); //状态栏显示
            }
            else {
            }
        }
    }
    return 0;
}

int CGDrawCircle::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    if (window == nullptr)
        return -1;
    CCG2022116169李思怡View* view = (CCG2022116169李思怡View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    if (mStep == 0) { //还没点击第一个点（获取圆心）
        view->ShowPrompt("请鼠标左键单击输入圆的圆心"); //状态栏显示
    }
    else if (mStep == 1) { //已经输入了圆心后，当前鼠标移动的位置与圆心形成橡皮圆
        if (xpos == mCenter.x && ypos == mCenter.y) {
            return -1; //两点重合，不做处理
        }
        double preRadius, curRadius;
        preRadius = mRadius;
        // 计算半径
        mRadius = std::sqrt((xpos - mCenter.x) * (xpos - mCenter.x) + (ypos - mCenter.y) * (ypos - mCenter.y));
        curRadius = mRadius;

        glm::dvec3 center = view->DCS2WCS(mCenter);
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR); // 使用异或模式实现橡皮线效果GL_XOR
        glColor3f(0.0f, 0.0f, 1.0f);
        draw2dcircle(center, preRadius); // 擦除旧橡皮圆
        draw2dcircle(center, curRadius); // 绘制新橡皮圆
        glDisable(GL_COLOR_LOGIC_OP);
        glfwSwapBuffers(window);

        mRadius = curRadius; //记录最新位置，作为确定半径的点
    }
    else {
    }
    return 0;
}

//取消正在执行的命令（如按ESC键）
int CGDrawCircle::Cancel(GLFWwindow* window)
{
    if (window == nullptr)
        return -1;
    CCG2022116169李思怡View* view = (CCG2022116169李思怡View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    if (mStep == 1) { //如果已经单击左键一次，则结束操作前删除橡皮圆
        glm::dvec3 center = view->DCS2WCS(mCenter);
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR); // 使用异或模式实现橡皮线效果GL_XOR
        glColor3f(0.0f, 0.0f, 1.0f);
        draw2dcircle(center, mRadius); // 擦除旧橡皮圆
        glDisable(GL_COLOR_LOGIC_OP);
        glfwSwapBuffers(window);
    }
    mStep = 0;
    mCenter.x = mCenter.y = mRadius = 0.0f;
    view->ShowPrompt("就绪"); //状态栏显示
    return 0;
}