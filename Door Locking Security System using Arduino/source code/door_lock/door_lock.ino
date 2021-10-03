

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;
int pos=0; // LCD Connections
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
const byte rows=4;
const byte cols=4;
char Tem[5];
int j=0,flag=0,l=0;
char *passWords[] = {"0045", "0119", "0141",
                     "0021", "0046", "0144" ,"0044"
                    };
char *Names[] = {"Acccess SHUBHAM ", "Acccess HARSHIL", "Acccess VIRAJ",
                     "Acccess DRASHTI", "Acccess  NUPUR", "Acccess SHIKHAA", "Acccess VISHWA"
                    };
char key[rows][cols]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[rows]={4,5,6,7};
byte colPins[cols]={8,9,10,12};

Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="4567";
int currentposition=0;
int redled=10;
int greenled=11;
int buzz=11;
int invalidcount=0;
 
 
void setup()
{
displayscreen();
Serial.begin(9600);
pinMode(redled, OUTPUT);
pinMode(greenled, OUTPUT);
pinMode(buzz, OUTPUT);
noTone(buzz);
myservo.attach(3); //SERVO ATTACHED//
digitalWrite(11,LOW);
lcd.begin(16,2);

}
void loop()
{
  flag=0;
  if( currentposition==0)
  {
    displayscreen();
  }
  char code=keypad.getKey();
  if(code)
  {
    Tem[currentposition] = code;
    currentposition++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PASSWORD:");
    lcd.setCursor(7,1);
    lcd.print(" ");
    lcd.setCursor(7,1);
    for(l=0;l<currentposition;l++)
    {
      lcd.print("*");
      keypress(); 
    }
    if (currentposition==4)
    {
                for(int i=0;i<7;i++)
                {
                    if(strcmp(Tem,passWords[i])==0)
                    {
                       unlockdoor(i);
                       flag=1;
                       break;
                    }    
                }
                if(flag==1)
                {
                    currentposition=0;
                }
                else if(flag==0)
                {
                    ++invalidcount;
                    incorrect();
                    currentposition=0;
                }
      }
   }
  if(invalidcount==5)
  {
      ++invalidcount;
      torture1(); 
  }
  if(invalidcount==8)
  {
    invalidcount = 0;
    torture2();
  }
 
}
 
//********OPEN THE DOOR FUNCTION!!!!***********//
 
void unlockdoor(int k)
{
delay(900);
 
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,0);
lcd.print(Names[k]);
lcd.setCursor(0,1);
lcd.println("WELCOME HOME");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");

 
for(pos = 180; pos>=0; pos-=5) // goes from 180 degrees to 0 degrees
{
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(5); // waits 15ms for the servo to reach the position
}
unlockbuzz2();
unlockbuzz2();
delay(3000);
 
//delay(1000);
counterbeep();
 
delay(1000);
 
for(pos = 0; pos <= 180; pos +=5) // goes from 0 degrees to 180 degrees
{ // in steps of 1 degree
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15);
 
 
currentposition=0;
 
lcd.clear();
displayscreen();
 
}

}
 
//************WRONG CODE FUNCTION********//
 
void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("WRONG");
lcd.setCursor(5,0);
lcd.print(" PASSWORD");
lcd.setCursor(15,1);
lcd.println(" ");

lcd.setCursor(0,1);
lcd.println("Access Denied");
 
lcd.setCursor(13,1);
lcd.println(" ");

digitalWrite(redled, HIGH);
//digitalWrite(buzz, HIGH);
unlockbuzz();
delay(3000);
lcd.clear();
digitalWrite(redled, LOW);
//digitalWrite(buzz,LOW);
displayscreen();
}
//************** CLEAR THE SCREEN!!!*************//
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
}
//**************KEYPRESS********************//
void keypress()
{
//digitalWrite(buzz, HIGH);
//delay(50);
//digitalWrite(buzz, LOW);
}
//********DISPALAY FUNCTION!!!*************//OK
void displayscreen()
{
 
lcd.setCursor(1,0);
lcd.println("ENTER PASSWORD   ");
lcd.setCursor(1,1);
lcd.println("For Getting In   ");

}
void armservo()
{
 
for (pos=180;pos<=180;pos+=50)
{
myservo.write(pos);
delay(5);
//*************** ARM SERVO***********//
}

delay(5000);
 
for(pos=180;pos>=0;pos-=50)
{
myservo.write(pos);
}
 
}
//**********UNLOCK BUZZ*************//
void unlockbuzz()
{
 
//digitalWrite(buzz, HIGH);
//delay(80);
//digitalWrite(buzz, LOW);
//delay(80);
//digitalWrite(buzz, HIGH);
//delay(80);
//digitalWrite(buzz, LOW);
//delay(200);
//digitalWrite(buzz, HIGH);
//delay(80);
//digitalWrite(buzz, LOW);
//delay(80);
//digitalWrite(buzz, HIGH);
//delay(80);
//digitalWrite(buzz, LOW);
//delay(80);
tone(buzz,700);

delay(3000);
noTone(buzz);

}
void unlockbuzz2()
{
 
tone(buzz,700);

delay(50);
noTone(buzz);

delay(50);

noTone(buzz);

delay(50);

}
 
//**********COUNTER BEEP**********//
void counterbeep()
{
delay(1200);
 
lcd.clear();
//digitalWrite(buzz, HIGH);
 
lcd.setCursor(1,15);
lcd.println(" ");
lcd.setCursor(1,14);
lcd.println(" ");
lcd.setCursor(1,0);
delay(200);
lcd.println("GET IN WITHIN :");


lcd.setCursor(4,1);
lcd.print("5");
delay(1000);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
//digitalWrite(buzz,LOW);
//delay(1000);
//digitalWrite(buzz, HIGH);
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(1000);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
//digitalWrite(buzz,LOW);
//delay(1000);
//3
//digitalWrite(buzz, HIGH);
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //3
lcd.print("3");
delay(1000);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
//digitalWrite(buzz,LOW);
//delay(1000);
//4
//digitalWrite(buzz, HIGH);
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //4
lcd.print("2");
delay(1000);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
//digitalWrite(buzz,LOW);
//delay(1000);
//
//digitalWrite(buzz, HIGH);
lcd.setCursor(4,1);
lcd.print("1");
delay(1000);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN::");
//digitalWrite(buzz,LOW);
//delay(1000);
//5
//digitalWrite(buzz, HIGH);
//delay(40);
//digitalWrite(buzz,LOW);
//delay(40);
//digitalWrite(buzz, HIGH);
//delay(40);
//digitalWrite(buzz,LOW);
//delay(40);
//digitalWrite(buzz, HIGH);
//delay(40);
//digitalWrite(buzz,LOW);
//delay(40);
//digitalWrite(buzz, HIGH);
//delay(40);
//digitalWrite(buzz,LOW);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("LOCKED NOW ");
delay(440);
}
//*********TORTURE1***********//
void torture1()
{
delay(1000);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("WAIT FOR ");
lcd.setCursor(5,1);

lcd.print("15 SECONDS");
//digitalWrite(buzz, HIGH);
delay(15000);
//digitalWrite(buzz, LOW);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("LOL..");
lcd.setCursor(1,1);
lcd.print(" HOW WAS THAT??");
delay(3500);
lcd.clear();
 
}
//*****TORTURE2*****//
void torture2()
{
delay(1000);
lcd.setCursor(1,0);
lcd.print(" ");
lcd.setCursor(2,0);
lcd.print("EAR DRUMS ARE");
lcd.setCursor(0,1);
lcd.print(" PRECIOUS!! ");
delay(1500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print(" WAIT FOR");
lcd.setCursor(4,1);
lcd.print(" 1 MINUTE");
//digitalWrite(buzz, HIGH);
tone(buzz,450);
delay(5000);
counterbeep();
lcd.clear();
//digitalWrite(buzz, LOW);
noTone(buzz);
lcd.setCursor(2,0);
lcd.print("WANT ME TO");
lcd.setCursor(1,1);
lcd.print("REDICULE MORE??");
delay(2500);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("Ha Ha Ha Ha");
delay(1700);
lcd.clear();
}
