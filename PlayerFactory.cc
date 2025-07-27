export module PlayerFactory;

import Player;
import Shade;
import Drow;
import Vampire;
import Troll;
import Goblin;
import <memory>;
import <string>;

export std::unique_ptr<Player> createPlayer(const std::string& race);
