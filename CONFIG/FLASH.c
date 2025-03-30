#include "flash.h"
#include "stm32f10x_flash.h"

typedef enum {FAILED = 0, PASSED = !FAILED} Status;//����Ҫʹ�õ�״̬ö�ٱ���




uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t First_Page = 0x00;                       //��ʼҳ


__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO Status MemoryProgramStatus = PASSED;
//��������


//=============================================================================
//�ļ����ƣ�main
//���ܸ�Ҫ��������
//����˵������
//�������أ�int
//=============================================================================
void FLASH_write(int16_t *data,uint8_t len)
{
  FLASH_Unlock();//�Ƚ���
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); //�����Ӧ�ı�־λ

  {
    if (FLASH_ErasePage(FLASH_Start_Addr )!= FLASH_COMPLETE)
    {
      while (1)
      {			
      }
    }
  }
	
  /* д��FLASH */
  Address = FLASH_Start_Addr;
  while (len--)
  {
    if (FLASH_ProgramHalfWord(Address, *data) == FLASH_COMPLETE)
    {
		data++;
		Address = Address + 2;
    }
    else
    { 
      while (1)
      {
      }
    }
  }
  FLASH_Lock();
	/* ���� */
}	




void FLASH_read(int16_t *data,uint8_t len)
{
  Address = FLASH_Start_Addr;
  
  while (len--)
  {
    *data = *(__IO int16_t *)Address;
		data++;
    Address = Address + 2;
  }
}

/*****END OF FILE****/
