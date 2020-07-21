### <u>Instalación</u>:

#### Requerimientos de Software

A continuación se lista el software requerido para poder utilizar el programa:

- SDL2 (cliente)
- SDL2 Image (cliente)
- SDL2 Mixer (cliente)
- SDL2 TTF (cliente)
- msgpack (cliente y servidor)



#### Proceso de Instalación

Antes de poder instalar el juego se deben instalar las librerías de SDL2 y msgpack.

Para instalar lo necesario de SDL2 se deben ejecutar los siguientes comandos por consola:

- `$ sudo apt-get install libsdl2-dev`
- `$ sudo apt-get install libsdl2-image-dev`
- `$ sudo apt-get install libsdl2-mixer-dev`
- `$ sudo apt-get install libsdl2-ttf-dev`

Para instalar msgpack primero debemos instalar las boost libraries con el siguiente comando:

​	`$ sudo apt-get install libboost-all-dev`

Luego, para instalar msgpack en sí:

​	`$ git clone https://github.com/msgpack/msgpack-c.git`

​	`$ cd msgpack-c`

​	`$ git checkout cpp_master`

​	`$ cmake -DMSGPACK_CXX[11]=ON`

​	`$ sudo make install`

Una vez instalado todo podemos pasar a la instalación del juego. En la carpeta del proyecto, creamos una nueva carpeta "build" y dentro de dicha carpeta abrimos la consola y ejecutamos:

​	`$ cmake ..`

​	`$ make`

​	`$ sudo make install`

Una vez instalado el juego podemos correr el servidor y cliente con los comandos 
*sudo argentumServer* y *argentumClient* respectivamente.
