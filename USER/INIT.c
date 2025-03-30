/**************************************************************
 * 
 * @brief
   ZIN-7�׼�
	 �ɿذ���Ⱥ551883670
	 �Ա���ַ��https://shop297229812.taobao.com/shop/view_shop.htm?mytmenu=mdianpu&user_number_id=2419305772
 ***************************************************************/
#include "ALL_DEFINE.h"


volatile uint32_t SysTick_count; //ϵͳʱ�����
_st_Mpu MPU6050;   //MPU6050ԭʼ����
_st_AngE Angle;    //��ǰ�Ƕ���ֵ̬
_st_Remote Remote; //ң��ͨ��ֵ


_st_ALL_flag ALL_flag; //ϵͳ��־λ������������־λ��


PidObject pidRateX; //�ڻ�PID����
PidObject pidRateY;
PidObject pidRateZ;

PidObject pidPitch; //�⻷PID����
PidObject pidRoll;
PidObject pidYaw;

void pid_param_Init(void); //PID���Ʋ�����ʼ������дPID�����ᱣ�����ݣ��������ɺ�ֱ���ڳ�������� ����¼���ɿ�


/**************************************************************
 *  ����ϵͳ����ʹ�������ʼ��
 * @param[in] 
 * @param[out] 
 * @return     
 ***************************************************************/
void ALL_Init(void)
{
	USB_HID_Init();
	pid_param_Init();       //PID������ʼ��
	 
	

	delay_ms(100);

	LEDInit();              //LED���Ƴ�ʼ��
	
	IIC_Init();             //I2C��ʼ��		
//----------------------------------------	
// ˮƽ��ֹ�궨���ù���ֻ��Ҫ����һ�Σ���Ҫÿ�ν��С���ҷ���ǰ�Ѿ�����һ�α궨�ˣ��궨�����Զ����浽MCU��FLASH�С�
// ����У׼�����´򿪼��ɣ���ʱ5S��Ϊ�˲��ϵ�غ��г����ʱ�佫���������ڵ��Ͻ���ˮƽ��ֹ�궨��
//	delay_ms(1000);MpuGetOffset();
//----------------------------------------		
//	USART1_Config();  //���ô���     
	
	MpuInit();              //MPU6050��ʼ��

	NRF24L01_init();				//2.4Gң��ͨ�ų�ʼ��

	TIM2_PWM_Config();			//4·PWM��ʼ��

	TIM3_Config();					//ϵͳ�������ڳ�ʼ�� 
	
}


/**************************************************************
 *  ��ʼ��PID����
 * @brief �����Ҫ�Լ��޸�PIDֵ��������Ϳ�����
 * @param[out] 
 * @return     
 ***************************************************************/
void pid_param_Init(void)
{

//	pidRateX.kp = 1.5f;//huanbaoxian
//	pidRateY.kp = 1.5f;
//	pidRateZ.kp = 6.0f;
//	
//	pidRateX.ki = 0.04f;
//	pidRateY.ki = 0.04f;
//	pidRateZ.ki = 0.05f;	
//	
//	pidRateX.kd = 0.06f;
//	pidRateY.kd = 0.06f;
//	pidRateZ.kd = 0.4f;	
//	
//	pidPitch.kp = 4.0f;
//	pidRoll.kp = 4.0f;
//	pidYaw.kp = 3.0f;
	
//	pidRateX.kp = 2.0f;//1
//	pidRateY.kp = 2.0f;
//	pidRateZ.kp = 6.0f;
//	
//	pidRateX.ki = 0.05f;
//	pidRateY.ki = 0.05f;
//	pidRateZ.ki = 0.05f;	
//	
//	pidRateX.kd = 0.08f;
//	pidRateY.kd = 0.08f;
//	pidRateZ.kd = 0.5f;	
//	
//	pidPitch.kp = 7.0f;
//	pidRoll.kp = 7.0f;
//	pidYaw.kp = 4.0f;
	
	pidRateX.kp = 2.0f;//1
	pidRateY.kp = 2.0f;
	pidRateZ.kp = 6.0f;
	
	pidRateX.ki = 0.01f;
	pidRateY.ki = 0.01f;
	pidRateZ.ki = 0.05f;	
	
	pidRateX.kd = 0.08f;
	pidRateY.kd = 0.08f;
	pidRateZ.kd = 0.5f;	
	
	pidPitch.kp = 7.0f;
	pidRoll.kp = 7.0f;
	pidYaw.kp = 4.0f;		
}















