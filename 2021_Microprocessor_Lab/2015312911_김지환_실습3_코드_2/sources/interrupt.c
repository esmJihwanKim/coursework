#include "interrupt.h"
                    
        
/*************************************************/
/*  ��Ʈ J�� ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�.   */
/*************************************************/
void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // ���ͷ�Ʈ ��Ʈ�� ���� ����
 Pim.piej.byte=0xff;		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
 Pim.ppsj.byte=0x00;		// ���ͷ�Ʈ ��Ʈ�� ���� ����  
}


void interruptJ_function(void)
{
  static int num = 0b00000001;
  
  if(Pim.pifj.byte & PIFJ0)      // SW2�� ���ͷ�Ʈ �߻� 
  { 
      // ���������� �̵� 
      if(Regs.portb.byte != 0x7F)
      {
        Regs.portb.byte = Regs.portb.byte ^ 0xFF;
        Regs.portb.byte = Regs.portb.byte << 1;
        Regs.portb.byte = Regs.portb.byte ^ 0xFF;
      }
      Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    
  } 
  else if(Pim.pifj.byte & PIFJ1)  // SW3�� ���ͷ�Ʈ �߻�   
  { 
      // �������� �̵� 
      if(Regs.portb.byte != 0xFE)
      {
         Regs.portb.byte = Regs.portb.byte ^ 0xFF;
         Regs.portb.byte = Regs.portb.byte >> 1; 
         Regs.portb.byte = Regs.portb.byte ^ 0xFF; 
      }
      Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
  }
    
}

