#include <REGX52.H>

#define SIG P3_4

extern void LcdInit();
extern void Lcd_Cursor(char row, char column);
extern void Lcd_DisplayCharacter(char a_char);
extern void Lcd_DisplayString(char row, char column, char *string);
extern void Lcd_WriteControl(unsigned char LcdCommand);
extern void Lcd_DisplayScreen (char *ptr);
extern void Lcd_WriteData (unsigned char LcdData);

unsigned char data Var1, Var2, Var3;
unsigned char data LC, PC, n, licznik, ctr;
char tab[] = {"00"};

void Wiadomosc(unsigned char dana){
    SIG = 1;
    TI = 0;
    SBUF = dana;
    while(TI==0){
			;
		}
    TI = 0;
    SIG = 0;
}

void Konwersja(unsigned char n) {
    LC = 0;
		PC = 0;
    LC = n / 10;
    PC = n % 10;
    tab[0] = '0' + LC;
    tab[1] = '0' + PC;
}

void Odbiornik(void) interrupt 4{
    unsigned char data dana;
    if(TI==1) {
			TI=0;
		}
    if(RI==1){
        RI=0;
        dana = SBUF;
        if(dana=='1') {
					licznik++; ctr = 1; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
				if(dana=='2') {
					licznik++; ctr = 2; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
				if(dana=='3') {
					licznik++; ctr = 3; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
				if(dana=='4') {
					licznik++; ctr = 4; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
				if(dana=='5') {
					licznik++; ctr = 5; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
				if(dana=='6') {
					licznik++; ctr = 6; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
				if(dana=='7') {
					licznik++; ctr = 7; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
				if(dana=='8') {
					licznik++; ctr = 8; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
				if(dana=='9') {
					licznik++; ctr = 9; if(licznik % 3 == 0){Wiadomosc('A');} Konwersja(ctr);
				}
    }
}

void Init(void){
    SIG = 0;
    ctr = 0;
    SCON = 0x50;
    T2CON = 0x30;
    TH2 = RCAP2H = 0xFF;
    TL2 = RCAP2L = 0xDC;
    ES = 1;
    EA = 1;
    TR2 = 1;
}

void main(void){
    LcdInit();
    Init();
    while(1){
			Lcd_DisplayString(2, 8, tab);
    }
}