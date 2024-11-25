#include <REGX52.H>

sbit WA=P2^4;
sbit WB=P2^5;
sbit WC=P2^6;
sbit WD=P2^7;
sbit K1=P2^3;
sbit K2=P2^2;
sbit K3=P2^1;
sbit D=P0^0;
bit Fp;
bit Fx;
bit Fy;
bit Fa;
bit Fb;
bit Fh;
bit Fm;
bit Fn;
volatile bit Fz=0;
char CounterA;
char CounterB;
char CounterC;
char CounterD;

void Dwupuszczenie(void)
{
		bit Fp2=0;
		unsigned int i=0;
				for(i=0; i<5000; i++)
				{
					if(K1==1 && Fp==1) {Fp=0; break;}
				}
				for (i=0; i<10000; i++)
				{
					if(K1==0 && Fp==0) Fp2=1;
				}
}
void ZapalenieCzasowe(void)
{
	unsigned int a=0;
	D=0;
	for(a=0; a<25000; a++) {;}
	D=1;
}

void BlokadaCzas(void)
{
	unsigned int b = 0;
	for(; b<30000; b++) {;}
	for(b=0; b<30000; b++) {;}
}

void trzymaj(void)
{
	unsigned int j=0;
	for(j=0; j<30000; j++)
	{
		if(K2!=0) return;
	}
	if(Fm == 0){
		D=0;
	}
	else {
		BlokadaCzas();
	}
			
}

void Blokada(void)
{
	WA=1;
	WB=1;
	WC=1;
	WD=0;
	while(1)
	{
		if(K1==0) break;
	}
}

void ZerowanieFlag(void)
{
    Fy=0;
    Fx=0;
}

void BlokadaKod (void){
    bit Fz = 0;
		WA = 1;
		WB = 0;
    WC = 1;
		WD = 1;
	  while(1)
		{
			WA = 1;
			WB = 0;
			WC = 1;
			WD = 1;
      if(K3 == 0)
			{
            while(K3 == 0) {;}
						WA = 1;
						WB = 1; 
						WC = 0;
						WD = 1;
            while(1)
						{
                if(K1 == 0)
								{
                    while(K1 == 0) {;}
											WA = 1;
											WB = 1; 
											WC = 0;
											WD = 1;
                        while(1)
												{
                            if(K2 == 0)
														{
															while(1)
															{ 
																if(K2 == 0)
																{
																	return;
																}
																if(K1 == 0 || K3 == 0) 
																{
																	Fz = 1; 
																	break;
																}
															}
														}
														if(Fz == 1) {return;}
														if(K3 == 0 || K1 == 0) {break;}
                        }
                }
								if(Fz == 1) {return;}
                if(K3 == 0 || K2 == 0) {break;}
            }
        }
		}
}

void Dwuklik(void)
{
        unsigned int i=0;
                    for(i=0; i<5000; i++)
                {
                    if(K3==1 && Fp==1) Fp=0;
                    if(K3==0 && Fp==0) BlokadaKod();
                }
}

void main(void)
{
    Fh=0;
    Fb=0;
    Fp=0;
    Fx=0;
    Fy=0;
		Fm=0;
		Fa=0;
		Fn=0;
    CounterA=0;
    CounterB=0;
    CounterC=0;
		CounterD=0;
    
    while(1)
    {	
            WA=0;
            WB=1;
						WC=1;
						WD=1;
			
						//1
						//DZIALA 
						//Co trzecie wcisniecie - zapalenie i zgaszenie diody
						if(K1==0 && CounterA==2) {ZapalenieCzasowe(); Fp=0; CounterA=0;}
            else if(K1==0) 
            {CounterA++; ZerowanieFlag(); while(K1==0) {;}}
						
						//2
						//DZIALA
						//Co trzecie puszczenie - zmiana funckji przyciskow 4 i 5
						if(K2==0 && CounterB==2) {while(K2==0) {;} Fm = !Fm; CounterB=0;}
            else if(K2==0) 
            {CounterB++; ZerowanieFlag(); while(K2==0) {;}}
						
						//3 
						//DZIALA
						//Podwojne wcisniecie - Blokuje klwiature, odblokowanie jesli: 1. 6 2. 7 3. 8
            //dopisac flaga fb==0,
						if(K3==0) {Fh=1; Fb=1; if(Fa == 0) { Fp=1; Dwuklik(); }}
							
							
            WA=1;
            WB=0;
						WC=1;
						WD=1;
						
						//4
						//DZIALA
						//Podwojne puszczenie - blokuje klawiature na 5s
            if(K1==0 && Fm==0) {Fp=1; ZerowanieFlag(); Dwupuszczenie(); BlokadaCzas();}
						if(K1==0 && Fm==1) {Fp=1; ZerowanieFlag(); Dwupuszczenie(); D=0;}
						
						//5
						//DZIALA
						//Przytrzymanie na ok. 3 s - zapalenie
            if(K2==0 && Fm == 0) {Fp=1; ZerowanieFlag(); trzymaj();}
						if(K2==0 && Fm == 1) {Fp=1; ZerowanieFlag(); trzymaj();}
						
						//6
						//DZIALA
						//Podczas wcisnietego przycisku - zgaszenie
            if(K3==0) {Fx=0; D=1;}
						
            WA=1;
            WB=1;
						WC=0;
						WD=1;
						
						//7 
						//DZIALA
						//Na wcisniecie jesli przycisk id 3 - zmiana stanu diody
            if(K1==0 && Fh==1) {D = !D; Fh=0; while(K1==0) {;} }
						
						//8 
						//DZIALA
						//Na puszczenie jesli przycisk id 3 - blokada klawiatury
            if(K2==0 && Fb==1) {while(K2==0) {;} Fb=0; Blokada();  }
						
						//9
						//DZIALA
						//Wcisniecie - blokada klawiatury
						if(K3==0) {ZerowanieFlag(); Blokada();}
						
            WA=1;
            WB=1;
						WC=1;
						WD=0;
						
            //* 
						//DZIALA
						//Puszczenie - Odblokowanie klawiatury
						if(K1==1) {Fp=0; ZerowanieFlag();}
            
						//0 
						//DZIALA
						//Co drugie puszczenie - Wylaczenie dzialania funkcji o przycisku id: 3
						if(K2==0) 
						{
							if(CounterC%2==1) {Fa = 1;}
							else {Fa = 0;}
							while(K2==0) {;}
							CounterC++;
						}
						
						//# 
						//DZIALA
						//Co drugie wcisniecie - zmiana stanu diody
						if(K3==0) 
						{
							if(CounterD%2==1) {D=!D;}
							while(K3==0) {;}
							CounterD++;
						}
    }
}
