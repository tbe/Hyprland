#pragma once
#include "PassElement.hpp"

class CRectPassElement : public IPassElement {
  public:
    struct SRectData {
        Hyprutils::Math::CBox box;
        CHyprColor            color;
        int                   round         = 0;
        float                 roundingPower = 2.0f;
        bool                  blur = false, xray = false;
        float                 blurA = 1.F;
        Hyprutils::Math::CBox clipBox;
    };

    CRectPassElement(const SRectData& data);
    virtual ~CRectPassElement() = default;

    virtual void                                 draw(const Hyprutils::Math::CRegion& damage);
    virtual bool                                 needsLiveBlur();
    virtual bool                                 needsPrecomputeBlur();
    virtual std::optional<Hyprutils::Math::CBox> boundingBox();
    virtual Hyprutils::Math::CRegion             opaqueRegion();

    virtual const char*                          passName() {
        return "CRectPassElement";
    }

  private:
    SRectData m_data;
};
