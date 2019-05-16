#pragma once

#include "Element.h"
#include "Sources.h"


namespace my_math
{

  class DiffractionGrating : public Element
  {
   public:
    DiffractionGrating(void)
        : Element( ) {
    }

    virtual ~DiffractionGrating(void);

    DiffractionGrating(const Vector2 & position, const float period, const float slot_width, const int num_hatches = 1);

    DiffractionGrating(const DiffractionGrating & that);

    DiffractionGrating(DiffractionGrating && that);

    DiffractionGrating & operator=(const DiffractionGrating & that) = delete;

    DiffractionGrating & operator=(DiffractionGrating && that) = delete;


    /**
      \brief Check DiffractionGrating.
      \return True - Grating is correct, flase - grating is incorrect. 
    */
    bool Ok(void) const;


    /**
      \brief  Print information about grating.
    */
    virtual bool Dump(void) const override;  


    /**
      \brief  Draw grating.
      \param[in] window - Window to draw grating on it.
    */
    virtual bool Draw(sf::RenderWindow & window) override;


    /** 
      \breif Give you a coordinate of the right diffraction grating's part.
      \return This coordinate.
    */
    VECTOR_TYPE Right(void) const;


    /** 
      \breif Give you a coordinate of the left diffraction grating's part.
      \return This coordinate.
    */
    VECTOR_TYPE Left(void) const;


    /** 
      \breif Give you a coordinate of the bottom diffraction grating's part.
      \return This coordinate.
    */
    VECTOR_TYPE Bottom(void) const;


    /** 
      \breif Give you a coordinate of the top diffraction grating's part.
      \return This coordinate.
    */
    VECTOR_TYPE Top(void) const;


    /**
      \breif Give you value of num_hatches_
      \return Number of hatches.
    */
    int GetNumberHatches(void) const;


    /** 
      \breif This function handles the collision of the diffraction grating and wave front.
      \param[in] position - Position of collision.
      \param[out] secondary_source_coordinate - Coordinate to set coordinate of created secondary_sources in it.
      \param[out] secondary_source_number - Number of secondary_source, that was created. 
      \param[out] is_main_wave - Function will set it in true if secondary wave was create firstly.   
      \return True - new secondary source was created. False - new secondary source wasn't created.
    */
    bool HandleCollision(const Vector2 & position, Vector2 *secondary_source_coordinate, int* secondary_source_number,
                         bool* is_main_wave);

    void RemoveSecondarySource(const int ind, const WAVE_STATUSES wave_status);

    Vector2 GetFieldStrength(const Vector2 & position, const float t, const std::vector<Dipole> &dipoles_) const;

   protected:

    // If first secondary wave exits, it will set this variable in true.
    // If first secondary wave doesn't exist, it will set this variable in false.
    bool is_first_wave_created_;

    float period_;

    float slot_width_;

    int num_hatches_;

    std::vector<sf::Sprite> hatches_;

    std::vector<SecondarySource> secondary_sources_;

    // proportions_[0] - x coordinate of left side. proportions_[1] - x coordinate of right side.
    // proportions_[2] - y coordinate of bottom side. proportions_[3] - y coordinate of top side. 
    float proportions_[NUMBER_SIDES];

    // If secondary source exists in appropriate hatch(from bottom to top) it will be set by true.
    std::vector<bool> secondary_sources_presence_;


    /** 
      \breif Set appropriate values in proportions_.
      \param[in] hatch_ind - Index of the lowest hatch.
    */ 
    void CreateProportions(const int hatch_ind); 


    sf::Sprite CreateHatchSprite(const Vector2 & position);


    /** 
      \breif Create secondary source in position.
      \param[in] position - Position to create secondary source.
      \param[in] ind - ind in secondary_sources_presence_ and secondary_sources_ to create secondary source.
      \param[out] secondary_source_coordinate - Pointer on vector to set it into position of created secondary source.
      \return True - Secondary source was created. False - secondary source has already exist and wasn't created.
    */
    bool CreateSecondarySourceCollision(const Vector2 & position, const int ind, Vector2 *secondary_source_coordinate,
                                          int *secondary_source_number, bool* is_main_wave);

  };


  /**
    \brief Load texture for grating. It should be called only once.
    \param[in] grating_texture - Grating to load texture in it. 
  */
  void CreateGratingTexture(sf::Texture &grating_texture);

} // End of namespace my_math.

