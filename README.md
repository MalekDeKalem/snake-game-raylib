# How to play
- First you have to acquire raylib by installing it :) obviously
- Or you can build it from source [here](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) this is especially relevant for Linux users

When the building process is done you have to link the library you just installed/build. Kinda like this:

```
g++ -I /path/to/headerfiles programm.cpp -o /path/to/lib
```

my headerfiles were in /usr/local/include while my library was in /usr/local/lib/.. \
This should be default. If however this is different on your setup you have to find out where the headerfiles and libs are.