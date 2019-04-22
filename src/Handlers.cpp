#include "Handlers.h"

bool handleEvent(sf::RenderWindow &window, Store &store)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				handleMouse(window, event, store);
				break;
		}
	}

  return true;
}

bool handleMouse(sf::RenderWindow &window, sf::Event event, Store &store)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);

	switch(event.key.code)
	{
		case sf::Mouse::Left:
      #ifdef MOUSE_DEBUG
      std::cout << "handleMouse(): Left" << std::endl;
      #endif /* MOUSE_DEBUG */

			store.Push(Dipole(my_math::Vector2(position)));
			break;
		case sf::Mouse::Right:
      #ifdef MOUSE_DEBUG
      std::cout << "handleMouse(): Right" << std::endl;
      std::cout << std::endl;
      #endif /* MOUSE_DEBUG */

      store.Dump();
			break;
		case sf::Mouse::Middle:
      #ifdef MOUSE_DEBUG
      std::cout << "handleMouse(): Middle" << std::endl;
      std::cout << std::endl;
      #endif /* MOUSE_DEBUG */

      Vector2 field = store.GetFieldStrength(my_math::Vector2(position));
      std::cout << "Result field: " << field << std::endl;
      std::cout << "Field strength: " << field.Len() << std::endl;
      std::cout << std::endl;
			break;
	}

  return true;
}

bool handleDraw(sf::RenderWindow &window, Store &store) {
  store.Draw(window);
  return true;
}
