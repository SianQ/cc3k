module Input;
import Direction;
import <iostream>;
import <string>;

using namespace std;

void Input::applyInput(Level& level) {
    string command;
    cout << "Enter command: ";
    getline(cin, command);
    
    if (command.empty()) return;
    
    char action = command[0];
    Direction dir = Direction::North; // 默认方向
    
    // 解析方向（如果有第二个字符）
    if (command.length() > 1) {
        switch (command[1]) {
            case 'n': dir = Direction::North; break;
            case 's': dir = Direction::South; break;
            case 'e': dir = Direction::East; break;
            case 'w': dir = Direction::West; break;
            case 'a': dir = Direction::NorthEast; break;
            case 'z': dir = Direction::NorthWest; break;
            case 'd': dir = Direction::SouthEast; break;
            case 'x': dir = Direction::SouthWest; break;
        }
    }
    
    switch (action) {
        case 'n': case 's': case 'e': case 'w':
        case 'a': case 'z': case 'd': case 'x':
            level.playerMove(static_cast<Direction>(action - 'a'));
            break;
        case 'f': // 攻击
            level.playerAttack(dir);
            break;
        case 'u': // 使用药水
            level.playerPotion(dir);
            break;
        case 'q': // 退出
            // 设置游戏结束标志
            break;
    }
}