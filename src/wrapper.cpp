#include "include/prism/qt/modular/wrapper.h"
#include "include/prism/qt/modular/interfaces/intf_module.h"
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QPluginLoader>
#include <QVariant>

namespace prism::qt::modular {

wrapper::wrapper(std::vector<intfModule*> plugins,std::function<int()> runapp):m_plugins(plugins),m_fuc_runapp(runapp)
{

}

int wrapper::run()
{

    for (intfModule* m : m_plugins)
    {
        qDebug() << "execute register types : " << m->objectName();
        m->register_types();
    }

    for (intfModule* m : m_plugins)
    {
        qDebug() << "execute init           : " << m->objectName();
        m->init();
    }

    for (intfModule* m : m_plugins)
    {
        qDebug() << "execute install        : " << m->objectName();
        m->install();
    }

    int result = m_fuc_runapp();

    for (auto rit = m_plugins.rbegin(); rit != m_plugins.rend(); ++rit)
    {
        qDebug() << "execute uninstall      : " << (*rit)->objectName();
        (*rit)->uninstall();
    }

    for (auto rit = m_plugins.rbegin(); rit != m_plugins.rend(); ++rit)
    {
        qDebug() << "execute uniniti        : " << (*rit)->objectName();
        (*rit)->uninit();
    }


    for (auto rit = m_plugins.rbegin(); rit != m_plugins.rend(); ++rit)
    {
        qDebug() << "execute delete         : " << (*rit)->objectName();
        (*rit)->deleteLater();
    }

    return result;
}

std::string wrapper::startupUrl = "";
} //prism::qt::modular
