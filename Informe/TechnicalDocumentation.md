# Documentación técnica

### <u>Requerimientos de Hardware</u>

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
&nbsp;&nbsp;&nbsp;&nbsp;Clase que engloba la lista de clientes conectados y clientes en 
espera. Se utiliza para pedirle a cada cliente que realice alguna acción específica, protege
también la lista de espera de race conditions al juntarla con la lista de clientes activos. 
AGREGAR COSAS DE PLAYER MANAGER AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#### PlayerManager
AGREGAR COSAS DE PLAYER MANAGER AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#### ServerMonitor
AGREGAR COSAS DE SERVER MONITOR AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#### ServerProtocol
&nbsp;&nbsp;&nbsp;&nbsp;Se encarga de almacenar la información del mapa y los mensajes a
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
Contiene una lista con los items que se encuentran en su posición.
Delega acciones como list, attack, buy, etc al entity que almacena (si es que almacena uno)