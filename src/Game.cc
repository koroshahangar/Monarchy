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
    static auto nextAgent = world.getPlayerMinds().begin(); // Whose turn is it?
    if(nextAgent == world.getPlayerMinds().end())
        nextAgent = world.getPlayerMinds().begin();
    UnitId unit_id = nextAgent->second->getUnitId();
    PlayerMovePtr move = nextAgent->second->makeAMove(world.getGameState());
    try {
        updater.handleMove(move, unit_id);
    } catch(std::exception) {
        std::cout << "server: exception thrown by updater while handling move" << std::endl;
    }
    nextAgent++;
    world.getGameState().turn_count++;
    std::cout << world.getGameState() << std::endl;
}

void Game::run() {
    while(true)
        executeNextMove();
}
