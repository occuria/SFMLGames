#ifndef DEF_STATE
#define DEF_STATE

#include <SFML/Graphics.hpp>
#include <experimental/optional>
#include <memory>
#include "Card.hpp"


/* Cross reference handling */
class Game;

class State
{
  public:
    virtual ~State() {}
    virtual std::experimental::optional<std::unique_ptr<State>>
      update(Game&, sf::Vector2i) = 0;

};

class PendingForCardsState : public State
{
  public: 
    std::experimental::optional<std::unique_ptr<State>>
      update(Game&, sf::Vector2i);

  private:
    std::vector<Card> cards;
};

  

#endif
