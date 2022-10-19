#ifndef _CREATE2DPOLYGON_H_INCLUDED
#define _CREATE2DPOLYGON_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DPolygon : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DPolygon(CGView* pview = nullptr);
	~Create2DPolygon();
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
#endif //_CREATE2DPOLYGON_H_INCLUDED