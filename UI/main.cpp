
#include <stdlib.h>
#include <crtdbg.h>

#include "stdio.h"
#include <wtf/Vector.h>
#include <wtf/text/StringBuilder.h>
#include <wtf/text/CString.h>
#include <wtf/RefPtr.h>
#include <wtf/MainThread.h>
#include "RunLoop.h"

#include "FrameHostWnd.h"
#include "ViewTree.h"
#include "ViewFactory.h"
#include "Container.h"
#include "LinearLayout.h"
#include "TextView.h"

#include "ImageManager.h"
#include "ViewTreeBuild.h"

using namespace UI;


void test1() 
{
	RefPtr<FrameHostWnd> frameHostWnd = FrameHostWnd::create();

	RefPtr<ViewTree> viewTree = ViewTree::create();

	RefPtr<View> view1 = ViewFactory::createView("view");
	RefPtr<View> view2 = ViewFactory::createView("view");
	RefPtr<View> view3 = ViewFactory::createView("view");
	RefPtr<View> view4 = ViewFactory::createView("view");
	RefPtr<View> view5 = ViewFactory::createView("view");

	view1->setRect(0, 0, 100, 100);
	view2->setRect(50, 50, 300, 300);
	view3->setRect(333, 100, 100,100);
	view4->setRect(100, 200, 200, 300);
	view5->setRect(400, 400, 100, 200);

	RefPtr<View> root = ViewFactory::createView("LinearLayout");
	Container *pContainer = reinterpret_cast<Container *>(root.get());
	pContainer->setRect(0, 0, 500, 500);

	//pContainer->addChild(view1);
	//pContainer->addChild(view2);
	//pContainer->addChild(view3);
	pContainer->addChild(view4);
	//pContainer->addChild(view5);

	//pContainer->layout();

	viewTree->setRoot(root);


	frameHostWnd->createHost(NULL, L"aaaaaaaaaaaaa", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0);
	frameHostWnd->setViewTree(viewTree);
	//frameHostWnd->showModal();

	UI::RunLoop *runLoop = UI::RunLoop::main();

	runLoop->run();

}

void test2() 
{
	RefPtr<FrameHostWnd> frameHostWnd = FrameHostWnd::create();

	RefPtr<ViewTree> viewTree = ViewTree::create();

	RefPtr<View> view1 = ViewFactory::createView("view");
	RefPtr<View> view2 = ViewFactory::createView("view");
	RefPtr<View> view3 = ViewFactory::createView("view");
	RefPtr<View> view4 = ViewFactory::createView("view");
	RefPtr<View> view5 = ViewFactory::createView("view");

	view1->setRect(0, 0, 100, 100);
	view2->setRect(50, 50, 300, 300);
	view3->setRect(333, 100, 100,100);
	view4->setRect(100, 200, 200, 300);
	view5->setRect(400, 400, 100, 200);

	RefPtr<View> root = ViewFactory::createView("LinearLayout");
	Container *pContainer = reinterpret_cast<Container *>(root.get());
	pContainer->setRect(0, 0, 100, 500);

	view1->setAttributeWidth(FillParent);
	//pContainer->setAttributeWidth(View::WrapContent);

	pContainer->addChild(view1);
	pContainer->addChild(view2);
	pContainer->addChild(view3);
	pContainer->addChild(view4);
	pContainer->addChild(view5);

	//pContainer->layout();

	viewTree->setRoot(root);


	frameHostWnd->createHost(NULL, L"aaaaaaaaaaaaa", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0);
	frameHostWnd->setViewTree(viewTree);
	//frameHostWnd->showModal();

	UI::RunLoop *runLoop = UI::RunLoop::main();

	runLoop->run();

}


void test3() 
{
	RefPtr<FrameHostWnd> frameHostWnd = FrameHostWnd::create();

	RefPtr<ViewTree> viewTree = ViewTree::create();

	RefPtr<View> view1 = ViewFactory::createView("view");
	RefPtr<View> view2 = ViewFactory::createView("view");
	RefPtr<View> view3 = ViewFactory::createView("view");
	RefPtr<View> view4 = ViewFactory::createView("view");
	RefPtr<View> view5 = ViewFactory::createView("TextView");

	reinterpret_cast<TextView *>(view5.get())->setText(L"你好你好你好你好你好你好你好你好你好你好你好你好你好你好你好你好你好");
	view5->setAttributeHeight(WrapContent);
	view5->setAttributeWidth(WrapContent);

	view1->setRect(0, 0, 20, 30);
	//view1->setMargin(5, 5, 5, 5);

	view2->setRect(50, 50, 20, 20);

	view3->setRect(0, 0, 10, 10);
	//view3->setMargin(5, 5, 5, 5);
	view3->setHorizontalAlign(AlignRight);
	view3->setVerticalAlign(AlignCenterV);

	view4->setRect(100, 200, 40, 40);
	view4->setHorizontalAlign(AlignHCenter);
	view4->setVerticalAlign(AlignBottom);
	view4->setAttributeHeight(FillParent);
	//view4->setMargin(1,1,1,1);

	view5->setRect(400, 400, 40, 40);
	view5->setMargin(5, 5, 5, 5);
	view5->setPadding(1, 1, 1, 1);
	view5->setHorizontalAlign(AlignHCenter);

	view1->setAttributeWidth(Fixed);

	RefPtr<View> root = ViewFactory::createView("LinearLayout");
	Container *pContainer = reinterpret_cast<Container *>(root.get());
	pContainer->setRect(0, 0, 100, 500);
	//pContainer->setMargin(5, 5, 5, 5);
	pContainer->setPadding(5, 5, 5, 5);
	reinterpret_cast<LinearLayout *>(root.get())->setOrientation(LinearLayout::Vertical);
	//pContainer->setAttributeWidth(View::WrapContent);

	pContainer->addChild(view1);
  	pContainer->addChild(view2);
  	pContainer->addChild(view3);
  	pContainer->addChild(view4);
  	pContainer->addChild(view5);

	view1->setAttributeWidth(FillParent);
	view3->setAttributeWidth(FillParent);
	view4->setAttributeWidth(FillParent);

	//pContainer->layout();

	viewTree->setRoot(root);


	frameHostWnd->createHost(NULL, L"UI-test", WS_OVERLAPPEDWINDOW | WS_VISIBLE, /*WS_EX_LAYERED*/0);
	frameHostWnd->setViewTree(viewTree);
	frameHostWnd->setTitle(L"Test");
	//frameHostWnd->showModal();

	UI::RunLoop *runLoop = UI::RunLoop::main();

	runLoop->run();

}

void test4()
{
	RefPtr<FrameHostWnd> frameHostWnd = FrameHostWnd::create();
	RefPtr<ViewTree> viewTree = ViewTreeBuild::buildViewTreeFromXmlFile("F:\\Desktop1\\UI\\UI\\Debug\\dialog.xml");

	frameHostWnd->createHost(NULL, L"UI-test", WS_OVERLAPPEDWINDOW | WS_VISIBLE, /*WS_EX_LAYERED*/0);
	frameHostWnd->setViewTree(viewTree);
	frameHostWnd->setTitle(L"Test");

	UI::RunLoop *runLoop = UI::RunLoop::main();

	runLoop->run();
}

#include "WebCoreInstanceHandle.h"
int main(int args, char* argv[])
/*int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE / *hPrevInstance* /, LPSTR / *lpstrCmdLine* /, int / *nCmdShow* /)*/
{
	if (args < 2)
		return 0;
	setInstanceHandle((HINSTANCE)GetModuleHandle(NULL));
	//setInstanceHandle(hInstance);


	printf("%d", sizeof(unsigned));

	ImageFileManager::loadImageResourceFile("F:\\Desktop1\\UI\\UI\\Debug\\Resource.xml");
	
	WTF::initializeMainThread();
	UI::RunLoop::initializeMainRunLoop();
	printf("load xml: %s", argv[1]);
	//test4();

	RefPtr<FrameHostWnd> frameHostWnd = FrameHostWnd::create();
	RefPtr<ViewTree> viewTree = ViewTreeBuild::buildViewTreeFromXmlFile(argv[1]);

	frameHostWnd->createHost(NULL, L"UI-test", WS_VISIBLE, /*WS_EX_LAYERED*/WS_EX_APPWINDOW);
	frameHostWnd->setViewTree(viewTree);
	frameHostWnd->setTitle(L"Test");
	//::SetWindowLong(frameHostWnd->GetHWND(), GWL_STYLE, ::GetWindowLong(frameHostWnd->GetHWND(), GWL_STYLE) & ~WS_CAPTION);

	UI::RunLoop *runLoop = UI::RunLoop::main();

	runLoop->run();

	_CrtDumpMemoryLeaks();

	return 0;
}

#include "SharedBuffer.h"
#include "WebCoreInstanceHandle.h"

#include "resource.h"

PassRefPtr<UI::SharedBuffer> loadResourceIntoBuffer(const char* name)
{
/*	int idr = IDP_BUTTON;*/
	int idr = IDB_BITMAP1;

	//return 0;

	HRSRC resInfo = FindResource(UI::instanceHandle(), MAKEINTRESOURCE(idr),L"BMP"/* L"PNG"*/);
	if (!resInfo)
		return 0;
	HANDLE res = LoadResource(UI::instanceHandle(), resInfo);
	if (!res)
		return 0;
	void* resource = LockResource(res);
	if (!resource)
		return 0;
	int size = SizeofResource(UI::instanceHandle(), resInfo);

	return UI::SharedBuffer::create(reinterpret_cast<const char*>(resource), size);
}
