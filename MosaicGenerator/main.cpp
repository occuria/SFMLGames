#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

constexpr int width = 1600;
constexpr int height = 900;

/* Random draws */
int d(int const nbSides)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(1, nbSides);
	return distribution(engine);
}

int dsplit(int const nbSides)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(15, nbSides);
	return distribution(engine);
}

/* Splits a random rectangle into two child rectangles */
void splitRandom(std::vector<sf::RectangleShape> &rvector, int const pwhite) 
{
	int rr = d(rvector.size())-1;
	sf::RectangleShape r = rvector.at(rr);
	/* Checks the minimal size for a rectangle to be split (15x15) */
	if (r.getSize().x <= 15 || r.getSize().y <=15) {
		std::cout << "Rectangle too small to be split" << std::endl;
		return;
	}
	sf::RectangleShape r1;
	sf::RectangleShape r2;
	sf::Vector2f splitPoint;
	splitPoint.x = dsplit(r.getSize().x);
	splitPoint.y = dsplit(r.getSize().y);
	/* Horizontal split */
	if ( d(2)==1 ) {
		r1.setSize(sf::Vector2f(splitPoint.x, r.getSize().y));
		r1.setPosition(r.getPosition().x, r.getPosition().y);
		r2.setSize(sf::Vector2f(r.getSize().x-splitPoint.x, r.getSize().y)); 
		r2.setPosition(r.getPosition().x+splitPoint.x, r.getPosition().y);

	/* Vertical split */
	} else {
		r1.setSize(sf::Vector2f(r.getSize().x, splitPoint.y));
		r1.setPosition(r.getPosition().x, r.getPosition().y);
		r2.setSize(sf::Vector2f(r.getSize().x, r.getSize().y-splitPoint.y)); 
		r2.setPosition(r.getPosition().x, r.getPosition().y+splitPoint.y);
	}

	r1.setOutlineThickness(1);
	r1.setOutlineColor(sf::Color::Black);
	/* Chooses r1 colour */
	if (d(100) <= pwhite) {
		r1.setFillColor(sf::Color::White);
	} else {
		r1.setFillColor(sf::Color(d(255),d(255),d(255)));
	}
	r2.setOutlineThickness(1);
	r2.setOutlineColor(sf::Color::Black);
	/* Chooses r2 colour */
	if (d(100) <= pwhite) {
		r2.setFillColor(sf::Color::White);
	} else {
		r2.setFillColor(sf::Color(d(255),d(255),d(255)));
	}
	/* Replaces the original rectangle by his two children */
	rvector.erase(rvector.begin()+rr);
	rvector.insert(rvector.begin()+rr, r1);
	rvector.insert(rvector.begin()+rr, r2);
	return;
}

/* Generates a rectangle mosaic */
std::vector<sf::RectangleShape> newMosaic()
{
	unsigned int nbrec = d(100)+1;
	int pwhite = d(100);
	std::vector<sf::RectangleShape> rvector;
	sf::RectangleShape r(sf::Vector2f(width, height));
	r.setFillColor(sf::Color::White);
	r.setOutlineColor(sf::Color::White);
	r.setOutlineThickness(1);
	rvector.push_back(r);
	while (rvector.size() < nbrec) {
		splitRandom(rvector, pwhite);
		std::cout << "Rectangle split, vector size : " << rvector.size() << std::endl;
	}
	std::cout << "Vector is full" << std::endl;
	return rvector;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Rectangles Mosaic", sf::Style::Fullscreen);
	std::vector<sf::RectangleShape> rvector;

	rvector = newMosaic();
	for (sf::RectangleShape r : rvector) {
		window.draw(r);
	}
	window.display();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				window.clear();
				rvector = newMosaic();
				for (sf::RectangleShape r : rvector) {
					window.draw(r);
				}
				window.display();
			}
		}
	}
	return 0;
}
