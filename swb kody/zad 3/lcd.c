#include <REGX52.H>

extern void LcdInit();
extern void Lcd_Cursor(char row, char column);
extern void Lcd_DisplayCharacter(char a_char);
extern void Lcd_DisplayString(char row, char column, char *string);
extern void Lcd_WriteControl(unsigned char LcdCommand);
extern void Lcd_DisplayScreen (char *ptr);

unsigned char data Var1, Var2, Var3;
volatile unsigned char data licznik, ctr;
volatile unsigned char data LC, PC;
char l4[] = {"00"};

void Konwersja(unsigned char n) {
    // Inicjalizacja zmiennych LC i PC
    LC = PC = 0;
    // Ustalanie pierwszej cyfry (LC)
    LC = n / 10;
    // Ustalanie drugiej cyfry (PC)
    PC = n % 10;
		l4[0]='0'+LC;
		l4[1]='0'+PC;
		Lcd_DisplayString(4,8,l4);
}

void ISR_T1(void) interrupt 3{
	if(ctr<2){
	Lcd_DisplayString(1,1,"      Pawel     ");
	Lcd_DisplayString(2,1,"   Miksiewicz   ");
	Lcd_DisplayString(3,1,"   WCY21IX3S0   ");
	if(licznik > 5) {licznik--;} else {licznik=30; ctr++;}
	Konwersja(licznik);
	}
	else{
		licznik++;
		if(licznik<=40){
			//><(((º> 
			Lcd_DisplayString(1,1,"   --       --  ");
			Lcd_DisplayString(2,1,"     --  --     ");
			Lcd_DisplayString(3,1,"   --    --   _ ");
			Lcd_DisplayString(4,1,"--    --     | |");
		}
		else if(licznik<=50){
			Lcd_DisplayString(1,1,">     --  --  --");
			Lcd_DisplayString(2,1,"-- --   --  --  ");
			Lcd_DisplayString(3,1,"   --     --  _ ");
			Lcd_DisplayString(4,1,"--      --   | |");
		}
		else if(licznik<=60){
			Lcd_DisplayString(1,1,"*> -- -- --  -- ");
			Lcd_DisplayString(2,1," --     --  --  ");
			Lcd_DisplayString(3,1,"   --     --  _ ");
			Lcd_DisplayString(4,1," --  -- --   | |");
		}
		else if(licznik<=70){
			Lcd_DisplayString(1,1,"(*>  --   --  --");
			Lcd_DisplayString(2,1,"--    --   --   ");
			Lcd_DisplayString(3,1,"    --   --   _ ");
			Lcd_DisplayString(4,1," --    --    | |");
		}
		else if(licznik<=80){
			Lcd_DisplayString(1,1,"((*>    --  --  ");
			Lcd_DisplayString(2,1,"      --   --   ");
			Lcd_DisplayString(3,1,"  --     --   _ ");
			Lcd_DisplayString(4,1,"   --  --    | |");
		}
		else if(licznik<=90){
			Lcd_DisplayString(1,1,"(((*>     --  --");
			Lcd_DisplayString(2,1," --   --     -- ");
			Lcd_DisplayString(3,1,"   --   --    _ ");
			Lcd_DisplayString(4,1," --  --   -- | |");
		}
		else if(licznik<=100){
			Lcd_DisplayString(1,1,"<(((*> --    -- ");
			Lcd_DisplayString(2,1,"--   --   --    ");
			Lcd_DisplayString(3,1,"  -- --   --  _ ");
			Lcd_DisplayString(4,1,"  --   --    | |");
		}
		else if(licznik<=110){
			Lcd_DisplayString(1,1,"><(((*>   --    ");
			Lcd_DisplayString(2,1,"  -- -- --  --  ");
			Lcd_DisplayString(3,1,"  -- --   --  _ ");
			Lcd_DisplayString(4,1,"  --    --   | |");
		}
		else if(licznik<=120){
			Lcd_DisplayString(1,1," ><(((*>      --");
			Lcd_DisplayString(2,1,"--  --    --    ");
			Lcd_DisplayString(3,1,"-- -- --   -- _ ");
			Lcd_DisplayString(4,1,"   --    --  | |");
		}
		else if(licznik<=130){
			Lcd_DisplayString(1,1,"  ><(((*>  --   ");
			Lcd_DisplayString(2,1,"  --      --  --");
			Lcd_DisplayString(3,1,"--   -- --    _ ");
			Lcd_DisplayString(4,1,"   --  --    | |");
		}
		else if(licznik<=140){
			Lcd_DisplayString(1,1," -- --    -- -- ");
			Lcd_DisplayString(2,1,"   ><(((*>  --  ");
			Lcd_DisplayString(3,1,"  --   -- --  _ ");
			Lcd_DisplayString(4,1," -- -- --    | |");
		}
		else if(licznik<=150){
			Lcd_DisplayString(1,1,"   -- --  --    ");
			Lcd_DisplayString(2,1," -- --  -- --   ");
			Lcd_DisplayString(3,1,"--  ><(((*>   _ ");
			Lcd_DisplayString(4,1,"  --    --   | |");
		}
		else if(licznik<=160){
			Lcd_DisplayString(1,1,"-- -- --  --    ");
			Lcd_DisplayString(2,1," -- --  -- --   ");
			Lcd_DisplayString(3,1," -- --   --   _ ");
			Lcd_DisplayString(4,1," --  ><(((*> | |");
		}
		else if(licznik<=170){
			Lcd_DisplayString(1,1," --  -- --  --  ");
			Lcd_DisplayString(2,1," --  -- --  --  ");
			Lcd_DisplayString(3,1," -- --   --   _ ");
			Lcd_DisplayString(4,1,"  --  ><(((*>| |");
		}
		else if(licznik<=180){
			Lcd_DisplayString(1,1," --  -- --  --  ");
			Lcd_DisplayString(2,1,"  --  -- --  -- ");
			Lcd_DisplayString(3,1,"  -- --   --  _ ");
			Lcd_DisplayString(4,1," -- -- ><(((*| |");
		}
		else if(licznik<=190){
			Lcd_DisplayString(1,1,"  --  -- --  -- ");
			Lcd_DisplayString(2,1,"   --  -- --  --");
			Lcd_DisplayString(3,1,"   -- --   -- _ ");
			Lcd_DisplayString(4,1,"-- --   ><(((| |");
		}
		else if(licznik<=200){
			Lcd_DisplayString(1,1,"   --  -- --  --");
			Lcd_DisplayString(2,1,"    --  -- --  -");
			Lcd_DisplayString(3,1,"--  -- --   --_ ");
			Lcd_DisplayString(4,1," -- --   ><((| |");
		}
		else if(licznik<=210){
			Lcd_DisplayString(1,1,"--    --  -- -- ");
			Lcd_DisplayString(2,1,"  --  --  -- -- ");
			Lcd_DisplayString(3,1,"--  -- --   --_ ");
			Lcd_DisplayString(4,1,"-- -- --  ><(| |");
		}
		else if(licznik<=220){
			Lcd_DisplayString(1,1,"  -- -- --  --  ");
			Lcd_DisplayString(2,1,"  --  --  -- -- ");
			Lcd_DisplayString(3,1,"--  -- --   --_ ");
			Lcd_DisplayString(4,1,"  -- -- -- ><| |");
		}
		else if(licznik<=230){
			Lcd_DisplayString(1,1,"  -- -- --  --  ");
			Lcd_DisplayString(2,1,"  --  --  -- -- ");
			Lcd_DisplayString(3,1,"--  -- --   --_ ");
			Lcd_DisplayString(4,1,"-- -- -- -- >| |");
		}
		else if(licznik<=240){
			Lcd_DisplayString(1,1," -- -- -- --  --");
			Lcd_DisplayString(2,1,"--  --  --  -- -");
			Lcd_DisplayString(3,1,"  --  -- -- --_ ");
			Lcd_DisplayString(4,1,"--  -- -- -- | |");
		}
		else {licznik=30; ctr=0; Lcd_DisplayString(4,1,"                ");}
	}
}

void SET_T1_1(void){
	TCON=0x12;
	TH0=TL0=0x00;
	TMOD=TMOD & 0xF0;
	TMOD=TMOD | 0x00;
	ET1=1;
	TR1=1;
}

void main(void){
	
	licznik=30;
	ctr=0;
	LC=PC=0;
	LcdInit();
	SET_T1_1();
	
	EA = 1;
	while(1){
		;
	}
}