/**************************************************************
 * 
 * @brief
   ZIN-7�׼�
	 �ɿذ���Ⱥ551883670
	 �Ա���ַ��https://shop297229812.taobao.com/shop/view_shop.htm?mytmenu=mdianpu&user_number_id=2419305772
 ***************************************************************/
#include "spi.h"

#define  SCK_H  GPIOB->BSRR=GPIO_Pin_13  //SCK����
#define  SCK_L  GPIOB->BRR=GPIO_Pin_13  //SCK����
#define  MOSI_H  GPIOB->BSRR=GPIO_Pin_15  //MOSI����
#define  MOSI_L  GPIOB->BRR=GPIO_Pin_15  //MOSI����
#define  MISO  ((GPIOB->IDR&GPIO_Pin_14)?1:0)  //��ȡMISO


void SPI_Config(void)//io��ʼ������
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_SetBits(GPIOB, GPIO_Pin_12); //NRF_CSԤ��Ϊ�� 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//SCK
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//MOSI
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;//MISO
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //MOSIҪ��ģ������
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		SCK_L;
		MOSI_H;
}




u8 SPI_RW(u8 byte)
{
		uint8_t i;

		u8 Temp=0x00;

		for (i = 0; i < 8; i++)

		{

				SCK_L;//sclk = 0;//�Ƚ�ʱ������

				if (byte&0x80)
				{
						MOSI_H; // //SO=1
				}
				else
				{
						MOSI_L;// //SO=0
				}

				byte <<= 1;
				Temp<<=1;
				
				SCK_H; //����ʱ��
				
				if(MISO) //����1ʱ
				{
					Temp++;
				}
				SCK_L;	
		}
		return Temp; //���ض���miso�����ֵ

}
