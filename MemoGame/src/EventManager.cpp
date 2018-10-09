#include <iostream>
#include "../inc/EventManager.hpp"

EventManager::EventManager(Game& game, GameState& gs): game(game), gs(gs)
{}

void EventManager::ManageClick(sf::Vector2f pos)
{
  /* Iterates through all cards of the board */
  for (std::size_t i=0; i<this->game.getBoard().size(); i++) {
    for (std::size_t j=0; j<this->game.getBoard()[i].size(); j++) {
      Card c = this->game.getBoard()[i][j];
      if (c.getSprite().getGlobalBounds().contains(pos.x, pos.y)) {
        std::cout << "Collision détectée, à parti de là c'est cassé" << std::endl;
        /* Checks that the card is not already flipped over */
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
        }
        return;
      }
    }
  }
}
