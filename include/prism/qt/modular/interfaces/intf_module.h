#ifndef PRISM_QT_MODULAR_INTFMODULE_H
#define PRISM_QT_MODULAR_INTFMODULE_H
#include "../prism_qt_modular_global.h"
#include <QObject>

namespace prism::qt::modular {
class PRISM_QT_MODULAR_EXPORT intfModule : public QObject
{
    Q_OBJECT
  public:
    virtual ~intfModule()
    {
    }
    virtual bool register_types() = 0;
    virtual bool init() = 0;
    virtual bool install() = 0;
    virtual bool uninstall() = 0;
    virtual bool uninit() = 0;
};
} // namespace prism::qt::modular

#define moduleInterface_iid "prism::qt::modular::intfModule/1.0"
Q_DECLARE_INTERFACE(prism::qt::modular::intfModule, moduleInterface_iid)

#endif // PRISM_QT_MODULAR_INTFMODULE_H
