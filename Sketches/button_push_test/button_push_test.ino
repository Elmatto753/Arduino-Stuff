/* YourDuino.com Example Software Sketch
 TEST LCD Display with Pushbuttons
 Based on code by Mark Bramwell and debouncing by peterstrobl
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <LiquidCrystal.h>

/*-----( Declare objects )-----*/
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //These are the pins used on this shield

/*-----( Declare Constants )-----*/
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define PAGEMAX   2

typedef struct MOVE {

  char Name[ ];
  byte Power;
  byte Accuracy;
  
}Move;

typedef struct MOVESET {

  Move firstMove;

  Move secondMove;

  Move thirdMove;

  Move fourthMove;
  
}Moveset;

/*-----( Declare Variables )-----*/
int lcd_key       = 0;
int adc_key_in    = 0;
int adc_key_prev  = 0;
byte rowSelected   = 0;
byte page          = 1;
Moveset Moves;

/*-----( Temporary things, should be provided by other sections of project )----*/




void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  lcd.begin(16, 2);              // start the lcd object
  
  lcd.setCursor(0,0);
  lcd.print("kek");
  lcd.setCursor(14,0);
  lcd.print("<-");

  lcd.setCursor(0,1);
  lcd.print("top kek");
  
  //lcd.setCursor(10,1);
  //lcd.print("A="); // For display of A0 Analog values from button push
  
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  //lcd.setCursor(7,1);            // move cursor to second line "1" and 7 spaces over
  //lcd.print(millis()/1000);      // display seconds elapsed since power-up

  adc_key_prev = lcd_key ;       // Looking for changes
  lcd_key = read_LCD_buttons();  // read the buttons

//  if (adc_key_prev != lcd_key)
//  {
//    lcd.setCursor(12,1); 
//    lcd.print("    ");         // Blank, display returned Analog value of button
//    lcd.setCursor(12,1); 
//    lcd.print(adc_key_in); 
//  }

//  lcd.setCursor(0,1);            // move to the begining of the second line

  
  getMoveSet(Moves);
  
  if (lcd_key==btnDOWN)               // depending on which button was pushed, we perform an action
  {
    lcd.setCursor(14,rowSelected);
    lcd.print("  ");
    if(rowSelected == 1)
    {
      switchPage();
    }
    switchRow();
    lcd.setCursor(14,rowSelected);
    lcd.print("<-");
    delay(300);
  }

  else if (lcd_key == btnUP)
  {
    lcd.setCursor(14,rowSelected);
    lcd.print("  ");
    if(rowSelected == 0)
    {
      switchPage();
    }
    switchRow();
    lcd.setCursor(14,rowSelected);
    lcd.print("<-");
    delay(300);
  }

  else if (lcd_key == btnSELECT)
  {
    page=0;
    lcd.setCursor(0,rowSelected);
    lcd.print("                ");
    lcd.setCursor(0,rowSelected);
    lcd.print("Selected!");
  }

  if (page==1)
  {
  lcd.setCursor(0,0);
  lcd.print(Moves.firstMove.Name[14]);
  lcd.setCursor(14,0);
  
  lcd.setCursor(0,1);
  lcd.print(Moves.firstMove.Name[14]);
  }

  else if(page == 2)
  {
  lcd.setCursor(0,0);
  lcd.print("Fire Bomb");
  lcd.setCursor(14,0);

  lcd.setCursor(0,1);
  lcd.print("Tackle");
  }

  else
  {
    
  }
  
//  case btnUP:
//    {
//      lcd.print("UP    ");
//      break;
//    }
//  case btnDOWN:
//    {
//      lcd.print("DOWN  ");
//      break;
//    }
//  case btnSELECT:
//    {
//      lcd.print("SELECT");
//      break;
//    }
//  case btnNONE:
//    {
//      lcd.print("NONE  ");
//      break;
//    }
}/* --(end switch )-- */

/* --(end main loop )-- */

/*-----( Declare User-written Functions )-----*/

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor 
  delay(5); //switch debounce delay. Increase this delay if incorrect switch selections are returned.
  int k = (analogRead(0) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
  if (5 < abs(k)) return btnNONE;  // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 195)  return btnUP; 
  if (adc_key_in < 380)  return btnDOWN; 
  if (adc_key_in < 555)  return btnLEFT; 
  if (adc_key_in < 790)  return btnSELECT;   
  return btnNONE;  // when all others fail, return this...
}

void switchRow()
{
  if(rowSelected==0)
  {
    rowSelected=1;
  }
  else
  {
    rowSelected=0;
  }
}

void switchPage()
{
  lcd.setCursor(0,0);
  lcd.print("              ");
  lcd.setCursor(0,1);
  lcd.print("              ");
  if(page==PAGEMAX)
  {
    page=1;
  }
  else
  {
    page+=1;
  }
}

void getMoveSet(Moveset Moves)
{
  char MoveName1[ ] = {"Fire Blast"};
  char MoveName2[ ] = {"Pound"};
  char MoveName3[ ] = {"Fire Bomb"};
  char MoveName4[ ] = {"Tackle"};
  Moves.firstMove.Name[14]=*MoveName1;
  Moves.secondMove.Name[14]=*MoveName2;
  Moves.thirdMove.Name[14]=*MoveName3;
  Moves.fourthMove.Name[14]=*MoveName4;
  
}











// Base code found at https://arduino-info.wikispaces.com/LCD-Pushbuttons
