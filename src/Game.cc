#include "Game.h"

using namespace Monarchy;

Game::Game() {

}

World& Game::getWorld() {
    return world;
}

WorldUpdater& Game::getUpdater() {
    return updater;
}

void Game::addTeam(TeamPtr team) {
    world.addTeam(std::move(team));
}

void Game::executeNextMove() {
    if(world.getPlayerMinds().size() == 0)
        return;
    static auto turn = world.getPlayerMinds().begin(); // Whose turn is it?
    if(turn == world.getPlayerMinds().end())
        turn = world.getPlayerMinds().begin();
    UnitId unit_id = turn->second->getUnitId();
    PlayerMovePtr move = turn->second->makeAMove(world.getGameState());
    try {
        updater.handleMove(move, unit_id);
    } catch(std::exception) {
        std::cout << "GOT AN EXCEPTION" << std::endl;
    }
    turn++;
}

void Game::run() {
    while(true)
        executeNextMove();
}
