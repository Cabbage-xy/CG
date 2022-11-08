#ifndef _CGDI2DSCENE_H_INCLUDED
#define _CGDI2DSCENE_H_INCLUDED
#include "CGScene.h"
CG_NAMESPACE_ENTER
class CGDI2DScene : public CGScene
{
	DECLARE_SERIAL(CGDI2DScene)
public:
	CGDI2DScene();
	virtual ~CGDI2DScene();
	//���л�
	virtual void Serialize(CArchive& ar);
	//��Ⱦ������ָ���ͻ���������CGDI2DView��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DSCENE_H_INCLUDED