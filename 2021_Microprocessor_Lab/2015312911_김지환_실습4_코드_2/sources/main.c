#include "main.h"
#include <stdio.h>

void main ()
{
    init_LCD();         // LCD�� ����ϱ� ���� �ʱ�ȭ
    int_disable(); 
    ini_interrupt();
    xint_enable();
    int_enable();                             
    
    
    write_string(0x00, "NUM1=");   //LCD�� �ʱ�ȭ�� ǥ��
    write_string(0x08, "NUM2="); 
    
    for( ; ; );
}
