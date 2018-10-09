#include <iostream>
#include "../inc/EventManager.hpp"

sf::Vector2i EventManager::manageClick(
    std::vector<std::vector<Card>> board, sf::Vector2f pos)
{
  sf::Vector2i v(-1,-1);
  /* Iterates through all cards of the board */
  for (std::size_t i=0; i<board.size(); i++) {
    for (std::size_t j=0; j<board[i].size(); j++) {
      Card c = board[i][j];
      /* Fills the vector if this is the right card */
      if (c.getSprite().getGlobalBounds().contains(pos.x, pos.y)) {
        v.x = i;
        v.y = j;
        return v;
      }
    }
  }
  std::cout << std::endl;
  return v;
}
