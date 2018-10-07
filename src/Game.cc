#include "Game.h"

using namespace Monarchy;

Game::Game() {
    // return world;
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
