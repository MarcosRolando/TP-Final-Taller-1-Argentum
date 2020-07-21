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
resurrección de jugadores.  

Persistencia: Se encarga de mantener la información
entre conexiones de los distintos jugadores con cuenta, guardándolos en un 
archivo. Realiza guardado de datos periódicamente y cuando los jugadores se desconectan.  

Entidades:  Se encarga re "darle vida" al juego. Este módulo
maneja los jugadores y npcs con los que interactuará el usuario. Maneja el comportamiento
de los monstruos, los ciudadanos (curas, comerciantes y banqueros) y los jugadores.  

Configuración: Se encarga de trabajar con los archivos de 
configuración del juego, aquellos usados para cambiar los distintos valores del juego sin
necesidad de recompilarlo. Trabaja con los archivos config.json y map.json.

#### Cliente General


### <u>Servidor</u>

#### ArgentumServer
Esta clase se encarga de inicializar los objetos necesarios para 
que pueda funcionar Game correctamente, además de contener el gameloop. Se encarga tambien
de delegar el a ClientsMonitor el proceso de enviado de la información del último update
a los clientes activos y pide que se agreguen a la lista de clientes activos aquellos que
estén en espera si es que hay tiempo suficiente para hacerlo.

#### ArgentumServerSide
Esta es la clase principal del servidor, es aquella que se utiliza
cuando se quiere empezar a ejecutarlo.

#### ClientAccepter
Clase que se encarga de aceptar a los clientes que intenten 
conectarse, diciéndole a ClientsMonitor que los agregue a su lista de espera.

#### ClientHandler
Clase que se encarga de interactuar con un cliente conectado al 
servidor. Se utiliza para mandarle la información actual del juego cuando este se conecta
y para mandarle la información cada update.

#### ClientsMonitor
Clase que engloba la lista de clientes conectados y clientes en 
espera. Todos los clientes que sean aceptados por el ClientAccepter serán 
agregagos a una lista de espera de ClientsMonitor hasta que el Game los
acepte y proceda a mergear dicha lista con la lista de clientes activos.
Si algún cliente se desconecta entonces se le desconectará debidamente
cuando se verifique el estado de los clientes.

#### PlayerManager
AGREGAR COSAS DE PLAYER MANAGER AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#### ServerMonitor
AGREGAR COSAS DE SERVER MONITOR AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#### ServerProtocol
Se encarga de almacenar la información del mapa y los mensajes a
comunicar en cada update, guardándolos en un vector de chars para mandar por el socket.

### <u>Persistance</u>


### <u>Map</u>

#### Map
Contiene una matriz de tiles, se encarga de agregar, sacar y 
cambiar de lugar las entidades cuando se mueven y de delegarle al tile acciones que se 
apliquen en esta, como atacarla, pedirle un list, pedirle un buy, etc. Se encarga 
también de obtener caminos entre dos coordenadas y de conseguir los jugadores a 
atacar dentro de cierto rango alrededor de una coordenada. Otorga también 
posiciones de spawn para monstruos y para jugadores.

#### Tile

Contiene una lista con los items que se encuentran en su posición. Permite agregar y sacar
items. 
Delega acciones como list, attack, buy, etc al entity que almacena (si es que almacena uno).

### <u>Items</u>

#### ItemsFactory
Se encarga de crear items, tanto particulares como aleatorios. Se utiliza la creación 
particular para inicializar correctamente los inventarios de los jugadores y los Storage.
La creación aleatoria se utiliza para generar un drop de un item al morir un monstruo.
Contiene un unordered_map de punteros a las funciones que generan los distintos items, y
un vector de nombres que permite obtener un item aleatorio para generar.

#### Item
Clase base de la que heredan todos los items, guarda su nombre, qué tipo de item es 
y su id dentro de ese tipo de items (se repite entre distintos tipos). Tiene el método
abstracto use(), que retorna la posición en la que debería ser equipado ese item luego
de ser utilizado, este puede llegar a ser nulo y, por lo tanto, el item deberá ser eliminado
del inventario, en adición a esto, useItem hará cualquier acción que deba hacer sobre el
jugador que la invoca antes de retornar su lugar de equipamiento. Implementa también el 
método virtual isGold(), que fue agregado para evitar el uso de double dispatch al tomar
un item del piso.

#### Inventory
Clase que se encarga de manejar los items que almacena el jugador, almacena tanto los items
que tiene equipado el jugador como los que tiene en su "mochila" (es decir, los que guarda
pero no usa). Permite el uso de items guardados, y los equipa (o elimina) en la posición 
correspondiente recibida por useItem. Permite también desequipar items, guardándolos en el
inventario. Otro uso que se le da es guardar y sacar items, utilizado para almacenar items
tomados del piso y para dejarlos en este.

#### Weapon
Clase que hereda de item, se utiliza para atacar un jugador o monstruo. Contiene un ataque
mínimo y máximo y un valor de maná que consumirá al ser utilizado para atacar. El valor de
ataque que retorna estará entre esos valores máximo y mínimo si es que se tiene la cantidad
de mana necesaria, sino no podrá realizarse el ataque. Al crearse recibe un enum que indica
qué tipo de weapon es, es decir, qué arma es específicamente, para que pueda pedirle a 
config los datos apropiados para inicializar el objeto correctamente.

#### Clothing
Clase que hereda de item, también es abstracta, es la clase base para todos los tipos de
vestimenta. Tiene como atributos la defensa mínima y máxima, que funcionan de la misma forma
que con el arma, al pedir el valor de esta, retorna un valor que se encuentra entre la defensa
mínima y la máxima. Tiene un método abstracto que indica si es un tipo de clothing default,
para evitar el uso de double dispatch cuando se quiere equipar o desequipar un item en el
inventario.

#### Head
Clase que hereda de clothing, es utilizada para distinguir a los items que deben ser equipados
en la cabeza, esto lo hace retornando ese lugar de equipamiento al llamar al método use(). 
También recibe el indicador de qué tipo de Head se quiere crear, no se debe mandar el enum
de un item que no sea un Head.

#### Shield
Clase que hereda de clothing, es utilizada para distinguir a los items que deben ser equipados
como escudo, esto lo hace retornando ese lugar de equipamiento al llamar al método use().
También recibe el indicador de qué tipo de Shield se quiere crear, no se debe mandar el enum
de un item que no sea un Shield.

#### Chest
Clase que hereda de clothing, es utilizada para distinguir a los items que deben ser equipados
en el pecho, esto lo hace retornando ese lugar de equipamiento al llamar al método use().
También recibe el indicador de qué tipo de Chest se quiere crear, no se debe mandar el enum
de un item que no sea un Chest.

#### Gold
Clase que hereda de item, se utiliza para representar un conjunto de oro, se utiliza 
para depositarlo en el piso como un  drop de un monstruo. No es equipado en ningún 
lugar, por lo que usarlo lo eliminaría del  inventario, sin embargo, al tomarlo del 
piso se suma directamente al oro almacenado por el player, por lo que nunca se llamará 
a su función use.

#### Potion
Clase que hereda de item, se utiliza como base para las pociones, es una clase abstracta.
Su use retorna que no va equipado en ningún lado, por lo que las pociones son consumidas al
ser utilizadas, no son equipables. Tiene un método abstracto llamado restoreStat() que debe 
ser implementado por las clases que heredan de ella para que restauren el stat apropiado 
para el player. Este método es llamado por use.

#### HealthPotion
Clase que hereda de Potion, implementa restoreStat(), haciendo que llame al método de Player
que restaura su vida en cierta cantidad recibida.

#### ManaPotion
Clase que hereda de Potion, implementa restoreStat(), haciendo que llame al método de Player
que restaura su mana en cierta cantidad recibida.

## <u>Cliente</u>

### Modulo Principal:

#### ArgentumClientSide

Primero verifica que los argumentos con los que se ejecuta el cliente son correctos. Si es asi instancia al cliente e inicia su ejecución.

#### ArgentumClient

Cuando se llama a su constructor inicializa SDL y crea un nuevo cursor. Luego ejecuta el gameLoop. El gameLoop comienza con el menú principal que se detalla mas adelante. Cuando el usuario logra conectarse, se lanzan dos hilos: Uno se encarga de procesar los eventos SDL que corresponden al input del usuario y el otro recibe actualizaciones del servidor. En cada loop del juego se ejecutan las actualizaciones recibidas y finalmente se reproducen los sonidos correspondientes y se renderiza. Cuando se termina el juego se cierra el socket del cliente y se hace join de los hilos.

#### BlockingQueue

#### ClientEventHandler

Argentum crea la cola Bloqueante sdlEvents a la que pushea los eventos que recibe. ClientEventHandler va desencolando sdlEvents y por cada evento arma un mensaje con toda la información necesaria y se lo envía al servidor.

#### ClientProtocol



#### GameGUI

Delega a la clase Map la actualización de lo que paso en el mapa(cuando se mueve una entidad o se lanza un hechizo). También se encarga de llamar a los métodos de renderizado de cada clase de la interfaz gráfica.

#### GameInitializer

Inicializa el juego con la información que recibe del servidor. Primero recibe el mapa. Itera por cada tile cargando el tipo de piso y un ciudadano o estructura si es que hay. Luego carga todos los monstruos, items o jugadores que haya en el mapa en el instante que el usuario se conecto.

#### ProtocolEnumTranslator

Cuando recibo del servidor un update que tiene informacion como un item o un tipo de suelo esto se recibe en forma de un enum que comparten tanto el servidor como el cliente. Del lado del cliente necesitamos traducir el enum recibido a un id de una textura para poder renderizar. De eso se ocupa esta clase

#### Update


#### UpdateManager


#### UpdateReceiver
