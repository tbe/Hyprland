#pragma once
#include "PassElement.hpp"
#include <optional>
#include "../../helpers/time/Time.hpp"

class CWLSurfaceResource;
class CTexture;
class CSyncTimeline;

class CSurfacePassElement : public IPassElement {
  public:
    struct SRenderData {
        PHLMONITORREF             pMonitor;
        Time::steady_tp           when = Time::steadyNow();
        Hyprutils::Math::Vector2D pos, localPos;

        void*                     data        = nullptr;
        SP<CWLSurfaceResource>    surface     = nullptr;
        SP<CTexture>              texture     = nullptr;
        bool                      mainSurface = true;
        double                    w = 0, h = 0;
        int                       rounding      = 0;
        bool                      dontRound     = true;
        float                     roundingPower = 2.0F;
        bool                      decorate      = false;
        float                     alpha = 1.F, fadeAlpha = 1.F;
        bool                      blur                  = false;
        bool                      blockBlurOptimization = false;

        // only for windows, not popups
        bool squishOversized = true;

        // for calculating UV
        PHLWINDOW pWindow;
        PHLLS     pLS;

        bool      popup = false;

        // counts how many surfaces this pass has rendered
        int                   surfaceCounter = 0;

        Hyprutils::Math::CBox clipBox = {}; // scaled coordinates

        uint32_t              discardMode    = 0;
        float                 discardOpacity = 0.f;

        bool                  useNearestNeighbor = false;

        bool                  flipEndFrame = false;
    };

    CSurfacePassElement(const SRenderData& data);
    virtual ~CSurfacePassElement() = default;

    virtual void                                 draw(const Hyprutils::Math::CRegion& damage);
    virtual bool                                 needsLiveBlur();
    virtual bool                                 needsPrecomputeBlur();
    virtual std::optional<Hyprutils::Math::CBox> boundingBox();
    virtual Hyprutils::Math::CRegion             opaqueRegion();
    virtual void                                 discard();
    Hyprutils::Math::CRegion                     visibleRegion(bool& cancel);

    virtual const char*                          passName() {
        return "CSurfacePassElement";
    }

  private:
    SRenderData           m_data;

    Hyprutils::Math::CBox getTexBox();
};
