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

volatile unsigned char data index;
volatile unsigned char data proba;
bit data dobry;

volatile bit Fs;
unsigned char data dana;

void Wiadomosc(unsigned char dana){
		ES = 0;
    SIG = 1;
    TI = 0;
    SBUF = dana;
    while(TI == 0){
			;
		}
    TI = 0;
    SIG = 0;
		ES = 1;
}

void Blokada(void){
	Fs = 0;
	D = 1;
	while(1)
	{
		if(Fs == 1) {
		D = 0;
		break;
		}
	}
}

void BlokadaKod (void){
    bit Fz = 0;
		D = 1;
    WA = 0;
    WB = 1;
    WC = 1;
		WD = 1;
    while(1){
        Fz = 0;
				WA = 0;
				WB = 1;
        WC = 1;
				WD = 1;
        if(K1 == 0){
            while(K1 == 0) {;}
						WA = 1;
						WB = 0; 
						WC = 1;
						WD = 1;
            while(1){
                if(K1 == 0){
                    while(K1 == 0) {;}
											WA = 1;
											WB = 1; 
											WC = 0;
											WD = 1;
                        while(1){
                            if(K1 == 0){
															while(1){ 
																WA = 1;
																WB = 1; 
																WC = 1;
																WD = 0;
																if(K1 == 0){
																	D = 0;
																	Wiadomosc('S');
																	return;
																}
																if(K2 == 0 || K3 == 0) {
																	Fz = 1; 
																	break;
																}
															}
														}
														if(Fz == 1) {return;}
														if(K3 == 0 || K2 == 0) {break;}
                        }
                }
								if(Fz == 1) {return;}
                if(K3 == 0 || K2 == 0) {break;}
            }
        }
    }
}

void Odbiornik(void) interrupt 4{
    if(TI == 1) {
			TI = 0;
		}
    if(RI == 1){
      RI = 0;
      dana = SBUF;
      if(dana == 'S' || dana == 'A'){
				Fs = 1;
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
		index = 0;
		proba = 0;
		dobry = 1;
}

void main(void){
		Initialize();
		Blokada();
    while(1){
				WA=0;
        WB=1;
				WC=1;
				WD=1;
				
        if(K1 == 0) {
					while(K1 == 0){;} dobry = 0; index++;
				}
        if(K2 == 0) {
					while(K2 == 0){;} dobry = 0; index++;
				}
				if(K3 == 0) {
					while(K3 == 0){;} if(index != 2){dobry = 0;} index++;
				}
					
				WA=1;
        WB=0;
				WC=1;
				WD=1;
				
				if(K1 == 0) {
					while(K1 == 0){;} if(index != 1){dobry = 0;} index++;
				}
        if(K2 == 0) {
					while(K2 == 0){;} if(index != 3){dobry = 0;} index++;
				}
				if(K3 == 0) {
					while(K3 == 0){;} dobry = 0; index++;
				}
					
				WA=1;
        WB=1;
				WC=0;
				WD=1;
					
				if(K1 == 0) {
					while(K1==0){;} dobry = 0; index++;
				}
        if(K2 == 0) {
					while(K2==0){;} dobry = 0; index++;
				}
				if(K3 == 0) {
					while(K3==0){;} dobry = 0; index++;
				}	
					
				WA=1;
        WB=1;
				WC=1;
				WD=0;
				
				if(K1 == 0) { 
					//sekwencja odblokowania 147*
				}
        if(K2 == 0) {
					while(K2 == 0){;} if(index != 0){dobry = 0;} index++;
				}
				if(K3 == 0) { // # - zatwierdzenie kodu PIN
					while(K3 == 0){;}		
				}
				if(index == 4) {
					while(K3 == 1){;}
					while(K3 == 0){;}
					if(dobry == 1){	
						proba = 0;
						index = 0;
						dobry = 1;						
						Wiadomosc('Z');
						Blokada();
					}
					else{
						dobry = 1;
						proba++;
						index = 0;
						Wiadomosc('B');
					}
					if(proba == 3){
						D = 1;
						proba = 0;
						BlokadaKod();	
					}
				}
    }
}