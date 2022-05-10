#include "interrupt.h"
#include <stdio.h>


/*************************************************/
/*  ��Ʈ J�� ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�. */
/*************************************************/
void ini_interrupt(void){
 
 Pim.ptj.byte = 0b00000000;    // ���ͷ�Ʈ ��Ʈ�� ���� ����
 Pim.piej.byte= 0xFF;		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
 Pim.ppsj.byte= 0x00;		// ���ͷ�Ʈ ��Ʈ�� ���� ����
 
}

/*****************************************************/
/*  ����ġ 2,3�� ����� ��Ʈ J�� ������ �����Ѵ�.    */
/*  ����ġ 2�� ������ cnt ���ڰ� �����ϰ� LCD�� ǥ���Ѵ�.*/
/*  ����ġ 3�� ������ cnt ���ڰ� �����ϰ� LCD�� ǥ���Ѵ�.  */
/*  ����ġ 1�� ������ cnt���� ��ũ��Ʈ ǥ���Ѵ�.     */
/*****************************************************/

int cnt1 = 0;      //Count ��
int cnt2 = 0;
char str1[8]=""; // ���ڿ� ����
char str2[8]=""; // 
char str3[16]="";

void interruptJ_function (void){


  if(Pim.pifj.byte & PIFJ0)  {   // SW2�� ���ͷ�Ʈ �߻�
 
    cnt1++;
    
    (void) sprintf(str1, "NUM1=%d", cnt1);  //���ڿ� ����
    write_string(0x00, str1);
    
    Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ (���������� ��ƾ�� ���������� ����)
    
  } 
  else if(Pim.pifj.byte & PIFJ1)  {  // SW3�� ���ͷ�Ʈ �߻�
      
    cnt2++;        
    
    (void) sprintf(str2, "NUM2=%d", cnt2);  //���ڿ� ����
    write_string(0x08, str2);
        
 
    Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ (���������� ��ƾ�� ���������� ����)
  }
  
}



void interruptX_function(void){
       (void) sprintf(str3, "Result=%d", cnt1*cnt2);
       // print multiplication result 
       write_string(0x40, str3);

}
  