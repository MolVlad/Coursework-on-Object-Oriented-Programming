#include "DipoleArea.h"

namespace my_math {
  
  DipoleArea::DipoleArea(void) {

    circle_shape_ = sf::CircleShape(DEFAULT_AREA_RADIUS, DEFAULT_AREA_PCOUNT);
    circle_shape_.setFillColor(sf::Color::Yellow);

    const sf::Vector2f scale_vect = circle_shape_.getScale( );
    circle_shape_.setPosition(DEFAULT_AREA_CENTER_X - DEFAULT_AREA_RADIUS,
                              DEFAULT_AREA_CENTER_Y - DEFAULT_AREA_RADIUS);
    return;
  }


  bool DipoleArea::Draw(sf::RenderWindow & window) {
    window.draw(circle_shape_);
    return true;
  }


  bool DipoleArea::Dump(void) const {
    #ifdef DIPOLE_AREA_DEBUG
    std::cout << "DipoleArea::Dump( )" << std::endl;
    #endif /* DIPOLE_AREA_DEBUG */

    sf::Vector2f area_vect = circle_shape_.getPosition( );
    std::cout << "\tposition: (" << area_vect.x << ", " << area_vect.y << ")" << std::endl;

    #ifdef DIPOLE_AREA_DEBUG
    std::cout << "DipoleArea::Dump() end" << std::endl;
    #endif /* DIPOLE_AREA_DEBUG */

    std::cout << std::endl;
    return true;
  }

} // End of namespace my_math.
