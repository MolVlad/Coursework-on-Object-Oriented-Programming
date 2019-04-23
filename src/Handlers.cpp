#include "Handlers.h"

bool IsRightPosition(const sf::Vector2i & position) {

  Vector2 center = Vector2(DEFAULT_AREA_CENTER_X, DEFAULT_AREA_CENTER_Y);
  return (DEFAULT_AREA_RADIUS > (center - position).Len( ));
}

bool HandleEvent(sf::RenderWindow &window, Store &store)
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
        HandleMouse(window, event, store);
        break;
    }
  }

  return true;
}

bool HandleMouse(sf::RenderWindow &window, sf::Event event, Store &store)
{
  sf::Vector2i position = sf::Mouse::getPosition(window);
  Wave singular_wave;
  FrontElement front_element;

  switch(event.key.code)
  {
    case sf::Mouse::Left:
      #ifdef MOUSE_DEBUG
      std::cout << "handleMouse(): Left" << std::endl;
      #endif /* MOUSE_DEBUG */

      if (IsRightPosition(position)) {
        store.Push(Dipole(my_math::Vector2(position)));
      }

      break;
    case sf::Mouse::Middle:
      #ifdef MOUSE_DEBUG
      std::cout << "handleMouse(): Middle" << std::endl;
      std::cout << std::endl;
      #endif /* MOUSE_DEBUG */

      if (IsRightPosition(position)) {
        Dipole dipole = Dipole(my_math::Vector2(position));
        dipole.SetDirection(90);
        store.Push(dipole);
      }

      break;
    case sf::Mouse::Right:
      #ifdef MOUSE_DEBUG
      std::cout << "handleMouse(): Right" << std::endl;
      std::cout << std::endl;
      #endif /* MOUSE_DEBUG */

      singular_wave.Push(FrontElement(position));
      store.Push(singular_wave);
      std::cout << std::endl;

      break;
  }

  return true;
}

bool HandleDraw(sf::RenderWindow &window, Store &store) {
  store.Draw(window);
  return true;
}

bool HandleStore(Store &store)
{
    store.RemoveDistantWaves();
    store.MoveWaves();
    store.UpdateTime();
}
