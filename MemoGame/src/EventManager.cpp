#include <iostream>
#include "../inc/EventManager.hpp"

sf::Vector2i EventManager::manageClick(std::vector<std::vector<Card>> board, sf::Vector2f pos)
{
  sf::Vector2i v(-1,-1);
  /* Iterates through all cards of the board */
  for (std::size_t i=0; i<board.size(); i++) {
    for (std::size_t j=0; j<board[i].size(); j++) {
      Card c = board[i][j];
      if (c.getSprite().getGlobalBounds().contains(pos.x, pos.y)) {
        v.x = i;
        v.y = j;
      }
      return v;
    }
  }
  return v;
}


        /* Checks that the card is not already flipped over */
        /**
        if (!c.flipFront()) {
          cardId cid = { (Textures::ID)c.getPairId(), (int)i, (int)j };
          switch (gs.getState()) {
            case GameState::PendingForFirstCard:
              std::cout << "Click détecté, état 1" << std::endl;
              gs.flipFirstCard(cid);
              break;
            case GameState::PendingForSecondCard:
              std::cout << "Click détecté, état 2" << std::endl;
              gs.flipSecondCard(cid);
              break;
            case GameState::GameOver:
              std::cout << "Click détecté, état 3" << std::endl;
              break;
          }
          */
