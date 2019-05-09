
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

void DiffractionGrating::CreateProportions(const int hatch_ind)
{
  const sf::Vector2f bottom_hatch_position = hatches_[hatch_ind].getPosition( );
  sf::Vector2u texture_size = hatches_[hatch_ind].getTexture( ) -> getSize( );

  proportions_[0] = bottom_hatch_position.x - (texture_size.x / 2) * GRATING_SCALE_X;
  proportions_[1] = bottom_hatch_position.x + (texture_size.x / 2) * GRATING_SCALE_X;
  proportions_[2] = bottom_hatch_position.y + (period_ - slot_width_) / 2;

  if (hatch_ind == 0)
  {
      proportions_[3] = bottom_hatch_position.y + (period_ - slot_width_) / 2;  
  }
  else
  {
    const sf::Vector2f top_hatch_position = hatches_[num_hatches_ - 2].getPosition( );
    proportions_[3] = top_hatch_position.y - (period_ - slot_width_) / 2;
  }
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

    CreateProportions(num_hatches_ - 1);
  }
  else
  {
  	hatches_.push_back(CreateHatchSprite(position_now));
    sf::Vector2u testure_size = hatches_[num_hatches_ - 1].getTexture( ) -> getSize( );

    if (num_hatches_ == 1)
    {
      CreateProportions(0);  
    }

  	for (int ind = 1; ind <= (num_hatches_ - 1) / 2 ; ind++)
  	{
      position_now += paint_vector * ind ;
      hatches_.push_back(CreateHatchSprite(position_now));
      position_now -= paint_vector * ind * 2;
      hatches_.push_back(CreateHatchSprite(position_now));
      position_now += paint_vector * ind;

      CreateProportions(num_hatches_ - 1); 
    }
  }

  for (int ind = 0; ind < num_hatches_ - 1; ind ++)
  {
    secondary_sources_presence_.push_back(false);
  }
  secondary_sources_.resize(num_hatches_ - 1);

  return;
}

DiffractionGrating::DiffractionGrating(const DiffractionGrating & that)
    :  Element(that),
       period_(that.period_),
       slot_width_(that.slot_width_),
       num_hatches_(that.num_hatches_),
       hatches_(that.hatches_),
       secondary_sources_presence_(that.secondary_sources_presence_),
       secondary_sources_(that.secondary_sources_)  {

    for (int ind = 0; ind < 4; ind++)
    {
      proportions_[ind] = that.proportions_[ind];
    }
    return;
}


DiffractionGrating::DiffractionGrating(DiffractionGrating && that)
    :  Element(that),
       period_(std::move(that.period_)),
       slot_width_(std::move(that.slot_width_)),
       num_hatches_(std::move(that.num_hatches_)),
       hatches_(std::move(that.hatches_)),
       secondary_sources_(std::move(that.secondary_sources_)),
       secondary_sources_presence_(std::move(that.secondary_sources_presence_))  {

    for (int ind = 0; ind < 4; ind++)
    {
      proportions_[ind] = std::move(that.proportions_[ind]);
    }
    return;
}


bool DiffractionGrating::Ok(void) const
{
  return slot_width_ > 0. && period_ > 0. && num_hatches_ > 0 && period_ > slot_width_ && proportions_[1] > proportions_[0] 
         &&  proportions_[2] > proportions_[3];
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
  std::cout << "\tleft_side: " << proportions_[0] << std::endl;
  std::cout << "\tright_side: " << proportions_[1] << std::endl;
  std::cout << "\tbottom_side: " << proportions_[2] << std::endl;
  std::cout << "\ttop_side: " << proportions_[3] << std::endl;

  std::cout << "Secondary sources presence:\n" << std::endl;
  for (int ind = 0; ind < secondary_sources_presence_.size( ); ind++)
  {
    std::cout << secondary_sources_presence_[ind];
  }
  std::cout << std::endl;

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


VECTOR_TYPE DiffractionGrating::Left(void) const
{
  return proportions_[0]; 
}


VECTOR_TYPE DiffractionGrating::Right(void) const
{
  return proportions_[1]; 
}


VECTOR_TYPE DiffractionGrating::Bottom(void) const
{
  return proportions_[2]; 
}


VECTOR_TYPE DiffractionGrating::Top(void) const
{
  return proportions_[3]; 
}

bool DiffractionGrating::CreateSecondarySourceCollision(const Vector2 & position, const int ind,
                                                        Vector2 *secondary_source_coordinate, int *secondary_source_number)
{
  assert(secondary_source_coordinate != nullptr);

  if (secondary_sources_presence_[ind] == true)
  {
    return false;
  }
  else
  {
    secondary_sources_presence_[ind] = true;
    secondary_sources_[ind] = SecondarySource(position, slot_width_);
    *secondary_source_coordinate = position;
    *secondary_source_number = ind;

    #ifdef CREATING_SECONDARY_SOURCE_DEBAG
    std::cout << "Add secondary source with coordinates:\n";
    std::cout << position << std::endl;
    #endif // End of CREATING_SECONDARY_SOURCE_DEBAG

    return true;
  }
}

bool DiffractionGrating::HandleCollision(const Vector2 & position, Vector2 *secondary_source_coordinate,
                                         int *secondary_source_number)
{
  assert(secondary_source_number != nullptr);
  Vector2 basis_vector = Vector2(0., 1.);


  float y_position = position.GetY( );
  if (num_hatches_ % 2 == 0)
  {
    // Jump to the bottom.
    int num_bottom_jumps = (num_hatches_ - 2) / 2;
    Vector2 position_now = position_ + num_bottom_jumps * period_ * basis_vector;

    if (y_position <= position_now.GetY( ) + slot_width_ / 2 && y_position >= position_now.GetY( ) - slot_width_ / 2)
    {
      bool status = CreateSecondarySourceCollision(position_now, 0, secondary_source_coordinate, secondary_source_number);

      CHECK
      return status;
    }

    for (int ind = 1; ind <= num_hatches_ - 2; ind++)
    {
      position_now -= period_ * basis_vector;
      if (y_position <= position_now.GetY( ) + slot_width_ / 2 && y_position >= position_now.GetY( ) - slot_width_ / 2)
      {
        bool status = CreateSecondarySourceCollision(position_now, ind, secondary_source_coordinate, secondary_source_number);

        CHECK
        return status;
      }
    }
  }
  else
  {
    if (num_hatches_ == 1)
    {
      return false;
    }

    Vector2 position_now = position_ +  basis_vector * period_ / 2;

    int num_bottom_jumps = (num_hatches_ - 3) / 2;
    position_now += num_bottom_jumps * period_ * basis_vector;
    if (y_position <= position_now.GetY( ) + slot_width_ / 2 && y_position >= position_now.GetY( ) - slot_width_ / 2)
    {
      bool status = CreateSecondarySourceCollision(position_now, 0, secondary_source_coordinate, secondary_source_number);

      CHECK
      return status;
    }     

    for (int ind = 1; ind <= num_hatches_ - 2; ind++)
    {
      position_now -= period_ * basis_vector;

      if (y_position <= position_now.GetY( ) + slot_width_ / 2 && y_position >= position_now.GetY( ) - slot_width_ / 2)
      {
        bool status = CreateSecondarySourceCollision(position_now, ind, secondary_source_coordinate, secondary_source_number);

        CHECK
        return status;
      }     
    }

  }

  // There was only a black part of diffraction_grating.
  return false;
}

void DiffractionGrating::RemoveSecondarySource(const int ind)
{
  secondary_sources_presence_[ind] = false;
  return;
}

Vector2 DiffractionGrating::GetFieldStrength(const Vector2 & position, const float t,
                                             const std::vector<Dipole> &dipoles_) const
{
  Vector2 result = Vector2(0., 0.);
  Vector2 additional_strength;

  for (int ind = 0; ind < secondary_sources_presence_.size( ); ind++)
  {
    if (secondary_sources_presence_[ind])
    {
      additional_strength = secondary_sources_[ind].GetFieldStrength(position, t, dipoles_);
      result += additional_strength;

      #ifdef SECONDARY_SOURCE_STRENGTH_DEBAG
      std::cout << "field from secondary source number " << ind << " = " << additional_strength << "\n\n";
      #endif    

    }
  }

  return result;
}

} // End of namespace my_math.
