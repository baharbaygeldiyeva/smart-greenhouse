#include <elapsedMillis.h>

#define mot1 2
#define mot2 3

#define suSeviye 4

#define yesil 5
#define kirmizi 6

byte sulamaDurum = 0;

elapsedMillis blSend = 0;

void setup()c:\Users\Bahar\OneDrive\Desktop\AKILLI SERA\toprak\toprak.ino
{
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);

  pinMode(yesil, OUTPUT);
  pinMode(kirmizi, OUTPUT);

  pinMode(suSeviye, INPUT_PULLUP);
  digitalWrite(mot1, LOW);
  digitalWrite(mot2, LOW);

  Serial.begin(9600);
}


void loop()
{
  //-------------------------------------
  int toprakNemDeger = analogRead(A0);
  if (toprakNemDeger > 550)sula();
  if (toprakNemDeger < 250 && sulamaDurum == 0)sulama();
  //-----------------------------------
  if (digitalRead(suSeviye) == HIGH)
  {
    digitalWrite(kirmizi, HIGH);
    digitalWrite(yesil, LOW);
  }
  else
  {
    digitalWrite(kirmizi, LOW);
    digitalWrite(yesil, HIGH);
  }
  //-------------------------------------
  long toplam = 0;
  int okunan = 0;
  for (byte i = 0; i < 50; i++)
  {
    okunan = analogRead(A1);
    toplam += okunan;
  }
  okunan = toplam / 50;

  byte sicaklik = ((5000.0 / 1023) * okunan) / 10;
  if (blSend > 1000)
  {
    Serial.write(sicaklik);
    blSend = 0;
  }
  //------------------------------------
  if (Serial.available())
  {
    char gelen = Serial.read();
    if (gelen == 'S')
    {c:\Users\Bahar\OneDrive\Desktop\AKILLI SERA\proje\proje.ino
      sulamaDurum = 1;
      sula();
    }
    if (gelen == 'F')
    {
      sulamaDurum = 0;
      sulama();
    }
  }
}
//-----------------------------------
void sula()
{
  digitalWrite(mot1, HIGH);
  digitalWrite(mot2, LOW);
}

void sulama()
{
  digitalWrite(mot1, LOW);
  digitalWrite(mot2, LOW);
}
//------------------------------------
