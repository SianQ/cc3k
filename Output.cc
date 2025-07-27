export module Output;
import GameCore;  // 改为import GameCore

export class Output {
public:
    void render(const Level& level);  // Level现在来自GameCore
    void renderGameOver();
    void clearScreen();
};
