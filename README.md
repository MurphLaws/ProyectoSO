# ProyectoSO


## 1. Escriba el comando uptime



## 2. Escriba el comando date           

Para escribir el comando `date.c`, cuya funcion es mostrar la hora actual del sistema en formato horas:minutos:segundos año\mes\dia UCT, se creo la llamada al sitema `date`. Para esto se modificaron los siguientes archivos, con las lieas descritas a continuacion:  

``` c
  //syscall.c
  extern int sys_date(void);
  
  [SYS_date]    sys_date,
  
  //syscal.h
  #define SYS_date   22
  
  
  //sysproc.c
  int
  sys_date(void)
  {
   struct rtcdate *r;
   argptr(0, (void*)&r, sizeof(&r))
   cmostime(r);
   return 0;
  }
  
  
  //user.h
  int date(struct rtcdate*);
  
  
  //usys.S
  SYSCALL(date)

    
```

Ademas, se contaba con una estructura en el arhivo `date.h`que se utilizo para almacenar la hora actual del sistema y su posterior impresion. 

```c
struct rtcdate {
  uint second;
  uint minute;
  uint hour;
  uint day;
  uint month;
  uint year;
};


```

Por utlimo se crea el archivo `date.c` en el que se imprimen los datos de la estructura con un formato especifico.

```c
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
  printf(1, "%d:%d:%d   %d/%d/%d\n",r.hour-5, r.minute, r.second, r.year, r.month, r.day);
  //Se agrega esta linea para que el comando realice la impresion
  exit();
}

```
# Se usaron los siguientes recursos para la realizacion del proyecto.

Como crear una llamada al sistema en XV6:https://arjunkrishnababu96.gitlab.io/post/xv6-system-call/

Como obtener el tiempo del sistema:https://pdos.csail.mit.edu/6.828/2019/labs/util.html

Como pasar una estructura a una llamada del sistema:https://stackoverflow.com/questions/53383938/pass-struct-to-xv6-system-call
