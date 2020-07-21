# Documentación técnica

### <u>Requerimientos de Software</u>
Este trabajo fue probado en computadoras con Ubuntu 18.04.4 y 20.04.

Para compilar se utilizo g++ 9.3.0, se necesita CMake de versión al menos 3.10.2.

El depuramiento fue realizado con el depurador de Clion, sin embargo, 
puede utilizarse GDB.

### <u>Descripción general</u>
El proyecto se divide en cliente y servidor. Para el desarrollo del mismo
se diseño un patrón (no logramos encontrar si ya existía así que lo tomamos como propio)
al que llamamos *Product Pattern*. El nombre viene de la idea de que generemos un
*functor* que ya esta preparado para ejecutar el evento correspondiente, permitiendo
que el que consuma dicho evento ya tenga todo ensamblado y no se complique 
innecesariamente. Este patrón resultó clave en el diseño del TP y se lo utilizó
para los updates que recbie el cliente del servidor, para los comandos que ingresa el
cliente por minichat y para los eventos que procesa el juego del servidor.  


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

Se divide en las entidades del juego (players y npcs, tanto monstruos como
citizens), las clases gráficas, el mapa, la ventana/pantalla, los sonidos,
texturas, eventos de update y otras clases generales englobadas por el submódulo
Cliente.

Character: Se encarga de administrar a los personajes del mundo de Argentum,
estos son los monstruos, citizens (banker, priest, trader) y los jugadores.

Graphics: Se encarga de administrar la UI con los datos particulares del cliente
(salvo el mapa gráfico, eso se delega en el módulo Map) como las stats, la vida, el
maná, el inventario, etc.

Map: Se encarga de administrar la UI del mapa del cliente, actualizando a los elementos
que lo comoponen (como los tiles o las entidades).

Miscellaneous: Se encarga de manejar los hechizos, las flechas y el chequeo de
qué elementos son renderizables (visibles en la cámara).

Screen: Se encarga de manejar la ventana donde se renderiza el juego y el Menú
Principal (este submódulo debería estar en Graphics pero por motivos de tiempo
no se llegó a cambiar de lugar).

Sound: Se encarga de administrar los sonidos del juego, filtrando sonidos 
en base a la cantidad/tiempo que pasó entre cada sonido para no sobrecargar al
cliente de información.

Texture: Se encarga de administrar las texturas del juego, desde las texturas de los
personajes hasta las de los items. 

UpdateEvents: Contiene todos los posibles eventos que el cliente puede recibir
del servidor y debe aplicar a su representación del juego para poder transmitir
esa información claramente al jugador.

#### libs

Contiene las clases comúnes entre el cliente y el servidor.

Scoket: Maneja la conexión y el envío de información entre el cliente y el servidor.
Permite levantar un servidor en un puerto específico o conectar un cliente a un
servidor.

Thread: Clase abstracta, los que heredan de ella pueden ejecutar un thread de POSIX
para que corra un método específico. 

Timer: Es un cronómetro, permite obtener el tiempo transcurrido en milisegundos
desde que se llama a su método startTime.

TPException: Exception general, permite recibir cualquier texto para poder mostrar
un mensaje claro de error. 

GameEnums: enums generales como tipo de arma, ropa, eventos del cliente, eventos
del servidor, entre otros. Estos se comparten entre el cliente y el servidor
para poder entenderse el uno con el otro.

SharedConstants: constantes compartidas entre el cliente y el servidor, para este
TP tan solo se comparte la distancia de un tile al otro para poder traducir dicha
distancia a pixeles en el cliente.

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

### Persistence

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

##### Coordinate
Struct utilizado para simplificar el pasaje de coordenadas a funciones, se utiliza también
para el algoritmos de caminos mínimos, se implementó su función de hashing y equal para poder
utilizarlo como key.

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
mensajes a los clientes, como la creación de nuevos monstruos. Un diagrama de clase que muestra
los atributos y métodos de Game en forma general, además de sus interacciones con algunas clases
del mismo módulo es:

![LoadPlayer](/Informe/img/DiagramaDeClaseGame.png)

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
mensajes generales la información necesaria. Al adjuntar esta información introducen primero
una tupla con un id de evento, que permite distinguir qué tipo de información se está 
proporcionando al cliente, esto le permite a este saber qué datos tendrá que recibir para
poder interpretar la información recibida de la forma correcta. Un diagrama de clases general
que permite ver cómo está organizada la interacción entre esta clase y las que heredan de ella
(mostrando únicamente algunas de las clases hijas como ejemplo, ya que sino el diagrama 
sería ilegible) es:

![LoadPlayer](/Informe/img/DiagramaDeClaseEvent.png)

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
Para este trabajo se utilizaron tres custom exceptions:  

TPException: Exception principal, es la utilizada en casi la totalidad del código.    
Permite ingresar cualquier mensaje de texto para hacer claro el error.

Las siguientes dos exceptions se lanzan en las clases de persistencia para poder
mandar un mensaje custom al cliente dependiendo el error ocasionado.

UnavailablePlayerException: esta exception se lanza cuando el cliente quiere 
crear un cliente ya existe o si el cliente quiere cargar un player y dicho player
ya esta loggeado en la partida.

InexistentPlayerException: esta exception se lanza cuando un cliente quiere loggearse
con un player que no existe.


### Entities

##### Entity
Es una clase abstracta, es la clase base para todas las entidades. Implementa por default
todas las funciones de interacción con otra entity como vacía ya que no todas las entidades
pueden realizar todas esas interacciones con los players. Cada clase que herede de esta
deberá implementar la interacción que le corresponda. Guarda su coordenada, tipo de entidad
y valores importantes para el movimiento.

##### Minichat
Es una clase sencilla, basicamente es un wrapper de un string que permite agregar
texto a dicho string o borrrarlo (para no repetir envío de mensajes en cada update
al cliente).

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
correspondiente.

##### Player
Es una clase que hereda de Entiy, representa un juguador, es decir, un cliente interactuando
con el servidor. Realiza todas las acciones que puede realizar un jugador. Almacena una 
instancia de PlayerStats y de Inventory, además del oro y otros datos que identifican su 
raza y clase. Permite conectar los pedidos de los clientes con el juego en sí.

##### PlayerProxy
Es la clase que comecta el ClientHandler con Player. Almacena los eventos en una cola interna,
que luego es vaciada por Game para ver qué acciones realizará Player.

##### Storage
Clase que contiene items y oro. Guarda un unordered map que contiene como key el nombre del
item y como valor una lista de instancias de items. Al inicializarse recibe un unordered_map
con el nombre del item y la cantidad de ese item que tendrá que almacenar. Permite agregar
al minichat de un player mensajes que indican el oro y los items almacenados, junto con su 
cantidad, ademas de guardar y sacar items y oro.

##### Shop
Clase que engloba Storage y le otorga comportamiento de comercio, permitiendo comprar y 
vender items. Almacena también un unordered_set, que permite ver si el item que se está
intentando vender al shop es aceptado por este. Almacena un unordered_map con los precios de
los items con los que opera, lo cual le permite manejar la compra y venta de estos, e indicar
los items presentes y su precio al hacerle un list.

##### Banker
Clase que almacena items que le otorga un Player. Permite a este almacenar y retirar items
y oro, tiene un límite de cantidad de items a guardar para un player específico. Guarda
un unordered_map de Storage estático en el que guarda los Storage de todos los jugadores
conectados, es estático para que sea una variable de clase y lo compartan todos los bankers,
ya que los jugadores deben poder acceder a sus elementos desde cualquier banker. Pedirle que
haga un list guardará en el minichat del player que lo haya hecho los items y oro que este
tiene almacenado en su banco. Los players tienen un límite de cantidad de items a guardar
para mantener la restricción de tener un struct de tamaño fijo para guardar en el archivo de
persistencia. Implementa las funciones que reaccionan a list, withdraw y deposit de player.

##### Priest
Clase que representa un cura o sacerdote. Implementa las funciones que reaccionan a list, heal, 
buy y sell de player. Cura y "resucita" (esto es manejado por Game, como fue dicho previamente)
jugadores. También guarda un Shop, que utiliza para comprar y vender pociones y hechizos.

##### Trader
Clase que representa comerciante. Implementa las funciones que reaccionan a list, buy y sell de 
player. Tiene un comportamiento similar a Priest, con la diferencia de que no reacciona al comando
heal, y en vez de comprar y vender hechizos y pociones compra y vende armas y pociones.

### Config

##### Calculator
Clase que contiene todas las ecuaciones utilizadas por la lógica del juego, con algunas funciones
adicionales utilizadas para la aleatoridad.

##### ConfigFileReader
Clase que se encarga de leer los datos del archivo de configuración, utiliza json.

##### Configuration
Clase que almacena todos los datos del archivo de configuración, se utiliza para obtener estos 
valoes.

##### MapFileReader
Clase que se encarga de leer y almacenar los datos del json que contiene la información del 
mapa. Se utiliza para la inicialización de los datos del mapa cuando este es creado.

##### map.json
Este archivo es generado automáticamente por el programa Tiled con toda la información del mapa creado con el programa. Como es generado por una aplicación externa tiene muchos datos que no nos sirven. Lo que si utilizamos son los campos "layers" y "tilesets". 

- **Layers**: Hay 5 layers: El primero tiene el tipo de suelo (pasto, agua, desierto etc), el segundo tiene las estructuras (arboles, arbustos, casas etc). El tercero tiene a los NPC que están fijos en el mapa (comerciantes, curas y banqueros). Los últimos dos layers son "mascaras lógicas". El primero me dice si el tile puede ser ocupado por una entidad y el segundo me dice si el tile pertenece a una ciudad.
- **Tilesets**: Cada tileset tiene un id general llamado "firstgid", el archivo donde esta la imagen del tileset y el tilecount. Si el tilecount es 1 quiere decir que la imagen es todo el tile. Si es mayor a 1, quiere decir que en la imagen tengo mas de un tile.



##### config.json
El archivo se separa en distintas secciones:

- **Race**: contiene a cada raza con los valores de vida, mana, meditationRate, RecoveryRate y cada habilidad
- **Class**: idéntica a "Race" pero contiene a las clases
- **Monster**: contiene a los monstruos, con sus valores de vida, daño, rango de visión, rango de niveles, velocidad y habilidades
- **Weapon**: Contiene cada arma con su daño mínimo y máximo, su rango, su consumo de mana y su precio
- **Clothing**: Contiene cada item de vestimenta con su defensa mínimo y máximo y su precio
- **Potion**: Contiene las pociones con su precio y la cantidad de mana o vida que recuperan
- **GoldModifiers**: Contiene los valores que se usan en las ecuaciones respectivas al oro
- **XPModifiers**: Contiene los valores que se usan en las ecuaciones respectivas a la experiencia
- **MonsterSpawnData**: Valores que modifican el spawn de los monstruos como la cantidad total o el tiempo entre spawns.
- **General**: Valores mas generales que no pertenecían a ninguna categoría de las anteriores y no ameritaban una categoría nueva.
- **Files**: Aquí se encuentra el puerto donde escuchara el servidor y las rutas de los archivos de persistencia.



## <u>Cliente</u>

### Modulo Principal:

##### ArgentumClientSide

Primero verifica que los argumentos con los que se ejecuta el cliente son correctos. Si es así instancia al cliente e inicia su ejecución.

##### ArgentumClient

Cuando se llama a su constructor inicializa SDL y crea un nuevo cursor. Luego ejecuta el gameLoop. El gameLoop comienza con el menú principal que se detalla mas adelante. Cuando el usuario logra conectarse, se lanzan dos hilos: Uno se encarga de procesar los eventos SDL que corresponden al input del usuario y el otro recibe actualizaciones del servidor. En cada loop del juego se procesa el input del usuario y se envia el mensaje correspondiente al servidor; se ejecutan las actualizaciones recibidas; se reproducen los sonidos correspondientes y finalmente se renderiza todo y se muestra por pantalla. Al finalizar el juego se cierra el socket del cliente y se hace join de los hilos.

##### BlockingQueue

Es una cola bloqueante que no permite desencolar eventos hasta que se hayan dejado de añadir. Se usa para encolar eventos de sdl a una cola que comparten ArgentumClient y ClientEventHandler

##### ClientEventHandler

ArgentumClient crea la cola Bloqueante sdlEvents a la que pushea los eventos que recibe. Luego lanza el hilo que comienza la ejecución de la clase ClientEventHandler. Durante su ejecución, esta clase va desencolando sdlEvents y por cada evento arma un mensaje con toda la información necesaria y se lo envía al servidor.

##### ClientProtocol

Contiene funciones generales que utilizan tanto el GameInitializer como el 
UpdateReceiver (como por ejemplo la creación de un player) evitando repetir
innecesariamente código en ambos módulos.


##### GameGUI

Delega a la clase Map la actualización de las animaciones(hechizos o movimiento de entidades). También se encarga de llamar a los métodos de renderización de cada clase de la interfaz gráfica.

##### GameInitializer

Inicializa el juego con la información que recibe del servidor. Primero recibe el mapa. Itera por cada tile cargando el tipo de piso y un ciudadano o estructura si es que hay. Luego carga todos los monstruos, items o jugadores que haya en el mapa en el instante que el usuario se conectó.

##### ProtocolEnumTranslator

Cuando recibo del servidor un update que tiene información como un item o un tipo de suelo, un tipo de estructura o un npc, esto se recibe en forma de un enum que comparten tanto el servidor como el cliente. Del lado del cliente necesitamos traducir el enum recibido a un id de una textura para poder renderizar. De eso se ocupa esta clase.

##### Update


Es una cola que contiene los eventos de actualización. Cada update se compone
de eventos que sucedieron en el juego, piense en esos eventos como pequeños 
bloques de información que representan un único cambio en el juego.


##### UpdateManager

Maneja una cola de Updates (clase previamente descripta). Permite almacenar múltiples
Updates de forma tal que se evite el bottleneck donde no se pueden recibir un Update hasta que no se
termine de procesar otro. Actúa como mediador entre el thread que ejecutra el loop
del cliente y el thread que recibe constantemente los updates del servidor.

##### UpdateReceiver

Recibe un evento del servidor, lo procesa y arma un UpdateEvent (functor) que luego es pusheado a la cola de eventos para ser ejecutado en el hilo principal.

### Graphics:

##### PlayerInfoGUI

Contiene toda la información del jugador que debe ser mostrada por pantalla: nickname, vida, mana, experiencia, nivel, habilidades, oro y posición.. Sin embargo, solo renderiza las barras de vida, mana y experiencia en la parte inferior de la ventana

##### PlayerInventoryGUI

Tiene el inventario del jugador, junto con los items equipados. Se encarga de mostrar los items por pantalla, ademas de la información del jugador que le pide a PlayerInfoGUI.

##### Minichat

Una de sus funciones es mostrar los mensajes relevantes recibidos por el servidor. Para esto tiene una lista de Text que en el constructor se llena con mensajes vacíos. Cada vez que el servidor me manda un mensaje se desencola el mas viejo y se encola el recibido. Cuando se renderiza el minichat se itera por esa lista imprimiendo solo algunos mensajes, ya que la cantidad total de mensajes es mas grande que los que se pueden mostrar en el minichat. Para poder mostrar mas mensajes de los que se entran normalmente se implementó una función para poder scrollear y ver mas mensajes.

La otra función es tomar el input del usuario para que este pueda ingresar los comandos.

El minichat se desarrollo en las primeras semanas del trabajo, cuando solo había un hilo para el cliente. Luego, cuando se empezó a implementar la comunicación entre cliente y servidor se paso a usar tres hilos para el cliente. Esto causo muchas race conditions, especialmente en el minichat. Para arreglarlas se tuvieron que usar dos mutex, ya que al utilizar uno solo había situaciones en las que podía ocurrir un dead lock. Obviamente esta no es la solución ideal, pero se priorizaron otras áreas del proyecto que requerían mas atención.

##### Selector

Hay ciertos comandos que requieren tener seleccionado a un personaje del mapa o a un lugar del inventario. Esta clase se encarga de verificar que se selecciono y guardarlo para poder usarlo para armar los mensajes que se enviarán al servidor. 

Los datos que guarda esta clase son modificados en el hilo de ClientEventHandler, pero se utilizan luego en el hilo principal. Por esto la clase esta protegida por un mutex

##### Text

Me permite mostrar texto con una font y tamaño especificos. Despues de crear un Text puedo modificar el texto que se imprimirá de varias maneras. Para cambiar totalmente el texto esta updateText, para agregar esta el operador +=, para quitar una letra esta el operador --. El operador * crea la textura con el texto actual. Esto sirve porque hay veces que se quiere renderizar siempre lo mismo, y crear siempre la textura no es muy eficiente.

##### Font

Crea una font a partir de un archivo .ttf

### Map

![DiagramaDeClaseMapCliente](/Informe/img/DiagramaDeClaseMapCliente.png)

#### ItemDrop

Representa una imágen individual de un item. Estas se muestran cuando el item
esta droppeado en un Tile o en el inventario del jugador. Para agregar dinamismo
los drops de los Tiles están rotados 90 grados.

#### Structure

Representa una estructura, estas pueden ocupar uno o más Tiles visualmente
pero internamente para la lógia del cliente existen en un único Tile.

#### Tile

Es la unidad mínima del mapa, su principal utilidad es abstraerse de posiciones 
absoultas de pixeles para los objetos/entidades del mapa y a su vez permitir
renderizar únicamente lo visible por el jugador sin necesidad de recorrer todos
los elementos del mapa (personajes, estructuras, hechizos, etc) lo cual pdoría resultar
inviable dado su magnitud (el mapa desarrollado para el juego es de 100x100 Tiles,
es decir, 10.000 tiles en total).

#### Map 

Engloba toda la interfaz visual del mapa, actuando como administrador de los
elementos que contiene ya sean hechizos, flechas, entidades, estructuras, etc.
Es uno de los módulos principales de la GUI del cliente, junto con PlayerInfoGUI
y PlayerInventoryGUI.

### Miscellaneous

#### Arrow

Representa la instancia de una flecha. Internamente maneja la lógica de desplazamiento
(animación) moviendose una cierta distancia cada X tiempo transcurrido que recibe del main 
game loop. La flecha comienza existiendo en la posición del arquero que la disparó
y termina de existir cuando alcanza el target (el Tile al que fue disparada).
Sin embargo la animación es solo una ilusión ya que físicamente la flecha, 
como todo ataque, ataca instantáneamente (no es posible esquivarla ni frenarla
cruzandose en su camino).

#### Spell

Representa la instancia de un hechizo. Al igual que la flecha, recibe el tiempo 
transcurrido desde el último update del cliente y actualiza su animación 
en base a esto. Sin embargo a diferencia de la flecha el hechizo actualiza su
frame y no su posición. Si bien en el juego el hechizo se mantiene en la entidad
a la que fue lanzado esto se debe a que la entidad mantiene una referencia 
a dicho hechizo y actualiza la posición de este en base a la propia.
Si la entidad dejase de existir (muere o se desconecta el jugador) el hechizo
pasará a ser referenciado por el Tile correspondiente a esa entidad, garantizando
la continuación de la animación.

#### CameraCollisionVerifier

Verifica si un objeto es visible en la pantalla para ser
entonces poder renderizado. En retrospectiva lo mejor sería
una clase Camera que contenga a los métodos de esta clase para que quede 
más compacto, pero dado que se le prestó más atención a otros módulos
de mayor complejidad no se llegó a modificar esto.

### Screen

##### MainMenu

Se encarga de mostrar las pantallas de inicio donde se elige si cargar o crear un jugador, los datos de dicho jugador y el puerto e ip a donde nos queremos conectar. Cada pantalla consiste de un loop que maneja los inputs del usuario (clicks o texto) y renderiza los botones y cajas de texto correspondiente. 

Luego de elegir una ip y un puerto y hacer click en "Connect" el cliente intentara conectarse al servidor. Si la conexión es exitosa, se le envían los datos del jugador(nickname y también raza + clase si se esta creando) al servidor que me responderá si me pude conectar exitosamente, o si hubo algún error. Los posibles errores son: 

- INEXISTENT_PLAYER: Cuando se trata de cargar un jugador que no existe.
- UNAVAILABLE_PLAYER: Puede ocurrir de dos formas. Si se trata de cargar un personaje que alguien ya esta usando o si trato de crear un personaje con un nickname que ya esta en uso.

En retrospectiva, hubiese sido mejor crear distintas clases para cada pantalla, principalmente para evitar la repetición de codigo, pero tambien para que sea mas claro.

##### Window

Primero crea la ventana y el renderer. Luego se encarga de manejar todos los eventos de sdl asociados a la ventana (cambiar el tamaño, pantalla completa). Finalmente se encarga de mostrar todo lo que haya sido renderizado.

### Sound

##### Sound

Crea un sonido a partir de un archivo .wav 

##### SoundRepository

Cuando es instanciado al principio del programa carga todos los sonidos en un unordered_map y la música. 

##### SoundPlayer

Tiene una cola de sonidos que son ejecutados al final de cada gameLoop. También reproduce la música y permite pausarla. Como los sonidos se reproducen en el hilo principal pero se encolan en el hilo de UpdateReceiver esta clase esta protegida por un mutex.

### Texture

Maneja las texturas generadas por SDL y su renderización, otorgando una API más
amigable al resto de las clases. Una textura puede tener varios sprites, permitiendo
renderizar cada uno fácilmente y evitando generar más de una textura por sprite.

### UpdateEvents

##### UpdateEvent

Es una interfaz para los eventos recibidos por el servidor que se deben 
ejecutar en el thread principal. Estos eventos siguen el *Product Pattern*
desarrollado para ese TP.

##### UpdateAttack

Se fija con que arma se realizó el ataque y verifica la posición del ataque para decidir si se debe encolar un sonido porque esta cerca del jugador. Si el ataque es un hechizo también añade la animación a esa posición del mapa.

##### UpdateCreateItem

En el constructor recibe la posicion donde se creara el item y un enum con el tipo de item con el que consigue el id de la textura del ProtocolEnumTranslator. Cuando se ejecuta delega al mapa la creacion de ese item en la posicion correspondiente.

##### UpdateCreateNPC

Delega al mapa la creacion de un NPC con la data que recibe en su constructor

##### UpdateCreatePlayer

Delega al mapa la creacion de un NPC con la data que recibe en su constructor

##### UpdateDestroyItem

Delega al mapa la destruccion del item en la posicion recibida

##### UpdateEquip

Mediante el ProtocolEnumTranslator consigue la textura del item recibido y se lo equipa al jugador en la posicion especificada. Tambien puede recibir un enum que desequipa el item en la posicion especificada.

##### UpdateGUI

Recibe toda la informacion del jugador y la actualiza. Desde los items equipados y del inventario hasta la vida, mana, experiencia, nivel etc

##### UpdateLevelUp

Le sube el nivel al jugador. Esto permite que se imprima el nivel debajo de cada jugador.

##### UpdateMove

Mueve a una entidad en la direccion especificada. Tambien recibe la distancia que se movio (en metros) que luego se interpola a pixeles para que las animaciones se vean mas fluidas

##### UpdatePlayerDeath

Delega al mapa el matar a un jugador. El objetivo final es setear la variable isAlive del jugador en false para que al ser renderizado se use la textura del fantasma.

##### UpdatePlayerResurrect

Delega al mapa el revivir a un jugador. El objetivo final es setear la variable isAlive del jugador en true para que al ser renderizado se use muestre el equipamiento normalmente

##### UpdateRemoveEntity

Borra a una entidad. Esto sirve tanto para cuando mueren los monstruos o cuando se desconecta un jugador.

##### UpdateTeleportEntity

Teletransporta a una entidad. Sirve para cuando el jugador ingresa el comando resurrect sin haber clickeado a un cura, ya que entonces debe ser transportado, despues de un tiempo, al cura mas cercano.


### InputCommands

##### InputCommand

Es una interfaz para los comandos ingresados por el usuario en el minichat. Estos eventos siguen el *Product Pattern*desarrollado para ese TP. Cada comando recibe en su constructor la información necesaria para luego poder mandarle el mensaje al servidor.

##### CommandVerifier

En su constructor llena un unordered_map con comandos para poder verificarlos mas facilmente y no llenar todo de if else statements. Luego tiene el método verifyCommand que recibe un string y lo procesa para ver si es un comando valido. Si no lo es devuelve nullptr, pero si el comando es valido devuelve un unique_ptr de InputCommand para que lo ejecute el thread principal.

##### BuyCommand

Arma un mensaje con el tile que tengo seleccionado (para ver si seleccione a un cura o comerciante) y el item que quiero comprar.

##### DepositCommand

Arma un mensaje con el tile que tengo seleccionado (para ver si seleccione a un banquero) y el item que quiero depositar.

##### DropCommand

Arma un mensaje con el lugar del inventario que tengo seleccionado para poder tirar ese item.

##### HealCommand

Arma un mensaje con la posición que tengo seleccionada para ver si seleccione a un cura.

##### ListCommand

Arma un mensaje con la posición que tengo seleccionada. Si es un cura, comerciante me muestra lo que puedo comprar. Si es un banquero me muestra los items que tengo depositados. Si es un tile donde hay items me lista los items que están en ese tile.

##### MeditateCommand

Arma un mensaje solamente con el evento de meditar ya que no necesita de mas información.

##### MessageToPlayerCommand

Arma un mensaje con el nickname del jugador al que le quiero mandar el mensaje junto con el mensaje que quiero mandar.

##### PickUpCommand

Arma un mensaje solamente con el evento de tomar un item ya que no necesita mas información porque agarra el primer item del tile en el que estoy parado.

##### RequestInventoryNamesCommand

Arma un mensaje con el evento. Me muestra en el minichat que item tengo en cada posición del minichat.

##### ResurrectCommand

Arma un mensaje con la posición que tengo seleccionada para ver si seleccione a un cura.

##### SellCommand

Arma un mensaje con el tile que tengo seleccionado (para ver si seleccione a un cura o comerciante) y el item que quiero comprar.

##### WithdrawCommand

Arma un mensaje con el tile que tengo seleccionado (para ver si seleccione a un banquero) y el item que quiero depositar.



