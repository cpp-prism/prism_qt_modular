#ifndef PRISM_QT_MODULAR_WRAPPER_H
#define PRISM_QT_MODULAR_WRAPPER_H

#include "interfaces/intf_module.h"
#include "prism_qt_modular_global.h"
#include <vector>
#include <functional>

namespace prism::qt::modular {
class PRISM_QT_MODULAR_EXPORT wrapper
{
    std::function<int()> m_fuc_runapp;
    std::vector<intfModule*> m_plugins;

public:
    /**
     * @brief wrapper
     * 插件包装器
     * @param plugins
     * 传入要加载的插件列表
     * @param runapp
     * 传入插件加载完后 要做的事情， 一般是app.exe();
     */
    wrapper(std::vector<intfModule*> plugins,std::function<int()> runapp);
    int run();
};

} // namespace prism::qt::modular

#endif // PRISM_QT_MODULAR_WRAPPER_H
