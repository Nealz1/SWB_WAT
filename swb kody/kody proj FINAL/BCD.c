#include <REGX52.H>
#define SIG P3_4

sbit BUTTON = P3^2;

volatile unsigned char xdata LW _at_ 0xFE00;
volatile unsigned char xdata PW _at_ 0xFD00;
volatile unsigned char data LL, LP;
volatile unsigned char data ctr;

bit stop;
bit Fg3;
bit Ft;

unsigned int i;
unsigned char program;
unsigned char podpowiedz[]= {0x00, 0x00, 0x00, 0x2A, 0x2A, 0x06, 0x06, 0x00};

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
	TR1 = 1;
	if (program == 0){
			if(BUTTON == 0){
				Wiadomosc('S');
				TH0 = 0x3C; 
				TL0 = 0xB0; 
				TH1 = TL1 = 0x00; 
				TR1 = 1; 
				TR0 = 1; 	
				program = 1;
			}
	}
	if (BUTTON == 0 &&  program == 1) {
		i = 0;
		Ft = 1;
		
		while(i < 19000) { 
			if(BUTTON == 1){
				Ft = 0;
				break;
			}
		i++; 
		}	
		if(Ft == 1){
			stop = 0;
			TR1 = 1; 
			TR0 = 1;
			LL = 0;
			LP = 0;
			Fg3 = 1;
		}		
	}
}

void WyswietlPodpowiedz(void) interrupt 3{
	if(Fg3 == 1) {
		LW = podpowiedz[LL]; 
		PW = podpowiedz[LL + 1];
	}
}

void ROLKA(void) interrupt 1{
	if(Fg3 == 1 && program == 1){
		if(LL < 6 && stop == 0) {
			LL++;
			ctr++;
		}
		else if(ctr >= 18){
			ctr = 0;
			stop = 1;
		}
		else LL = 0;
	}
}

void Set_T1_CTR(void){
	TH1=TL1=0x00; //wartosc poczatkowa T1
	TMOD = TMOD & 0x0F; //T1 zerowanie trybu
	TMOD = TMOD | 0x20;	//T1 w autoreload, tryb 2
	ET1=1; //wlaczenie T1
}

void Set_T0_TIME() {
    TMOD = TMOD & 0xF0;
		TMOD = TMOD | 0x01;   //T0 w trybie 16-bitowego timera
    TH0 = 0x3C;
    TL0 = 0xB0;
    ET0 = 1;
}

void Initialize(void){
	SIG=0;
	SCON=0x50;
  T2CON=0x30;
  TH2=RCAP2H=0xFF;
	TL2=RCAP2L=0xDC;
  TR2=1;
	
	LW=0x00;
	PW=0x00;
	LL=0;
	LP=0;
}

void InitLiczniki(void){
	program = 0;
	Fg3 = 0;
	i = 0;
	ctr = 0;
	stop = 0;
}

void main(void){
	Initialize();
	InitLiczniki();
	Set_T1_CTR();
	Set_T0_TIME();
	IT0 = 1;
	EX0 = 1;
	EA = 1;
	while(1){
			;
	}
}