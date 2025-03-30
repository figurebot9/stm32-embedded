/**************************************************************
 * 
 * @brief
   ZIN-7�׼�
	 �ɿذ���Ⱥ551883670
	 �Ա���ַ��https://shop297229812.taobao.com/shop/view_shop.htm?mytmenu=mdianpu&user_number_id=2419305772
 ***************************************************************/
#include "stm32f10x.h"
#include "USB_HID.h"
#include "USB_config.h"
//#include "USB_init.h" 
#include "usb_lib.h"
#include "delay.h"

u8 USB_ReceiveFlg = FALSE;
u8 Hid_RxData[64];
u8 HID_SEND_TIMEOUT = 5;			//hid���Ͳ���һ֡ʱ���ȴ�HID_SEND_TIMEOUT���ڽ��з���
u8 hid_datatemp[256];					//hid���λ�����
u8 hid_datatemp_begin = 0;		//���λ���������ָ�룬ָ��Ӧ�����͵�����
u8 hid_datatemp_end = 0;			//���λ��������ݽ�β
//bool USB_ReceiveFlg;
void USB_HID_Init(void)
{
//	USB_GPIO_Configuration();
	
	Set_USBClock();     
	USB_Init();
	USB_ReceiveFlg = FALSE;
	USB_Connect(FALSE);//�������Ӳ������usb
	delay_ms(100);
	USB_Connect(TRUE);
	USB_Interrupts_Config();
}

void Usb_Hid_Adddata(u8 *dataToSend , u8 length)
{
	u8 i;
	for(i=0; i<length; i++)
	{
		hid_datatemp[hid_datatemp_end++] = dataToSend[i];
	}
}

void Usb_Hid_Receive()//���ϲ�ѯ
{
	if (USB_ReceiveFlg == TRUE)
	{
		if(Hid_RxData[0] < 33 && Hid_RxData[1]==0xaa)
		{
		//	ANO_DT_Data_Receive_Anl(&(Hid_RxData[1]),Hid_RxData[0]);
			//ANO_NRF_TxPacket_AP(&(Hid_RxData[1]),Hid_RxData[0]);
		}
		USB_ReceiveFlg = 0x00;	
	}

}

void Usb_Hid_Send (void)
{
	static u8 notfull_timeout=0;
	u8 i;
	if(hid_datatemp_end > hid_datatemp_begin)
	{
		if((hid_datatemp_end - hid_datatemp_begin) >= 63)
		{
			notfull_timeout = 0;
			Transi_Buffer[0] = 63;
			for( i=0; i<63; i++)
			{
				Transi_Buffer[i+1] = hid_datatemp[hid_datatemp_begin++];
			}
			UserToPMABufferCopy(Transi_Buffer, ENDP2_TXADDR, 64);
			SetEPTxValid(ENDP2);
		}
		else
		{
			notfull_timeout++;
			if(notfull_timeout == HID_SEND_TIMEOUT)
			{
				notfull_timeout = 0;
				Transi_Buffer[0] = hid_datatemp_end - hid_datatemp_begin;
				for( i=0; i<63; i++)
				{
					if(i<hid_datatemp_end - hid_datatemp_begin)
						Transi_Buffer[i+1] = hid_datatemp[hid_datatemp_begin+i];
					else
						Transi_Buffer[i+1] = 0;
				}
				hid_datatemp_begin = hid_datatemp_end;
				UserToPMABufferCopy(Transi_Buffer, ENDP2_TXADDR, 64);
				SetEPTxValid(ENDP2);
			}
		}
	}
	else if(hid_datatemp_end < hid_datatemp_begin)
	{
		if((256 - hid_datatemp_begin + hid_datatemp_end) >= 63)
		{
			notfull_timeout = 0;
			Transi_Buffer[0] = 63;
			for( i=0; i<63; i++)
			{
				Transi_Buffer[i+1] = hid_datatemp[hid_datatemp_begin++];
			}
			UserToPMABufferCopy(Transi_Buffer, ENDP2_TXADDR, 64);
			SetEPTxValid(ENDP2);
		}
		else
		{
			notfull_timeout++;
			if(notfull_timeout == HID_SEND_TIMEOUT)
			{
				notfull_timeout = 0;
				Transi_Buffer[0] = 256 - hid_datatemp_begin + hid_datatemp_end;
				for( i=0; i<63; i++)
				{
					if(i<256 - hid_datatemp_begin + hid_datatemp_end)
						Transi_Buffer[i+1] = hid_datatemp[(u8)(hid_datatemp_begin+i)];
					else
						Transi_Buffer[i+1] = 0;
				}
				hid_datatemp_begin = hid_datatemp_end;
				UserToPMABufferCopy(Transi_Buffer, ENDP2_TXADDR, 64);
				SetEPTxValid(ENDP2);
			}
		}
	}
}







/*********************END OF FILE******************************************************/
















