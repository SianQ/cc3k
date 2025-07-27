export module Input;

import GameCore;  // 改为import GameCore
import <iostream>;

export class Input {
public:
    void applyInput(Level& level);  // Level现在来自GameCore
};
