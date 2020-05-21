#include <wiringPi.h>
#include <iostream>
#include <sys/time.h>
using namespace std;

  int CM;
  long CZAS;
  int trig = 4;
  int echo = 1;
  void pomiar_odleglosci();
  int pulseIn(int pin, int level);


int main (void)
{
 wiringPiSetup ();

 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);

 cout <<"Test czujnika odleglosci"<<endl<<endl;

 while(1)
 {
  pomiar_odleglosci();              //pomiar odległości
  cout<<"Odleglosc: ";      //wyświetlanie wyników na ekranie w pętli co 200 ms
  cout<<CM<<" cm"<<endl;
  delay(200);
 }
  return 0 ;
}

void pomiar_odleglosci ()
{
  digitalWrite(trig, HIGH);       //ustawienie stanu wysokiego na 10 uS - impul$
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  CZAS = pulseIn(echo, HIGH);
  CM = CZAS / 58;                //szerokość odbitego impulsu w uS podzielone p$
}

int pulseIn(int pin, int level)  //funkcja mierząca czas do osiągnięcia danego $
{
   struct timeval tn, t0, t1;
   long micros;
   gettimeofday(&t0, NULL);
   micros = 0;

   while (digitalRead(pin) != level)
   {
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;

      micros += (tn.tv_usec - t0.tv_usec);

      if (micros > 10000) return 0;
   }

   gettimeofday(&t1, NULL);

   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;

      micros = micros + (tn.tv_usec - t0.tv_usec);

      if (micros > 10000) return 0;
   }

   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);

   return micros;
}
