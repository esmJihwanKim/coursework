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

int pushcnt = 0;   

void interruptJ_function (void)
{

  // SW2 Interrupt - increment GUI counter
  if(Pim.pifj.byte & PIFJ0)
  {   
     char dataString[10];
     char dataText;
     pushcnt++; 
     dataText = '0' + pushcnt;
     sprintf(dataString, "%s%c%s", "<021000", dataText, ">");
     write_sci0(dataString);
     
     Pim.pifj.byte |= 0x01;  // end interrupt
     
  }
 
  // SW3 Interrupt - send ADC value     
  else if(Pim.pifj.byte & PIFJ1)
  {  
     int i;
     char level;
     char dataString[10];
     i = get_atd0(0);
     level = '0' + convertADCLevel(i);
     
     sprintf(dataString, "%s%c%s", "<041000", level, ">");
     write_sci0(dataString);
     
     Pim.pifj.byte |= 0x02;
  }

}


// SW1 Interrupt - Segment - number of LEDs turned on
void interruptX_function(void)
{  
    int ledcnt = 0;
    int i;
    //Regs.portb.byte : LED[1-8]
    //Pim.ptm.byte    : LED[9-10]
    char numberText;
    unsigned char dataString[10];
    unsigned char checker = 0b00000001;
    
    for(i=0; i<7; i++) 
    {
        if( (Regs.portb.byte & checker) == 0x00) 
        { 
            ledcnt++;
        }
        checker = checker << 1;
    }
    if( (Regs.portb.byte & 0b10000000) == 0x00) ledcnt++;
    if( (Pim.ptm.byte & 0b10000000) == 0x00) ledcnt++;
    if( (Pim.ptm.byte & 0b01000000) == 0x00) ledcnt++;
    
    // ledcnt to text
    if(ledcnt == 10) numberText = 'X';
    else numberText = '0' + ledcnt;
       
    sprintf(dataString, "%s%c%s", "<011000", numberText, ">");
    set_7segment((unsigned char)ledcnt);
    write_sci0(dataString);
}
  