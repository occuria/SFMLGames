#include "../inc/EventHandler.hpp"
#include "../inc/Card.hpp"

void EventHolder::handleEvent(sf::RenderWindow& window, Game& game, sf::Event event)
{
  switch(event.type) {
    /* Window closure */
    case sf::Event::Closed:
        window.close();
        break;
    case sf::Event::MouseButtonPressed:
        /* Left Click */
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i v = handleLeftClick(
              game, sf::Vector2f(event.mouseButton.x,event.mouseButton.y));
          game.updateState(v);
        break;
        }
    default:
      break;
  }
}

sf::Vector2i EventHolder::handleLeftClick(Game& game, sf::Vector2f pos)
{
  sf::Vector2i v(-1,-1);
  /* Iterates through all cards of the board */
  for (std::size_t i=0; i<game.getBoard().size(); i++) {
    for (std::size_t j=0; j<game.getBoard()[i].size(); j++) {
      Card c = game.getBoard()[i][j];
      /* Fills the vector if this is the right card */
      if (c.getSprite().getGlobalBounds().contains(pos.x, pos.y)) {
        v.x = i;
        v.y = j;
        return v;
      }
    }
  }
  return v;
}
