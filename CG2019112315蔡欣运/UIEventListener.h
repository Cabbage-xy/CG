#ifndef _UIEVENTLISTENER_H_INCLUDED
#define _UIEVENTLISTENER_H_INCLUDED
#include "Vector2.h"
#include "CGObject.h"
CG_NAMESPACE_ENTER
enum CommandType
{
	cmdNone = 0, //�ޣ���ʾ���ָ�룬��������ͼ
	cmd2dLineSegment = 1, //������㡢�յ����ֱ�߶�
	cmd2dLine = 2, //��������������޳�ֱ��
	cmd2dRay = 3, //������㡢���򣨵ڶ���ȷ������������
	cmd2dPolyline = 4, //��������������ֱ�߶��γ�
	cmd2dCircle1PointRadius = 5, //һ��+����뾶��Բ
	cmd2dCircle2PointRadius = 6, //����Ϊ�뾶��Բ
	cmd2dCircle2PointDiameter = 7, //����Ϊֱ����Բ
	cmd2dCircle3Point = 8, //�������Բ
	cmd2dPolygon = 9, //����һ������
	cmd2dSeedFill = 10, //�������
	//��ά�任ָ��
	cmd2dTranslateRenderable = 100, //����ƽ��
	cmd2dRotateRenderable = 101, //��ѡ����ת
	cmd2dScaleRenderable = 102, //ָ���㣬ָ����������
	cmd2dMirrorRenderable = 103, //ָ�����߶Գ�
	//��ά�۲�ָ��
	cmd2dMoveCamera = 110,
	cmd2dPickRenderable = 1000, //ʰȡͼ��
};
//ʹ������ģʽ����CGView�������м��̡�����¼��Ĵ���
class UIEventListener : public CGObject
{
	friend class CGView;
public:
	UIEventListener(CGView* pview = nullptr); //ʹ����������View����CGView�����ࣩ
	~UIEventListener();
	virtual int GetType() = 0; //�������ͣ�����������������д
	//����¼�����ֻ����Ĭ��ʵ�֣������������Ҫ��д��Ӧ�ĺ�����
	virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnLButtonDblClk(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseWheel(UINT nFlags, short zDelta, Pos2i pt);
	virtual int OnMButtonUp(UINT nFlags, const Pos2i& pos);
	virtual int OnMButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMButtonDblClk(UINT nFlags, const Pos2i& pos);
	virtual int OnRButtonUp(UINT nFlags, const Pos2i& pos);
	virtual int OnRButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnRButtonDblClk(UINT nFlags, const Pos2i& pos);
	//�����¼�
	virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//ȡ�������ESC���жϵ�ǰ�����ִ�У�������������������д
	virtual int Cancel() = 0;
	//CGRenderContext* RenderContext(); //
protected:
	int mStep; // �����������
	CGView* mView; // �����¼��Ĵ���
};
CG_NAMESPACE_EXIT
#endif //_UIEVENTLISTENER_H_INCLUDED