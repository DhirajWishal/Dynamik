# Dynamik Engine
## Naming Convention

The engine uses a rather strict naming convention to make sure that the readability of the code is ensured. 
This allows clients to easily read and understand whats going on behind under the hood.

The naming convention is as follows:
#

Variables:
  Static variables which are inside a class or a struct must be in UpperCamelCase.
  Other variables inside a class or a struct may be lowerCamelCase.
  Global variables which are intended to be used by one module/ class or struct must contain double underscore to denote that the variable is reserved.
  Deceleration and definition of variables in function bodies may contain a single underscore at the bigging or may use lowerCamelCase.

Classes and Structs:
  Both classes and structs must be in UpperCamelCase.
  Classes or structs which the client is allowed to directly access must contain the "DMK" prefix.
  Classes or structs which are internal to a specific module and does not allow clients to use them contain a prefix to their module. (see below)
  Classes or structs inside another class or struct must always be in UpperCamelCase.

Functions:
  Global functions (which are not inside a class or a struct (methods)) must be in UpperCamelCase.
  Functions inside classes or structs must be in lowerCamelCase (static and non-static).
  Function parameters may contain a prefix to identify its type and the rest of the name is in UpperCamelCase. (see below)

Defines and Macros:
  Defines and Macros will always be in UpperSnakeCase (UPPER_SNAKE_CASE).

### Prefixes
"DMK"       - Stands for Dynamik and variables, classes or structs with this can be used by the client.
"A"         - An internal class or struct to the Animation module.
"R"         - An internal class or struct to the Renderer module.
"Vulkan"    - An internal class or struct to the VulkanRBL module.

'b'         - A B1 variable (bool).
'p'         - A pointer variable.
'i'         - An integer variable (signed/ unsigned or both).
'f'         - A F32 variable (float).

'I'/ 'I_'   - An interface class or struct. 