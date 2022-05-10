
#include "main.h"
unsigned char *txbuffer_sci0; //text�� �����ϴ� �����̴�. 
int txoffset_sci0;            //text���ڿ� ���̸� �˱����� �ʿ��� �����̴�.
unsigned char *rxbuffer_sci0; //rx�� �����ϴ� �����̴�.

/*********************************************************/
/*  �ø��� ��� 0�� ä���� �ʱ�ȭ �Ѵ�.				                       */
/*********************************************************/ 
void init_sci0(int baud_rate, unsigned char *rxbuf) 
{
/*sci�� �ʱ�ȭ �ϴ� �Լ��̴�. bps�� ���ڿ��� ���� �׸��� �ۼ��� interrupt�� ������� ���� �����Ѵ�.*/
  unsigned long oscclk, modclk;  //SCIBD register�� SBR�� �����ϱ� ���� ����
  unsigned short br;    //�츮 ����� �ϴ� bps�� �����ϴ� ����
  oscclk = 16000000;	  //MCU�� ���ļ��� 16 MHz�̴�.
  modclk = (oscclk/2);	  //Set SCI module clock = (Oscillator Freq.)/2
  br = (  modclk/(16*baud_rate) );    //Set BR, SCI baud rate = (SCI module clock)/(16*BR)
/*���� �ĵ��� �츮�� ����ϴ� MCU�� ������ ���� �������� ���̴�. */

  Sci0.scibd.word =  ( 26 );  //������ BR ���� SCIBD register�� ����
  Sci0.scicr1.byte = (0b00000000);  //SCI ���� ���� register �ʱ�ȭ. Normal operation & 8 data bit format & Parity disabled
  Sci0.scicr2.byte = (0b00101100);  //SCI ���� ���� register �ʱ�ȭ. transmit & receive & receive interrupt Ȱ��ȭ 
/* ���⼭ transmit interrpt�� ���� �� interrupt�� �߻���Ű�� ������ �ʱ�ȭ �� �� �ʿ����. */ 
	txoffset_sci0 = 0;          
	rxbuffer_sci0 = rxbuf;
/*������ offset�� buffer�� �ʱ�ȭ �Ѵ�.*/     
}
/*********************************************************/
/*  �Է¹��� ���ڿ��� �ø��� ������� �����Ѵ�.                          */
/*  �Է¹��� ���ڿ��� ���̸� ���ۿ� �����ϰ� �۽� interrupt�� enable����     */
/*  MCU�� interrupt handler�� �����ϵ��� �Ѵ�.                   */
/*********************************************************/ 
void write_sci0(unsigned char *text)
{
/*�� �Լ��� �Է¹��� ���ڿ��� ��ǻ�Ϳ� ������ ������ �ϴ� �Լ��̴�. transmit interrupt�� �߻����� sci interrupt handler�Լ��� ȣ���ϰ� �ȴ�*/

	txbuffer_sci0 = text;
/*���ڿ� ���̸� offset�� ���� ��Ų��.*/
	Sci0.scicr2.byte |= ( 0b10001000 );         //TIE & TE Ȱ��ȭ

}
/*****************************************************************/
//  �ø��� ��� �۽� �� ���� ���ͷ�Ʈ�� �߻����� �� ó���Ǵ� �Լ�.                      
//  �� ����Ʈ�� ���ڰ� �۽� �� ���� �� ������ ���ͷ�Ʈ�� �߻���                        
//  sci�� interrupt TDRE�� RDRF�� �߻����� �� ȣ��Ǵ� �Լ��̴�. ���� ���� �� �Լ��� projectvectors.c�� ����� �Ǿ� �־�� �Ѵ�. ���������� ��Ʈ ���Ͽ� ���� ��/���� ���°� �����ȴ�.        						 
/*****************************************************************/ 
void sci0_handler(void)
{
  Regs.portb.byte = ( 0b11111111 );   // ��Ʈ B�� ��� ���� 1�� ����
  Pim.ptm.byte = ( 0b11000000 );      // ��Ʈ M�� 6,7�� ���� 1�� ����

  if(Sci0.scisr1.bit.rdrf == 1)   //���� �����̸� RDRF�� �ݵ�� 1�� �Ǿ��ִ�.
  {
        *rxbuffer_sci0 = Sci0.scidrl.byte;  // scidrl�� ����� 1bit ���� �����͸� ���� ���ۿ� ����    
        /*�׷��� ������ �����͸� ����ϱ����� rxbuffer�� ù ��° �ڸ����� �����ϰ� �ȴ�. */
  	    /* Application code  */
  	    
        switch(*rxbuffer_sci0) {
            case '0':
                Regs.portb.byte = 0b11111111;
                break;
            case '1':
                Regs.portb.byte = 0b11111110;
                break;
            case '2':
                Regs.portb.byte = 0b11111100;
                break;
            case '3':
                Regs.portb.byte = 0b11111000;
                break;
            case '4':
                Regs.portb.byte = 0b11110000;
                break;
            case '5':
                Regs.portb.byte = 0b11100000;
                break;
            case '6':
                Regs.portb.byte = 0b11000000;
                break;
            case '7':
                Regs.portb.byte = 0b10000000;
                break;
            case '8':
                Regs.portb.byte = 0b00000000;
                break;
            default:
                break; 
        }
 	
  }
  else if (Sci0.scisr1.bit.tdre == 1)  
/*���� ���°� �ƴ� �۽� �����̸� TDRE�� 1�̵ǰ� ���� ���� status�� ���� �ָ� �ȴ�. */
  {
 
    Sci0.scidrl.byte = *txbuffer_sci0;    // scidrl�� �۽��� ������ ����
    txbuffer_sci0++;

    if(*txbuffer_sci0 == '\0')
    {
      Sci0.scicr2.byte &= 0b01111111;           // Transmitter Interrupt Enable Bit�� Ŭ����
    }
  }
}