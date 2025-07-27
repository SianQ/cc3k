module Decorator;

Decorator::Decorator(std::shared_ptr<Player> nxt)
  : Player(
      nxt->getRace(),     // race string
      nxt->getHp(),      // current HP
      nxt->getAtk(),     // attack
      nxt->getDef()     // defense
    ),
    next(std::move(nxt))
{}
