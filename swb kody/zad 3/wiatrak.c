#include <REGX52.H>
#define max 255
#define IN1 P2_1
#define IN2 P2_2
#define EN1 P2_3
#define EN2 P2_4
#define IN3 P2_5
#define IN4 P2_6

volatile bit data Tryb;

volatile unsigned char data ctr1, ctr2;
volatile unsigned char data nastawa1, nastawa2;
volatile unsigned char data suwak1, suwak2;

void SET_T0_2(void)
{
    TCON=0;
    TH0=TL0= 0x00;
    TMOD = TMOD & 0xF0;
    TMOD = TMOD | 0x02;
    TH0=TL0=0xD1;
    ET0=1;
}

void SET_T1_2(void)
{
    TCON=0;
    TMOD=TMOD & 0x0F;
    TMOD=TMOD | 0x20;
    TH1=TL1=0xF0;
    ET1=1;
}

void Test(void)
{
        if ((ctr1 >= 6 && Tryb==0) || (ctr2 >= 8 && Tryb==0))
        {
						ctr1 = ctr2 = 0;
            Tryb=1;
            nastawa2 = 0x55;
            nastawa1 = 0x7F;
            IN3 = 0;
            IN4 = 1;
            IN1 = 1;
            IN2 = 0;
				}
        else if ((ctr1 >= 8 && Tryb==1) || (ctr2 >= 6 && Tryb==1))
        {
            ctr1 = ctr2 = 0;
            Tryb=0;
            nastawa2 = 0x66;
            nastawa1 = 0xAA;
            IN3 = 1;
            IN4 = 0;
            IN1 = 0;
            IN2 = 1;
        }
}

void ISR_PWM2(void) interrupt 3
{
    suwak2++;
    if(suwak2<nastawa2) {EN2=1;}
    else {
        if (suwak2<max) {EN2=0;}
        else {suwak2=0; EN2=1;}
    }
}

void Licznik_S1() interrupt 2 {
  ctr1++;
    Test();
}


void ISR_PWM1(void) interrupt 1
{
    suwak1++;
    if(suwak1<nastawa1) {EN1=1;}
    else {
        if (suwak1<max) {EN1=0;}
        else {suwak1=0; EN1=1;}
    }
}

void Licznik_S2() interrupt 0 {
  ctr2++;
    Test();
}

void main(void)
{
    P3_4 = 0;
    suwak1=suwak2=0;

    nastawa1=0xAA;
    nastawa2=0x33;

    Tryb=0;
    SET_T0_2();
    SET_T1_2();
    EN1=EN2=1;
    IN2=1;
		IN4=0;
    IN1=0;
		IN3=1;
    ctr1=ctr2=0;
    IT0=IT1=1;
    EX0=EX1=1;
    EA=1;
    TR0=1;
    TR1=1;
    while(1)
    {
        ;
    }
}
