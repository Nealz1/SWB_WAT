#include <REGX52.H>

#define SIG P3_4

void Wiadomosc(unsigned char dana){
    SIG = 1;
    TI = 0;
    SBUF = dana;
    while(TI == 0){
			;
		}
    TI = 0;
    SIG = 0;
}

void Przycisk(void) interrupt 0{
    Wiadomosc('Z');
}

void Initialize(void){
	  SIG = 0; 
    SCON = 0x50;
    T2CON = 0x30;
    TH2 = RCAP2H = 0xFF;
    TL2 = RCAP2L = 0xDC;
    IT0 = 1;
    EX0 = 1;
    EA = 1;
    TR2 = 1;
}

void main(void){

    Initialize();
    while(1){
        ;
    }
}