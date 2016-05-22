# exercise
To compile:
cd doggy
./autogen.sh
mkdir $HOME/doggy
./configure --prefix=$HOME/doggy
make install

If lazy: cd doggy;./compile.sh

Explicacion:
Implementado el problema base, con las siguientes partes opcionales:
	Testing de la aplicación
	Leer los datos sobre la aplicación a correr (doggy) y otros
  parámetros de un fichero de configuración
	Ser capaces de ejecutar N instancias de la aplicación doggy en
  paralelo.
- Decisión: En el fichero de configuración se incluye el tamaño de fichero de log como unsigned long representando los bytes por simplicidad. Lo óptimo hubiera sido incluir tamaño en K/MB parseando texto.
- Decisión: Hay redefinidas constantes en doggy.h, simulando que es una aplicación de terceros.
- Decisión: Copia de ficheros. POSIX vs funciones no standard incluidas en Linux. Se usa POSIX para asegurar el correcto funcionamiento.
- Decisión: Se decide usar hilos (pthread_create) que creen procesos (fork) y hagan el respawn en caso de caída. Al revés no se puede hacer exec de una imagen.
-Decisión: los logs se escriben en /tmp/ para evitar problemas de permisos. Se podía haber incluido en el fichero de configuración para usar /var/log/doggy, por ejemplo.
- Diseño:
- Aplicación "doggy" para probar el wrapper. Fuentes doggy.c y doggy.h
- Aplicacion "doggy_watcher":
	- Modulo principal: función principal. Fuentes: doggy_watcher.c y doggy_watcher.h.
	- Modulo process: gestión de procesos. Fuentes: doggy_process.h y doggy_process.c
	- Modulo logs: gestionar logs. Fuentes: doggy_watcher_log.c y doggy_watcher_log.h.
	- Modulo parameters: gestión de parametros. Fuentes doggy_watcher_params.c y doggy_watcher_params.h.
	- Modulo común: Código común. Fuente doggy_watcher_constants.h

