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

    sprite_ = sf::Sprite(area_texture);
    const sf::Vector2f scale_vect = sprite_.getScale( );
    sprite_.setScale(scale_vect.x * DEFAULT_AREA_SCALE, scale_vect.y * DEFAULT_AREA_SCALE);
    position_ = Vector2(0., 0.);
    return;
  }


  bool DipoleArea::Draw(sf::RenderWindow & window) {
    sprite_.setPosition(position_.GetX( ), position_.GetY( ));
    window.draw(sprite_);
    return true;
  }


  bool DipoleArea::Dump(void) const {
    #ifdef DIPOLE_AREA_DEBUG
    std::cout << "DipoleArea::Dump( )" << std::endl;
    #endif /* DIPOLE_AREA_DEBUG */

    std::cout << "\tposition: " << position_ << std::endl;

    #ifdef DIPOLE_AREA_DEBUG
    std::cout << "DipoleArea::Dump() end" << std::endl;
    #endif /* DIPOLE_AREA_DEBUG */

    std::cout << std::endl;
    return true;
  }

} // End of namespace my_math.