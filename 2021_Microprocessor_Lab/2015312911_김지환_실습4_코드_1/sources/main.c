#include "main.h"
#include <stdio.h>

void main ()
{
    init_LCD();         // LCD�� ����ϱ� ���� �ʱ�ȭ
    init_7segment();
    int_disable(); 
    ini_interrupt();
    xint_enable();
    int_enable();                             
    
    
    write_string(0x00, "Count = 0");   //LCD�� �ʱ�ȭ�� ǥ��
    
    for( ; ; );
}
