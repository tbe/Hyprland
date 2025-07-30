#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include "../../helpers/math/Math.hpp"
#include "../../desktop/DesktopTypes.hpp"

class CWindow;
class IHyprWindowDecoration;

enum eDecorationPositioningPolicy : uint8_t {
    DECORATION_POSITION_ABSOLUTE = 0, /* Decoration wants absolute positioning */
    DECORATION_POSITION_STICKY,       /* Decoration is stuck to some edge of a window */
};

enum eDecorationEdges : uint8_t {
    DECORATION_EDGE_TOP    = 1 << 0,
    DECORATION_EDGE_BOTTOM = 1 << 1,
    DECORATION_EDGE_LEFT   = 1 << 2,
    DECORATION_EDGE_RIGHT  = 1 << 3
};

/*
Request the positioner to position a decoration

DECORATION_POSITION_ABSOLUTE:
    - desiredExtents has to contain the extents. Edges has to have the edges used.
    - reserved allowed
DECORATION_POSITION_STICKY:
    - one edge allowed
    - priority allowed
    - desiredExtents contains the desired extents. Any other edge than the one selected is ignored.
    - reserved is allowed
*/
struct SDecorationPositioningInfo {
    eDecorationPositioningPolicy policy   = DECORATION_POSITION_ABSOLUTE;
    uint32_t                     edges    = 0;  // enum eDecorationEdges
    uint32_t                     priority = 10; // priority, decos will be evaluated high -> low
    Hyprutils::Math::SBoxExtents desiredExtents;
    bool                         reserved = false; // if true, geometry will use reserved area
};

/*
A reply from the positioner. This may be sent multiple times, if anything changes.

DECORATION_POSITION_ABSOLUTE:
    - assignedGeometry is empty
DECORATION_POSITION_STICKY:
    - assignedGeometry is relative to the edge's center point
    - ephemeral is sent
*/
struct SDecorationPositioningReply {
    Hyprutils::Math::CBox assignedGeometry;
    bool                  ephemeral = false; // if true, means it's a result of an animation and will change soon.
};

class CDecorationPositioner {
  public:
    CDecorationPositioner();

    Hyprutils::Math::Vector2D getEdgeDefinedPoint(uint32_t edges, PHLWINDOW pWindow);

    // called on resize, or insert/removal of a new deco
    void                         onWindowUpdate(PHLWINDOW pWindow);
    void                         uncacheDecoration(IHyprWindowDecoration* deco);
    Hyprutils::Math::SBoxExtents getWindowDecorationReserved(PHLWINDOW pWindow);
    Hyprutils::Math::SBoxExtents getWindowDecorationExtents(PHLWINDOW pWindow, bool inputOnly = false);
    Hyprutils::Math::CBox        getBoxWithIncludedDecos(PHLWINDOW pWindow);
    void                         repositionDeco(IHyprWindowDecoration* deco);
    Hyprutils::Math::CBox        getWindowDecorationBox(IHyprWindowDecoration* deco);
    void                         forceRecalcFor(PHLWINDOW pWindow);

  private:
    struct SWindowPositioningData {
        PHLWINDOWREF                pWindow;
        IHyprWindowDecoration*      pDecoration = nullptr;
        SDecorationPositioningInfo  positioningInfo;
        SDecorationPositioningReply lastReply;
        bool                        needsReposition = true;
    };

    struct SWindowData {
        Hyprutils::Math::Vector2D    lastWindowSize = {};
        Hyprutils::Math::SBoxExtents reserved       = {};
        Hyprutils::Math::SBoxExtents extents        = {};
        bool                         needsRecalc    = false;
    };

    std::map<PHLWINDOWREF, SWindowData>     m_windowDatas;
    std::vector<UP<SWindowPositioningData>> m_windowPositioningDatas;

    SWindowPositioningData*                 getDataFor(IHyprWindowDecoration* pDecoration, PHLWINDOW pWindow);
    void                                    onWindowUnmap(PHLWINDOW pWindow);
    void                                    onWindowMap(PHLWINDOW pWindow);
    void                                    sanitizeDatas();
};

inline UP<CDecorationPositioner> g_pDecorationPositioner;