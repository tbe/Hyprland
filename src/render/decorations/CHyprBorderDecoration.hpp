#pragma once

#include "IHyprWindowDecoration.hpp"

class CHyprBorderDecoration : public IHyprWindowDecoration {
  public:
    CHyprBorderDecoration(PHLWINDOW);
    virtual ~CHyprBorderDecoration() = default;

    virtual SDecorationPositioningInfo getPositioningInfo();

    virtual void                       onPositioningReply(const SDecorationPositioningReply& reply);

    virtual void                       draw(PHLMONITOR, float const& a);

    virtual eDecorationType            getDecorationType();

    virtual void                       updateWindow(PHLWINDOW);

    virtual void                       damageEntire();

    virtual eDecorationLayer           getDecorationLayer();

    virtual uint64_t                   getDecorationFlags();

    virtual std::string                getDisplayName();

  private:
    Hyprutils::Math::SBoxExtents m_extents;
    Hyprutils::Math::SBoxExtents m_reportedExtents;

    PHLWINDOWREF                 m_window;

    Hyprutils::Math::CBox        m_assignedGeometry = {0};

    int                          m_lastBorderSize = -1;

    Hyprutils::Math::CBox        assignedBoxGlobal();
    bool                         doesntWantBorders();
};
