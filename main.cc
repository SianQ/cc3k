import "Cc3k.h";
import <iostream>;
import <string>;
import <chrono>;
import <stdexcept>;

int main(int argc, char* argv[]) {
    // 1) Defaults
    std::string mapPath = "defaultMap.txt";
    unsigned seed = static_cast<unsigned>(
        std::chrono::system_clock::now()
            .time_since_epoch()
            .count()
    );

    // 2) Parse args
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-m") {
            if (i + 1 >= argc) {
                std::cerr << "Error: -m requires a <mapPath>\n";
                return 1;
            }
            mapPath = argv[++i];
        }
        else if (arg == "-s") {
            if (i + 1 >= argc) {
                std::cerr << "Error: -s requires a <seed>\n";
                return 1;
            }
            try {
                seed = static_cast<unsigned>(std::stoul(argv[++i]));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid seed: not a number\n";
                return 1;
            } catch (const std::out_of_range& e) {
                std::cerr << "Invalid seed: out of range\n";
                return 1;
            }
        }
        else {
            std::cerr << "Unknown option: " << arg << "\n";
            std::cerr << "Usage: " << argv[0]
                      << " [-m <mapPath>] [-s <seed>]\n";
            return 1;
        }
    }

    // For demonstration: print what we got
    std::cout << "Using map file: " << mapPath << "\n";
    std::cout << "Using RNG seed: " << seed << "\n";

    Cc3k game(mapPath, seed);
    game.run();

    return 0;
}
