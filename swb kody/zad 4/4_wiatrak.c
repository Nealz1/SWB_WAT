#include <REGX52.H>

#define max 255
#define IN1p P2_1
#define IN1l P2_2
#define EN1 P2_3
#define EN2 P2_4
#define IN2p P2_5
#define IN2l P2_6
#define SIG P3_4

volatile unsigned char data ctr;

void Odbiornik(void) interrupt 4{
    unsigned char data dana;
    if(TI == 1) {
			TI = 0;
		}
    if(RI == 1){
        RI = 0;
        dana = SBUF;
				if(dana == 'Z'){
					IN1p = !IN1p;
					IN1l = !IN1l;
					IN2p = !IN2p;
					IN2l = !IN2l;
				}
    }
}

void InitEN(void){
		IN1p = 1;
    IN1l = 0;
		IN2p = 0;
		IN2l = 1;
    EN1 = 1;
    EN2 = 1;
}

void Initialize(void){
    SIG = 0;
    ctr = 0;
    IT1 = 1;
    EX1 = 1;
    SCON = 0x50;
    T2CON = 0x30;
    TH2 = RCAP2H = 0xFF;
    TL2 = RCAP2L = 0xDC;
    IP = 0x10;
    ES = 1;
    EA = 1;
    TR2 = 1;
}

void main(void){
		InitEN();
    Initialize();
    while(1){
        ;
    }
}