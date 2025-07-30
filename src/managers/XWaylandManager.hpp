#pragma once

#include "../defines.hpp"

class CWindow; // because clangd
using PHLWINDOW = SP<CWindow>;
class CWLSurfaceResource;

class CHyprXWaylandManager {
  public:
    CHyprXWaylandManager();
    ~CHyprXWaylandManager();

    SP<CWLSurfaceResource>    getWindowSurface(PHLWINDOW);
    void                      activateSurface(SP<CWLSurfaceResource>, bool);
    void                      activateWindow(PHLWINDOW, bool);
    Hyprutils::Math::CBox     getGeometryForWindow(PHLWINDOW);
    void                      sendCloseWindow(PHLWINDOW);
    void                      setWindowFullscreen(PHLWINDOW, bool);
    bool                      shouldBeFloated(PHLWINDOW, bool pending = false);
    void                      checkBorders(PHLWINDOW);
    Hyprutils::Math::Vector2D xwaylandToWaylandCoords(const Hyprutils::Math::Vector2D&);
    Hyprutils::Math::Vector2D waylandToXWaylandCoords(const Hyprutils::Math::Vector2D&);
};

inline UP<CHyprXWaylandManager> g_pXWaylandManager;