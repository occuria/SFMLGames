#ifndef DEF_EVENT_HOLDER
#define DEF_EVENT_HOLDER

#include <SFML/Graphics.hpp>
#include "Game.hpp"

/**
 * Singleton class that centralizes the handling of user input.
 * Used by every game state, so that event handling depends on 
 * the current game state.
 */
class EventHolder
{
  public:
    /**
     * Singleton implementation.
     */
    static EventHolder& get()
    {
      static EventHolder instance;
      return instance;
    }

    /**
     * Handles all types of SFML events.
     */
    void handleEvent(sf::RenderWindow&, Game&, sf::Event);

    /**
     * Returns the position of the card that has been clicked on.
     * Returns (-1, -1) vector if none.
     */
    sf::Vector2i handleLeftClick(Game&, sf::Vector2f);
  
  private:

    EventHolder(EventHolder const&) = delete;
    void operator=(EventHolder const&) = delete;
    EventHolder() = default;

};

#endif
