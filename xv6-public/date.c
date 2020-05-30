#include "types.h"
#include "user.h"
#include "date.h"

int
main(int argc, char *argv[])
{
  struct rtcdate r;

  if (date(&r)) {
    printf(2, "date failed\n");
    exit();
  }

  // su codigo debe imprimir el tiempo en el formato que desee..
  printf(1, "%d:%d:%d   %d/%d/%d UTC\n",r.hour, r.minute, r.second, r.year, r.month, r.day);
  //Se agrega esta linea para que el comando realice la impresion
  exit();
}
