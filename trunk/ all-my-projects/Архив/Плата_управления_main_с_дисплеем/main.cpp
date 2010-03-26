#include "main.h"


//int main(void);

#define   LED1              2
#define   LED1_PIN          &PORTG, LED1
#define   LED2              4
#define   LED2_PIN          &PORTG, LED2
#define   LED3              3
#define   LED3_PIN          &PORTG, LED3



/*
BYTE LCD_last_x;
BYTE LCD_last_y;
BYTE LCD_stert_line;

*/


int main()
{ 
  
  // светодиоды
 DDRG|=(1<<PG2);
  DDRG|=(1<<PG3); 
  DDRG|=(1<<PG4);
  
  Display_Init();


 /*   
 

  
   
  IDX my_c=1;    
    Set_crystal(my_c);
  Write_Cmd_Page_Addr_Set(7);Write_Cmd_Column_Addr_Set(0);

   


    
    BYTE tx_byte=0xAA;
    BYTE rx_byte=0;
    //Write_Data_to_LCD(my_c, tx_byte);
    
      Write_Data_to_LCD(my_c, 0x00);Write_Data_to_LCD(my_c, 0x00);
      Write_Data_to_LCD(my_c, 0x80);Write_Data_to_LCD(my_c, 0xc0);
      Write_Data_to_LCD(my_c, 0xe0);Write_Data_to_LCD(my_c, 0xf0);
      Write_Data_to_LCD(my_c, 0xfc);Write_Data_to_LCD(my_c, 0xf0);
      Write_Data_to_LCD(my_c, 0xe0);Write_Data_to_LCD(my_c, 0xc0);
      Write_Data_to_LCD(my_c, 0x80);Write_Data_to_LCD(my_c, 0x00);
    
      //Write_Data_to_LCD(my_c, 0x00);
        Write_Cmd_Page_Addr_Set(7);Write_Cmd_Column_Addr_Set(0);   
      Write_Data_to_LCD(my_c, 0x00);
      
      Write_Data_to_LCD(my_c, 0x00);Write_Data_to_LCD(my_c, 0x03);
      Write_Data_to_LCD(my_c, 0x07);Write_Data_to_LCD(my_c, 0x17);
      Write_Data_to_LCD(my_c, 0x1b);Write_Data_to_LCD(my_c, 0x1f);
      Write_Data_to_LCD(my_c, 0x1b);Write_Data_to_LCD(my_c, 0x17);
      Write_Data_to_LCD(my_c, 0x07);Write_Data_to_LCD(my_c, 0x03);
      Write_Data_to_LCD(my_c, 0x00);
    
    FONT  *my_font;
    //*my_font=Font_7x10_thin ;
    *my_font=Font_6x8;
    
    for(BYTE i = 0; i < 8; i++)
    {    
    Draw_Bitmap(30+7*i, 56, 6, 8,(my_font->pData+12*(0+i)),DRAW_XOR);
    //delay_ms(50);
   } 
    
 // Draw_Bitmap(10, 8, 7, 10,(my_font->pData+(7*14)),DRAW_DIRECT);
    


     //data=0xff;
     if (is_Output_Line_in_Port_Set(LED3_PIN)) Clr_Line_in_Port(LED3_PIN); 
     else  Set_Line_in_Port(LED3_PIN); 
      //delay_ms(10);
     
 

*/      

    Set_crystal(0);  
  Write_Cmd_Set_Start_Line(0);
  Set_crystal(1);  
  Write_Cmd_Set_Start_Line(0);  
     Set_Line_in_Port(LED3_PIN); 
    

    char  *str; 
    str= "Привет Макс";
   // *my_font=Font_7x10_thin ;
  //  *my_font=Font_12x16;
    Draw_Text(str,50, 62, &Font_7x10_thin ,DRAW_DIRECT);
    
    delay_ms(20);

  Set_crystal(0);  
  carrent_offset=0;
  Write_Cmd_Set_Start_Line(carrent_offset);
  Set_crystal(1);  
  Write_Cmd_Set_Start_Line(carrent_offset);

  
delay_ms(20);
 
Y=0;
X=7;
//Start_Line_increment(13);
delay_ms(20);
LCD_Clear();

//delay_ms(64);

//Clr_Lines(48,3);

while (1)
  { 

delay_ms(20);

str=Convert_hex_to_str(0xA5);

 Add_Text(str,&Font_6x8);
   delay_ms(48);
  Add_Text(str,&Font_7x10_thin);
     delay_ms(48);
    Add_Text(str,&Font_12x16);
delay_ms(48);

  if ( Wait_LCD_Ready(0))  Clr_Line_in_Port(LED1_PIN);
    else Set_Line_in_Port(LED1_PIN);   
    
    if ( Wait_LCD_Ready(1))  Clr_Line_in_Port(LED2_PIN);
    else Set_Line_in_Port(LED2_PIN);   
        
	

	//led_3_on();

  }  
  //return 0;  
} 

