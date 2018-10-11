#include <chrono>
#include <thread>
#include "../inc/Game.hpp"
#include "../inc/State.hpp"

void PendingForCardsState::update(Game& game, sf::Vector2i coord)
{
  /* Checks if a card has been clicked on */
  if (coord.x == -1 && coord.y == -1) { return; }

  Card& c = game.getBoard()[coord.x][coord.y];

  /* Stops here if the card is already flipped on the front side */
  if (c.isPaired()) { return; }

  /* Flips the card and fills the coordinates vector */
  c.flipFront();
  this->cards.push_back(c);

  /* Stops here if only one card has be flipped */
  if (cards.size() != 2) { return; }

  /* Checks wether cards can be paired */
  if (cards[0].get().getPairId() != cards[1].get().getPairId()) {
    /* Not paired : flip cards back and go back to pending state */
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    cards[0].get().flipBack();
    cards[1].get().flipBack();
  }

  /* Resets the pending state */
  cards.pop_back();
  cards.pop_back();

  //TODO check if all cards are paired : return GameOver state
}
