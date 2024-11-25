#include <REGX52.H>

#define WA P2_4
#define WB P2_5
#define WC P2_6
#define WD P2_7
#define K1 P2_3
#define K2 P2_2
#define K3 P2_1
#define D P0_0
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

void Odbiornik(void) interrupt 4{
    unsigned char data dana;
    if(TI == 1) {
			TI = 0;
		}
    if(RI == 1){
      RI = 0;
      dana = SBUF;
      if(dana == 'A'){
				D = !D;
			}
    }
}

void Initialize(void){
	  SIG = 0;
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

		Initialize();
    while(1){
				WA=0;
        WB=1;
				WC=1;
				WD=1;
				
        if(K1 == 0) {
					Wiadomosc('1'); while(K1==0){;}
				}
        if(K2 == 0) {
					Wiadomosc('2'); while(K2==0){;}
				}
				if(K3 == 0) {
					Wiadomosc('3'); while(K3==0){;}
				}
					
				WA=1;
        WB=0;
				WC=1;
				WD=1;
				
				if(K1 == 0) {
					Wiadomosc('4'); while(K1==0){;}
				}
        if(K2 == 0) {
					Wiadomosc('5'); while(K2==0){;}
				}
				if(K3 == 0) {
					Wiadomosc('6'); while(K3==0){;}
				}
					
				WA=1;
        WB=1;
				WC=0;
				WD=1;
					
				if(K1 == 0) {
					Wiadomosc('7'); while(K1==0){;}
				}
        if(K2 == 0) {
					Wiadomosc('8'); while(K2==0){;}
				}
				if(K3 == 0) {
					Wiadomosc('9'); while(K3==0){;}
				}	
					
				WA=1;
        WB=1;
				WC=1;
				WD=0;
    }
}