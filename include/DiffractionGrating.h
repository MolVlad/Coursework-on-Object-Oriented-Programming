#include "Element.h"




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

    protected:
      float period_;
      float slot_width_;
      int num_hatches_;
      std::vector<sf::Sprite> hatches_;

      sf::Sprite CreateHatchSprite(const Vector2 & position);
  };


  /**
    \brief Load texture for grating. It should be called only once.
    \param[in] grating_texture - Grating to load texture in it. 
  */
  void CreateGratingTexture(sf::Texture &grating_texture);
































} // End of namespace my_math.