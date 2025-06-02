// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CG2022116169李思怡Doc.h: CCG2022116169李思怡Doc 类的接口
//


#pragma once
#include <memory>
#include "CGCamera.h"
#include "CGScene.h"
#include "CGCameraControl.h"
class CGscene;
class CGRenderContext;
class CGNode;
class CGGroup;
class CCGSceneGraphView;
class CCG2022116169李思怡Doc : public CDocument
{
protected:
	CGGroup* mSelectedGroup = nullptr;
	HTREEITEM mSelectedItem = nullptr;
public:
	CCGSceneGraphView* GetSceneGraphView();
	void InstToSceneTree(CTreeCtrl* pTree);//实列节点加入场景树
	void InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hInst, CGNode* node);
	void OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem); //场景树中选中节点
protected: // 仅从序列化创建
	CCG2022116169李思怡Doc() noexcept;
	DECLARE_DYNCREATE(CCG2022116169李思怡Doc)

// 特性
public:
	std::shared_ptr<CGScene> mScene = nullptr;
// 操作
public:
	bool RenderScene(CGRenderContext* pRC);
	bool AddRenderable(std::shared_ptr<CGNode> r);

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CCG2022116169李思怡Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnDraw2dLineseg();
	afx_msg void OnUpdateDraw2dLineseg(CCmdUI* pCmdUI);
	afx_msg void OnButton2();
	afx_msg void OnUpdateButton2(CCmdUI* pCmdUI);
	afx_msg void OnLeftMove();
	afx_msg void OnPickOne();
	afx_msg void OnUpdatePickOne(CCmdUI* pCmdUI);
	afx_msg void OnRightMove();
	afx_msg void OnTopMove();
	afx_msg void OnBottomMove();
	afx_msg void OnAnticlockwise();
	afx_msg void OnClockwise();
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnRotate();
	afx_msg void OnXAmplify();
	afx_msg void OnXReduce();
	afx_msg void OnYAmplify();
	afx_msg void OnYReduce();
	afx_msg void OnEqualAmplify();
	afx_msg void OnEqualReduce();

	//三维图形绘制
	afx_msg void OnSphSurface();
	afx_msg void OnSphWireframe();

protected:
	UINT mTimer = 0; //定时器
	std::shared_ptr<CGCamera> m_camera;  // 相机成员变量
	std::shared_ptr<CGCameraControl> m_cameraControl;
public:
	afx_msg void OnTimer();
	afx_msg void OnUpdateTimer(CCmdUI* pCmdUI);
	void CreateRobot();
	afx_msg void OnRobot();
	afx_msg void OnCube();
	afx_msg void OnUpdateCube(CCmdUI* pCmdUI);
	std::shared_ptr<CGTransform> createTransfrom(CString name);
	std::shared_ptr<CGTransform> createBoxPart(float len, float width, float height, const glm::vec4& color, const CString name);
	void buildRobot();
	bool AddNode(std::shared_ptr<CGNode> node);
public:
	void OnViewResize(int cx, int cy) { mScene->GetMainCamera()->viewport()->set(0, 0, cx, cy); }
	afx_msg void OnBtnCameraControl();
	afx_msg void OnUpdateBtnCameraControl(CCmdUI* pCmdUI);
	afx_msg void OnButton3();
	afx_msg void OnUpdateButton3(CCmdUI* pCmdUI);
};
