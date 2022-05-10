#include "main.h"
unsigned char RX[11]; 
/*RX[11]�� �ø��� ��� ���� ��ǻ�� ���̿� �ְ���� ���ڸ� �����ϴ� ������ ������ �Ѵ�.  �ִ� ���� �� �ִ� ���ڿ��� 11���� �����Ͽ���.*/
void main ()
{  
  init_LCD();
  
  // ��Ʈ B�� ��Ʈ M�� ���� ����
  Regs.ddrb.byte = 0b11111111;  // ��Ʈ B�� ��� ������� ����
  Pim.ddrm.byte = 0b11000000;   // ��Ʈ M�� 6,7�� ���� ������� ����
  int_disable();
     
/*�ø��� ��Ʈ�� �ʱ�ȭ �ϴ� �����̴�. bps�� 19200�̰� ���ڿ��� �ִ� ���̴� 10�̴�. */
  init_sci0(19200,RX);
  ini_interrupt();

  // ��� LED ���α�
  Regs.portb.byte = 0b11111111;   // ��Ʈ B�� ��� ���� 1�� ����
  Pim.ptm.byte = 0b11000000;      // ��Ʈ M�� 6,7�� ���� 1�� ���� 
  
  xint_enable();
  int_enable();
    
  write_string(0x00, "A");
	write_sci0( (unsigned char*) "SCI OK\n" );   // �������͹̳ο� "SCI OK" �޽��� ���
  
  for (;;){ 
  }
}