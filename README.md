# Monarchy: Simple Multi-Agent Game

## Overview of The Game
There are two teams, each with their own monarch. The objective of the players is to eliminate the opponent monarch. Players are of different roles and accordingly can perform different actions. As of now, there are three basic roles: Leader (monarch), Archer, Spearman.
The actions and the agents that are allowed to perform them are as follows:

Action Name | Action Description | Agent
------------ | ------------- | -------------
PlayerReproduction | Spawns a new player into the game | Leader
ArrowAttack | Shoots an arrow | Archer
SpearAttack | Hurls a spear | Spearman
PlayerWalk | Moves to an adjacent position | All Players

Both ArrowAttack and SpearAttack cause certain amount of damage and can be perfomed only if the target is within the agent's reach; such specific parameters can be found in [config/server.h](./config/server.h).

## Usage
First build the server and the teams:
```
make
```
and then run the game by running:
```
bin/monarchy
```

## Team Integration
If teams are put in the [teams](./teams/) folder with a structure similar to that of [sample_team](./teams/sample_team), then they can be smoothly integrated into the game; that is to say, you can build and link your team just by running the usual make. The only modification that needs to be made is the initialization of the team in [game_setup.cc](./game_setup.cc).
Otherwise, modfiy the makefile to make sure that the code for your team is compiled and the objects are linked with server objects and game_setup.cc to producde the final binary.

## Tests

The game comes with an almost comprehensive set of tests for server functionality. In order to run these, first install Google Test on your device and then change GTEST_DIR in the [Makefile](./Makefile) to the path to your GTest installation. Then, you can make and run the tests by:
```
make tests
```
If you ever wanted to work on the code for the game server, you can also format your code by installing astyle on your device and running:
```
make format
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
