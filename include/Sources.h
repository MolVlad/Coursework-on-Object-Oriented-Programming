#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"
#include <assert.h>

//#define DIPOLE_DEBUG 1
//#define DIPOLE_STRENGTH_DEBUG 1

using namespace my_math;

class Source : public Element {
 public:
  Source();

  Source(const Vector2 & position);

  virtual bool Draw(sf::RenderWindow & window) = 0;

  virtual bool Dump() const = 0;

  // get field strength from this source in point
  virtual Vector2 GetFieldStrength(const Vector2 & point, const float t) const = 0;

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

  bool Draw(sf::RenderWindow & window) override;

  bool Dump() const override;

  // get field strength from this source in point
  virtual Vector2 GetFieldStrength(const Vector2 & point, const float t) const;

  // Image_scale is increase in size. It should be positive.
  bool SetImageScale(const float image_scale);

  virtual bool SetDirection(const float direction) override;

  virtual bool SetPosition(const Vector2 & position) override;

  ~Dipole();
};

class SecondarySource : public Source {
 public:
  SecondarySource();

  explicit SecondarySource(const Vector2 & position);

  bool Draw(sf::RenderWindow & window) override;

  bool Dump() const override;

  // get field strength from this source in point
  virtual Vector2 GetFieldStrength(const Vector2 & point, const float t) const override;

  ~SecondarySource();

 private:
  float field_strength_;
};