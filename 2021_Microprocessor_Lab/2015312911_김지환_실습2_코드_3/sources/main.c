#include "main.h"

void delay(unsigned int n);

void main()
{   
    //unsigned char mask;

    
    // ��Ʈ B ����¹��� ����
    Regs.ddrb.byte = 0b11111111;    // ��Ʈ B�� ��� ������� ����
    
    // ��� LED ���α�
    Regs.portb.byte = 0b11111111;   // ��Ʈ B�� ��� ���� 1�� ����    
    
        
    for (;;) {      
    
        
        Regs.portb.byte = 0b01111110;
     
        delay(5);
        
        Regs.portb.byte = 0b10111101;
        
        delay(5);
        
        Regs.portb.byte = 0b11011011;
        
        delay(5);
        
        Regs.portb.byte = 0b11100111;
        
        delay(5);
        
        Regs.portb.byte = 0b11111111;
         
        delay(5);
        
        Regs.portb.byte = 0b11011011;
        
        delay(5);

        Regs.portb.byte = 0b10111101;      
        
        delay(5);                         
    }
}

// ������ �ð��� ������Ű�� �Լ�
void delay(unsigned int n) 
{
    unsigned int i;
    
    while (n > 0) {
        for (i=1; i != 0; i++);     // �ƹ��͵� ���� �����鼭 �ð� ����
        n--;
    }
}




