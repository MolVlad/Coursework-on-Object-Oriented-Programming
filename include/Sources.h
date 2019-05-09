#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"
#include <assert.h>

//#define DIPOLE_DEBUG 1
//#define DIPOLE_STRENGTH_DEBUG 1
#define CREATING_SECONDARY_SOURCE_DEBAG 1
//#define SECONDARY_SOURCE_STRENGTH_DEBAG 1

namespace my_math
{
class Source : public Element {
 public:
  Source(void);

  Source(const Vector2 & position);

  Source(const Source & that);

  Source(Source && that);

  virtual bool Draw(sf::RenderWindow & window) = 0;

  virtual bool Dump(void) const = 0;

  // get field strength from this source in point
  virtual Vector2 GetFieldStrength(const Vector2 & point, const float t) const;

  bool SetPhase(const float phase);

  bool SetAmplitude(const float amplitude);

  const float GetPhase(void) const;

  const float GetAmplitude(void) const;

  virtual ~Source();

 protected:
  float phase_;
  float amplitude_;
};

class Dipole : public Source {
 public:
  Dipole();

  // Texture index is index of texture in IMAGE_ARRAY (Element.h) and dipole_texture_array (Sources.cpp).
  Dipole(const Vector2 & position, const int texture_index = 0);

  Dipole(const Dipole & that);

  Dipole(Dipole && that);

  bool Draw(sf::RenderWindow & window) override;

  bool Dump() const override;

  // get field strength from this source in point
  virtual Vector2 GetFieldStrength(const Vector2 & point, const float t) const override;

  // Image_scale is increase in size. It should be positive.
  bool SetImageScale(const float image_scale);

  virtual bool SetDirection(const float direction) override;

  virtual bool SetPosition(const Vector2 & position) override;

  ~Dipole();

 private:
  sf::Sprite sprite_;
};

bool CreateDipoleTexture(sf::Texture *texture_array);



class SecondarySource : public Source {
 public:
  SecondarySource( );

  SecondarySource(const Vector2 & position, const float width_secondary_source_area);

  SecondarySource(const SecondarySource & that);

  SecondarySource(SecondarySource && that);

  void Swap(SecondarySource & that);

  SecondarySource & operator=(const SecondarySource & that);

  SecondarySource & operator=(SecondarySource && that);
 
  bool Draw(sf::RenderWindow & window) override;

  bool Dump() const override;

  // get field strength from this source in point
  Vector2 GetFieldStrength(const Vector2 & point, const float t, const std::vector<Dipole> &dipoles_) const;

  ~SecondarySource();

 private:
  float field_strength_;

  // Square of secondary source's area.
  float square_;
};

} // End of namespace my_math.
