#include "include/prism/qt/modular/wrapper.h"
#include "include/prism/qt/modular/interfaces/intf_module.h"
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QPluginLoader>
#include <QVariant>
#include <QtQml/QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQuickWindow>
#include <iostream>
#include <prism/container.hpp>

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
    int result = -1;

    try{
        auto qmlengine = prism::Container::get()->resolve_object<QQmlApplicationEngine>();
        auto app = prism::Container::get()->resolve_object<QGuiApplication>();

        if(qmlengine && app)
        {
            static QMetaObject::Connection connection = QObject::connect(
                qmlengine.get(),
                &QQmlApplicationEngine::objectCreated,
                app.get(),
                [&](QObject* object, const QUrl& url) {
                    if (url.toString() == QString::fromStdString(prism::qt::modular::wrapper::startupUrl))
                    {
                        if (!object)
                        {
                            app->exit(-1);
                        }

                        auto* win = reinterpret_cast<QQuickWindow*>(object);
                        if (win)
                        {
                            QObject::disconnect(connection);

                            std::shared_ptr<QQuickWindow> sp_win(win, [](QQuickWindow* p) { Q_UNUSED(p) });
                            prism::Container::get()->register_instance(sp_win);
                        }
                    }
                },
                Qt::QueuedConnection);
        }

        if(qmlengine)
            qmlengine->load(QString(prism::qt::modular::wrapper::startupUrl.c_str()));

        if(this->m_fuc_runapp)
            result = this->m_fuc_runapp();
        else
            result = app->exec();
    }
    catch(std::string str)
    {
        qDebug() << str.data();
    }
    catch(const char* msg)
    {
        qDebug() << msg;
    }
    catch(std::exception& ex)
    {
        qDebug() << ex.what();
    }

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
