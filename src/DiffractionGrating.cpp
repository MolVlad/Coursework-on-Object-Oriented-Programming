
#include "DiffractionGrating.h"

namespace my_math
{

#define CHECK if(!(Ok( )))                                                 \
{                                                                          \
  std::cout << "Error of " << __PRETTY_FUNCTION__ << " method:\n";         \
  Dump( );                                                                 \
  exit(EXIT_FAILURE);                                                      \
}


sf::Texture grating_texture;



sf::Sprite DiffractionGrating::CreateHatchSprite(const Vector2 & position) 
{
  sf::Sprite hatch_sprite = sf::Sprite(grating_texture);
  const sf::Vector2u grating_size = hatch_sprite.getTexture( ) -> getSize( );
  hatch_sprite.setScale(GRATING_SCALE_X, (period_ - slot_width_) / grating_size.y);
  hatch_sprite.setOrigin(grating_size.x / 2, grating_size.y  / 2);
  hatch_sprite.setPosition(position.GetX( )  , position.GetY( ));
  hatch_sprite.setRotation(DEFAULT_GRATING_DIRECTION);

  return hatch_sprite;	
}


void CreateGratingTexture(sf::Texture &grating_texture)
{
  if (!grating_texture.loadFromFile(GRATING_TEXTURE))
  {
    assert(!"Texture for grating wasn't created!!!\n");
  	exit(-1);
  }
  
  return;
}


DiffractionGrating::~DiffractionGrating(void)
{

}


DiffractionGrating::DiffractionGrating(const Vector2 & position, const float period, const float slot_width, const int num_hatches)
    :  Element(position),
       period_(period),
       slot_width_(slot_width),
       num_hatches_(num_hatches)
{
  #ifndef GRATING_TEXTURE_WAS_CREATED
  CreateGratingTexture(grating_texture);
  #define GRATING_TEXTURE_WAS_CREATED -6665
  #endif /* DIPOLE_TEXTURE_WAS_CREATED */


  Vector2 position_now = position_;
  Vector2 paint_vector = Vector2(0., 1.);
  paint_vector.Rotate(-direction_);
  paint_vector *= period_;

  if (num_hatches_ % 2 == 0)
  {
  	Vector2 correction_vector = paint_vector / 2;
  	for (int ind = 1; ind <= num_hatches_ / 2; ind++)
  	{\
      position_now += paint_vector * ind - correction_vector;
      hatches_.push_back(CreateHatchSprite(position_now));
      position_now -= paint_vector * ind * 2 - 2 * correction_vector;
      hatches_.push_back(CreateHatchSprite(position_now));
      position_now += paint_vector * ind - correction_vector;
  	}
  }
  else
  {
  	hatches_.push_back(CreateHatchSprite(position_now));
  	for (int ind = 1; ind <= (num_hatches_ - 1) / 2 ; ind++)
  	{
      position_now += paint_vector * ind ;
      hatches_.push_back(CreateHatchSprite(position_now));
      position_now -= paint_vector * ind * 2;
      hatches_.push_back(CreateHatchSprite(position_now));
      position_now += paint_vector * ind ;
    }
  }
  return;
}

DiffractionGrating::DiffractionGrating(const DiffractionGrating & that)
    :  period_(that.period_),
       slot_width_(that.slot_width_),
       num_hatches_(that.num_hatches_),
       hatches_(that.hatches_) {
    }


DiffractionGrating::DiffractionGrating(DiffractionGrating && that)
    :  period_(std::move(that.period_)),
       slot_width_(std::move(that.slot_width_)),
       num_hatches_(std::move(that.num_hatches_)),
       hatches_(std::move(that.hatches_)) {
    }

bool DiffractionGrating::Ok(void) const
{
  return slot_width_ > 0. && period_ > 0. && num_hatches_ > 0 && period_ > slot_width_;
}

bool DiffractionGrating::Dump(void) const
{
  #ifdef DIPOLE_DEBUG
  std::cout << "Grating::Dump()" << std::endl;
  #endif /* DIPOLE_DEBUG */

  std::cout << "\tposition: " << position_ << std::endl;
  std::cout << "\tdirection: " << direction_ << std::endl;
  std::cout << "\tperiod: " << period_ << std::endl;
  std::cout << "\tslot_width: " << slot_width_ << std::endl;

  #ifdef DIPOLE_DEBUG
  std::cout << "Grating::Dump() end" << std::endl;
  #endif /* DIPOLE_DEBUG */

  std::cout << std::endl;
  return true;
}


bool DiffractionGrating::Draw(sf::RenderWindow & window)
{
  CHECK
  for (int ind = 0; ind < num_hatches_; ind++)
  {
    window.draw(hatches_[ind]);  	
  }

  return true;	
}

} // End of namespace my_math.
