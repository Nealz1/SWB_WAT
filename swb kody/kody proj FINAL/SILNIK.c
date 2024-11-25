#include <REGX52.H>

#define max 255
#define EN1 P2_3
#define EN2 P2_4
#define IN1p P2_1
#define IN1l P2_2
#define IN2p P2_5
#define IN2l P2_6
#define SIG P3_4

volatile bit flaga;

volatile unsigned char data ctr, obr;
volatile unsigned char data nastawa1, nastawa2;
volatile unsigned char data suwak1, suwak2;

void Wiadomosc(unsigned char dana){
		ES = 0;
    SIG = 1;
    TI = 0;
    SBUF = dana;
		if(dana == 'A'){flaga = 0;}
    while(TI == 0){
			;
		}
    TI = 0;
    SIG = 0;
		ES = 1;
}

void SET_T0_2(void){
    TCON = 0;
    TH0 = TL0 = 0x00;
    TMOD = TMOD & 0xF0;
    TMOD = TMOD | 0x02;
    TH0 = TL0 = 0xD1;
    ET0 = 1;
}

void SET_T1_2(void){
    TCON = 0;
    TMOD = TMOD & 0x0F;
    TMOD = TMOD | 0x20;
    TH1 = TL1 = 0xF0;
    ET1 = 1;
}

void Licznik_S2() interrupt 0 {
		obr++; ctr++;
}

void ISR_PWM2(void) interrupt 3
{
	if(flaga == 1){
    suwak2++;
    if(suwak2 < nastawa2){
			EN2 = 1;
		}
    else{
        if(suwak2 < max){
					EN2 = 0;
				}
        else{
					suwak2 = 0; 
					EN2 = 1;
			}
    }
	}
}

void ISR_PWM1(void) interrupt 1{
	if(flaga == 1){
    suwak1++;
    if(suwak1 < nastawa1) {
			EN1 = 1;
		}
    else{
     if(suwak1 < max) {
				EN1 = 0;
			}
     else {
			suwak1 = 0; 
			EN1 = 1;
		}
    }
	}
}

void Wstrzymaj(void) {
    unsigned long i;
		EN1 = 0;
		EN2 = 0;
    for(i = 0; i < 20000; i++) {
        ;
    }
}

void Silniczki(void) interrupt 2{
if(flaga == 1){
    if(ctr >= 15){
			Wstrzymaj();
			ctr = 0;
			EN1 = 1;
			EN2 = 1;
			IN1p = !IN1p;
			IN1l = !IN1l;
			IN2p = !IN2p;
			IN2l = !IN2l;
		}
		if(obr >= 30){
			ctr = 0;
			obr = 0;
			EN1 = 0;
			EN2 = 0;
			Wiadomosc('A');
		}
	}
}

void Odbiornik(void) interrupt 4{
    unsigned char data dana;
    if(TI == 1) {
			TI = 0;
		}
    if(RI == 1){
        RI = 0;
        dana = SBUF;
				if(dana == 'Z'){
					flaga = 1;
				}
    }
}

void Init(void){
    SIG = 0;
    ctr = 0;
		obr = 0;
		flaga = 0;
		SET_T0_2();
    SET_T1_2();
    IN1p = 1;
    IN1l = 0;
		IN2p = 0;
		IN2l = 1;
		
    EN1 = 0;
    EN2 = 0;
		  
    SCON = 0x50;
    T2CON = 0x30;
    TH2 = RCAP2H = 0xFF;
    TL2 = RCAP2L = 0xDC;
    IP = 0x10;
    ES = 1;
    EA = 1;
    TR0 = TR1 = TR2 = 1;
		IT0 = IT1 = 1;
    EX0 = EX1 = 1;
		
		suwak1 = suwak2 = 0;
		nastawa2 = 0x80;
    nastawa1 = 0x80;
}

void main(void){
    Init();
    while(1)
    {
        ;
    }
}