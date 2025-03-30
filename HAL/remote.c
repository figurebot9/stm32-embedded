/**************************************************************
 * 
 * @brief
   ZIN-7�׼�
	 �ɿذ���Ⱥ551883670
	 �Ա���ַ��https://shop297229812.taobao.com/shop/view_shop.htm?mytmenu=mdianpu&user_number_id=2419305772
 ***************************************************************/
#include "ALL_DATA.h"
#include "nrf24l01.h"
#include "control.h"
#include <math.h>
#include "myMath.h"
#include "LED.h"
#include "Remote.h"
#include "mpu6050.h"
#include "imu.h"
#undef SUCCESS
#define SUCCESS 0
#undef FAILED
#define FAILED  1

/*****************************************************************************************
 *  ͨ�����ݴ���
 * @param[in] 
 * @param[out] 
 * @return     
 ******************************************************************************************/	
	uint8_t RC_rxData[32];
void remote_unlock(void);	

void RC_Analy(void)  
{
		static uint16_t cnt_15s;
/*             Receive  and check RC data                               */	
	if(NRF24L01_RxPacket(RC_rxData)==SUCCESS)
	{ 	

		uint8_t i;
		uint8_t CheckSum=0;
		cnt_15s = 0;
		for(i=0;i<31;i++)//У���
		{
			CheckSum +=  RC_rxData[i];
		}
		if(RC_rxData[31]==CheckSum && RC_rxData[0]==0xAA && RC_rxData[1]==0xAF)  //������յ���ң��������ȷ
		{
			  Remote.roll = ((uint16_t)RC_rxData[4]<<8) | RC_rxData[5];  //ͨ��1
			
				Remote.pitch = ((uint16_t)RC_rxData[6]<<8) | RC_rxData[7];  //ͨ��2
	
				Remote.thr = 	((uint16_t)RC_rxData[8]<<8) | RC_rxData[9];   //ͨ��3

				Remote.yaw =  ((uint16_t)RC_rxData[10]<<8) | RC_rxData[11];   //ͨ��4
		
				Remote.AUX1 =  ((uint16_t)RC_rxData[12]<<8) | RC_rxData[13];   //ͨ��5  ���Ͻǰ���������ͨ��5  
	
				Remote.AUX2 =  ((uint16_t)RC_rxData[14]<<8) | RC_rxData[15];   //ͨ��6  ���Ͻǰ���������ͨ��6 

				Remote.AUX3 =  ((uint16_t)RC_rxData[16]<<8) | RC_rxData[17];   //ͨ��7  ������鿴�ֲ� 

				Remote.AUX4 =  ((uint16_t)RC_rxData[18]<<8) | RC_rxData[19];   //ͨ��8  
	
				//---------------------------------------------------------------------------------		
			
			
				//��ʼ����ң������
				{
							float roll_pitch_ratio = 0.04f;  //ң�ؿ�����̬����
					
					
							pidPitch.desired =-(Remote.pitch-1500)*roll_pitch_ratio;	 //��ң��ֵ��Ϊ���нǶȵ�����ֵ  
							pidRoll.desired = -(Remote.roll-1500)*roll_pitch_ratio;
							
					    if(Remote.yaw>1820 )
							{	//����Ϊң�ؿ���ƫ���� +-�Ŵ����� 0.75�������ƫ���ǵ���ת��							
								pidYaw.desired -= 0.45f;	
							}
							else if(Remote.yaw <1180)
							{
								pidYaw.desired += 0.45f;	
							}			
							//�������Ų�Ҫ̫������
							Remote.thr = 	LIMIT(Remote.thr,1000,2000);
				}		
		}
  }
	else //���û���յ�ң���źţ����ж�Ϊʧ��
	{
		cnt_15s++;
		if(cnt_15s>500)
		{
			cnt_15s = 0;
			ALL_flag.unlock = 0;  //ʧ������
			NRF24L01_init();  //��ʼNRF
		}
	}
	remote_unlock();
}

/*****************************************************************************************
 *  �����ж�
 * @param[in] 
 * @param[out] 
 * @return     
 ******************************************************************************************/	
void remote_unlock(void)
{
	volatile static uint8_t status=WAITING_1;
	static uint16_t cnt=0;

	if(Remote.thr<1050 &&Remote.yaw<1150)                         //����ң�����½�����
	{
		status = EXIT_255;
	}
	
	switch(status)
	{
		case WAITING_1://�ȴ�����
 //���������࣬�������->�������->������� ����LED�Ʋ����� ����ɽ���			
			if(Remote.thr<1100)  //��һ��        
			{			 
					 status = WAITING_2;				 
			}		
			break;
		case WAITING_2://�ڶ��� 
			if(Remote.thr>1750)          
			{		
						static uint8_t cnt = 0;
					 	cnt++;		
						if(cnt>5) //��������豣��200ms���ϣ���ֹң�ؿ�����ʼ��δ��ɵĴ�������
						{	
								cnt=0;
								status = WAITING_3;
						}
			}			
			break;
		case WAITING_3:
			if(Remote.thr<1100)  //������        
			{			 
					 status = WAITING_4;				 
			}			
			break;			
		case WAITING_4:	//����ǰ׼��	               
				ALL_flag.unlock = 1;   //������־λ
				status = PROCESS_31;   //�������
				LED.status = AlwaysOn; //LED����	
	imu_rest();				
				 break;		
		case PROCESS_31:	//�������״̬
				if(Remote.thr<1020)    //��ң��������� ������״̬
				{
					if(cnt++ > 2000)                                     // ����ң�˴������6S�Զ�����
					{								
						status = EXIT_255;								
					}
				}
				else if(!ALL_flag.unlock)                           //�������������ֱ�������ɿأ�����DIYһ��������
				{
					status = EXIT_255;				
				}
				else					
					cnt = 0;
			break;
		case EXIT_255: //��������
			LED.status = AllFlashLight;	//LED������״̬������˸                                     //exit
			cnt = 0;
			LED.FlashTime = 100;  		 //LED������״̬������˸ʱ����Ϊ300ms                                 
			ALL_flag.unlock = 0;      //����
			status = WAITING_1;     //���صȴ�����
			break;
		default:
			status = EXIT_255;
			break;
	}
}
/***********************END OF FILE*************************************/







