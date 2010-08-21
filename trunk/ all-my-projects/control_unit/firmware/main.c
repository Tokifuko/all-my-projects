#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "control_unit.h"
#include "cc/cc1101.h"
#include "common/common.h"

void CC_Task (void);
void EVENT_Detected(void);
void EVENT_Hide(void);
void EVENT_NewPacket(void);
// Declare your global variables here
unsigned char dat;


float f_sr_LQI=0;
float f_sr_dBm=0;
unsigned int poket_counter;

#define dBm_ACCURACY 128
#define LQI_ACCURACY 128

struct {
    uint16_t Timer;
    bool JustEnteredRX;
    bool DeepSleep;
    uint8_t Channel;
} CC_Srv;
struct {
    bool Detected;
    bool IsHere;
    uint16_t Timer;
} CStone;

// =============================== CC settings =================================
#define PKT_ID_CALL     0xCA
// Channels to use
#define CC_CHANNEL_COUNT    30  // Number of channels to use
#define CC_CHANNEL_START    11
#define CC_CHANNEL_END      (CC_CHANNEL_START + CC_CHANNEL_COUNT)

// ================================= Timings ===================================
#define CC_RX_ON_DELAY      18 // ms
#define CC_RX_OFF_DELAY     108 // ms

#define DETECTOR_TIMEOUT    3996 // ms


int i_a;


int main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
PORTA=0xFF;
DDRA=0x00;
PORTD=0x00;
DDRD=0x00;

DDRC=0;//0xF0;
PORTC=0;//0xF0;
sei();  // Global enable interrupts

control_unit_init();
display_on();
    // CC init
    CC_Srv.Channel = 0;
    CC_Srv.JustEnteredRX = false;
    CC_Srv.DeepSleep = false;
    //TimerResetDelay(&CC_Srv.Timer);
    CC_Init();
    CC_SetChannel(0);
    CC_SetAddress(4);   //Never changes in CC itself
//unsigned char i=0;
int  j=0;
while (1)
      {
        CC_Task();
        if (j>10000)
        {
            if (KEY_1_STATE) // нажата первая кнопка -выводим LQI
            {
                display_int_out(f_sr_LQI);
                display_LED_on();
            }
            else if (KEY_2_STATE) // нажата вторая кнопка - выводим количество пакетов
                {
                    display_int_out(poket_counter);
                }
                else    // ничего не нажато - выводим уровень сигнала помноженый на два
                {
                    display_signed_int_out(f_sr_dBm);
                    display_LED_off();
                }

         poket_counter=0;
        j=0;
        }
j++;
/*
        _delay_ms(75);
      	
        j++;
	 	if (i>7) i=0;
        if (j>199) j=0;
*/
      //	display_digits[0]=i;
      //	display_digits[1]=i;
      //	display_digits[2]=i;
      //	display_digits[3]=i;
/*
	  display_animation(0,i);
	 	//display_char_out(1,i);
                display_char_out(1,j/2);
*/
		//display_digits[2]=10;
		//display_digits[3]=10;
      	//display_repaint();
		
       }
}
FORCE_INLINE void CC_Task (void){


    // Handle packet if received
    if (CC.NewPacketReceived) {
        CC.NewPacketReceived = false;
        EVENT_NewPacket();
    }

/*
    if (CC_Srv.DeepSleep) {
        if (TimerDelayElapsed(&CC_Srv.Timer, CC_RX_OFF_DELAY)) CC_Srv.DeepSleep = false;
        else return;
    }
*/
    //PORTA |= (1<<PA2); // DEBUG
    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_IDLE:
            CC_ENTER_RX();
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

// =============================== Events ======================================
void EVENT_Detected(void) {
   // ELED.PWMDesired = PWM_MAX;
}
void EVENT_Hide(void) {
    //ELED.PWMDesired = 0;
}

void EVENT_NewPacket(void) {
    if (CC.RX_Pkt.CommandID == PKT_ID_CALL) {
        CStone.Detected = true;
        // Send event if needed
        if (!CStone.IsHere) {
            CStone.IsHere = true;
            EVENT_Detected();
        }

       // poket_counter  - счетчик пакетов
        poket_counter++;
// переводим RSSI в двойные децебелы
    float f_dBm;
    if (CC.RX_Pkt.RSSI>=128) f_dBm=(CC.RX_Pkt.RSSI-256)-(74*2);
        else f_dBm=CC.RX_Pkt.RSSI-(74*2);


   // вычисление наподобе скользящего среднего   
    if (f_dBm<f_sr_dBm) f_sr_dBm-=(f_sr_dBm-f_dBm)/dBm_ACCURACY;
    else f_sr_dBm+=(f_dBm-f_sr_dBm)/dBm_ACCURACY;

    float f_LQI;
  // вычисление наподобе скользящего среднего
    f_LQI=CC.RX_Pkt.LQI;
    if (f_LQI<f_sr_LQI) f_sr_LQI-=(f_sr_LQI-f_LQI)/LQI_ACCURACY;
    else f_sr_LQI+=(f_LQI-f_sr_LQI)/LQI_ACCURACY;

    } // if PKT_ID_CALL

}