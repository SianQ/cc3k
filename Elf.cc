import Enemy;

export class Elf : public Enemy {
public:
    Elf();
    int attack(const Character* target, bool isSuccess) override;
};
