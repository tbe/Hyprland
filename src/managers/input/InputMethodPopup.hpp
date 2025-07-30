#pragma once

#include "../../desktop/WLSurface.hpp"
#include "../../macros.hpp"
#include "../../helpers/math/Math.hpp"
#include "../../helpers/signal/Signal.hpp"

class CInputMethodPopupV2;

class CInputPopup {
  public:
    CInputPopup(SP<CInputMethodPopupV2> popup);

    void                   damageEntire();
    void                   damageSurface();

    bool                   isVecInPopup(const Hyprutils::Math::Vector2D& point);

    Hyprutils::Math::CBox                   globalBox();
    SP<CWLSurfaceResource> getSurface();

    void                   onCommit();

  private:
    SP<CWLSurface>          queryOwner();
    void                    updateBox();

    void                    onDestroy();
    void                    onMap();
    void                    onUnmap();

    WP<CInputMethodPopupV2> m_popup;
    SP<CWLSurface>          m_surface;
    Hyprutils::Math::CBox                    m_lastBoxLocal;
    MONITORID               m_lastMonitor = MONITOR_INVALID;

    struct {
        CHyprSignalListener map;
        CHyprSignalListener unmap;
        CHyprSignalListener destroy;
        CHyprSignalListener commit;
    } m_listeners;
};
