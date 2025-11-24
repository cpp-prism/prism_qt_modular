#ifndef PRISM_QT_MODULAR_INTFMODULE_H
#define PRISM_QT_MODULAR_INTFMODULE_H
#include "../prism_qt_modular_global.h"
#include <prism/container.hpp>
#include <QQmlApplicationEngine>
#include <QVariant>
#include <QGuiApplication>
#include <QDebug>
#include <QObject>

namespace prism::qt::modular {
class PRISM_QT_MODULAR_EXPORT intfModule : public QObject
{
    Q_OBJECT
  public:
    virtual ~intfModule()
    {
    }
    Q_INVOKABLE virtual bool register_types() = 0;
    Q_INVOKABLE virtual bool init() = 0;
    Q_INVOKABLE virtual bool install() = 0;
    Q_INVOKABLE virtual bool uninstall() = 0;
    Q_INVOKABLE virtual bool uninit() = 0;
    Q_INVOKABLE void attach_engine(QQmlApplicationEngine* engine)
    {
        std::shared_ptr<QQmlApplicationEngine> engine_ptr(engine, [](QQmlApplicationEngine*) {
        });
        prism::Container::get()->register_instance<QQmlApplicationEngine>(engine_ptr);

    }
    Q_INVOKABLE  void attach_app(QGuiApplication* app)
    {
        std::shared_ptr<QGuiApplication> app_ptr(app, [](QGuiApplication*) {
        });
        prism::Container::get()->register_instance<QGuiApplication>(app_ptr);
    }
};
} // namespace prism::qt::modular

#define moduleInterface_iid "prism::qt::modular::intfModule/1.0"
Q_DECLARE_INTERFACE(prism::qt::modular::intfModule, moduleInterface_iid)

#endif // PRISM_QT_MODULAR_INTFMODULE_H
