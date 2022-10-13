#include "pch.h"
#include "UIEventListener.h"
#include "CGView.h"
CG_NAMESPACE_ENTER
UIEventListener::UIEventListener(CGView* pview/* = nullptr*/)
{
	mStep = 0;
	mView = pview;
}
UIEventListener::~UIEventListener()
{
}
int UIEventListener::OnLButtonUp(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnLButtonDblClk(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnMouseWheel(UINT nFlags, short zDelta, Pos2i pt)
{
	return 0;
}
int UIEventListener::OnMButtonUp(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnMButtonDown(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnMButtonDblClk(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnRButtonUp(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnRButtonDown(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
int UIEventListener::OnRButtonDblClk(UINT nFlags, const Pos2i& pos)
{
	return 0;
}
//¼üÅÌÊÂ¼þ
int UIEventListener::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return 0;
}
int UIEventListener::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return 0;
}
int UIEventListener::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return 0;
}
int UIEventListener::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return 0;
}
int UIEventListener::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return 0;
}
CG_NAMESPACE_EXIT