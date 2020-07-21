# Manual de Usuario



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



### <u>Configuración:</u>

El proyecto dispone de un archivo de configuración de formato JSON ubicado  en 
*/etc/Argentum/config.json* . Como el archivo se encuentra en /etc/ una vez instalado 
se necesitan permisos de root para poder editarlo, sin embargo si se utiliza el 
instalador nuevamente se sobrescribirá el archivo con el del repositorio, por lo 
que se recomienda editarlo dentro de este y luego reinstalar. Si se quiere modificar el 
archivo en directamente en etc para no reinstalar podemos usar el comando:

`$ sudo -i vim /etc/Argentum/config.json`

Se puede utilizar otro editor de texto en lugar de vim.

En el archivo podemos editar las estadísticas de razas, clases, monstruos e items. 
Ademas se pueden editar parámetros mas relacionados con la jugabilidad como la 
experiencia obtenida, la cantidad de monstruos en el mapa, el nivel de newbie 
entre otros. Por ultimo, se puede editar el puerto donde escuchara el servidor que es 8081 por defecto.

A continuación se explican en que afectan algunos valores del archivo cuya función puede no estar tan clara:

- **Price:** Cada item tiene un precio base, pero los npcs pueden venderlos a un precio mayor.
- **GoldModifiers:**
  - MinRange y MaxRange: Definen un rango del cual se toma un numero random que actúa como factor en la ecuación que calcula el oro que dropea un npc al morir.
  - MaxSafeGoldFactor y MaxGoldLevelModifier: Valores que se utilizan en la ecuación para calcular el oro seguro de un jugador. Vale aclarar que MaxGoldLevelModifier estará en el exponente así que tendrá mas peso en la ecuación.
- **XPModifiers:**
  - NextLevelFactor y NextLevelModifier: Valores que se utilizan en la ecuación para calcular la cantidad de experiencia necesaria para subir de nivel. Vale aclarar que NextLevelModifier estará en el exponente así que tendrá mas peso en la ecuación.
  - MinKillXPModifier y MaxKillXPModifier: Definen un rango del cual se toma un numero random que actúa como factor en la ecuación que calcula la experiencia que gano al matar a otro npc o jugador.
  - AttackXPModifier y KillXPModifier: Modifican un factor de la ecuación que calcula cuanta experiencia gano al atacar o matar a un npc o jugador.
- **MonsterSpawnData:**
  - MaxAmount: Máxima cantidad de monstruos en el mapa.
  - TimeBetweenSpawns: Tiempo entre repoblación del mapa (en milisegundos).
  - SpawnAmount: Máxima cantidad de monstruos que spawnean en cada repoblación.
- **TimeForPlayerRecoveryInSeconds:** Tiempo que tarda el jugador en recuperar una cierta cantidad de vida o mana.



### <u>Forma de Uso:</u>	

1. #### Servidor

El servidor se ejecuta con el comando

`$ sudo argentumServer`

Durante su ejecución el servidor escuchara conexiones en el puerto especificado 
en el archivo de configuración. 

Para terminar la ejecución del servidor se deberá presionar la tecla 'q' en 
la consola donde se haya ejecutado el comando.

1. #### Cliente 

El cliente se ejecuta con el comando 

`$ argentumClient`

El juego comienza con el menú principal. Primero debemos elegir si queremos crear 
o cargar un jugador:


![SelectScreen](/Informe/img/SelectScreen.png)

#### Crear jugador

Al crear un jugador debemos elegir su nickname (no puede contener espacios), su 
clase y su raza. El nickname debe ser nuevo.

![CreatePlayer](/Informe/img/CreatePlayer.png)

#### Cargar jugador

Para cargar un jugador solo tenemos que ingresar su nickname, que debe pertenecer 
a un jugador existente.

![LoadPlayer](/Informe/img/LoadPlayer.png)


#### Conexión

Luego de cargar/crear un jugador se muestra la pantalla de conexión donde debemos 
elegir el host y port al que nos queremos conectar. Si se quiere conectar en la misma 
pc que ejecuta el servidor entonces se debe escribir "localhost" en el lugar de host. 

![Connection](/Informe/img/Connection.png)

##### 	

Si logramos conectarnos empieza el juego en si. 

![Game](/Informe/img/game.png)

*Aclaracion: En la primera posicion del inventario se ve una ElvenFlute. Lamentablemente si uno se equipara dicho item no lo vería equipado en el jugador ya que no encontramos la imagen correspondiente.

#### Minichat

![minichat](/Informe/img/minichat.png)

En el minichat se podrán leer los mensajes relevantes recibidos por el server 
(daño causado o recibido, ataques esquivados o críticos y mensajes de otros jugadores). 
Ademas, al hacer click en el minichat podrán ingresar los siguientes comandos:

- ###### /meditate: 

  Si el jugador no es un guerrero comenzara a meditar.

- ###### /revive

  Si el jugador esta muerto, revivirá al lado del cura mas cercano luego de unos
   segundos (la duración depende de la distancia a dicho cura). Si se ingresa el 
   comando habiendo seleccionado a un cura el jugador revivirá inmediatamente.

- ###### /heal

  Se debe tener seleccionado a un cura. En tal caso el jugador recuperara toda su vida y mana.

- ###### /deposit \<item>

  Se debe tener seleccionado a un banquero. En tal caso se deposita el item 
  (si es que se encuentra en el inventario y no está equipado) en el banco para 
  poder retirarlo en otro momento.

- ###### /deposit \<Gold> \<cantidad>

  Se debe tener seleccionado a un banquero. En tal caso se depositara la cantidad 
  de oro especificada (si se tiene una cantidad mayor o igual de oro).

- ###### /withdraw \<item>

  Se debe tener seleccionado a un banquero. En tal caso se retira del banco el 
  item especificado (si es que estaba guardado previamente).

- ###### /withdraw \<Gold> \<cantidad>

  Se debe tener seleccionado a un banquero. En tal caso se retira la cantidad 
  de oro especificada (si es que el banco tiene una cantidad mayor o igual a la pedida).

- ###### /list

  Si tengo seleccionado a un cura o comerciante me mostrara los items que tiene 
  en su inventario junto con su precio. Si tengo seleccionado a un banquero me 
  mostrara los items que tengo depositados en el banco. Si tengo seleccionado un 
  tile sin un personaje mostrara los items en ese tile.

- ###### /buy \<item>

  Debo tener seleccionado a un cura o comerciante. En tal caso se intenta comprar 
  el item especificado.

- ###### /sell \<item>

  Debo tener seleccionado a un cura o comerciante. En tal caso intenta vender 
  el item especificado.

- ###### /take

  Toma el item sobre el que esta parado el jugador.

- ###### /drop

  Tira el item que se encuentra en la posición seleccionada del inventario al suelo.

- ###### /inventory

  Lista las cosas que tengo en el inventario, indicando la posicion del item 
  (la posición de arriba a la izquierda es el 0, y va creciendo hacia la derecha 
  y hacia abajo) junto con su nombre.

- ###### /clear

  Limpia el minichat.



#### Información del jugador

![playerInfo](/Informe/img/playerInfo.png)

Aquí se muestran las estadísticas de vida, mana y experiencia del jugador

#### Inventario

![inventory2](/Informe/img/inventory2.png)

Arriba se pueden ver el  nivel y el nickname del usuario. Abajo se encuentra 
el inventario con los items que posee el jugador. El cuadrado que tiene un 
borde blanco es el que esta seleccionado. Por ultimo se ve la cantidad de oro 
del jugador y entre paréntesis el oro seguro.

#### Stats

![skills](/Informe/img/skills.png)

A la izquierda se ven las habilidades del jugador. A la derecha están los items 
equipados y debajo se ve la posición actual.



#### Controles

##### Teclado

- **Flechas**: Controlan el movimiento del jugador
- **Enter**: Ejecuta el comando ingresado en el minichat
- **Retroceso**: Borra la ultima letra del comando ingresado en el minichat
- **Tabulación**: Pausa o reproduce la música de fondo

##### Mouse

- **Click izquierdo:** Selecciona un tile o una posición del inventario. También 
habilita el minichat para escribir comandos.
- **Click derecho:** Al hacer click derecho en el mapa, el personaje intentara 
atacar la posición donde se hizo click. Si se hace click en el inventario, el 
personaje hará uso del item que se encuentre en la posición donde se hizo click. 
Si el item es un arma o una armadura sera equipado. Inversamente, si hago click 
sobre un item equipado, el personaje se desequipara dicho item.
