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
unsigned char data LC, PC, n, ctr;
char tab[] = {"3"};

void Konwersja(unsigned char n) {
		PC = 0;
    PC = n % 10;
    tab[0] = '0' + PC;
}

void Odbiornik(void) interrupt 4{
    unsigned char data dana;
    if(TI==1) {
			TI=0;
		}
    if(RI==1){
        RI=0;
        dana = SBUF;
				if(dana == 'S' || dana == 'A'){
					ctr = 3;
					Konwersja(ctr);
					Lcd_DisplayString(1,1, "|   WPROWADZ   |");
					Lcd_DisplayString(2,1, "|     KOD      |");
					Lcd_DisplayString(3,1, "|   DOSTEPU    |");
					Lcd_DisplayString(4,1, "|LICZBA PROB:  |");
					Lcd_DisplayString(4,15, tab);
				}
				if(dana == 'Z'){
					Lcd_DisplayString(1,1, "|--------------|");
					Lcd_DisplayString(2,1, "|    DOSTEP    |");
					Lcd_DisplayString(3,1, "|   PRZYZNANO  |");
					Lcd_DisplayString(4,1, "|--------------|");
				}
				if(dana == 'B'){
					ctr--;
					if(ctr == 0){
						Lcd_DisplayString(1,1, "|--------------|");
						Lcd_DisplayString(2,1, "|    DOSTEP    |");
						Lcd_DisplayString(3,1, "|  ZABLOKOWANO |");
						Lcd_DisplayString(4,1, "|--------------|");
					}
					else{
					Konwersja(ctr);
					Lcd_DisplayString(1,1, "|BLEDNE HASLO  |");
					Lcd_DisplayString(2,1, "|SPROBUJ       |");
					Lcd_DisplayString(3,1, "|PONOWNIE      |");
					Lcd_DisplayString(4,1, "|LICZBA PROB:  |");
					Lcd_DisplayString(4,15, tab);
					}
					
			}
		}
}

void Init(void){
    SIG = 0;
    ctr = 3;
    SCON = 0x50;
    T2CON = 0x30;
    TH2 = RCAP2H = 0xFF;
    TL2 = RCAP2L = 0xDC;
    ES = 1;
    EA = 1;
    TR2 = 1;
		ctr = 3;
}

void main(void){
    LcdInit();
    Init();
		Lcd_DisplayString(1,1, "|    KLIKNIJ   |");
		Lcd_DisplayString(2,1, "|   PRZYCISK   |");
		Lcd_DisplayString(3,1, "|      ABY     |");
		Lcd_DisplayString(4,1, "|   ROZPOCZAC  |");
    while(1){
			;
    }
}