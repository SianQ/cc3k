#include "Orc.h"
#include "Gold.h"
#include <cstdlib>
#include <cmath>

Orc::Orc(int row, int col)
  : Enemy(180,30,25,row,col,"O",true,false) {}

void Orc::act(Map& map, Player& pc) {
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

void Orc::attack(Player& pc) {
    int base = calculateDamage(atk, pc.getDef());
    int dmg  = (pc.getRace()=="Goblin")
             ? static_cast<int>(std::ceil(base*1.5))
             : base;
    pc.takeDamage(dmg);
}

std::vector<Item*> Orc::dropLoot() const {
    return { new Gold(2,false) };
}
