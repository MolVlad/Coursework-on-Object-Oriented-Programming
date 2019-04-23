#include "DipoleArea.h"

namespace my_math {

  sf::Texture area_texture;

  bool CreateTexture(void) {

    if (!area_texture.loadFromFile("images/dipole_area.png")) {
      std::cout << "Error of loading texutre:\n";
      std::cout << "In file = " << __FILE__ << std::endl; 
      std::cout << "In line = " << __LINE__ << std::endl; 
      std::cout << "In function = " << __PRETTY_FUNCTION__ << std::endl;
      exit(-1); 
    }    
    return true;
  }
  
  DipoleArea::DipoleArea(void) {

    #ifndef DIPOLE_TEXTURE_WAS_CREATED
    CreateTexture( );
    #define DIPOLE_TEXTURE_WAS_CREATED -6666
    #endif /* DIPOLE_TEXTURE_WAS_CREATED */

    circle_shape_ = sf::CircleShape(DEFAULT_AREA_RADIUS, DEFAULT_AREA_PCOUNT);
    circle_shape_.setTexture(&area_texture);
    circle_shape_.setPosition(-DEFAULT_AREA_RADIUS, -DEFAULT_AREA_RADIUS);
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