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

int cnt = 0;      //Count ��
char str1[16]=""; //���ڿ� ����

void interruptJ_function (void){


  if(Pim.pifj.byte & PIFJ0)  {   // SW2�� ���ͷ�Ʈ �߻�
 
    cnt++;
    if(cnt == 10) cnt=9; //cnt���� 0~9
    
    (void) sprintf(str1, "Count = %d", cnt);  //���ڿ� ����
    write_string(0x00, str1);
    
    Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ (���������� ��ƾ�� ���������� ����)
    
  } 
  else if(Pim.pifj.byte & PIFJ1)  {  // SW3�� ���ͷ�Ʈ �߻�
      
    cnt--;
    if(cnt<0) cnt=0;
        
    
    (void) sprintf(str1, "Count = %d", cnt);  //���ڿ� ����
    write_string(0x00, str1);
        
 
    Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ (���������� ��ƾ�� ���������� ����)
  }
  
}



void interruptX_function(void){

       //7-���׸�Ʈ�� cnt�� ���
       print_number(cnt);

}
  