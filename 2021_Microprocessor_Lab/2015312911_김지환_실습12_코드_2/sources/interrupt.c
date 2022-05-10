#include "interrupt.h"


int num[16]; 
char binary_num[16];
int pos = 0;
int i;

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

// SW1 : convert binary to decimal and print to CAN 
void interruptX_function (void)    
{	  
     int res = 0; 
     write_can0(0, binary_num, pos+1);  
     ms_delay(20);
      
}


void interruptJ_function(void)
{
  char print_num[10] = {0x00, };
  // SW2 : select binary (between 0 and 1)
  if(Pim.pifj.byte & 0x01)     
  {  
      num[pos] = !num[pos];

      for(i = 0; i <= pos; i++) 
      {
          binary_num[i] = num[i] + '0';
          print_num[i] = binary_num[i];
      }     
      write_string(0x40, print_num);
      ms_delay(20);
       
      Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
  }
  // SW3 : move to next number 
  else if(Pim.pifj.byte & 0x02)  
  {  
      pos++;
      
      for(i = 0; i <= pos; i++) 
      {
          binary_num[i] = num[i] + '0';
          print_num[i] = binary_num[i]; 
      }   
      write_string(0x40, print_num);  
      ms_delay(20);
      
      Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�
  }
  
               
}