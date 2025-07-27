module Output;
import GameCore;
import Map;
import Tile;
import Character;
import Player;
import Item;
import TerrainType;
import <iostream>;

using namespace std;

void Output::render(const Level& level) {
    clearScreen();
    
    const Map& map = level.getMap();
    int height = map.getHeight();
    int width = map.getWidth();
    
    // 渲染地图
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Tile& tile = map.getTile(x, y);
            
            // 优先显示角色
            if (Character* character = tile.getCharacter()) {
                cout << character->getSymbol();
            }
            // 其次显示物品
            else if (Item* item = tile.getItem()) {
                cout << item->getSymbol();
            }
            // 最后显示地形
            else {
                switch (tile.getTerrain()) {
                    case TerrainType::Floor:
                        cout << '.';
                        break;
                    case TerrainType::Passage:
                        cout << '#';
                        break;
                    case TerrainType::WallHorizontal:
                        cout << '-';
                        break;
                    case TerrainType::WallVertical:
                        cout << '|';
                        break;
                    case TerrainType::Door:
                        cout << '+';
                        break;
                    case TerrainType::Empty:
                        cout << ' ';
                        break;
                }
            }
        }
        cout << '\n';
    }
    
    // 显示玩家状态
    const Player& player = level.getPlayer();
    cout << "Race: " << player.getRace() 
         << " Gold: " << player.getGoldNum()
         << " HP: " << player.getHP() << "/" << player.getMaxHP()
         << " Atk: " << player.getAtk()
         << " Def: " << player.getDef()
         << " Floor: " << level.getFloorNumber() << endl;
    
    // 显示消息
    for (const string& msg : level.getMessages()) {
        cout << msg << endl;
    }
}

void Output::renderGameOver() {
    cout << "Game Over!" << endl;
}

void Output::clearScreen() {
    cout << "\033[2J\033[H"; // ANSI清屏命令
}
