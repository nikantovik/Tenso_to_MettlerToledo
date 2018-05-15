#include <mbed.h>

Timer t;
char ReadCom;
char ves[20];
int count_char=0;

int main()
{
  Serial device(PA_2, PA_3,9600); // tx, rx
  Serial HP25(PA_9, PA_10,9600);  // tx, rx

  t.start ();
  while(1) {
    if(device.readable()) {
      ReadCom=device.getc();
      ves[count_char]= ReadCom;
      count_char++;
      if (ReadCom=='%' || ReadCom=='$') {
        if (ReadCom=='$')  HP25.puts ("S S     ");
        if (ReadCom=='%')  HP25.puts ("S D     ");
        for (size_t i = 3; i < 8; i++) { // Выводим вес в сом порт
          HP25.putc(ves[i]);
        }
        HP25.puts("0 kg");
        count_char=0;
        HP25.putc (13); HP25.putc(10);
      }
    }
    if (t.read()>=0.2) {  // запрос веса по протоколу 6.43 (см. Documents)
      device.putc (0x10);
      t.reset();
    }
  }
}
