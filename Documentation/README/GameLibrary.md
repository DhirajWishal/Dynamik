# Dynamik Engine Documentation
## Game Library

The Dynamik Engine allows users a maximum degree of freedom in designing a game. The entire application is submitted 
using the object "DMKGameServer". This object contains the actual engine runtime and allows users to interact directly 
with the runtime itself. The game logic is coded into "DMKGameModule" and is presented using the game server.

### DMKGameServer
This object is the actual engine instance. Although the runtime is not fully visible and usable to the user, some 
functionalities are enabled allowing users to interact directly with the engine runtime or with the systems. This 
object contains the basic information and the startup of the game application. The reason why this object is called the 
"GameServer" is because this object occupies a full thread and all the other major systems are in different threads and 
are behaves more like servers. 
This object is responsible of initializing the game code, submitting system listeners which are required by the game, 
loading game modules, handling logins, and much more.

### DMKGameModule
This object is considered as one game match (eg: Capture the flag, Search and destroy, Battle Royale, ...). This object 
contains the logic based on the current player's perspective. This module contains the game world (inheritable).

### DMKGameWorld
The game world holds information about one game world/ map. All of the data in this is submitted using Entities, Environment 
Maps and Light Components. This allows one module to switch between game worlds at runtime. 

#### Dynamik Entity System
Entities in the engine represent objects with some behavior/ functionality attached to it. The engine supplies multiple 
Entity types which the users are allowed to inherit from and use. Some of these entities are: 
- DMKPlayerEntity
  - This entity contains all the required information about the player character.
  - The player entity is attached to the player controller at runtime.
- DMKStaticModelEntity
  - This entity holds information about one single model which contains one or more meshes. 
  - This model contains a rendering specification which is applies to all the mesh objects stored in it.
  - Allows instancing (Adding copies of one entity).
- DMKAnimatedModelEntity
  - This is the same as the static model entity but this contains animation information. 
  - Allows instancing.
- DMKAudioControllerEntity
  - This object stores information about audio.
  - Audio data are submitted using this entity.
- DMKPhyaicalEntity
  - This object stores physics information about an entity.
- DMKTrigger2D
  - This entity suplies the entity with trigger mechanisms.
  - Triggers occur when a certain event occurs to an entity. 
  - This is a 2D instance of a trigger and only accepts events from the perpendicular axis of the specified axises. 
  - Instances can be added which will contains an ID to uniquily identify the trigger instance.
- DMKTrigger3D
  - This entity is the same as the 2D entity but it contains 3D bounds.
- DMKCanvasEntity
  - This provides an entity with a 2D canvas which the user can draw or wright anything to. 
  - Mostly this is used in menus and HUDs.
  - Buttons are required to be added using Trigger2D or trigger3D entities.

To create an entity, users are required to inherit their entity from these entities. All the entities are suplied using 
the game world. And entities are to be initialized and submitted to the relevant systems explicitly in the 
onInitializeEntities() method.

##### Warning: Do not inherit from both DMKAnimatedModelEntity and DMKStaticModelEntity at the same time as the animated model is inherited from the static model entity.