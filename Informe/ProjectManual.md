# <u>Manual de Proyecto</u>



### Integrantes y división de tareas

##### Agustín Cambiano (centrado en el servidor):
- Diseño del servidor (se pensó una idea general entre todos pero se fueron aplicando cambios particulares)
- Clases relacionadas al mapa (Map, Tile, etc.)
- Spawn y decisiones de movimiento y ataque de monstruos
- Código relacionadas a los items (Inventory, Item, drops, etc.)
- Código relacionado al funcionamiento de los comandos realizados por
los jugadores (drop, buy, sell, deposit, withdraw, etc.)

##### Iván Soriano (centrado en el cliente):

- Reproducción de sonidos y música
- Texto
- Interfaz Gráfica (salvo mapa).
- Minichat del cliente
- Interacción por parte del usuario
- Eventos del cliente
- Menú Principal
- Configuración
- Protocolo del lado del cliente
- Clase de ecuaciones del juego
- Clase de lectura del archivo JSON de configuracion
- Comandos ingresados por el usuario

##### Marcos Rolando (inicialmente cliente, luego servidor y al final ambos):

- Interfaz gráfica del mapa, entidades, hechizos, flechas, etc.
- Animaciones.
- Lágica de updates del cliente.
- Protocolo del lado del cliente (aportando también al del servidor).
- Persistencia del servidor.
- La mayor parte del manejo de conexiones de los clientes en el servidor.
- Desplazamiento gradual de las entidades en el servidor (interpolación).
- Lógica del Minichat del servidor.
- Mapa utilizado, armado con Tiled.
- Generado del JSON del mapa, lectura del mapa en el servidor.
- Interacción entre el cliente y el player (PlayerProxy).
- Manejo de vida, maná y niveles de los jugadores y monstruos del servidor.
- Texturas del cliente.
- Lógica de sincronización entre el cliente y el servidor.

### Evolución del proyecto

- Las primeras tres semanas se siguió el calendario propuesto en el enunciado del TP para el cliente al pie de la letra, incluso adelantando cosas.
  El servidor se encaró más globalmente, es decir, al final de las primeras semanas se había hecho lo propuesto pero no en el
  orden propuesto. La segunda mitad del TP ya se abandonó lo propuesto dado que no se adaptaba a las circunstancias del momento
  (fixes de bugs, secciones del TP que necesitaban mas atención, etc) volviendose todo más dinámico pero siempre habiendo
  total comunicación entre los integrantes del grupo.

### Inconvenientes
- Inicialmente se manejaba el movimiento en base a un unico mensaje del cliente pero el cliente podia mantener la tecla
  y enviar continuamente mensajes al servidor, esto perjudicaba el performance del cliente y sobrecargaba innecesariamente
  al Servidor. Se revisó esto con el corrector y se solucionó de forma sencilla gracias a 
  al modelo de Eventos (para las acciones de los clientes) con el que se desarrolló el Servidor.
  
- Inicialmente aparecieron unas race conditions en el Minichat pero se solucionaron rápidamente. La mayor parte del TP se ejecuta
  secuencialmente por lo que salvo esa situacion en particular no se nos presentaron race conditions.
  
- Habia un bug en el guardado de los jugadores donde nos estabamos olvidando de actualizar el unordered map (pero lo actualizabamos bien en el archivo).
  Bajo ciertas condiciones especificas (si cambiaba el tamaño de los datos del jugador y se reconectaba sin haber reiniciado el server)
  esto rompia. Se logró encontrar y solucionar sencillamente este error pero tomó más tiempo del esperado.
  
- Como hay un solo thread que acepta clientes y nosotros inicialmente nos conectabamos primero y enviabamos nuestro nombre/raza/clase
  para que el aceptador nos aceptara, sucedía que mientras esperaba para recibir nuestro datos bloqueabamos a otros clientes que querían conectarse.
  Esto se solucionó haciendo que al momento de conectarnos ya le enviasemos toda la información requerida por el Servidor para entonces no
  bloquear a otros jugadores que quisieran conectarse. Si bien idealmente el puerto/ip es lo primero que se eligiria es por este motivo que
  se selecciona al final: la idea era cambiarlo pero no nos dio el tiempo y no lo consideramos algo que arruine la experiencia del usuario.

### Herramientas

- CLion 2020.1.2 (todos los integrantes).
- Git.
- Tiled (para generar el mapa y su JSON).
- Photopea y online-image-editor (para armar texturas acorde al formato que leemos).
- Catch2 para el framework de las pruebas, combinándolo con Fakeit para poder generar stubs.

### Conclusiones

- Aprendimos a trabajar en grupo y distribuir las tareas eficientemente.
- Aprendimos a utilizar librerias externas y leer su documentación (Catch, Fakeit, Msgpack, nholmannJson).
