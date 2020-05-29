# ProyectoSO




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
  printf(1, "%d-%d-%d %d:%d:%d\n", r.year, r.month, r.day, r.hour-5, r.minute, r.second); 
  //Se agrega esta linea para que el comando realice la impresion
  exit();
}

```

Idea de usar grep para ver los archivos a modificar y cmostime()
https://pdos.csail.mit.edu/6.828/2019/labs/util.html

Idea de usar el metodo argptr  
https://stackoverflow.com/questions/53383938/pass-struct-to-xv6-system-call
