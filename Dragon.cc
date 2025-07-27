export module Dragon;
import Enemy;

export class Dragon : public Enemy {
private:
    int hoardX = -1;
    int hoardY = -1;
public:
    Dragon();
    void setHoard(int x, int y);
    int getHoardX();
    int getHoardY();
};
