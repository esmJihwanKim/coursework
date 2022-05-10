
#include "main.h"
unsigned char RX[11]; 
/*RX[11]�� �ø��� ��� ���� ��ǻ�� ���̿� �ְ���� ���ڸ� �����ϴ� ������ ������ �Ѵ�.  �ִ� ���� �� �ִ� ���ڿ��� 11���� �����Ͽ���.*/



/********************************************************/
/*             Parsing Buffer to Structure              */
/********************************************************/
void parse(char* buffer) 
{

    int group_number = 0;
    int cmd_class = 0;
    int cmd_number = 0;
    int data_format = 0; 
    char data_text[16]; 
    int i;
    int data_cnt = 0;
    
    int error_result;
    
    char debug_str[5];

    
    // read 2 bytes group number 
    group_number = group_number + (*buffer - '0') * 10;
    buffer++;
    group_number = group_number + (*buffer - '0');
    buffer++;
    // read 1 byte cmd class 
    cmd_class = *buffer - '0';
    buffer++;
    // read 2 byte cmd number
    cmd_number = cmd_number + (*buffer - '0') * 10;
    buffer++; 
    cmd_number = cmd_number + (*buffer - '0');
    buffer++;
    // read 1 byte data format 
    data_format = *buffer - '0'; 
    buffer++;
    
    // count data size and throw ERROR0 
    while(*buffer != '\0') 
    {
       data_cnt++;
       buffer++;
    }
    sprintf(debug_str, "%d", group_number);
    
    //write_string(0x00,debug_str); 
    
    buffer -= data_cnt;

    error_result = findError(group_number, cmd_class, 
                             cmd_number, data_format, data_cnt); 
    if(error_result == -1) return;
    
  
    // parsing data bits based on data format   
  	switch (data_format)
  	{
    	case 0:  // d1 - 1 byte 
    		*(data_text) = *buffer;
    		break;
    	case 2:  // d3 - 3 bytes
    		for (i = 0; i < 3; i++)
    		{
    			data_text[i] = *buffer;
    			buffer++;
    		}
    		break;
    	case 3:  // d4 - 4 bytes  
    		for (i = 0; i < 4; i++)
    		{
    			data_text[i] = *buffer;
    			buffer++;
    		}
    		break;
    	case 4:  // d10 - 10 bytes 
    		for (i = 0; i < 10; i++)
    		{
    			data_text[i] = *buffer;
    			buffer++;
    		}
    		break;
    	case 5:  // d16 - 16 bytes 
    		for (i = 0; i < 16; i++)
    		{
    			data_text[i] = *buffer;
    			buffer++;
    		}
    		break;
    	default:
    		break;
  	}

  	
  	/* Start operation */
  	
  	 // LED
    if(group_number == 0)
    {
        //turn on led by GUI Button
        if(cmd_number == 0)
        { 
            switch(data_text[0]) 
            {
                case '0':
                    Regs.portb.byte &= 0b11111110;
                    break;
                case '1':
                    Regs.portb.byte &= 0b11111101;
                    break;
                case '2':
                    Regs.portb.byte &= 0b11111011;
                    break;
                case '3':
                    Regs.portb.byte &= 0b11110111;
                    break;
                case '4':
                    Regs.portb.byte &= 0b11101111;
                    break;
                case '5':
                    Regs.portb.byte &= 0b11011111;
                    break;
                case '6':
                    Regs.portb.byte &= 0b10111111;
                    break;
                case '7':
                    Regs.portb.byte &= 0b01111111;
                    break;
                case '8':
                    Pim.ptm.byte &= 0b10111111;
                    break;
                case '9':
                    Pim.ptm.byte &= 0b01111111;
                    break;
                default:
                    break; 
            }
        
        }
        // turn on led by decimal number 
        else if (cmd_number == 1)
        {
           int decimal = txtdecToDecimal(data_text); 
           int below = (decimal & 0b0011111111);  // cut bits
           int above = (decimal & 0b1100000000) >> 2;
           Regs.portb.byte = ~below;
           Pim.ptm.byte = ~above;           
        } 
        // turn on led by hexadecimal number
        else if (cmd_number == 2)
        {
            int hexadecimal = txthexToDecimal(data_text);
            int below = (hexadecimal & 0b0011111111);
            int above = (hexadecimal & 0b1100000000) >> 2;
            Regs.portb.byte = ~below;
            Pim.ptm.byte = ~above;
        } 
        // turn on led by binary number
        else if (cmd_number == 3)
        {
            int binary = txtbinToDecimal(data_text);
            int below = (binary & 0b0011111111);
            int above = (binary & 0b1100000000) >> 2;
            Regs.portb.byte = ~below;
            Pim.ptm.byte = ~above; 
        }
        // turn off led by GUI Button
        else if (cmd_number == 4)
        {
            switch(data_text[0]) 
            {
                case '0':
                    Regs.portb.byte |= 0b00000001;
                    break;
                case '1':
                    Regs.portb.byte |= 0b00000010;
                    break;
                case '2':
                    Regs.portb.byte |= 0b00000100;
                    break;
                case '3':
                    Regs.portb.byte |= 0b00001000;
                    break;
                case '4':
                    Regs.portb.byte |= 0b00010000;
                    break;
                case '5':
                    Regs.portb.byte |= 0b00100000;
                    break;
                case '6':
                    Regs.portb.byte |= 0b01000000;
                    break;
                case '7':
                    Regs.portb.byte |= 0b10000000;
                    break;
                case '8':
                    Pim.ptm.byte |= 0b01000000;
                    break;
                case '9':
                    Pim.ptm.byte |= 0b10000000;
                    break;
                default:
                    break; 
            }   
        }
    }
    
    // LCD
    else if(group_number == 3)
    {
        if(cmd_number == 0) write_string(0x00, data_text);  
        else if(cmd_number == 1) write_string(0x40, data_text);
    } 	

  	return; 
}


/********************************************************/
/*                         MAIN                         */
/********************************************************/
void main ()
{ 
  //initialize external global variables 
  dataCompleteSignal = 0;
  p_buffer = p_base_buffer;
  
  init_LCD();  
  init_atd0();
  init_7segment();

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
    
  for (;;) 
  {
     if(dataCompleteSignal == 1) 
     { 
        //write_string(0x00, p_base_buffer);
        // data contained in buffer needs to be parsed 
        parse(p_base_buffer);
        dataCompleteSignal = 0;              
     }
     
  }
  
  return;
}
        
     