#pragma once

#include "../../defines.hpp"
#include "PassElement.hpp"

class CGradientValueData;
class CTexture;

class CRenderPass {
  public:
    bool                     empty() const;
    bool                     single() const;

    void                     add(UP<IPassElement>&& elem);
    void                     clear();
    void                     removeAllOfType(const std::string& type);

    Hyprutils::Math::CRegion render(const Hyprutils::Math::CRegion& damage_);

  private:
    Hyprutils::Math::CRegion              m_damage;
    std::vector<Hyprutils::Math::CRegion> m_occludedRegions;
    Hyprutils::Math::CRegion              m_totalLiveBlurRegion;

    struct SPassElementData {
        Hyprutils::Math::CRegion elementDamage;
        UP<IPassElement>         element;
        bool                     discard = false;
    };

    std::vector<UP<SPassElementData>> m_passElements;

    void                              simplify();
    float                             oneBlurRadius();
    void                              renderDebugData();

    struct {
        bool         present = false;
        SP<CTexture> keyboardFocusText, pointerFocusText, lastWindowText;
    } m_debugData;

    friend class CHyprOpenGLImpl;
};
