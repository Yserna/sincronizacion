#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main(void){
  char buffer[30];
  struct timeval tv, ti, tf;
  time_t curtime;
  double tiempo;

  gettimeofday(&tv, NULL); 
  curtime = tv.tv_sec;

  strftime(buffer, 30,"%m-%d-%Y  %T.",localtime(&curtime));
  printf("Current date and time: %s%ld\n", buffer, tv.tv_usec);

  gettimeofday(&ti, NULL);   // Instante inicial
  printf("Presiona ENTER\n");
  getchar();
  gettimeofday(&tf, NULL);   // Instante final
  tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
  printf("Has tardado: %g milisegundos\n", tiempo);

  return 0;
}