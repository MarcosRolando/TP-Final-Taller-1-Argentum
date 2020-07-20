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

#### Servidor
&nbsp;&nbsp;&nbsp;&nbsp;Se encuentra subdividido en la parte del servidor 
en sí (conexiones, etc), el mapa, los items, el manejo general del estado 
del juego, la persistencia  y las entidades, además de la parte de 
configuración.  
&nbsp;&nbsp;&nbsp;&nbsp;Servidor:  Se encarga de aceptar y rechazar jugadores.
Toma los nuevos clientes que intentan conectarse y cumple con los pedidos que estos
realizan, crea nuevas cuentas, carga cuentas ya existentes, carga los jugadores 
delegándole al módulo de persistencia la inicializaión de estos con sus datos y
crea nuevos jugadores con los datos correspondientes cuando es necesario. Se encarga
de almacenar y mandar la información necesaria para que el cliente pueda mostrarle
de forma adecuada los sucesos del juego.  
&nbsp;&nbsp;&nbsp;&nbsp;Mapa: Se encarga de guardar las entidades e items 
en posiciones específicas de una matriz, para así facilitar las 
interacciones entre  estos y poder representarlos fácilmente en 
un espacio bidimensional.  
&nbsp;&nbsp;&nbsp;&nbsp;Items: Se encarga de manejar los atributos de los
distintos items existentes y la interacción entre estos y las distintas
entidades del juego. Unos ejemplos de esto son la comunicacíon al jugador
de dónde debe equiparse un item al ser utilizado (o si es consumido), 
la existencia del inventario del jugador, y los drops de los monstruos 
al morir.  
&nbsp;&nbsp;&nbsp;&nbsp;Estado del juego: Se encarga de realizar todos los
cambios que le pidan los distintos componentes del juego, delega los pedidos
a las clases correspondientes cuando deba hacerlo. Se encarga tamién de 
algunas reglas particulares del juego como los spawns de monstruos y 
resurrección de jugadores.  
&nbsp;&nbsp;&nbsp;&nbsp;Persistencia: Se encarga de mantener la información
entre conexiones de los distintos jugadores con cuenta, guardándolos en un 
archivo. Realiza guardado de datos periódicamente y cuando los jugadores se desconectan.  
&nbsp;&nbsp;&nbsp;&nbsp;Entidades:  Se encarga re "darle vida" al juego. Este módulo
maneja los jugadores y npcs con los que interactuará el usuario. Maneja el comportamiento
de los monstruos, los ciudadanos (curas, comerciantes y banqueros) y los jugadores.  
&nbsp;&nbsp;&nbsp;&nbsp;Configuración: Se encarga de trabajar con los archivos de 
configuración del juego, aquellos usados para cambiar los distintos valores del juego sin
necesidad de recompilarlo. Trabaja con los archivos config.json y map.json.