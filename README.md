# R-type

The purpose of this project is to create a one to four players game, based on a client / server architecture and an ECS game engine.

## Dependencies

The only dependencies are sfml-graphics and sfml-audio.
Optionally, to run the test suite, you'll need google-test.

All other abstractions and libraries has been written from scratch (e.g. the network, game engine, state machine, logger, protocol, etc..)

## Compilation on Linux/Windows

The compilation has been tested with:

- `cmake` v3.6 (for linux & windows)
- `gcc` v6+ (for linux)
- `msvc` v14 (for windows)

```shell
$ mkdir build; cd build
$ cmake ..
$ make
$ make install
```

`make install` will only move the built files in the `bin` in the repo folder.

You will find in the `bin` folder:

## Client-Server

Once the server is started, one or more clients can connect and join a room. Up to 4 players can play in a room, and the number of room is only limited by the capacities of the computer on which the server is running.

See the [RFC](/RFC) for informations on the protocol used between the client and the server.

## ECS Game engine

The game engine has an ECS architecture (Entity Component System), which allow great flexibility and ease of use.

More informations [here](https://en.wikipedia.org/wiki/Entity–component–system).
