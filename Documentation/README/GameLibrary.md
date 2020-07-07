# Dynamik Engine Documentation
## Game Library

### Structure
- Game Package
  - Level Components
    - Game World
      - Entities - Contains components which performs a task/ tasks. By default entities do not have any 
        functionality. Entities are almost like wrappers to scene components but when given functionalities, 
        it can perform tasks like an NPC.
        - Audio Component
        - Physics Component
        - Renderable Component
          - Static Mesh
          - Animated Mesh
      - Environment Map
      - Light Components
    - Game Mechanics
      - Key Bindings
      - Win Condition
      - Game Mode
    - Player Object
      - Player Controller
      - Animation Controller
      - Character Components
      - Camera Module
        - Attachments
  - Game Menus
    - Layers
      - Layer Components

### Basic Description
#### Game Package
Game package is a super class which defines a game. This is the only way a game is imported to the engine.

#### Level Component
Level component directly translates to a level in the game. Every level contains entities (scene components),
game mechanics and a player object.

##### Entity
An entity is an object consisting of one or more components. Collectively this may recreate a complete asset, 
or another character, or any other complex object. By default these objects do not have any functionality.
In multi-player games, other players are considered as entities.

###### Components
Components are the containers which contain all the raw data (eg: Audio, Video, Mesh, ...). These components
are divided into 3 main types,
- Audio Component
- Renderer Component
- Compute Component (Used to perform calculations)

##### Game Mechanics
This defines the rules of a game. This includes,
- Key Bindings
- Win Conditions
- Game Modes 

##### Player Object
This is the object which the player/ user uses to interact with the game world. This is, as the name suggests,
the player in the game. This object updates and controls the camera module.

###### Player Controller
This component defines the player controls (waling, jumping, swimming, ...)

###### Character Components
This defines the components possessed by the player (Audio (Voice), Mesh (Skinned, Bone), Physics (Capsule), ...).

##### Camera Module
This is the main camera of the level. Even though cinematic cameras can be setup by game mechanics, this camera
is the active camera when the player is on a mission. HUDs can be added to the camera using attachments.

##### Game Menus
This is the main game UI. The game can have multiple UIs and the first menu will be loaded upon engine initialization.
A single menu or UI interface is called as a Level and level components provide buttons, textures and other 
visual and functional components.