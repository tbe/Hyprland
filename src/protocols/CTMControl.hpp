#pragma once

#include <vector>
#include <cstdint>
#include "WaylandProtocol.hpp"
#include "hyprland-ctm-control-v1.hpp"
#include <unordered_map>
#include <map>
#include "../helpers/AnimatedVariable.hpp"

class CMonitor;

class CHyprlandCTMControlResource {
  public:
    CHyprlandCTMControlResource(UP<CHyprlandCtmControlManagerV1>&& resource_);
    ~CHyprlandCTMControlResource();

    bool good();
    void block();

  private:
    UP<CHyprlandCtmControlManagerV1>                         m_resource;

    std::unordered_map<std::string, Hyprutils::Math::Mat3x3> m_ctms;
    bool                                                     m_blocked = false;
};

class CHyprlandCTMControlProtocol : public IWaylandProtocol {
  public:
    CHyprlandCTMControlProtocol(const wl_interface* iface, const int& ver, const std::string& name);

    virtual void bindManager(wl_client* client, void* data, uint32_t ver, uint32_t id);

  private:
    void destroyResource(CHyprlandCTMControlResource* resource);

    void setCTM(PHLMONITOR monitor, const Hyprutils::Math::Mat3x3& ctm);
    bool isCTMAnimationEnabled();

    //
    std::vector<UP<CHyprlandCTMControlResource>> m_managers;
    WP<CHyprlandCTMControlResource>              m_manager;

    //
    struct SCTMData {
        SCTMData();
        Hyprutils::Math::Mat3x3 ctmFrom = Hyprutils::Math::Mat3x3::identity(), ctmTo = Hyprutils::Math::Mat3x3::identity();
        PHLANIMVAR<float>       progress;
    };
    std::map<PHLMONITORREF, UP<SCTMData>> m_ctmDatas;

    friend class CHyprlandCTMControlResource;
};

namespace PROTO {
    inline UP<CHyprlandCTMControlProtocol> ctm;
};
