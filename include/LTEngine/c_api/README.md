# C API
The C API is designed to provide compatibility with C users for bindings, choice and preformance.


## How?
### Short answer
Void pointers, also known as handles.

### Long answer

The way communication with C++ is done is with handles which are basically void pointers, the modification and reading of handles is wrapped around functions that take the handles as input.


## Developing with the C API
All handles can be casted to eachother. Relationships are marked by if it is automatically casted to the base type. Any compatible relationship will have child object `typedef`ed as the base object. Handles can be manually created easily and you can get the void pointer easily.


## Conventions

Because namespaces are non existant in C, they aren't used. All objects are named this way `LTEngine_{Actual Object Name}`. Functions are named like `LTEngine_{Object name}_{Function Name}`. Examples are easily found within the codebase.