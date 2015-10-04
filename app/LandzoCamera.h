#ifndef _LANDZOCAMERA_H
#define _LANDZOCAMERA_H

#include "gpio.h"

 /**********************
 *����ͷ
 *********************/
#define  DATAROW    30//��������
#define  DATACOUNT  140        //��������
#define  ADLENGT    4000     
 /**********************/
/********************************************************************/

void Camera_init(void);
void Camera_Black1(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black);
void Camera_Black2(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black);
void Camera_Black3(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black);
void Camera_Black4(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black);
void Camera_Black5(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black);
void Camera_Black6(uint8 *point1,uint8 *rightblackedge,uint8 *leftblackedge,uint8 *centre_black);
/********************************************************************/

/*********************
�㷨�ӳ��� ��define
***********************/

#define  FAVMIN      0X30        //AD��ֵ����С��ֵ
#define  FAVMAX      0X80        //AD��ֵ�������ֵ
#define  FAVDEA      0X20        //AD��ֵ���ο���ֵ
#define  LEFTINIT    0X05        //��߳�ʼ��λ��
#define  RINGTINIT   0X0A        //���ҳ�ʼ��λ��
/*************************** 
�������ƣ�Line_calculate
***********************/

#define  L_WITHMIN     0X02      //��ߺ��������Ե���Сֵ
#define  L_WITHMAX     0X05      //��ߺ��������Ե����ֵ
#define  R_WITHMIN     0X02      //�ұߺ��������Ե���Сֵ
#define  R_WITHMAX     0X05      //�ұߺ��������Ե����ֵ

#endif