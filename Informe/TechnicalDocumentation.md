# Documentación técnica

### <u>Requerimientos de Software</u>
Este trabajo fue probado en computadoras con Ubuntu 18.04.4 y 20.04.

Para compilar se utilizo g++ (Ubuntu 9.3.0-10ubuntu2) 9.3.0, se necesita 
cmake de version al menos 3.10.2.

El depuramiento fue realizado con el depurador de Clion, sin embargo, 
puede utilizarse GDB.

### <u>Descripción general</u>
El proyecto se divide en cliente y servidor:

#### Servidor General
Se encuentra subdividido en la parte del servidor 
en sí (conexiones, etc), el mapa, los items, el manejo general del estado 
del juego, la persistencia  y las entidades, además de la parte de 
configuración.  

Servidor:  Se encarga de aceptar y rechazar jugadores.
Toma los nuevos clientes que intentan conectarse y cumple con los pedidos que estos
realizan, crea nuevas cuentas, carga cuentas ya existentes, carga los jugadores 
delegándole al módulo de persistencia la inicializaión de estos con sus datos y
crea nuevos jugadores con los datos correspondientes cuando es necesario. Se encarga
de almacenar y mandar la información necesaria para que el cliente pueda mostrarle
de forma adecuada los sucesos del juego.  

Mapa: Se encarga de guardar las entidades e items 
en posiciones específicas de una matriz, para así facilitar las 
interacciones entre  estos y poder representarlos fácilmente en 
un espacio bidimensional.  

Items: Se encarga de manejar los atributos de los
distintos items existentes y la interacción entre estos y las distintas
entidades del juego. Unos ejemplos de esto son la comunicacíon al jugador
de dónde debe equiparse un item al ser utilizado (o si es consumido), 
la existencia del inventario del jugador, y los drops de los monstruos 
al morir.  

Estado del juego: Se encarga de realizar todos los
cambios que le pidan los distintos componentes del juego, delega los pedidos
a las clases correspondientes cuando deba hacerlo. Se encarga tamién de 
algunas reglas particulares del juego como los spawns de monstruos y 
resurrección de jugadores. Hace uso de functors para encolar todas las acciones
que deberán ser realizadas en un update del juego.  

Persistencia: Se encarga de mantener la información
entre conexiones de los distintos jugadores con cuenta, guardándolos en un 
archivo. Realiza guardado de datos periódicamente y cuando los jugadores se desconectan.  

Entidades:  Se encarga de "darle vida" al juego. Este módulo
maneja los jugadores y npcs con los que interactuará el usuario. Maneja el comportamiento
de los monstruos, los ciudadanos (curas, comerciantes y banqueros) y los jugadores.  

Configuración: Se encarga de trabajar con los archivos de 
configuración del juego, aquellos usados para cambiar los distintos valores del juego sin
necesidad de recompilarlo. Trabaja con los archivos config.json y map.json.

#### Cliente General


## <u>Servidor</u>

### Server

##### ArgentumServer
Esta clase se encarga de inicializar los objetos necesarios para 
que pueda funcionar Game correctamente, además de contener el gameloop. Se encarga tambien
de delegar el a ClientsMonitor el proceso de enviado de la información del último update
a los clientes activos y pide que se agreguen a la lista de clientes activos aquellos que
estén en espera si es que hay tiempo suficiente para hacerlo.

##### ArgentumServerSide
Esta es la clase principal del servidor, es aquella que se utiliza
cuando se quiere empezar a ejecutarlo.

##### ClientAccepter
Clase que se encarga de aceptar a los clientes que intenten 
conectarse, diciéndole a ClientsMonitor que los agregue a su lista de espera.

##### ClientHandler
Clase que se encarga de interactuar con un cliente conectado al 
servidor. Se utiliza para mandarle la información actual del juego cuando este se conecta
y para mandarle la información cada update.

##### ClientsMonitor
Clase que engloba la lista de clientes conectados y clientes en 
espera. Todos los clientes que sean aceptados por el ClientAccepter serán 
agregagos a una lista de espera de ClientsMonitor hasta que el Game los
acepte y proceda a mergear dicha lista con la lista de clientes activos.
Si algún cliente se desconecta entonces se le desconectará debidamente
cuando se verifique el estado de los clientes.

#### PlayerManager
Administra el guardado y carga de los jugadores, es el nexo entre el juego y
las clases de persistencia. Cada vez que un jugador se desconecta se encarga
de removerlo del juego y almacenar sus datos actualizados en la correspondiente
entrada del archivo. Si un jugador se conecta busca sus datos en el archivo 
y se los pasa al Game para agregarlo al juego.

#### ServerMonitor
Esta clase tiene una única y simple responsabilidad: monitorear el ingreso
del caracter terminador ('q') para forzar el cierre del servidor. Cerrar el servidor
almacenará el estado actual de todos sus clientes conectados (este backup no se realiza
si el Servidor se cierra inesperadamente por algún error ya que no se podría garantizar
que la información correcta y/o no este corrupta).

#### ServerProtocol
Se encarga de almacenar la información del mapa base (al ser fijo y de gran tamaño
el mapa no sería lógico rearmar este buffer por cada cliente que se conecte).
Genera los mensajes de update para los clientes conectados.

### Persistance

#### PlayerIndexFile

Maneja el archivo de índice de los jugadores registrados. Dado que este archivo es
pequeño y para disminuir los accesos a memoria que implica leer/escribir de archivo
esta clase carga a memoria los datos del archivo.

#### PlayerSaveFile

Maneja el archivo de salvado de los jugadores. Este archivo contiene todos los datos
relevantes del jugador que son necesarios para poder cargarlo al juego cuando
se conecte, manteniendo su player intacto desde su última conexión.


Maneja el archivo de índice de los jugadores registrados. Dado que este archivo es
pequeño y para disminuir los accesos a memoria que implica leer/escribir de archivo
esta clase carga a memoria los datos del archivo.

#### SaveFileManager

Relaciona las dos clases anteriores, asegurandose de mantenerlas sincronizadas y
de usar los datos del índice para acceder al archivo de guardado de los datos de 
los jugadores. Esta clase es almacenada por PlayerManager, quien la utiliza para
poder guardar/cargar los datos de los jugadores.

### Map

##### Map
Contiene una matriz de tiles, se encarga de agregar, sacar y 
cambiar de lugar las entidades cuando se mueven y de delegarle al tile acciones que se 
apliquen en esta, como atacarla, pedirle un list, pedirle un buy, etc. Se encarga 
también de obtener caminos entre dos coordenadas y de conseguir los jugadores a 
atacar dentro de cierto rango alrededor de una coordenada. Otorga también 
posiciones de spawn para monstruos y para jugadores.

##### Tile

Contiene una lista con los items que se encuentran en su posición. Permite agregar y sacar
items. 
Delega acciones como list, attack, buy, etc al entity que almacena (si es que almacena uno).

### Items

##### ItemsFactory
Se encarga de crear items, tanto particulares como aleatorios. Se utiliza la creación 
particular para inicializar correctamente los inventarios de los jugadores y los Storage.
La creación aleatoria se utiliza para generar un drop de un item al morir un monstruo.
Contiene un unordered_map de punteros a las funciones que generan los distintos items, y
un vector de nombres que permite obtener un item aleatorio para generar.

##### Item
Clase base de la que heredan todos los items, guarda su nombre, qué tipo de item es 
y su id dentro de ese tipo de items (se repite entre distintos tipos). Tiene el método
abstracto use(), que retorna la posición en la que debería ser equipado ese item luego
de ser utilizado, este puede llegar a ser nulo y, por lo tanto, el item deberá ser eliminado
del inventario, en adición a esto, useItem hará cualquier acción que deba hacer sobre el
jugador que la invoca antes de retornar su lugar de equipamiento. Implementa también el 
método virtual isGold(), que fue agregado para evitar el uso de double dispatch al tomar
un item del piso.

##### Inventory
Clase que se encarga de manejar los items que almacena el jugador, almacena tanto los items
que tiene equipado el jugador como los que tiene en su "mochila" (es decir, los que guarda
pero no usa). Permite el uso de items guardados, y los equipa (o elimina) en la posición 
correspondiente recibida por useItem. Permite también desequipar items, guardándolos en el
inventario. Otro uso que se le da es guardar y sacar items, utilizado para almacenar items
tomados del piso y para dejarlos en este.

##### Weapon
Clase que hereda de item, se utiliza para atacar un jugador o monstruo. Contiene un ataque
mínimo y máximo y un valor de maná que consumirá al ser utilizado para atacar. El valor de
ataque que retorna estará entre esos valores máximo y mínimo si es que se tiene la cantidad
de mana necesaria, sino no podrá realizarse el ataque. Al crearse recibe un enum que indica
qué tipo de weapon es, es decir, qué arma es específicamente, para que pueda pedirle a 
config los datos apropiados para inicializar el objeto correctamente.

##### Clothing
Clase que hereda de item, también es abstracta, es la clase base para todos los tipos de
vestimenta. Tiene como atributos la defensa mínima y máxima, que funcionan de la misma forma
que con el arma, al pedir el valor de esta, retorna un valor que se encuentra entre la defensa
mínima y la máxima. Tiene un método abstracto que indica si es un tipo de clothing default,
para evitar el uso de double dispatch cuando se quiere equipar o desequipar un item en el
inventario.

##### Head
Clase que hereda de clothing, es utilizada para distinguir a los items que deben ser equipados
en la cabeza, esto lo hace retornando ese lugar de equipamiento al llamar al método use(). 
También recibe el indicador de qué tipo de Head se quiere crear, no se debe mandar el enum
de un item que no sea un Head.

##### Shield
Clase que hereda de clothing, es utilizada para distinguir a los items que deben ser equipados
como escudo, esto lo hace retornando ese lugar de equipamiento al llamar al método use().
También recibe el indicador de qué tipo de Shield se quiere crear, no se debe mandar el enum
de un item que no sea un Shield.

##### Chest
Clase que hereda de clothing, es utilizada para distinguir a los items que deben ser equipados
en el pecho, esto lo hace retornando ese lugar de equipamiento al llamar al método use().
También recibe el indicador de qué tipo de Chest se quiere crear, no se debe mandar el enum
de un item que no sea un Chest.

##### Gold
Clase que hereda de item, se utiliza para representar un conjunto de oro, se utiliza 
para depositarlo en el piso como un  drop de un monstruo. No es equipado en ningún 
lugar, por lo que usarlo lo eliminaría del  inventario, sin embargo, al tomarlo del 
piso se suma directamente al oro almacenado por el player, por lo que nunca se llamará 
a su función use.

##### Potion
Clase que hereda de item, se utiliza como base para las pociones, es una clase abstracta.
Su use retorna que no va equipado en ningún lado, por lo que las pociones son consumidas al
ser utilizadas, no son equipables. Tiene un método abstracto llamado restoreStat() que debe 
ser implementado por las clases que heredan de ella para que restauren el stat apropiado 
para el player. Este método es llamado por use.

##### HealthPotion
Clase que hereda de Potion, implementa restoreStat(), haciendo que llame al método de Player
que restaura su vida en cierta cantidad recibida.

##### ManaPotion
Clase que hereda de Potion, implementa restoreStat(), haciendo que llame al método de Player
que restaura su mana en cierta cantidad recibida.

### Game

##### Game
Clase que maneja el comienzo de la ejecución de casi todas las acciones del juego. Tiene el 
método update, que realiza todas las acciones de un tic del juego. Es la clase que utilizan las
entidades para interactuar con tiles y otras entidades, para cosas como atacar, moverse, etc.
Su principal funcionalidad es delegar estos pedidos a las clases que saben cómo reaccionar 
a ellos. Se encarga también del manejo de la resurrección de los jugadores y de enviar algunos
mensajes a los clientes, como la creación de nuevos monstruos.

##### MonstersFactory
Clase que se encarga de la creación de monstruos. Se utiliza para crear monstruos aleatorios
al repopular el mapa. Al igual que ItemsFactory, guarda un unordered_map de punteros a 
función.

##### ShouldMonsterBeRemoved
Functor utilizado para mandar una instancia al remove_if del erase realizado sobre la lista de
monstruos, retorna true cuando un monstruo esta muerto.

##### ShouldPlayerBeRevived
Functor utilizado para mandar una instancia al remove_if del erase realizado sobre la lista de
players a revivir, aumenta la cantidad de tiempo que lleva un jugador esperando ser revivido y, 
en caso de que este sea suficiente, revive al jugador alrededor del cura más cercano, 
retorna true cuando un jugador es revivido o está vivo. Cuando un jugador es revivido le pide
al mapa una coordenada de spawn y lo mueve a esta, agrega también al protocolo el mensaje de 
que el jugador revivió y fue teletransportado.

##### Event
Interfaz usada como base para todos los eventos guardados en la cola de Game. Se 
utiliza para que todos estos tengan el mismo formato y, por lo tanto, puedan ser ejecutados
de la misma forma, reciben el protocolo al ser ejecutados para que puedan adjuntar a los
mensajes generales la información necesaria.

##### Attack
Clase que hereda de Event, es utilizada por una entidad para comunicarle a Game que se 
quiere atacar un tile. Si se realiza un ataque comunica a los clientes con qué arma 
fue realizado.

##### Buy
Clase que hereda de Event, es utilizada por un Player para pedirle a Game que llame a buy
para un tile específico.

##### Deposit
Clase que hereda de Event, es utilizada por un Player para pedirle a Game que llame a 
deposit para un tile específico.

##### Drop
Clase que hereda de Event, es utilizada por un Player para decirle a game que deje uno
de los items del player en la posicion en la que este se encuentra. Si se deja un item
en un tile le comunica a los clientes cuál item es y dónde se encuentra.

##### GetInventoryNames
Clase que hereda de Event, almacena en el minichat del player que invocó el comando los
nombres de los items que tiene guardados en el inventario.

##### List
Clase que hereda de Event, es utilizada por un Player para pedirle a Game que llame a 
deposit para un tile específico. Si este tiene un entidad entonces llama a su list, 
sino agrega en el minichat los items que se encuentran en el tile seleccionado.

##### Message
Clase que hereda de Event, le pide a Game que le comunique un mensaje a un Player con un 
nombre específico.

##### ModifyPlayerMovement
Clase que hereda de Event, cambia el proximo estado de movimiento del Player, puede setearlo
como que se moverá en otra dirección o como que dejará de moverse, en ambos casos cuando 
termine el movimiento gradual que esté siendo ejecutado.

##### Move
Clase que hereda de Event, le pide a game que mueva la entidad en cierta dirección, si esto
es posible entonces comienza el desplazamiento gradual.

##### Moved
Clase que hereda de Event, ejecuta el desplazamiento gradual de la entidad y le comunica
este cambio a los clientes agregándolo al protocolo.

##### NotifyDeath
Clase que hereda de Event, notifica a los clientes de la muerte de un player, agregándolo
al protocolo.

##### PickUpItem
Clase que hereda de Event, le pide a Game que tome el item de arriba de todo en un tile,
comunica a los clientes que se debe poner otro item en ese tile o que ya no hay más items,
dependiendo del resultado de la operación.

##### PlayerLeveledUp
Clase que hereda de Event, notifica a los clientes que un player subió de nivel, agregandolo
al protocolo.

##### RequestResurrect
Clase que hereda de Event, le pide a Game que reviva al player, si la posición seleccionada
pertenece a un sacerdote entonces resucita instantáneamente, sino el jugador entra en la 
lista de espera para la resurrección. En el caso de que reviva inmediatamente agrega el 
mensaje de resurrección al protocolo para que sea enviado a los clientes.

##### RestoreStats
Clase que hereda de Event, es utilizada por un Player para pedirle a Game que llame a 
heal para un tile específico.

##### Sell
Clase que hereda de Event, es utilizada por un Player para pedirle a Game que llame a 
sell para un tile específico.

##### Unequip
Clase que hereda de Event, es utilizada por un Player para decirle a su inventario que 
se quiere desequipar un item.

##### UseItem
Clase que hereda de Event, es utilizada por un Player para decirle a su inventario que 
quiere usar un item en cierta posicion.

##### Withdraw
Clase que hereda de Event, es utilizada por un Player para pedirle a Game que llame a 
withdraw para un tile específico.

### Exceptions
AGREGAR COSAS AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA


### Entities

##### Entity
Es una clase abstracta, es la clase base para todas las entidades. Implementa por default
todas las funciones de interacción con otra entity como vacía ya que no todas las entidades
pueden realizar todas esas interacciones con los players. Cada clase que herede de esta
deberá implementar la interacción que le corresponda. Guarda su coordenada, tipo de entidad
y valores importantes para el movimiento.

##### Minichat
AAAAAAAAAAAAAAAAAA ESCRIBIR COSAS DEL MINICHAT

##### Monster
Es una clase que representa a un monstruo genérico, hereda de entity, no implementa ninguno
de los métdodos de interacción no violentos entre un player y un npc. Recibe en el 
constructor el tipo de monstruo que se quiere crear, y con esto se le pide a config los 
datos con los que debe ser inicializado. En cada update busca jugadores cercanos a los que
acercarse para atacar, si pasan cierta cantidad de tiempo sin desplazarse entonces realizan
un desplazamiento en una dirección aleatoria. Cuando muere tiene cierta probabilidad de
dejar un drop en el tile en el que murió.

##### MonsterStats
Es una clase almacenada por Monster, se encarga de manejar la vida de este. Agrega alguna
información adicional al mensaje de ataque cuando es necesario y modifica la vida que tiene
el monstruo cuando este es atacado, fijándose si el ataque fue crítico, fue esquivado, o fue
un ataque normal.

##### PlayerStats
Es una clase almacenada por Player, se encarga de manejar la vida, mana y experiencia de 
este. Realiza las mismas operaciones que MonsterStats al ser atacado. Cuando un player 
intenta atacar a alguien, el arma debe pedirle a esta clase que baje la cantidad de mana
correspondiente

##### Player
Es una clase que hereda de Entiy, representa un juguador, es decir, un cliente interactuando
con el servidor. 

## <u>Cliente</u>

### Modulo Principal:

##### ArgentumClientSide

Primero verifica que los argumentos con los que se ejecuta el cliente son correctos. Si es asi instancia al cliente e inicia su ejecución.

##### ArgentumClient

Cuando se llama a su constructor inicializa SDL y crea un nuevo cursor. Luego ejecuta el gameLoop. El gameLoop comienza con el menú principal que se detalla mas adelante. Cuando el usuario logra conectarse, se lanzan dos hilos: Uno se encarga de procesar los eventos SDL que corresponden al input del usuario y el otro recibe actualizaciones del servidor. En cada loop del juego se ejecutan las actualizaciones recibidas y finalmente se reproducen los sonidos correspondientes y se renderiza. Cuando se termina el juego se cierra el socket del cliente y se hace join de los hilos.

##### BlockingQueue

Es una cola bloqueante que no permite desencolar eventos hasta que se hayan dejado de añadir.

##### ClientEventHandler

ArgentumClient crea la cola Bloqueante sdlEvents a la que pushea los eventos que recibe. Luego lanza el hilo que comienza la ejecución de la clase ClientEventHandler. Durante su ejecucion, esta clase va desencolando sdlEvents y por cada evento arma un mensaje con toda la información necesaria y se lo envía al servidor.

##### ClientProtocol

##### GameGUI

Delega a la clase Map la actualización de lo que paso en el mapa(cuando se mueve una entidad o se lanza un hechizo). También se encarga de llamar a los métodos de renderizado de cada clase de la interfaz gráfica.

##### GameInitializer

Inicializa el juego con la información que recibe del servidor. Primero recibe el mapa. Itera por cada tile cargando el tipo de piso y un ciudadano o estructura si es que hay. Luego carga todos los monstruos, items o jugadores que haya en el mapa en el instante que el usuario se conecto.

##### ProtocolEnumTranslator

Cuando recibo del servidor un update que tiene información como un item o un tipo de suelo esto se recibe en forma de un enum que comparten tanto el servidor como el cliente. Del lado del cliente necesitamos traducir el enum recibido a un id de una textura para poder renderizar. De eso se ocupa esta clase

##### Update

Es una cola que contiene los eventos de actualización.

##### UpdateManager

##### UpdateReceiver

Recibe un evento del servidor, lo procesa y arma un UpdateEvent(functor) que luego es pushado a la cola de eventos para ser ejecutada en el thread principal.

### Modulo Graphics:

##### PlayerInfoGUI

Contiene toda la informacion del jugador que debe ser mostrada por pantalla: nickname, vida, mana, experiencia, nivel, habilidades, oro y posicion. Sin embargo, solo renderiza las barras de vida, mana y experiencia en la parte inferior de la ventana

##### PlayerInventoryGUI

Tiene el inventario del jugador, junto con los items equipados. Se encarga de mostrar los items por pantalla, ademas de la informacion del jugador que le pide a PlayerInfoGUI.

##### Minichat

Una de sus funciones es mostrar los mensajes relevantes recibidos por el servidor. Para esto tiene una lista de Text que en el constructor se llena con mensajes vacios. Cada vez que el servidor me manda un mensaje se desencola el mensaje mas viejo y se encola el nuevo. Cuando se renderiza el minichat se itera por esa lista imprimiendo solo algunos mensajes, ya que la cantidad total de mensajes es muy grande y no entra en el rectangulo del minichat. Se permite scrollear por el minichat para poder ver mensajes mas viejos.

Su otra funcion es tomar el input del usuario para que este pueda ingresar los comandos.

##### Selector

Hay ciertos comandos que requieren tener seleccionado a un personaje del mapa o a un lugar del inventario. Esta clase se encarga de verificar que se selecciono y guardarlo para poder usarlo para armar los mensajes que se enviaran al servidor.

##### Text

Me permite mostrar texto con una font y tamaño especificos. Despues de crear un Text puedo modificar el texto que se imprimirá de varias maneras. Para cambiar totalmente el texto esta updateText, para agregar esta el operador +=, para quitar una letra esta el operador --. El operador * crea la textura con el texto actual. Esto sirve porque hay veces que quiero renderizar siempre lo mismo, y crear siempre la textura no es muy eficiente.

##### Font

Crea una font a partir de un archivo .ttf

### Map

### Miscellanous

### Screen

##### MainMenu

Se encarga de mostrar las pantallas de inicio donde se elige si cargar o crear un jugador, los datos de dicho jugador y el puerto e ip a donde nos queremos conectar. Cada pantalla consiste de un loop que maneja los inputs del usuario (clicks o texto) y renderiza los botones y cajas de texto correspondiente. 

Luego de elegir una ip y un puerto y hacer click en "Connect" el cliente intentara conectarse al servidor. Si la conexión es exitosa, se le envían los datos del jugador(nickname y también raza + clase si se esta creando) al servidor que me responderá si me pude conectar exitosamente, o si hubo algún error.

##### Window

Primero crea la ventana y el renderer. Luego se encarga de manejar todos los eventos de sdl asociados a la ventana (cambiar el tamaño, pantalla completa). Finalmente se encarga de mostrar todo lo que haya sido renderizado.

### Sound

##### Sound

Crea un sonido a partir de un archivo .wav .

##### SoundRepository

Cuando es instanciado al principio del programa carga todos los sonidos en un unordered_map y la música. 

##### SoundPlayer

Tiene una cola de sonidos que son ejecutados al final de cada gameLoop. Tambien reproduce la musica y permite pausarla.

### Texture

### UpdateEvents



