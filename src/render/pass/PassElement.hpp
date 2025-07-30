#pragma once

#include "../../defines.hpp"
#include <optional>

class IPassElement {
  public:
    virtual ~IPassElement() = default;

    virtual void                                 draw(const Hyprutils::Math::CRegion& damage) = 0;
    virtual bool                                 needsLiveBlur()                              = 0;
    virtual bool                                 needsPrecomputeBlur()                        = 0;
    virtual const char*                          passName()                                   = 0;
    virtual void                                 discard();
    virtual bool                                 undiscardable();
    virtual std::optional<Hyprutils::Math::CBox> boundingBox();  // in monitor-local logical coordinates
    virtual Hyprutils::Math::CRegion             opaqueRegion(); // in monitor-local logical coordinates
    virtual bool                                 disableSimplification();
};
