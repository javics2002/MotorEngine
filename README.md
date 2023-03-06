# P3-Motor
Motor de videojuegos desarrollado como parte de la asignatura Proyectos III en el grado de Desarrollo de Videojuegos de la UCM

## <p align="center">**MOTOR ENGINE**</p>
<div align="center">
    <img src="readme_assets/engine_logo.png" alt="engine_logo" width="827" height="400">
</div>

* Javier Cano Salcedo, jacano01@ucm.es 
* José Miguel Villacañas, josemv03@ucm.es 
* Pablo Arredondo Nowak, pablarre@ucm.es
* Rodrigo Cabello Hernández, rodricab@ucm.es
* Alfonso Rodulfo Guío, arodulfo@ucm.es
* Diego Rol Sánchez, drol@ucm.es 
* Pedro Pablo Cubells Talavera, pablocub@ucm.es 
* Liyuan Li, liyli@ucm.es

## <p align="center">**LINKS DE INTERÉS**</p>

<div align="center">
  <a href="https://www.pivotaltracker.com/n/projects/2630589">
    <img src="readme_assets/pivotal_logo.png" alt="Logo_pivotal" width="214" height="80">
  </a>
</div>


|**Hitos**| |
| ------ | ----------- |
| 0. Propuesta del concepto: 13 de febrero de 2023  | 1. Arquitectura base: 6 de marzo de 2023  |
|2. Ciclo de juego: 27 de marzo de 2023 | 3. Release: 5 de mayo de 2023 |

## Estructura de clases del motor
MotorEngine es un motor de videojuegos concebido para crear videojuegos de carreras. El motor está compuesto por una serie de módulos que gestionan una gran parte del trabajo.
Cada módulo contiene un h declarando todas las clases y métodos que defina y un main.cpp que testea el funcionamiento del módulo en modo DEBUG.
MÓDULOS:
- MotorEngine
- Components
- Render
- Physics
- Input
- Audio
- Utils
- Scripting


### MotorEngine
En este proyecto tendremos las funciones que se ejecutarán al inicio del programa;
MotorEngine se encarga de crear todos los módulos del proyecto necesarios para el motor, ejecutará el bucle principal (encargado de la ejecución de la física y el render con distintos cronómetros) y eliminará  toda la memoria creada para la ejecución del motor.
En la función principal (main.cpp) se encuentran las funciones siguientes. Su descripción está comentada en el código.
int setup();
void loop();
void exit();

Además, en el namespace propio de MotorEngine, el módulo define los siguientes métodos y funciones, cuya descripción también está definida en el encabezado.

```
void updateTimeValues(const std::chrono::steady_clock::time_point& beginFrame,const std::chrono::steady_clock::time_point& endFrame, const std::chrono::steady_clock::time_point& gameStartFrame);

static int quitLoop(void* userdata, SDL_Event* event);
```

### Components
La arquitectura que usa el motor para gestionar las entidades está basada en componentes. Cada escena contiene una serie de entidades cuya información y comportamiento se define en base a los componentes.
Un componente es… define los métodos…
Componente
Descripción
Transform
Este componente posee los métodos set de distintas características (posición, escala dada la nueva escala o escalar la actual con un factor, rotación), de la misma forma tiene métodos get de las mismas características. 

Por otro lado puede añadir como un hijo un transform de un objeto o eliminarlo. También puede contar los hijos que tiene, devolver quién es su padre o quien es su hijo. 

| Componente | Descripción |
| ------ | ----------- |
| Rigidbody | Este componente posee los métodos set de distintas cualidades (masa, trigger, fricción y restitución). La constructora simplemente asigna la información recibida, el start por su parte es el que le da la información al physics manager para poder darle presencia en el mundo .También puede aplicar un impulso o una fuerza. |
| MeshRenderer | |
| AudioPlayer | |
| AudioListener | |
| Animator | |
| Collider | |

### Render
El módulo de render incorpora la clase Ogre Manager, que contiene y añade información sobre el renderizado de las entidades.
Este módulo está dividido en varias clases, la primera ya presentada OgreManager, la siguiente clase incluida en este módulo es Ogre Window, que contiene toda la información relacionada con la ventana del juego.
Por último, contiene Ogre Camera, que tiene toda la información relacionada con la cámara (necesaria para el renderizado).
Physics
El proyecto de input incorpora la clase Physics Manager, un singleton que ofrece información y métodos relevantes para el uso de Bullet y la gestión del mundo físico.
Physics Manager gestiona la creación de objetos físicos (“Rigid Bodies”), así como de objetos fantasmas(“Triggers”) así como de su mantenimiento.

Con la constructora establecemos la configuración de las colisiones a la par que inicializamos el mundo dinámico donde interactúan las distintas entidades. 
En esta clase se pueden crear rigid bodies con distintas características y a su vez añadirlos al mundo dinámico para que se tengan en cuenta a la hora de las colisiones o actualización de alguna de sus características.
Cuenta con los siguientes métodos: 
```
PhysicsManager()
btCollisionShape *createShape(Shapes shape, btVector3 *scale)
void createRigidBody(btTransform *transform, btVector *scale, Shapes shape, MovementType mvType, bool isTrigger, float friction, float mass, float restitution)
```

### Input
El proyecto de input incorpora la clase InputManager, un singleton que ofrece información y soporte para callbacks para cualquier input del usuario, ya sea una tecla del teclado, un botón del ratón o un botón de un gamepad.
InputManager gestiona botones y ejes virtuales para que puedan enlazarse con cualquier input y desenlazarse en tiempo de ejecución.
Un botón virtual cuenta con un nombre y un booleano pressed. Un botón virtual puede corresponder con uno o varios Input. Un input contiene información del tipo de evento de SDL que lo acciona, para distinguir si se trata de un input del teclado, del ratón o de un gamepad. 
Un eje virtual cuenta con un nombre, un número racional entre -1 y 1 value, un valor gravity que representa la velocidad con la que el eje vuelve al 0 cuando no hay input y un valor dead que representa la distancia que tiene que registrar el eje para que se empiece a detectar.
Internamente, el InputManager utiliza std::unordered_map para encontrar cada botón y cada eje por su nombre en tiempo constante, así como para encontrar a qué botón virtual  o eje corresponde un input.
Los métodos que proporciona son los siguientes. Su descripción está comentada en el código.
```
void addEvent(SDL_EventFilter filter, void* userdata = NULL);
void deleteEvent(SDL_EventFilter filter, void* userdata = NULL);

bool addButton(std::string name);
bool addButton(std::string name, Input input);
bool deleteButton(std::string name);

bool addAxis(std::string name, AxisInfo info);
bool addAxis(std::string name, AxisInfo info, AxisInput input);
bool deleteAxis(std::string name);

bool addBinding(std::string name, Input input);
bool addBinding(std::string name, AxisInput input);
bool deleteBinding(std::string name, Input input);
bool deleteBinding(std::string name, AxisInput input);

bool getButton(std::string name);
float getAxis(std::string name);

bool addOnButtonPressedEvent(std::string name, int(*callback)(void*), void* additionalData = NULL);
bool deleteOnButtonPressedEvent(std::string name, int(*callback)(void*), void* additionalData = NULL);
```

### Audio
El proyecto de audio incorpora la clase SoundManager, un singleton que ofrece los wrappers necesarios para usar las funcionalidades de FMOD. 
La clase SoundManager implementa la creación, reproducción, gestión y modulado de efectos de sonido y música, así como toda la infraestructura de canales y grupos de canales necesarias para la correcta reproducción de audio.
Internamente el SoundManager usa dos “unordered_map”, uno para guardar la información sobre la reproducción de sonidos en sus respectivos canales de audio y uno para realizar la creación, gestión y almacenaje de los grupos de canales.
Los métodos que proporciona son los siguientes. Su descripción está comentada en el código.
```
void systemRefresh();
void create3DSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel);
void createNormalSound(const char* soundPath, FMOD::Sound*& soundHandle, int channel);
void setSpeed(FMOD::Sound* soundHandle, float newSpeed);
void setMode(FMOD::Sound* sound, int flags);
void createChannel(const char* newChannelGroup);
void setVolume(FMOD::Sound* sound, float value);
float getVolume(FMOD::Sound* sound);
void stopSound(FMOD::Sound* sound);
void pauseSound(FMOD::Sound* sound, bool pause);
void playSound(FMOD::Sound* soundHandle, bool isLoop, const char* channelGroup, int timesLooped = -1);
void deleteSound(FMOD::Sound* soundHandle);
void updateListenersPosition(int index, FMOD_VECTOR listenerPos, FMOD_VECTOR listenerFW, FMOD_VECTOR listenerUP, FMOD_VECTOR listenerVel = { 0,0,0 });
void removeListener(int index);
void setSoundPosition(FMOD::Sound*& sound,Vector3 position);
int getNextUsefulListenerIndex();
```

### Utils

### Scripting

## Estructura de componentes del motor y del juego
<div align="center">
    <img src="readme_assets/architecture.png" alt="Arquitectura de MotorEngine" width="827" height="400">
</div>

## Estructura de la solución y repositorios de Git
MotorEngine
Vroom Vroom
|-MotorEngine
|---------Src
|---------Main
|---------Ogre
|---------Fmod
|---------Lua
|---------LuaBridge
|---------Bullet
|---------Nuklear
|---------Entity-Component
|---------SDL
|---------Utils
|---------Projects
|---------Main
|---------Ogre
|---------Fmod
|---------Lua
|---------LuaBridge
|---------Bullet
|---------Nuklear
|---------Entity-Component
|---------SDL
|---------Utils
|---------Dependencies
|---------CMake
|---------bin
|---------share
|---------Ogre
|---------Src
/--  --  -- Build
|---------Lua
|---------Fmod
|---------Nuklear
|---------Bullet
|---------SDL
/--  --  -- Exe
/--  --  -- Assets
/--  --  -- x64
/--  --  -- Debug
/--  --  -- Lib
/--  --  -- Ogre
/--  --  -- Fmod
/--  --  -- Lua
/--  --  -- LuaBridge
/--  --  -- Bullet
/--  --  -- Nuklear
/--  --  -- Entity-Component
/--  --  -- SDL
/--  --  -- Utils
/--  --  -- Temp
/--  --  -- Ogre
/--  --  -- Fmod
/--  --  -- Lua
/--  --  -- LuaBridge
/--  --  -- Bullet
/--  --  -- Nuklear
/--  --  -- Entity-Component
/--  --  -- SDL
/--  --  -- Utils
|-VroomVroom
|---------Src
|---------Project
/--  --  -- Bin
/--  --  -- Temp
/--  --  -- MotorEngine

## Pipeline de generación de contenido
Tipo de archivo
Carpeta
Extensión
Fuentes
Fonts
.ttf y .fontdef
Audios	
Sounds
.mp3 y .wav
Materiales
Materials
.material
Texturas
Materials/Textures
.png y .jpg
Modelos
Models
.mesh
Mapas
Saves
.txt
Scripts
Scripts
.lua
Partículas
Particles
.particle



