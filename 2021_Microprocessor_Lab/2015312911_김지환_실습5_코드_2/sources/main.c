#include "main.h"

void light7segment(unsigned int cnt)
{
 	//ATD ���� 0~9�� ��ȯ�ϴ� ���α׷��� �ۼ��Ͻÿ�.
 	unsigned char mapping;
 	
  if(cnt >= 409 && cnt < 435) {
 	  mapping = 0;
 	} else if (cnt >= 435 && cnt < 461) {
 	  mapping = 1;
 	} else if (cnt >= 461 && cnt < 487){
 	  mapping = 2;
 	} else if (cnt >= 487 && cnt < 513){
 	  mapping = 3;
 	} else if (cnt >= 513 && cnt < 539){
 	  mapping = 4;
 	}  else if (cnt >= 539 && cnt < 565){
 	  mapping = 5;
 	}  else if (cnt >= 565 && cnt < 591){
 	  mapping = 6;
 	}  else if (cnt >= 591 && cnt < 617){
 	  mapping = 7;
 	}  else if (cnt >= 617 && cnt < 643){
 	  mapping = 8;
 	} else if (cnt >= 643 && cnt < 675){
 	  mapping = 9;
 	} else if (cnt >= 675) {
 	  mapping = 10; 
 	}

 	set_7segment(mapping);	
}                           

void main ()
{
  unsigned int i;
  
  init_atd0();              
  init_7segment(); 
  ini_interrupt();
  int_enable();
  
	Page.ddrk.byte = 0b11111111;	          // �߱��� ����� ����	 // Port K data direction 
  global_mode = 0;
  
	//Insert Application Software Here
	for (;;){
	  if(global_mode == 0){
	      i= get_atd0(0);		//ATD ���� �޾ƿ**
	      light7segment(i);	// ATD �� Segment���
	      m_delay(50);
	  }
	}
		
}


void m_delay(unsigned int m) //������ ��ƾ
{
 unsigned int i, j; 
    
 //  disable_interrupt(); 
   
 for(i=0;i<m;i++)
    for(j=0;j<2650;j++);  //16MHz : 1msec  

 //   enable_interrupt();
}
