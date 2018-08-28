#ifndef PLAYER_LIST_H
#define PLAYER_LIST_H

#include <map>
#include <iostream>
#include "PlayerBody.h"
#include "PlayerMind.h"

namespace Monarchy {
	class PlayerList
	{
	private:
		std::map<UnitId, PlayerMind> minds;
		std::map<UnitId, PlayerBody> bodies;
	public:
		PlayerList();
		PlayerBody& addPlayerBody(PlayerBody&& body);
		PlayerBody& addPlayerBody(PlayerBody& body);
		PlayerBody& getPlayerBody(UnitId id);
		
		PlayerMind& addPlayerMind(PlayerMind&& mind);
		PlayerMind& getPlayerMind(UnitId id);
		
		void print(){
			// Iterating the map and printing unordered values
			std::cout << "BODIES" << std::endl;
		    for (auto i = bodies.begin(); i != bodies.end(); i++) {
		        std::cout << "index: " <<  i->first << '\n';
		        std::cout << i->second << '\n';
		    }
		}
	};
}


#endif /* PLAYER_LIST_H */
