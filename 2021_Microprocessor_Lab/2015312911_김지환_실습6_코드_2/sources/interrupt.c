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

int cnt1 = 0;
char alphabet = 'A';
int position = 0;      

char str1[8]=""; // ���ڿ� ����
char str2[8]="";  
char str3[16]="";

void interruptJ_function (void){

  // SW2�� ���ͷ�Ʈ �߻� - choose alphabet 
  if(Pim.pifj.byte & PIFJ0)  {   
 
    alphabet++;
    
    //check character
    if( (alphabet > 'Z') && (alphabet < 'a') ) 
        alphabet = 'a';
    if(alphabet > 'z') 
        alphabet = 'A';
    
    str1[position] = alphabet;
    write_string(0x00, str1);
    Pim.pifj.byte |= 0x01;                         
  }
 
  // SW3�� ���ͷ�Ʈ �߻� - next cursor   
  else if(Pim.pifj.byte & PIFJ1)  {  
     if(alphabet == 'A'-1) alphabet = 'A'; 
     str1[position] = alphabet; 
    
     position++;
     alphabet = 'A'-1;
     Pim.pifj.byte |= 0x02;
     str1[8] = "";
  }
  
  
}


// switch 1 - send to sci 
void interruptX_function(void){  
    	write_sci0( (unsigned char*) str1);
}
  