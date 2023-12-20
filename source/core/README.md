# exile.core

# stage 1 
 - memory allocators
 - panic handler

panic handler initializing occurs by calling `exLoadCriticalConfiguration` or `exSetupCriticalDefaultConfiguration` for use default configuration
```cpp
u8 exLoadCriticalConfiguration(const char* file);
void exSetupCriticalDefaultConfiguration();
```
also this functions allows you to load new configuration in runtime but do not forget 
to call `exFreeCriticalConfiguration` firstly for to free current configuration!
```cpp
void exFreeCriticalConfiguration();
```

# stage 2

- fs: File, Path, DirectoryIterator
- Engine instance
- Plugin system
- Universal logging protocol

