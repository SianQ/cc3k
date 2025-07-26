// export module Cc3k;

// import level;

// export 
export module Cc3k;
import Input;
import Level;
import Output;


export class Cc3k {
private:
    Level level;
    Input input;
    Output output;
    std::default_random_engine masterRng;
    std::string mapPath;
    bool isRunning;

public:
    Cc3k(std::string mapPath, int seed);
    void run();
};
