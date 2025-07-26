module Decorator;

Decorator::Decorator(std::shared_ptr<Player> nxt)
  : Player(
        nxt->getHP(),      // current HP
        nxt->getAtk(),     // attack
        nxt->getDef(),     // defense
        nxt->getMaxHP(),   // max HP  ← use the correct accessor
        nxt->getRace()     // race string
    ),
    next(std::move(nxt))
{}
