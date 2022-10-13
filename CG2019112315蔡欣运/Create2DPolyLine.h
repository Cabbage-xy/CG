#ifndef _CREATE2DPOLYLINE_H_INCLUDED
#define _CREATE2DPOLYLINE_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DPolyLine : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DPolyLine(CGView* pview = nullptr);
	~Create2DPolyLine();
	virtual int GetType(); //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel();
protected:
	std::vector<Pos2i> mPoints; //����ĵ������������߶�
};
CG_NAMESPACE_EXIT
#endif //_CREATE2DPOLYLINE_H_INCLUDED