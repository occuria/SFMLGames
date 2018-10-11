#ifndef DEF_STATE
#define DEF_STATE

#include <SFML/Graphics.hpp>
#include <functional>
#include <experimental/optional>
#include <memory>
#include "Card.hpp"


/* Cross reference handling */
class Game;

class State
{
  public:
    virtual ~State() {}
    virtual void update(Game&, sf::Vector2i) = 0;
};

class PendingForCardsState : public State
{
  public: 
    void update(Game&, sf::Vector2i);

  private:
    std::vector<std::reference_wrapper<Card>> cards;
};

  

#endif
