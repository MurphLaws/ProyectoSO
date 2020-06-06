# ProyectoSO

## Carlos Tovar (1741699), Nicolas Lasso (1740395)


## 1.Imprimir las llamadas al sistema que se llevan a cabo



Siguiendo la idea planteada en [este blog](https://zhuzilin.github.io/6.828-hw-xv6-system-call/),y la base sugerida por el profesor, se crea un archivo `count.c`que trabaja sobre un arreglo con todos los nombres de las distintas llamadas a sistema que imprime todos los llamados que se han hecho a estas si no se ingresa ningun argumento, y el numero de invocaciones de una llamada en especifico, si se ingresa el nombre de ella. Este comando trabaja invocando la llamada count() que retorna el numero de invocaciones que se han hecho a determinada llamada.

```c
int
main(int argc, char *argv[])
{


const char *namesyscalls[] = {
"date",
"fork",
"exit",
"wait",
"pipe",
"read",
"kill",
"exec",
"fstat",
"chdir",
"dup",
"getpid",
"sbrk",
"sleep",
"uptime",
"open",
"write",
"mknod",
"unlink",
"link",
"mkdir",
"close"	,
"count",
	};

 int nsyscall = -1;
 if (argc == 2) {
  nsyscall = atoi(argv[1]);
 }
 if (nsyscall == -1) {
  // mostrar todas las llamadas al sistema
  // con su correspondiente numero de invocaciones
	for(int i = 0; i < 23)
	{
	printf(1, "%s ---> %d \n", namesyscalls[i], count(i);
	} 
	
 } else {
  // mostrar la llamada al sistema dada en nsyscall
  // con su correspondiente numero de invocaciones
	printf(1, "%s ---> %d \n", namesyscalls[nsyscall], count(nsyscall));  
  // Ejemplo de impresion: fork ---> 4
  //                       exit ---> 3
 }
 exit();
}

```



## 2. Escriba el comando uptime

Para escribir el comando `uptime.c`, cuya función es mostrar el tiempo que lleva encendido el sistema hacemos uso de la llamada al sistema `uptime` que devuelve los ciclos del reloj que han habido desde que se inició el sistema. Nos dimos cuenta que la máquina en la que desarrollamos el comando nos daba 4000 ciclos del reloj por cada minuto, entonces hicimos lo siguiente para pasar a formato hh:mm:ss

``` c
  //uptime.c
  #include "types.h"
  #include "user.h"

  int main()
  {
        int time = (60*uptime())/4000;
        int hours = time / 36000;
        int minutes = (time-hours*3600)/60;
        int seconds = time-(hours*3600+minutes*60);
        printf(1, "up  %d:%d:%d\n", hours, minutes, seconds);
        exit();
  }
```

pero surge un inconveniente, y es que los ciclos del reloj no son iguales en todas las máquinas, porque estos se ven afectados por factores del hardware. Cuando se probó el programa anterior en otra máquina arrojó resultados incorrectos y no se encontró la manera de determinar de forma general cuántos ticks del reloj tendría por minuto cada máquina en la que se ejecutara el el comando, por lo que la implementación quedó de la siguiente forma para evitar resultados erroneos 

``` c
  //uptime.c
  #include "types.h"
  #include "user.h"

  int main()
  {
        printf(1, "up %d clock ticks\n", uptime());
        exit();
  }
```


## 3. Escriba el comando date           

Para escribir el comando `date.c`, cuya funcion es mostrar la hora actual del sistema en formato horas:minutos:segundos año\mes\dia UCT, se creo la llamada al sitema `date`. Para esto se modificaron los siguientes archivos, con las lineas descritas a continuacion:  

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
   argptr(0, (void*)&r, sizeof(&r));
   cmostime(r);
   return 0;
  }
  
  
  //user.h
  int date(struct rtcdate*);
  
  
  //usys.S
  SYSCALL(date)

    
```
Todos estos pasos son necesarios a la hora de crear una nueva llamada al sistema y se repiten en el punto 4. Ademas, se contaba con una estructura en el arhivo `date.h`que se utilizo para almacenar la hora actual del sistema y su posterior impresion. 

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
  printf(1, "%d:%d:%d   %d/%d/%d UCT\n",r.hour, r.minute, r.second, r.year, r.month, r.day);
  //Se agrega esta linea para que el comando realice la impresion
  exit();
}

```


## 4. Llamada al sistema que permita mostrar el número de invocaciones que una llamada al sistema ha tenido
          

Para crear esta nueva llamada al sistema, se deben modificar los siguientes archivos, de la siguiente manera.

``` c
  //syscall.c
  extern int sys_count(void);
  
  [SYS_count]    sys_count,
  
  //syscal.h
  #define SYS_count  23
  
  
  //sysproc.c
  int
  sys_count(void)
  {
    int n;
    argint(0, &n);
    return getCount(n);
  }
  
  
  //user.h
  int count(int);
  
  
  //usys.S
  SYSCALL(count)
  
 ```
 
 
Ademas, se debe modificar el archivo `defs.h` para agregar una nueva linea, pues para esta llamada al sistema dispondremos de una nueva funcion que nos retorna el numero de invocaciones de una determinada llamada.

```c
// syscall.c
int             argint(int, int*);
int             argptr(int, char**, int);
int             argstr(int, char**);
int             fetchint(uint, int*);
int             fetchstr(uint, char**);
void            syscall(void);
int 		getCount(int); nuvea linea


```

Luego, en el archivo `syscall.c` se crea un arreglo inicializado en ceros que almacenara el numero de invocaciones de cada llamada. Ademas, se crea la funcion getCount que retorna el valor dentro de ese arreglo.

```c

int numCalls[23] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int getCount(int k){
   return numCalls[k-1];
}

```

Y por ultimo, se agrega una nueva linea a la funcion syscall, que aumentara el numero de cada llamada al sistema

```c

void
syscall(void)
{
  int num;
  struct proc *curproc = myproc();

  num = curproc->tf->eax;
  if(num > 0 && num < NELEM(syscalls) && syscalls[num]){
    curproc->tf->eax = syscalls[num]();
    numCalls[num]++; // Nueva linea
  } else {
    cprintf("%d %s: unknown sys call %d\n",
            curproc->pid, curproc->name, num);
    curproc->tf->eax = -1;
  }
}


```

# Se usaron los siguientes recursos para la realizacion del proyecto.

Como crear un llamado para imprimir las llamadas a sistema: https://zhuzilin.github.io/6.828-hw-xv6-system-call/

Como crear una llamada al sistema en XV6:https://arjunkrishnababu96.gitlab.io/post/xv6-system-call/

Como obtener el tiempo del sistema:https://pdos.csail.mit.edu/6.828/2019/labs/util.html

Como pasar una estructura a una llamada del sistema:https://stackoverflow.com/questions/53383938/pass-struct-to-xv6-system-call
