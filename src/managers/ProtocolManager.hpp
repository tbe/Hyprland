#pragma once

#include "../helpers/memory/Memory.hpp"
#include "../helpers/signal/Signal.hpp"
#include "desktop/DesktopTypes.hpp"
#include <wayland.hpp>
#include <unordered_map>

class CProtocolManager {
  public:
    CProtocolManager();
    ~CProtocolManager();

    bool isGlobalPrivileged(const wl_global* global);

  private:
    std::unordered_map<std::string, CHyprSignalListener> m_modeChangeListeners;

    void                                                 onMonitorModeChange(PHLMONITOR pMonitor);
};

inline UP<CProtocolManager> g_pProtocolManager;
