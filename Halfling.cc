#include "Halfling.h"
#include "Gold.h"
#include <cstdlib>

Halfling::Halfling(int row, int col)
  : Enemy(100,15,20,row,col,"L",true,false) {}

void Halfling::act(Map& map, Player& pc) {
    for(int dr=-1; dr<=1; ++dr) {
        for(int dc=-1; dc<=1; ++dc) {
            if(dr==0 && dc==0) continue;
            int nr=row+dr, nc=col+dc;
            if(!map.isPassible(nr,nc)) continue;
            auto *ch = map.getTile(nr,nc).getCharacter();
            if(ch && ch->isPlayer()) {
                attack(pc);
                return;
            }
        }
    }
    static constexpr int dirs[8][2] = {{-1,-1},{-1,0},{-1,1},
                                       { 0,-1},        { 0,1},
                                       { 1,-1},{ 1,0},{ 1,1}};
    std::vector<std::pair<int,int>> moves;
    for(auto& d:dirs) {
        int nr=row+d[0], nc=col+d[1];
        if(map.isPassible(nr,nc)) moves.emplace_back(nr,nc);
    }
    if(!moves.empty()) {
        auto [nr,nc] = moves[std::rand()%moves.size()];
        map.moveCharacter(row,col,nr,nc);
        row=nr; col=nc;
    }
}

void Halfling::attack(Player& pc) {
    pc.beAttackedBy(this);
}

void Halfling::beAttackedBy(Character* attacker) {
    // 50% evade
    if(std::rand()%2 == 0) return;
    Character::beAttackedBy(attacker);
}

std::vector<Item*> Halfling::dropLoot() const {
    return { new Gold(2,false) };
}
