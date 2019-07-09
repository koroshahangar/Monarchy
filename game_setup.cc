#include "Game.h"
#include "SampleTeam.h"
#include "EventReport.h"
#include "socket.h"
using namespace Monarchy;

int main() {
    Game game;
    string team_name = "First Team";
    TeamId team_id = game.getWorld().getNewTeamId();
    game.addTeam(std::make_unique<SampleCode::SampleTeam>(team_name, team_id));
    team_name = "Second Team";
    team_id = game.getWorld().getNewTeamId();
    game.addTeam(std::make_unique<SampleCode::SampleTeam>(team_name, team_id));
    std::cout << "Please run the Monarchy Monitor to be able to interact with the server" << std::endl;

    setup_socket();

    while(true) { // message loop
        valread = read( new_socket , buffer, Monitor::MSG_SIZE);
        if(!valread) {
            std::cout << "failed to read from the socket" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        // std::cout << "INPUT FROM MONITOR: " << buffer << std::endl;
        if(std::strcmp(buffer, "next\r\n") == 0) {
            game.executeNextMove();
            const char * msg = game.getUpdater().latestEvent.c_str();
            send(new_socket , msg , strlen(msg) , 0 );
        } else if(std::strcmp(buffer, "run\r\n") == 0) {
            while(true) {
                game.executeNextMove();
                const char * msg = game.getUpdater().latestEvent.c_str();
                send(new_socket , msg , strlen(msg) , 0 );
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        } else if(std::strcmp(buffer, "begin\r\n") == 0) {
            std::string msg_str = EventReport::BattleBegins(game.getWorld());
            const char * msg = msg_str.c_str();
            send(new_socket , msg , strlen(msg) , 0 );
        } else if(std::strcmp(buffer, "quit\r\n") == 0)
            break;
        memset(buffer, 0, sizeof buffer);
    }
    close(server_fd);
    close(new_socket);
    return 0;
}
