 #include <REGX52.H>

sbit BUT=P3^2;
volatile unsigned char xdata LW _at_ 0xFE00;
volatile unsigned char xdata PW _at_ 0xFD00;
volatile unsigned char data LL, LP;
unsigned char	x;
unsigned char Liczba; //do konwersji
unsigned int i;
bit Fg1;
bit Fg2;
bit Fg3;
unsigned char numerAnimacji;
bit Ft;
unsigned char pierwszy=0;

unsigned char cfr[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned char tozsamosc[]= {0x00, 0x73,0x77,0x2A,0x79,0xB8,0x00,0x15,0x30,0x76,0x6D,0x30,0x79,0x2A,0x30,0x39,0x5B, 0x00, 0x66, 0x00};
unsigned char A2L[]= {0x27,0x0F,0x1E,0x3C,0x39,0x31,0x21,0x01,0,0,0,0,0,0,0,0x08,0x18,0x38,0x39,0x33};//22
unsigned char A2P[]= {0,0,0,0,0,0x01,0x03,0x07,0x0F,0x1E,0x3C,0x39,0x33,0x27,0x0F,0x0E,0x0C,0x08,0,0};//22

void BUTTON_Q1(void) interrupt 0
{
	TR1=1;
	if (numerAnimacji == 0) {
			if(BUT==0){
				TH0 = 0x3C; TL0 = 0xB0; TH1=TL1=0x00; TR1 = 1; TR0 = 1; 
				Fg1=1;
				numerAnimacji = 1;
			}
	}
	if(BUT == 0 && numerAnimacji == 1)//dwuklik
		{
			while(BUT==0)
			{
				;
			}
			for(i=0;i<7000;i++)
			{
				if(BUT == 0)
				{
					TH0 = 0x3C; TL0 = 0xB0; TH1=TL1=0x00; TR1 = 1; TR0 = 1; 
					LL=0;
					LP=3;
					Fg2=1;
					break;
				}
			}
			
		}
		if (BUT == 0 &&  numerAnimacji == 2) {
			i = 0;
			Ft = 1;
			
			while(i<19000) 
			{ 
				if(BUT == 1)
				{
					Ft=0;
					break;
				}
				i++; 
			}	
			if(Ft == 1)
			{
				TR1 = 1; TR0 = 1;
				LL = 0;
				LP = 0;
				Fg3 = 1;
			}		
	}
}

void IST_Tozsamosc(void) interrupt 3
{
	if(Fg1==1 && Fg2!=1) {LW=A2L[LP]; PW=A2P[LP]; }
	if(Fg2==1 && Fg3!=1) {LW=cfr[LL]; PW=cfr[LP];}
	if(Fg3==1) {LW=tozsamosc[LL]; PW=tozsamosc[LL+1];}
}

void ROLKA(void) interrupt 1
{

		if(numerAnimacji == 1 && Fg1==1 && Fg2!=1){
				if(LP<19) {LP++;} else {LP=0;}
				
		}
		else if(Fg2==1 && Fg3 != 1){
			numerAnimacji = 2;
			if(LP==9 && LL==2)
			{
				LL=0;
				LP=4;
				//numerAnimacji = 2;
			}
			else if(LP==9)
			{
				LP=0;
				LL++;
			}
			else
			{
				LP++;
			}
		}
		else if(Fg3 == 1 && numerAnimacji == 2){
		if(LL<19) {LL++;}
		else LL = 0;
	}
}

void Set_T1_CTR(void)
{
	TH1=TL1=0x00; //wartosc poczotkowa T1
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

void main(void)
{
	LW=0x00;
	PW=0x00;
	LL=0;
	LP=0;
	Set_T1_CTR();
	Set_T0_TIME();
	IT0=1;
	EX0=1;
	EA=1;
	numerAnimacji=0;
	
	Fg1=0;
	Fg2=0;
	x=0;
	i=0;
	while(1){
			//while(x==3) {LW=cfr[8]; PW=cfr[8];}
	}
}
