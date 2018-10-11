#ifndef DEF_GAME
#define DEF_GAME

#include "TextureHolder.hpp"
#include "BoardDimensions.hpp"
#include "State.hpp"
#include "Card.hpp"

class Game
{
  public:
    /**
     * Constructor, needed to contrust the boardDimensions structure,
     * which does not have a default constructor.
     */
    Game(float rspacing, float width, float height, int xcards, int ycards);
    /**
     * Loads resources into the texture holder before initializing any game.
     */
    void loadResources();
    /**
     * Initializes a new game, can be used to reset the game.
     * Creates all cards, sets their position and their front texture ID.
     */
    void initialize();
    /**
     * Displays the current game on the game window.
     */
    void display(sf::RenderWindow& window);
    /**
     * Calls the game state to update the state.
     */
    void updateState(sf::Vector2i coord);
    /**
     * Returns true if all cards are paired.
     */
    bool areAllCardsPaired();
    /**
     * Returns the texture map.
     */
    std::map<int, Textures::ID> getTexMap();
    /**
     * Returns the board of cards.
     */
    std::vector<std::vector<Card>> getBoard();

  private:
    std::map<int, Textures::ID> texMap;
    std::vector<std::vector<Card>> board;
    boardDimensions bd;
    std::unique_ptr<State> state;
};

#endif
