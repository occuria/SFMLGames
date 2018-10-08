#ifndef DEF_EVENT_MANAGER
#define DEF_EVENT_MANAGER

#include "Game.hpp"
#include "GameState.h"

class EventManager
{
  public:
    EventManager(Game&, GameState&);
    /**
     * Reacts to click.
     */
    void ManageClick(sf::Vector2f);

  private:
    Game& game;
    GameState& gs;

};

#endif
