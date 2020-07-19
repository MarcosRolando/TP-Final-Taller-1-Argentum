# Manual de Usuario



### <u>Instalación</u>:

#### Requerimientos de Software

A continuación se lista el software requerido para poder utilizar tanto el servidor como cliente:

- SDL2 
- SDL2
- SDL2 
- SDL2 ttf 
- msgpack

#### Requerimientos de Hardware

#### Proceso de Instalación

Antes de poder instalar el juego se deben instalar las librerías de SDL2 y msgpack.

Para instalar lo necesario de SDL2 se deben ejecutar los siguientes comandos por consola:

- `$ sudo apt-get install libsdl2-dev`
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

Una vez instalado el juego podemos correr el servidor y cliente con los comandos *argentumServer* y *argentumClient* respectivamente.



### <u>Configuración:</u>

El proyecto dispone de un archivo de configuración de formato JSON ubicado  en */etc/Argentum/config.json* . Como el archivo se encuentra en /etc/ se necesitan permisos de root para poder editarlo. Para esto podemos usar el comando:

`$ sudo -i vim /etc/Argentum/config.json`

Se puede utilizar otro editor de texto en lugar de vim.

En el archivo podemos editar las estadísticas de razas, clases, monstruos e items. Ademas se pueden editar parámetros mas relacionados con la jugabilidad como la experiencia obtenida, la cantidad de monstruos en el mapa, el nivel de newbie entre otros. Por ultimo, se puede editar el puerto donde escuchara el servidor.



### <u>Forma de Uso:</u>	

1. #### Servidor

   El servidor se ejecuta con el comando

   `$ argentumServer`

   Durante su ejecución el servidor escuchara conexiones en el puerto especificado en el archivo de configuración. 

   Para terminar la ejecución del servidor se deberá presionar la tecla 'q' en la consola donde se haya ejecutado el comando.

2. #### Cliente 

   El cliente se ejecuta con el comando 

   `$ argentumClient`

   El juego comienza con el menú principal. Primero debemos elegir si queremos crear o cargar un jugador:

   ![SelectScreen](/home/ivan/Documents/UBA/Taller/Argentum/UserManual/img/SelectScreen.png)

   ##### Crear jugador

   Al crear un jugador debemos elegir su nickname (no puede contener espacios), su clase y su raza. 

   ![CreatePlayer](/home/ivan/Documents/UBA/Taller/Argentum/UserManual/img/CreatePlayer.png)

   ##### Cargar jugador

   Para cargar un jugador solo tenemos que ingresar su nickname.

   ![LoadPlayer](/home/ivan/Documents/UBA/Taller/Argentum/UserManual/img/LoadPlayer.png)

   

   

   ##### Conexión

   Luego de cargar/crear un jugador se muestra la pantalla de conexión donde debemos elegir el host y port al que nos queremos conectar.

![Connection](/home/ivan/Documents/UBA/Taller/Argentum/UserManual/img/Connection.png)

##### 	

Si logramos conectarnos empieza el juego en si. 

![Game](/home/ivan/Documents/UBA/Taller/Argentum/UserManual/img/Game.png)

##### Minichat

En el minichat se podrán leer los mensajes relevantes recibidos por el server (daño causado o recibido, ataques esquivados o críticos y mensajes de otros jugadores) y también se podrán ingresar los siguientes comandos:

- ###### /meditate: 

  Si el jugador no es un guerrero comenzara a meditar.

- ###### /revive

  Si el jugador esta muerto, revivirá al lado del cura mas cercano luego de unos segundos. Si se ingresa el comando habiendo seleccionado a un cura el jugador revivirá inmediatamente.

- ###### /heal

  Se debe haber seleccionado a un cura. En tal caso el jugador recuperara toda su vida y mana.

- ###### /deposit \<item>

  Se debe haber seleccionado a un banquero. En tal caso se deposita el item en el banco para poder retirarlo en otro momento.

- ###### /deposit \<Gold> \<cantidad>

  Se debe haber seleccionado a un banquero. En tal caso se depositara la cantidad de oro especificada.

- ###### /withdraw \<item>

  Se debe haber seleccionado a un banquero. En tal caso se retira del banco el item especificado.

- ###### /withdraw \<Gold> \<cantidad>

  Se debe haber seleccionado a un banquero. En tal caso se retira la cantidad de oro especificada.

- ###### /list

  Si tengo seleccionado a un cura o comerciante me mostrara los items que tiene en su inventario junto con su precio. Si tengo seleccionado a un banquero me mostrara los items que tengo depositados en el banco

- ###### /buy \<item>

  Debo haber seleccionado a un cura o comerciante. En tal caso se intenta comprar el item especificado.

- ###### /sell \<item>

  Debo haber seleccionado a un cura o comerciante. En tal caso intenta vender el item especificado.

- ###### /take

  Toma el item sobre el que esta parado el jugador

- ###### /drop

  Tira el item que se encuentra en la posición seleccionada del inventario

- ###### /inventory

  Lista las cosas que tengo en el inventario

- ###### /clear

  Limpia el minichat

##### Información del jugador

Aqui se muestran las estadisticas de vida, mana y experiencia del jugador

##### Inventario



##### Stats



