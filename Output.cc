export module Output;
import Level;

export class Output{
public:
    void render(const Level& level);
    void renderGameOver();
    void clearScreen();
};
