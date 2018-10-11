#include "../inc/Game.hpp"
#include "../inc/State.hpp"

std::experimental::optional<std::unique_ptr<State>> 
  PendingForCardsState::update(Game& game, sf::Vector2i coord)
{
  /* Checks if a card has been clicked on */
  if (coord.x == -1 && coord.y == -1) { return{}; }

  Card& c = game.getBoard()[coord.x][coord.y];

  /* Stops here if the card is already flipped on the front side */
  if (c.isPaired()) { return{}; }

  /* Fills the coordinates vector */
  this->cards.push_back(c);

  /* Stops here if only one card has be flipped */
  if (cards.size() != 2) { return{}; }

  /* Checks wether cards can be paired */
  if (cards[0].getPairId() != cards[1].getPairId()) {
    /* Not paired : flip cards back and go back to pending state */
    cards[0].flipBack();
    cards[1].flipBack();
  }

  /* Resets the pending state */
  std::unique_ptr<State> newstate(new PendingForCardsState);
  return newstate;

  //TODO check if all cards are paired : return GameOver state
}
