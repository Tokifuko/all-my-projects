/**********************************************************************************************/
/*                                                                                            */
/*                           ��������� ���� �������� �������.                                 */
/*                                                                                            */
/**********************************************************************************************/
#ifndef DISPLAY_H
#define DISPLAY_H
#define OUT
#define IN

/*--------------------------------------------------------------------------------------------*/
/* ����� E ��� (�����)                                                                 */
/*--------------------------------------------------------------------------------------------*/
// �������� ������� - �������.
#define   LCD_E               4
#define   LCD_E_PIN           &PORTB, LCD_E

/*--------------------------------------------------------------------------------------------*/
/* ����� A0 ��� (������/�������)                                                       */
/*--------------------------------------------------------------------------------------------*/
// "1" - ���� �������� ������, "0" - ���� �������� �������.
#define   LCD_A0              4
#define   LCD_A0_PIN          &PORTC, LCD_A0

/*--------------------------------------------------------------------------------------------*/
/* ����� RW ��� (������/������)                                                       */
/*--------------------------------------------------------------------------------------------*/
// "1" - ���� ������, "0" - ���� ������.
#define   LCD_RW              3
#define   LCD_RW_PIN          &PORTC, LCD_RW

/*--------------------------------------------------------------------------------------------*/
/* ����� CS2 ��� (������� 2)                                                           */
/*--------------------------------------------------------------------------------------------*/
// �������� ������� - ������.
#define   LCD_CS2             1 
#define   LCD_CS2_PIN         &PORTC, LCD_CS2

/*--------------------------------------------------------------------------------------------*/
/* ����� CS1 ��� (������� 1)                                                            */
/*--------------------------------------------------------------------------------------------*/
// �������� ������� - ������.
#define   LCD_CS1             0
#define   LCD_CS1_PIN         &PORTC, LCD_CS1

/*--------------------------------------------------------------------------------------------*/
/* ����� RES ��� (�����)                                                               */
/*--------------------------------------------------------------------------------------------*/
// �������� ������� - ������.
#define   LCD_RES             2
#define   LCD_RES_PIN         &PORTC, LCD_RES




inline void Set_Line_in_Port(unsigned char volatile* port,unsigned char bit) {*port|=( 1 << bit );}
inline void  Clr_Line_in_Port(unsigned char volatile* port,unsigned char bit) {*port&=~( 1 << bit );}
inline bool  is_Output_Line_in_Port_Set(unsigned char volatile* port,unsigned char bit) { return (*port&( 0x01 << bit ))?(true):(false);}

inline void Set_crystal(BYTE c) 
{
  
  if (c)
    {
      Clr_Line_in_Port(LCD_CS1_PIN);
      Set_Line_in_Port(LCD_CS2_PIN);
    }
  else
  {
    Clr_Line_in_Port(LCD_CS2_PIN);
    Set_Line_in_Port(LCD_CS1_PIN);
  }
}

inline void Set_all_crystal(void) 
{
  Set_Line_in_Port(LCD_CS1_PIN);
  Set_Line_in_Port(LCD_CS2_PIN);
}


/*--------------------------------------------------------------------------------------------*/
/* ���� ������ ��� (PC).                                                                      */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_Data_Bus_to_Output()        DDRA = 0xff
#define   LCD_Data_Bus_To_Input()         { DDRA = 0x00; PORTA = 0xff; }
#define   Put_Data_to_LCD_Data_Bus(data)  PORTA = (data)
#define   Get_Data_from_LCD_Data_Bus()    PINA

/*--------------------------------------------------------------------------------------------*/
/* ������� ���� ������� � ��������.                                                           */
/*--------------------------------------------------------------------------------------------*/
#define   MAX_WIDTH     128
#define   MAX_HEIGHT    64

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������������� �������.                                                           */
/* ���������:   ������ �� ���������.                                                          */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void Display_Init(void);

/*--------------------------------------------------------------------------------------------*/
/* ��������� �������� ���������� ����������� ���.                                             */
/* ���������:   ���������� (0, 1).                                                            */
/* ����������:  true, ���� ���������� �����, false �����.                                     */
/*--------------------------------------------------------------------------------------------*/
OUT bool Wait_LCD_Ready(IN IDX c);

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ ��������� ����������� ���.                                                */
/* ���������:   ���������� (0, 1).                                                            */
/* ����������:  ��������� ���������.                                                          */
/*--------------------------------------------------------------------------------------------*/
//OUT BYTE Read_Status_from_LCD(IN IDX c);

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ ������� � ����������� ���.                                                */
/* ���������:   ���������� (0, 1), ��� ������������ �������.                                  */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
//void Write_Cmd_to_LCD(IN IDX c, IN BYTE cmd);
void Write_Cmd_to_LCD(IN BYTE cmd);

/*--------------------------------------------------------------------------------------------*/
/* ������������ ������� � ��� ������� ��������� (Display_ON).                                 */
/* ���������:   ������ �� ���������.                                                          */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   Write_Cmd_Display_ON()            {Set_crystal(0); Write_Cmd_to_LCD(0x3f);Set_crystal(1); Write_Cmd_to_LCD(0x3f); }

/*--------------------------------------------------------------------------------------------*/
/* ������������ ������� � ��� ������� ���������� (Display_OFF).                               */
/* ���������:   ������ �� ���������.                                                           */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   Write_Cmd_Display_OFF()           { Set_crystal(0);Write_Cmd_to_LCD(0x3e);Set_crystal(1); Write_Cmd_to_LCD(0x3e); }

/*--------------------------------------------------------------------------------------------*/
/* ������������ ������� � ��� ������� ��������� ������ ������ � ������ ���, ������������      */
/* � ������ ������ ������ (Set_Start_Line).                                                   */
/* ���������:   ���������� (0, 1), ����� ������ (0..63).                                      */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   Write_Cmd_Set_Start_Line(line) Write_Cmd_to_LCD(0xc0 + (line))

/*--------------------------------------------------------------------------------------------*/
/* ������������ ������� � ��� ������� ��������� ������ �������� (Page_Addr_Set).              */
/* ���������:   ����� �������� (0..7).                                     */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   Write_Cmd_Page_Addr_Set(page)  Write_Cmd_to_LCD(0xb8 + (page))

/*--------------------------------------------------------------------------------------------*/
/* ������������ ������� � ��� ������� ��������� ������ ������� (Column_Addr_Set).             */
/* ���������:   ����� ������� (0..63).                                     */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   Write_Cmd_Column_Addr_Set(col)    Write_Cmd_to_LCD(0x40 + (col));

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ 1 ����� ������ � ���������� ���.                                          */
/* ���������:   ���������� (0, 1), ������������ ���� ������.                                  */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
//void Write_Data_to_LCD(IN IDX c, IN BYTE data);
void Write_Data_to_LCD(IN BYTE data);
void Write_Data_to_LCD( IN BYTE data, IN BYTE n);

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ n ������ ������ � ���������� ���.                                         */
/* ���������:   ���������� (0, 1), ����� ������� ��������� ������, ����� ��������� ������.    */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void Write_Data_to_LCD(IN IDX c, IN BYTE __flash *pData, IN BYTE n);
void Write_Data_to_LCD(IN IDX c, IN BYTE *pData, IN BYTE n);

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ n ����� ����� ������ � ���������� ���.                                    */
/* ���������:   ���������� (0, 1), ��������� ����, ����� ��� ����������.                      */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
//void Write_Data_to_LCD(IN IDX c, IN BYTE data, IN BYTE n);


/*--------------------------------------------------------------------------------------------*/
/* ��������� ������� ���.                                                                     */
/* ���������:   ������ �� ���������.                                                          */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void LCD_Clear(void);

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ 1 ����� ������ �� ����������� ���.                                        */
/* ���������:   ���������� (0, 1).                                                            */
/* ����������:  ��������� ����.                                                               */
/*--------------------------------------------------------------------------------------------*/
OUT BYTE Read_Data_from_LCD(IN IDX c);

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ �������� ������ �� �������� �����������.                                  */
/* ���������:   ���������� ������ ����������� (�����������),                                  */
/*              ������ � ������ �����������,                                                  */
/*              ����� ������� � ������� ������� �� flash,                                     */
/*              ���� ��������� ������ �����������.                                            */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   DRAW_OVER         0
#define   DRAW_XOR          1
#define   DRAW_DIRECT       2

//#define   DRAW_INVERTED       (1 << 2)

//BYTE XOR (BYTE a, BYTE b) ;
inline BYTE XOR (BYTE a, BYTE b) { return (a | b) & (~ (a & b)); }


int Draw_Bitmap(IN BYTE X, IN BYTE Y, IN BYTE W, IN BYTE H, IN BYTE __flash *pData, IN BYTE flags = DRAW_OVER);
inline void Start_Line_increment(IN BYTE offset_step);
int Add_Text(IN char *str, IN struct FONT __flash *font);
void Clr_Lines(IN BYTE y,IN BYTE h);
inline void Set_all_crystal(void) ;
/*--------------------------------------------------------------------------------------------*/
/* ������������ ������ ������� �������� ������� �� �������� �����������.                      */
/* ���������:   ��� �������,                                                                  */
/*              ���������� ������ ������� (�����������),                                      */
/*              ����� ��������� �������� ������ �� flash,                                     */
/*              ���� ��������� ������ �����������.                                            */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   Draw_Char(ch, X, Y, font, flags)    Draw_Bitmap(X, Y, (font)->Width, (font)->Height, Get_Char_Data_Addr(ch, font), flags)

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ ������ �������� ������� �� �������� �����������.                          */
/* ���������:   ����� ������,                                                                 */
/*              ���������� ������ ������� (�����������),                                      */
/*              ����� ��������� �������� ������ �� flash,                                     */
/*              ���� ��������� ������ �����������.                                            */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
int Draw_Text(IN char *str, IN BYTE X, IN BYTE Y, IN struct FONT __flash *font, IN BYTE flags = DRAW_DIRECT);
int Draw_Text(IN char __flash *str, IN BYTE X, IN BYTE Y, IN struct FONT __flash *font, IN BYTE flags = DRAW_DIRECT);

/*--------------------------------------------------------------------------------------------*/
/* ������������ ���������� ������ ���������� �������� ������� � ������� �������� ��������.    */
/* ���������:   ��� �������,                                                                  */
/*              ����� ��������� �������� ������ �� flash,                                     */
/* ����������:  ����� ������ �������� �������.                                                */
/*--------------------------------------------------------------------------------------------*/
#define   Get_Char_Data_Addr(ch, font)    \
  (font)->pData + (ch) * (font)->Width * ((((font)->Height % 8) != 0) ? (1 + (font)->Height / 8) : ((font)->Height / 8))

/*--------------------------------------------------------------------------------------------*/
/* ��������� �������� ������.                                                                 */
/*--------------------------------------------------------------------------------------------*/
struct  FONT
{
  BYTE  Height;         // ������ ������� � ��������.
  BYTE  Width;          // ������ ������� � ��������.
  BYTE  Count;          // ����� �������� � ������ ����� ����.
  BYTE __flash *pData;  // ����� ������� � ��������� �������� ������.
};

inline BYTE min (BYTE a1, BYTE a2)
{
  if (a1>=a2) return a1;
    else return a2;
}
/*
signed char abs (signed char a1)
{
  if (a1<0) return (a1*(-1));
    else return a1;
}
*/ 
/*--------------------------------------------------------------------------------------------*/
/* ����� 6 � 8 ��������.                                                                      */
/*--------------------------------------------------------------------------------------------*/
extern __flash struct FONT Font_6x8;
extern __flash BYTE Font_6x8_Data[];

/*--------------------------------------------------------------------------------------------*/
/* ����� 7 � 10 �������� ������.                                                              */
/*--------------------------------------------------------------------------------------------*/
extern __flash struct FONT Font_7x10_thin;
extern __flash BYTE Font_7x10_thin_Data[];

/*--------------------------------------------------------------------------------------------*/
/* ����� 7 � 10 �������� ����������.                                                          */
/*--------------------------------------------------------------------------------------------*/
extern __flash struct FONT Font_7x10_bold;
extern __flash BYTE Font_7x10_bold_Data[];

/*--------------------------------------------------------------------------------------------*/
/* ����� 12 � 16 ��������.                                                                    */
/*--------------------------------------------------------------------------------------------*/
extern __flash struct FONT Font_12x16;
extern __flash BYTE Font_12x16_Data[];
volatile BYTE carrent_offset=0;
volatile BYTE X,Y;

/**********************************************************************************************/
#endif
