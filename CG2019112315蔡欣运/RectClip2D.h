#ifndef _RECTCLIP2D_H_INCLUDED
#define _RECTCLIP2D_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class RectClip2D :
    public UIEventListener
{
	friend class CGDI2DView;
public:
	RectClip2D(CGView* pview = nullptr);
	~RectClip2D();
	virtual int GetType(); //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel();
protected:
	Pos2i mStart; //����ĵ�һ����Ϊ�߶����
	Pos2i mEnd; //����ĵڶ�����Ϊ�߶��յ�
};
CG_NAMESPACE_EXIT
#endif //_RECTCLIP2D_H_INCLUDED