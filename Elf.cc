#include "Elf.h"
#include "Gold.h"
#include <cstdlib>

Elf::Elf(int row, int col)
  : Enemy(140,30,10,row,col,"E",true,false) {}

void Elf::act(Map& map, Player& pc) {
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

void Elf::attack(Player& pc) {
    pc.beAttackedBy(this);
    if(!pc.isDead() && pc.getRace()!="Drow") {
        pc.beAttackedBy(this);
    }
}

std::vector<Item*> Elf::dropLoot() const {
    return { new Gold(2,false) };
}
