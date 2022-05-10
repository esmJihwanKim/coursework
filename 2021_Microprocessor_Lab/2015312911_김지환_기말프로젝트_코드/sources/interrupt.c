#include "interrupt.h"

/*************************************************/
/*  ��Ʈ J�� ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�.   */
/*************************************************/
void ini_interrupt(void)
{
   Pim.ddrj.byte=0b00000000;    // ���ͷ�Ʈ ��Ʈ�� ���� ����
   Pim.piej.byte=0xff;		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
   Pim.ppsj.byte=0x00;		// ���ͷ�Ʈ ��Ʈ�� ���� ����  
}

/*****************************************************/
/*  ����ġ 2,3�� ����� ��Ʈ J�� ������ �����Ѵ�.	*/
/*  ����ġ 2�� �ð�������� ȸ��                 	 */
/*  ����ġ 3�� �ݽð�������� ȸ��.              */
/*  ����ġ 1�� ����			               */
/*****************************************************/

// SW1
void interruptX_function (void)    
{	  
    int i, j;
    if(g_queue.rear->data != 1) queuePush(&g_queue, 1);
    queueDisplay(&g_queue);
    for (i = 0; i < 100; i++) {
        for (j=0; j < 2650; j++);     // �ƹ��͵� ���� �����鼭 �ð� ����
    }
}


void interruptJ_function(void)
{
  // SW2
  if(Pim.pifj.byte & 0x01)     
  { 
      if(g_queue.rear->data != 2) queuePush(&g_queue, 2);  
      Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
  }
  // SW3 
  else if(Pim.pifj.byte & 0x02)  
  {  
      if(g_queue.rear->data != 3) queuePush(&g_queue, 3);
      Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�
  }
  
  queueDisplay(&g_queue);
               
}