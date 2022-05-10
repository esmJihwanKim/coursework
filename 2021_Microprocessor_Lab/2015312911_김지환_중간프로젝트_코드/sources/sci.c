
#include "main.h"


unsigned char *txbuffer_sci0; //text�� �����ϴ� �����̴�. 
int txoffset_sci0;            //text���ڿ� ���̸� �˱����� �ʿ��� �����̴�.
unsigned char *rxbuffer_sci0; //rx�� �����ϴ� �����̴�.

int recordFlag = 0;
int overflowFlag = 0;
int buffer_count;
/*********************************************************/
/*  �ø��� ��� 0�� ä���� �ʱ�ȭ �Ѵ�.				                       */
/*********************************************************/ 
void init_sci0(int baud_rate, unsigned char *rxbuf) 
{
/* sci�� �ʱ�ȭ �ϴ� �Լ��̴�. bps�� ���ڿ��� ���� �׸��� �ۼ��� interrupt�� ������� ���� �����Ѵ�.*/
  unsigned long oscclk, modclk;  //SCIBD register�� SBR�� �����ϱ� ���� ����
  unsigned short br;    //�츮 ����� �ϴ� bps�� �����ϴ� ����
  oscclk = 16000000;	  //MCU�� ���ļ��� 16 MHz�̴�.
  modclk = (oscclk/2);	  //Set SCI module clock = (Oscillator Freq.)/2
  br = ( modclk/(16*baud_rate) );    //Set BR, SCI baud rate = (SCI module clock)/(16*BR)
/* ���� �ĵ��� �츮�� ����ϴ� MCU�� ������ ���� �������� ���̴�. */

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
/**********************************************************/ 
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

  if(Sci0.scisr1.bit.rdrf == 1)   //���� �����̸� RDRF�� �ݵ�� 1�� �Ǿ��ִ�.
  {
      *rxbuffer_sci0 = Sci0.scidrl.byte;  // scidrl�� ����� 1bit ���� �����͸� ���� ���ۿ� ����  
      
      // start collecting
      if(*rxbuffer_sci0 == '<') 
      {
        overflowFlag = 0;
        recordFlag = 1;
        buffer_count = 0;
        
        
        return;
      }
      if(*rxbuffer_sci0 == '>')
      {
        recordFlag = 0;
        *p_buffer = '\0';           // specify end delimiter
        p_buffer = p_base_buffer;
        if(overflowFlag == 0) dataCompleteSignal = 1;
        return;
      }  
      if(recordFlag == 1)
      {
        *p_buffer = *rxbuffer_sci0;
        p_buffer++;
        buffer_count++;
        if(buffer_count > (22 + 5)) // ERROR7:exceeded maximum bytes for frame
        {
           p_buffer = p_base_buffer;
           buffer_count = 0;
           showError(7);
           recordFlag = 0;
           overflowFlag = 1;
             
        }
      }
  }
  
    else if (Sci0.scisr1.bit.tdre == 1)  
    /*���� ���°� �ƴ� �۽� �����̸� TDRE�� 1�̵ǰ� ���� ���� status�� ���� �ָ� �ȴ�. */
    {
   
      Sci0.scidrl.byte = *txbuffer_sci0;    // scidrl�� �۽��� ������ ����
      txbuffer_sci0++;

      if(*txbuffer_sci0 == '\0') {
        Sci0.scicr2.byte &= 0b01111111;           // Transmitter Interrupt Enable Bit�� Ŭ����
      }
      
    }
  
}