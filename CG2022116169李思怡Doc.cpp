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

// CG2022116169李思怡Doc.cpp: CCG2022116169李思怡Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2022116169李思怡.h"
#endif

#include "CG2022116169李思怡Doc.h"

#include <propkey.h>
#include "CG2022116169李思怡View.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGTransform.h"
#include "CGGeode.h"
#include "CGLineSegment.h"
#include "CGRenderContext.h"
#include "UIEventHandler.h"
#include "CGDraw2DLineSeg.h"
#include "CGDrawMulLineSeg.h"
#include "CGSceneGraphView.h"
#include "CGModel2DTransform.h"
#include "CGDrawCircle.h"
#include "CGCube.h"
#include "TessellationHints.h"
#include "CLnputDialogSphere.h"
#include "CGSphere.h"
#include "RobotBodyTransformParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2022116169李思怡Doc

IMPLEMENT_DYNCREATE(CCG2022116169李思怡Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2022116169李思怡Doc, CDocument)
	ON_COMMAND(ID_DRAW2D_LINESEG, &CCG2022116169李思怡Doc::OnDraw2dLineseg)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINESEG, &CCG2022116169李思怡Doc::OnUpdateDraw2dLineseg)
	ON_COMMAND(ID_BUTTON2, &CCG2022116169李思怡Doc::OnButton2)
	ON_UPDATE_COMMAND_UI(ID_BUTTON2, &CCG2022116169李思怡Doc::OnUpdateButton2)
	ON_COMMAND(ID_LEFT_MOVE, &CCG2022116169李思怡Doc::OnLeftMove)
	ON_COMMAND(ID_PICK_ONE, &CCG2022116169李思怡Doc::OnPickOne)
	ON_UPDATE_COMMAND_UI(ID_PICK_ONE, &CCG2022116169李思怡Doc::OnUpdatePickOne)
	ON_COMMAND(ID_RIGHT_MOVE, &CCG2022116169李思怡Doc::OnRightMove)
	ON_COMMAND(ID_TOP_MOVE, &CCG2022116169李思怡Doc::OnTopMove)
	ON_COMMAND(ID_BOTTOM_MOVE, &CCG2022116169李思怡Doc::OnBottomMove)
	ON_COMMAND(ID_ANTICLOCKWISE, &CCG2022116169李思怡Doc::OnAnticlockwise)
	ON_COMMAND(ID_CLOCKWISE, &CCG2022116169李思怡Doc::OnClockwise)
	ON_COMMAND(ID_DRAW_CIRCLE, &CCG2022116169李思怡Doc::OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CCG2022116169李思怡Doc::OnUpdateDrawCircle)
	ON_COMMAND(ID_ROTATE, &CCG2022116169李思怡Doc::OnRotate)
	ON_COMMAND(ID_X_AMPLIFY, &CCG2022116169李思怡Doc::OnXAmplify)
	ON_COMMAND(ID_X_REDUCE, &CCG2022116169李思怡Doc::OnXReduce)
	ON_COMMAND(ID_Y_AMPLIFY, &CCG2022116169李思怡Doc::OnYAmplify)
	ON_COMMAND(ID_Y_REDUCE, &CCG2022116169李思怡Doc::OnYReduce)
	ON_COMMAND(ID_EQUAL_AMPLIFY, &CCG2022116169李思怡Doc::OnEqualAmplify)
	ON_COMMAND(ID_EQUAL_REDUCE, &CCG2022116169李思怡Doc::OnEqualReduce)
	ON_COMMAND(ID_SPH_SURFACE, &CCG2022116169李思怡Doc::OnSphSurface)
	ON_COMMAND(ID_SPH_WIREFRAME, &CCG2022116169李思怡Doc::OnSphWireframe)
	ON_COMMAND(ID_TIMER, &CCG2022116169李思怡Doc::OnTimer)
	ON_UPDATE_COMMAND_UI(ID_TIMER, &CCG2022116169李思怡Doc::OnUpdateTimer)
	ON_COMMAND(ID_ROBOT, &CCG2022116169李思怡Doc::OnRobot)
	ON_COMMAND(ID_CUBE, &CCG2022116169李思怡Doc::OnCube)
	ON_UPDATE_COMMAND_UI(ID_CUBE, &CCG2022116169李思怡Doc::OnUpdateCube)
	ON_COMMAND(ID_BTN_CAMERA_CONTROL, &CCG2022116169李思怡Doc::OnBtnCameraControl)
	ON_UPDATE_COMMAND_UI(ID_BTN_CAMERA_CONTROL, &CCG2022116169李思怡Doc::OnUpdateBtnCameraControl)
	ON_COMMAND(ID_BUTTON3, &CCG2022116169李思怡Doc::OnButton3)
	ON_UPDATE_COMMAND_UI(ID_BUTTON3, &CCG2022116169李思怡Doc::OnUpdateButton3)
END_MESSAGE_MAP()


// CCG2022116169李思怡Doc 构造/析构

CCG2022116169李思怡Doc::CCG2022116169李思怡Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	mScene = std::make_shared<CGScene>();
	m_camera = std::make_shared<CGCamera>();  // 初始化相机
	mScene->SetMainCamera(m_camera);  // 设置场景主相机

	//长方体（模型）
	//auto c = std::make_shared<CGCube>();
	//auto h = std::make_shared<TessellationHints>();
	//c->setTessellationHints(h);
	//c->setDisplayListEnabled(true);
	////右长方体实例节点
	//auto t1 = std::make_shared<CGTransform>(); //实列组节点
	//auto e1 = std::make_shared<CGGeode>(); //实列叶节点
	//auto color1 = std::make_shared<CGColor>(); //属性
	//color1->setValue(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)); //黄色
	//e1->gocRenderStateSet()->setRenderState(color1, -1); //设置节点属性
	//t1->translate(100, 0, 0);
	//t1->rotate(45, 1, 1, 1);
	//t1->scale(100, 100, 100);
	//e1->AddChild(c);
	//t1->AddChild(e1);
	//mScene->GetSceneData()->asGroup()->AddChild(t1);
	////左长方体节点
	//auto t2 = std::make_shared<CGTransform>(); //实列组节点
	//auto e2 = std::make_shared<CGGeode>(); //实列叶节点
	//auto color2 = std::make_shared<CGColor>(); //属性
	//color2->setValue(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); //蓝色
	//e2->gocRenderStateSet()->setRenderState(color2, -1); //设置节点属性
	//auto p = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE); //设置线框模式
	//e2->gocRenderStateSet()->setRenderState(p, -1); //设置节点属性
	//t2->translate(-100, 0, 0);
	//t2->rotate(45, 1, 1, 1);
	//t2->scale(100, 100, 100);
	//e2->AddChild(c);
	//t2->AddChild(e2);
	//mScene->GetSceneData()->asGroup()->AddChild(t2);
	////更新回调测试
	//std::shared_ptr<RobotBodyTransformParam> data = std::make_shared<RobotBodyTransformParam>();
	//std::shared_ptr<RobotBodyRotate> rc = std::make_shared<RobotBodyRotate>();
	//t2->setUserData(data); //设置节点更新参数
	//t2->SetUpdateCallback(rc); //设置节点更新回调
	//
}

CCG2022116169李思怡Doc::~CCG2022116169李思怡Doc()
{
}

BOOL CCG2022116169李思怡Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}


// CCG2022116169李思怡Doc 序列化

void CCG2022116169李思怡Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2022116169李思怡Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCG2022116169李思怡Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCG2022116169李思怡Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCG2022116169李思怡Doc 诊断
#ifdef _DEBUG
void CCG2022116169李思怡Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2022116169李思怡Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG2022116169李思怡Doc 命令
bool CCG2022116169李思怡Doc::RenderScene(CGRenderContext* pRC)
{
	if (pRC == nullptr)
		return false;
	if (mScene == nullptr)
		return false;
	CGCamera* pCamera = mScene->GetMainCamera();
	if (pCamera == nullptr)
		return false;
	return mScene->Render(pRC, pCamera);
}

bool CCG2022116169李思怡Doc::AddRenderable(std::shared_ptr<CGNode> r)
{
	if (mSelectedGroup) { //需要先选中一各组节点
		//模型加入实例节点后加入场景
		auto ge = std::make_shared<CGGeode>();
		ge->AddChild(r);
		mSelectedGroup->AddChild(ge);
		CTreeCtrl& tree = GetSceneGraphView()->GetTreeCtrl();
		InstToSceneTree(&tree, mSelectedItem, ge.get());
		return true;
	}
	else {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
	}
	return false;
}

CCGSceneGraphView* CCG2022116169李思怡Doc::GetSceneGraphView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCGSceneGraphView))) {
			CCGSceneGraphView* view = dynamic_cast<CCGSceneGraphView*>(pView);
			return view;
		}
	}
	return nullptr;
}

void CCG2022116169李思怡Doc::InstToSceneTree(CTreeCtrl* pTree)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hInst;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = NULL;//
	CString str(_T("场景"));
	tvinsert.item.pszText = str.GetBuffer();
	str.ReleaseBuffer();
	hInst = pTree->InsertItem(&tvinsert);
	pTree->SetItemData(hInst, DWORD_PTR(mScene.get()));
	InstToSceneTree(pTree, hInst, mScene->GetSceneData());
	pTree->Expand(hInst, TVE_EXPAND);
}

void CCG2022116169李思怡Doc::InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hParent, CGNode* node)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hTree;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = TVI_LAST; tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = LPARAM(&node);//
	if (node->asGeode()) {
		CString str(_T("Geode"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		//叶子实例节点不再显示模型节点
	}
	else if (node->asTransform()) {
		CString str(_T("Trans"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asTransform()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asTransform()->GetChild(i));
		}
	}
	else if (node->asGroup()) {
		CString str(_T("Group"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asGroup()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asGroup()->GetChild(i));
		}
	}
}

void CCG2022116169李思怡Doc::OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem)
{
	mSelectedItem = hItem;
	if (!mSelectedItem) {
		mSelectedGroup = nullptr;
		return;
	}
	HTREEITEM hRoot = pTree->GetRootItem();
	if (mSelectedItem == hRoot) {
		mSelectedGroup = nullptr;
	}
	else {
		CGGroup* node = (CGGroup*)(pTree->GetItemData(mSelectedItem));
		if (node && node->asGroup() && !(node->asGeode())) { //不允许叶子节点上再
			mSelectedGroup = dynamic_cast<CGGroup*>(node);
		}
		else {
			mSelectedGroup = nullptr;
		}
	}
}

void CCG2022116169李思怡Doc::OnPickOne()
{
	// TODO: 在此添加命令处理程序代码
}

void CCG2022116169李思怡Doc::OnUpdatePickOne(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

//绘画
void CCG2022116169李思怡Doc::OnButton2()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDrawMulLineSeg(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}

void CCG2022116169李思怡Doc::OnUpdateButton2(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		EventType::Draw2DLineStrip);
}

void CCG2022116169李思怡Doc::OnDrawCircle()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// 查找对应的视图
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	// 如果找到了视图，则设置绘制圆的命令对象
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDrawCircle(view->glfwWindow())); // 创建绘制圆的命令对象
	}
}

void CCG2022116169李思怡Doc::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	// 设置菜单项或按钮的选中状态
	pCmdUI->SetCheck(UIEventHandler::CurCommand() &&
		UIEventHandler::CurCommand()->GetType() == EventType::Draw2DCircle);
}

void CCG2022116169李思怡Doc::OnDraw2dLineseg()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineSeg(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}

void CCG2022116169李思怡Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		EventType::Draw2DLineSeg);
}

//图形变换
void CCG2022116169李思怡Doc::OnRightMove()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向右平移变换（每次移动10个单位）
		const float translateAmount = 10.0f; // 正值表示向右移动
		child->Translate(translateAmount, 0);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向右移动");
	}
}

void CCG2022116169李思怡Doc::OnTopMove()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向上平移变换（每次移动10个单位）
		const float translateAmount = 10.0f; // 正值表示向上移动
		child->Translate(0, translateAmount);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向上移动");
	}
}

void CCG2022116169李思怡Doc::OnBottomMove()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向下平移变换（每次移动10个单位）
		const float translateAmount = -10.0f;
		child->Translate(0, translateAmount);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向下移动");
	}
}

void CCG2022116169李思怡Doc::OnAnticlockwise()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要旋转的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要旋转的子节点！"));
			return;
		}

		child->Rotate(10, 0, 0);


		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已旋转");
	}
}

void CCG2022116169李思怡Doc::OnLeftMove()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {

		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = -10.0f; // 负值表示向左移动
		child->Translate(translateAmount, 0);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向左移动");
	}
}

void CCG2022116169李思怡Doc::OnClockwise()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要旋转的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要旋转的子节点！"));
			return;
		}

		child->Rotate(-10, 0, 0);


		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已旋转");
	}
	
}

void CCG2022116169李思怡Doc::OnRotate()
{
	// TODO: 在此添加命令处理程序代码
	// 顺时针旋转操作
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow())); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022116169李思怡Doc::OnXAmplify()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), true, false)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022116169李思怡Doc::OnXReduce()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), true, false)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022116169李思怡Doc::OnYAmplify()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), false, true)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022116169李思怡Doc::OnYReduce()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), false, true)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022116169李思怡Doc::OnEqualAmplify()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), true, true)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022116169李思怡Doc::OnEqualReduce()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), true, true)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

// 三维表面球体绘制
void CCG2022116169李思怡Doc::OnSphSurface()
{
	CLnputDialogSphere dlg;
	if (dlg.DoModal() == IDOK)
	{
		double radius = dlg.mRadius;
		int latitude = dlg.mLatitude;
		int longitude = dlg.mLongitude;

		// 创建球体模型
		auto sphere = std::make_shared<CGSphere>(radius, latitude, longitude);
		sphere->setDisplayListEnabled(true);

		// 创建实例节点并添加变换
		auto t = std::make_shared<CGTransform>();
		auto e = std::make_shared<CGGeode>();
		auto color = std::make_shared<CGColor>();
		color->setValue(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // 红色

		// 添加几何变换（向右上方平移，绕轴旋转，缩放）
		t->translate(200, 100, 0);          // X轴正方向平移
		t->rotate(60.0, 1.0, 1.0, 0.0);    // 绕(1,1,0)轴旋转60度
		t->scale(1, 2, 1);
		
		e->gocRenderStateSet()->setRenderState(color, -1);
		e->AddChild(sphere);
		t->AddChild(e);
		mScene->GetSceneData()->asGroup()->AddChild(t);

		// 获取场景树的根节点
		CCGSceneGraphView* view = GetSceneGraphView();
		if (view)
		{
			CTreeCtrl& tree = view->GetTreeCtrl();
			HTREEITEM hRoot = tree.GetRootItem();

			// 更新场景树
			InstToSceneTree(&tree, hRoot, t.get());
		}
	}
	UpdateAllViews(NULL);
}

// 三维线框球体绘制
void CCG2022116169李思怡Doc::OnSphWireframe()
{
	CLnputDialogSphere dlg;
	if (dlg.DoModal() == IDOK)
	{
		double radius = dlg.mRadius;
		int latitude = dlg.mLatitude;
		int longitude = dlg.mLongitude;

		// 创建球体模型
		auto sphere = std::make_shared<CGSphere>(radius, latitude, longitude);
		sphere->setDisplayListEnabled(true);

		// 创建实例节点并添加变换
		auto t = std::make_shared<CGTransform>();
		auto e = std::make_shared<CGGeode>();
		auto color = std::make_shared<CGColor>();
		color->setValue(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); // 绿色

		// 添加几何变换（向左下方平移，不同轴向旋转，缩放）
		t->translate(-200, -100, 0);         // X轴负方向平移
		t->rotate(-90.0, 0.0, 1.0, 1.0);    // 绕(0,1,1)轴旋转-90度
		t->scale(1, 2, 1);

		// 设置线框模式
		auto p = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE);
		e->gocRenderStateSet()->setRenderState(p, -1);

		e->gocRenderStateSet()->setRenderState(color, -1);
		e->AddChild(sphere);
		t->AddChild(e);
		mScene->GetSceneData()->asGroup()->AddChild(t);

		// 获取场景树的根节点
		CCGSceneGraphView* view = GetSceneGraphView();
		if (view)
		{
			CTreeCtrl& tree = view->GetTreeCtrl();
			HTREEITEM hRoot = tree.GetRootItem();

			// 更新场景树
			InstToSceneTree(&tree, hRoot, t.get());
		}
	}
	UpdateAllViews(NULL);
}
void CCG2022116169李思怡Doc::OnTimer()
{
	// TODO: 在此添加命令处理程序代码
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}
	if (view != nullptr) {
		mTimer = view->toggleFrameTimer();// 启动定时器
	}
}
void CCG2022116169李思怡Doc::OnUpdateTimer(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mTimer != 0);
}


void CCG2022116169李思怡Doc::OnRobot()
{
	// TODO: 在此添加命令处理程序代码
	buildRobot();
	UpdateAllViews(NULL);
}


void CCG2022116169李思怡Doc::OnCube()
{
	// TODO: 在此添加命令处理程序代码
	
	buildRobot();
}


void CCG2022116169李思怡Doc::OnUpdateCube(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
std::shared_ptr<CGTransform> CCG2022116169李思怡Doc::createTransfrom(CString name)
{
	auto tran = std::make_shared<CGTransform>();
	tran->setName(name);
	return tran;
}

std::shared_ptr<CGTransform> CCG2022116169李思怡Doc::createBoxPart(float len, float width, float height, const glm::vec4& color, const  CString name)
{
	using namespace std;
	auto cube = make_shared<CGCube>(len, width, height);
	auto hints = make_shared<TessellationHints>();

	cube->setTessellationHints(hints);
	cube->setDisplayListEnabled(true);

	auto geode = make_shared<CGGeode>();
	geode->AddChild(cube);
	geode->setName(name);

	// 设置颜色
	auto colorState = make_shared<CGColor>();
	colorState->setValue(color);
	geode->gocRenderStateSet()->setRenderState(colorState, -1);

	//设置线框模式
	auto mode = make_shared<CGPolygonMode>(PM_LINE, PM_LINE);
	geode->gocRenderStateSet()->setRenderState(mode, -1);

	auto tran = make_shared<CGTransform>();
	tran->AddChild(geode);
	tran->setName(name);
	return tran;
}
void CCG2022116169李思怡Doc::buildRobot() {
	using namespace std;
	using namespace glm;
	// 定义常用颜色常量
	auto red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // 红色
	auto blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); // 蓝色
	auto white = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // 白色

	// 创建根节点（可选）
	auto root = createTransfrom("root");

	// create trunk 
	auto trunk = createTransfrom("trunk");

	auto middleTrunk = createBoxPart(40, 30, 30, blue, "middleTrunk");
	auto upperTrunk = createBoxPart(60, 40, 30, blue, "upperTrunk");
	auto lowerTrunk = createBoxPart(40, 20, 30, blue, "lowerTrunk");

	upperTrunk->translate(0, 35, 0);
	lowerTrunk->translate(0, -25, 0);

	trunk->AddChild(middleTrunk);
	trunk->AddChild(upperTrunk);
	trunk->AddChild(lowerTrunk);
	root->AddChild(trunk);

	//  head
	auto head = createBoxPart(30, 30, 30, red, "head");
	head->translate(0, 75, 0);
	root->AddChild(head);

	// create rightArm
	auto rightArm = createTransfrom("rightArm");

	auto rightUpperArm = createBoxPart(15, 50, 15, white, "rightUpperArm");
	auto rightLowerArm = createBoxPart(15, 50, 15, white, "rightLowerArm");

	rightLowerArm->translate(0, -40, 0);
	rightUpperArm->AddChild(rightLowerArm);

	rightArm->AddChild(rightUpperArm);
	rightArm->translate(30, 50, 0);
	rightArm->rotate(145, 0, 0, 1); // 将手臂旋转45度
	root->AddChild(rightArm);

	// 创建右手掌
	auto rightPalm = createBoxPart(15, 10, 15, white, "rightPalm");
	rightPalm->translate(0, -30, 0); // 根据手臂长度调整位置
	rightLowerArm->AddChild(rightPalm);

	// 定义手指的基本参数
	float fingerWidth = 2.0f; // 手指宽度
	float fingerHeight = 15.0f; // 手指长度
	float fingerSpacing = 3.0f; // 手指之间的间距

	// 创建右手的手指
	// 拇指
	auto thumb = createBoxPart(fingerWidth, fingerHeight, fingerWidth, white, "thumb");
	thumb->translate(-4.0f, -10.0f, 7.0f); // 调整到合适的位置
	rightPalm->AddChild(thumb);

	// 食指
	auto indexFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, white, "indexFinger");
	indexFinger->translate(-(fingerSpacing * 2), -10.0f, 0.0f);
	rightPalm->AddChild(indexFinger);

	// 中指
	auto middleFinger = createBoxPart(fingerWidth, fingerHeight + 3.0f, fingerWidth, white, "middleFinger"); // 中指稍长一些
	middleFinger->translate(-(fingerSpacing), -10.0f, 0.0f);
	rightPalm->AddChild(middleFinger);

	// 无名指
	auto ringFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, white, "ringFinger");
	ringFinger->translate(0.0f, -10.0f, 0.0f);
	rightPalm->AddChild(ringFinger);

	// 小指
	auto littleFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, white, "littleFinger");
	littleFinger->translate((fingerSpacing), -10.0f, 0.0f);
	rightPalm->AddChild(littleFinger);

	// create leftArm
	auto leftArm = createTransfrom("leftArm");

	auto leftUpperArm = createBoxPart(15, 50, 15, white, "leftUpperArm");
	auto leftLowerArm = createBoxPart(15, 50, 15, white, "leftLowerArm");

	leftLowerArm->translate(0, -40, 0);
	leftUpperArm->AddChild(leftLowerArm);

	leftArm->AddChild(leftUpperArm);
	leftArm->translate(-30, 50, 0);
	leftArm->rotate(-145, 0, 0, 1); // 将手臂旋转45度
	root->AddChild(leftArm);

	// 创建左手掌
	auto leftPalm = createBoxPart(15, 10, 15, white, "leftPalm");
	leftPalm->translate(0, -30, 0); // 根据手臂长度调整位置
	leftLowerArm->AddChild(leftPalm);

	// 创建左手的手指
	// 拇指
	auto leftThumb = createBoxPart(fingerWidth, fingerHeight, fingerWidth, white, "leftThumb");
	leftThumb->translate(4.0f, -10.0f, 7.0f); // 调整到合适的位置
	leftPalm->AddChild(leftThumb);

	// 食指
	auto leftIndexFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, white, "leftIndexFinger");
	leftIndexFinger->translate((fingerSpacing * 2), -10.0f, 0.0f);
	leftPalm->AddChild(leftIndexFinger);

	// 中指
	auto leftMiddleFinger = createBoxPart(fingerWidth, fingerHeight + 3.0f, fingerWidth, white, "leftMiddleFinger");
	leftMiddleFinger->translate((fingerSpacing), -10.0f, 0.0f);
	leftPalm->AddChild(leftMiddleFinger);

	// 无名指
	auto leftRingFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, white, "leftRingFinger");
	leftRingFinger->translate(0.0f, -10.0f, 0.0f);
	leftPalm->AddChild(leftRingFinger);

	// 小指
	auto leftLittleFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, white, "leftLittleFinger");
	leftLittleFinger->translate(-(fingerSpacing), -10.0f, 0.0f);
	leftPalm->AddChild(leftLittleFinger);

	// right leg
	auto rightLeg = createTransfrom("rightLeg");
	auto rightUpperLeg = createBoxPart(15, 60, 15, white, "rightUpperLeg");
	auto rightLowerLeg = createBoxPart(15, 60, 15, white, "rightLowerLeg");

	rightLowerLeg->translate(-12.5, -55, 0);
	rightLowerLeg->rotate(-10, 0, 0, 1);

	rightUpperLeg->AddChild(rightLowerLeg);
	rightLeg->rotate(10, 0, 0, 1);

	rightLeg->translate(5, -70, 0);

	rightLeg->AddChild(rightUpperLeg);
	root->AddChild(rightLeg);

	// 创建右脚掌
	auto rightFoot = createBoxPart(15, 10, 30, white, "rightFoot"); // 尺寸适合脚掌
	rightFoot->translate(0, -35, 0); // 调整到合适的位置
	rightLowerLeg->AddChild(rightFoot);

	// left leg
	auto leftLeg = createTransfrom("leftLeg");
	auto leftUpperLeg = createBoxPart(15, 60, 15, white, "leftUpperLeg");
	auto leftLowerLeg = createBoxPart(15, 60, 15, white, "leftLowerLeg");

	leftLowerLeg->translate(12.5, -55, 0);
	leftLowerLeg->rotate(10, 0, 0, 1);

	leftUpperLeg->AddChild(leftLowerLeg);
	leftLeg->rotate(-10, 0, 0, 1);

	leftLeg->translate(-5, -70, 0);

	leftLeg->AddChild(leftUpperLeg);

	root->AddChild(leftLeg);

	// 创建左脚掌
	auto leftFoot = createBoxPart(15, 10, 30, white, "leftFoot");
	leftFoot->translate(0, -35, 0);
	leftLowerLeg->AddChild(leftFoot);

	AddNode(root);
	// 添加根节点到场景
	if (mScene && mScene->GetSceneData()) {
		mScene->GetSceneData()->asGroup()->AddChild(root);
	}

	// 更新场景树
	CCGSceneGraphView* view = GetSceneGraphView();
	if (view) {
		CTreeCtrl& tree = view->GetTreeCtrl();
		HTREEITEM hRoot = tree.GetRootItem(); // 获取根节点（通常是"场景"节点）
		if (hRoot) {
			// 从场景树根节点开始，插入机器人根节点（root）
			InstToSceneTree(&tree, hRoot, root.get());
		}
	}

	std::shared_ptr<RobotBodyTransformParam> data = std::make_shared<RobotBodyTransformParam>();
	std::shared_ptr<RobotBodyRotate> rc = std::make_shared<RobotBodyRotate>();
	root->setUserData(data);
	root->SetUpdateCallback(rc);

	shared_ptr<RotateParam> leftParam = make_shared<RotateParam>();
	shared_ptr<RotateParam> rightParam = make_shared< RotateParam>();
	rightParam->setMaxAngle(45);
	rightParam->setAngle(45);
	rightParam->setStep(-2);

	shared_ptr<RotateCallback> callback = make_shared<RotateCallback>();

	leftArm->setUserData(leftParam);
	leftArm->SetUpdateCallback(callback);

	rightArm->setUserData(rightParam);
	rightArm->SetUpdateCallback(callback);

	leftLeg->setUserData(leftParam);
	leftLeg->SetUpdateCallback(callback);

	rightLeg->setUserData(rightParam);
	rightLeg->SetUpdateCallback(callback);

	// 刷新视图
	UpdateAllViews(NULL);
}

bool CCG2022116169李思怡Doc::AddNode(std::shared_ptr<CGNode>  node)
{
	if (node.get() == nullptr)
		return false;
	if (mSelectedGroup) {
		mSelectedGroup->AddChild(node);
	}
	else {
		mScene->GetSceneData()->asGroup()->AddChild(node);
	}
	return true;
}

void CCG2022116169李思怡Doc::OnBtnCameraControl()
{
	// 获取当前视图
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}

	if (!view) return;

	// 切换相机控制状态
	if (m_cameraControl) {
		// 如果已存在相机控制器，则移除
		UIEventHandler::DelCommand();
		m_cameraControl.reset();
		view->ShowPrompt("相机控制已关闭");
	}
	else {
		// 创建新的相机控制器
		m_cameraControl = std::make_shared<CGCameraControl>(
			view->glfwWindow(),
			m_camera
		);
		UIEventHandler::SetCommand(m_cameraControl.get());

		view->ShowPrompt("相机控制已激活 - 使用鼠标和键盘控制视角");
	}

	UpdateAllViews(NULL);  // 更新视图
	
}


void CCG2022116169李思怡Doc::OnUpdateBtnCameraControl(CCmdUI* pCmdUI)
{
	// 根据相机控制器是否存在来更新按钮状态
	pCmdUI->SetCheck(m_cameraControl != nullptr);
}


void CCG2022116169李思怡Doc::OnButton3()
{
	// 获取当前视图
	CCG2022116169李思怡View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022116169李思怡View))) {
			view = dynamic_cast<CCG2022116169李思怡View*>(pView);
			break;
		}
	}

	if (!view) return;

	// 切换相机控制状态
	if (m_cameraControl) {
		// 如果已存在相机控制器，则移除
		UIEventHandler::DelCommand();
		m_cameraControl.reset();
		view->ShowPrompt("相机控制已关闭");
	}
	else {
		// 创建新的相机控制器
		m_cameraControl = std::make_shared<CGCameraControl>(
			view->glfwWindow(),
			m_camera
		);
		UIEventHandler::SetCommand(m_cameraControl.get());

		view->ShowPrompt("相机控制已激活 - 使用鼠标和键盘控制视角");
	}

	UpdateAllViews(NULL);  // 更新视图
}


void CCG2022116169李思怡Doc::OnUpdateButton3(CCmdUI* pCmdUI)
{
	// 根据相机控制器是否存在来更新按钮状态
	pCmdUI->SetCheck(m_cameraControl != nullptr);
}
