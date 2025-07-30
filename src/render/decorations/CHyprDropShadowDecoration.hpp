#pragma once

#include "IHyprWindowDecoration.hpp"
#include "helpers/Color.hpp"

class CHyprDropShadowDecoration : public IHyprWindowDecoration {
  public:
    CHyprDropShadowDecoration(PHLWINDOW);
    virtual ~CHyprDropShadowDecoration() = default;

    virtual SDecorationPositioningInfo getPositioningInfo();

    virtual void                       onPositioningReply(const SDecorationPositioningReply& reply);

    virtual void                       draw(PHLMONITOR, float const& a);

    virtual eDecorationType            getDecorationType();

    virtual void                       updateWindow(PHLWINDOW);

    virtual void                       damageEntire();

    virtual eDecorationLayer           getDecorationLayer();

    virtual uint64_t                   getDecorationFlags();

    virtual std::string                getDisplayName();

    void                               render(PHLMONITOR, float const& a);

  private:
    Hyprutils::Math::SBoxExtents m_extents;
    Hyprutils::Math::SBoxExtents m_reportedExtents;

    PHLWINDOWREF                 m_window;

    Hyprutils::Math::Vector2D    m_lastWindowPos;
    Hyprutils::Math::Vector2D    m_lastWindowSize;

    void                         drawShadowInternal(const Hyprutils::Math::CBox& box, int round, float roundingPower, int range, CHyprColor color, float a);

    Hyprutils::Math::CBox        m_lastWindowBox          = {0};
    Hyprutils::Math::CBox        m_lastWindowBoxWithDecos = {0};
};
