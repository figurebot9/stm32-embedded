/*******************************************************************
 *@title PID ���ƺ���
 *@brief �����ĺ����е�����������PID��ʼ����PID�����������
 *@brief ��ʷ�޸����ݣ�
 *
 *       δ������ݣ�
 *       
 *@time  2016.10.13
 *@editorС��&zin
 *�ɿذ���QQȺ551883670,����759421287@qq.com
 ******************************************************************/
#ifndef __PID_H
#define __PID_H
#include "ALL_DATA.h"
#include <stdbool.h>

extern void CascadePID(PidObject* pidRate,PidObject* pidAngE,const float dt);  //����PID
extern void pidRest(PidObject **pid,const uint8_t len); //pid���ݸ�λ
extern void pidUpdate(PidObject* pid,const float dt);  //PID
#endif



