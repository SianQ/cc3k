// export module Cc3k;

// import level;

// export 
export module Cc3k;
import Input;
import GameCore;  // 改为import GameCore而不是Level
import Output;
import <string>;
import <random>;


export class Cc3k {
private:
    Level level;  // Level现在来自GameCore模块
    Input input;
    Output output;
    std::default_random_engine masterRng;
    std::string mapPath;
    bool isRunning;

public:
    Cc3k(std::string mapPath, int seed);
    void run();
};
