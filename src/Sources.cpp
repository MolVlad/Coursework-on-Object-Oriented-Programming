#include "Sources.h"

Source::Source(const Vector2 & position)
    :  Element(position)
{

}

Source::Source()
{

}

Source::~Source()
{

}

bool Source::SetPhase(const float phase)
{
  phase_ = phase;
}

bool Source::SetAmplitude(const float amplitude)
{
  amplitude_ = amplitude;
}

Dipole::Dipole(void) {
}

Dipole::Dipole(const Vector2 & position, const Vector2 & direction)
    :  Source(position),
       direction_(direction) {
}

// need to create
bool Dipole::Draw() const
{

}

// need to create
bool Dipole::Dump() const
{

}

// need to create
float Dipole::GetFieldStrength(const Vector2 point) const
{

}

// need to create
bool Dipole::SetImageScale(const float image_scale)
{

}

// need to create
bool Dipole::SetImageDirection()
{

}

Dipole::~Dipole()
{

}

SecondarySource::SecondarySource()
{

}

SecondarySource::SecondarySource(const Vector2 & position)
    :  Source(position)
{

}

// need to create
bool SecondarySource::Draw() const
{

}

// need to create
bool SecondarySource::Dump() const
{

}

// need to create
float SecondarySource::GetFieldStrength(const Vector2 point) const
{

}

SecondarySource::~SecondarySource()
{

}

