#pragma once
#include "PassElement.hpp"
#include <optional>

class CWLSurfaceResource;
class CTexture;
class CSyncTimeline;

class CTexPassElement : public IPassElement {
  public:
    struct SRenderData {
        SP<CTexture>             tex;
        Hyprutils::Math::CBox    box;
        float                    a     = 1.F;
        float                    blurA = 1.F;
        Hyprutils::Math::CRegion damage;
        int                      round         = 0;
        float                    roundingPower = 2.0f;
        bool                     flipEndFrame  = false;
        std::optional<Hyprutils::Math::Mat3x3>    replaceProjection;
        Hyprutils::Math::CBox    clipBox;
        bool                     blur = false;
        std::optional<float>     ignoreAlpha;
    };

    CTexPassElement(const SRenderData& data);
    CTexPassElement(SRenderData&& data);
    virtual ~CTexPassElement() = default;

    virtual void                                 draw(const Hyprutils::Math::CRegion& damage);
    virtual bool                                 needsLiveBlur();
    virtual bool                                 needsPrecomputeBlur();
    virtual std::optional<Hyprutils::Math::CBox> boundingBox();
    virtual Hyprutils::Math::CRegion             opaqueRegion();
    virtual void                                 discard();

    virtual const char*                          passName() {
        return "CTexPassElement";
    }

  private:
    SRenderData m_data;
};
