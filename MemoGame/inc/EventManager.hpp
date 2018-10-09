#ifndef DEF_EVENT_MANAGER
#define DEF_EVENT_MANAGER

#include <SFML/Graphics.hpp>
#include "Card.h"

class EventManager
{
  public:
    /**
     * Returns the position of the card that has been clicked on.
     * Returns {-1, -1} if none.
     */
    sf::Vector2i manageClick(std::vector<std::vector<Card>>, sf::Vector2f);

};

#endif
