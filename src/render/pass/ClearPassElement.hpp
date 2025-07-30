#pragma once
#include "PassElement.hpp"

class CClearPassElement : public IPassElement {
  public:
    struct SClearData {
        CHyprColor color;
    };

    CClearPassElement(const SClearData& data);
    virtual ~CClearPassElement() = default;

    virtual void                                 draw(const Hyprutils::Math::CRegion& damage);
    virtual bool                                 needsLiveBlur();
    virtual bool                                 needsPrecomputeBlur();
    virtual std::optional<Hyprutils::Math::CBox> boundingBox();
    virtual Hyprutils::Math::CRegion             opaqueRegion();

    virtual const char*                          passName() {
        return "CClearPassElement";
    }

  private:
    SClearData m_data;
};
