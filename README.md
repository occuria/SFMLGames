# SFMLGames

This repository contains several games and game engines I developed from
scratch, using the SFML library for C++. Each project is developed in
a separate branch and is eventually merged into master if it reaches
a functional and playable state.

There is the list of all projects :
- Mosaic generator, the first SFML project I worked on, as part of a C++
  course.
- Memory game, a simple game I first developed using an iterating method.
  I recently refactored the whole code to make it clear and modifiable. This is
  the most advanced project of this repo.
- A beat-them-all and a real-time tactical RPG, my two lasts projects that
  suffered from over-modelling. I may probably resume my work on these
  projects, with a more iterating approach.

## Memory Game

![alt text](https://github.com/occuria/SFMLGames/blob/master/MemoGame/screenshots/Gameplay_10_2018.png "Screenshot of gameplay")


My goal with this project was to build a game whose code is clear and
modifiable, so that I can easily and quickly add new features. To do so, I used
several design patterns taken from the Gang of Four's and *Game Programming
Patterns*, by Robert Nystrom.

A quick but important disclaimer to say that I did not design assets by myself.
Textures, sounds and musics are taken from free assets databases (itch.io,
kenney.nl, devassets.com, etc).

At the moment, the code is clear enough to be modifiable, but lacks of unit and 
integration tests for debugging phases. Here is the list of features I would
like to add to my game.

##### Todolist :

- Add logging and testing libraries to allow quick and easy debugging
- Create a CMake file to distribute the game
- Make the game responsive (1600x900 resolution is hard-coded for now)
- Add functionnal buttons (restart, quit, volume)
- Add different difficulty levels with different numbers of cards
- Add background music and sounds to make the game more living
- Add card flipping animations too
- Add a final state with an ending message
- Add a persistent scoretable 
