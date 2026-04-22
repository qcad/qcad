#include "core_global.h"

#include <QObject>
#include <QStringList>
#include "RSettings.h"

class QCADCORE_EXPORT RSettingsBridge : public QObject {
    Q_OBJECT

public:
    static RSettingsBridge* instance() {
        // If the instance doesn't exist yet, create it
        if (!m_instance) {
            m_instance = new RSettingsBridge();
            
            // Optional: Ensure the instance is cleaned up when the app closes
            // by setting the application object as the parent.
            // m_instance->setParent(QCoreApplication::instance());
        }
        return m_instance;
    }

    // Accessible from QML to get the latest list
    Q_INVOKABLE QStringList getRecentFiles() const {
        return RSettings::getRecentFiles();
    }

    // The single, generic notification point
    static void notifyChange() {
        if (m_instance) {
            emit m_instance->settingsChanged();
        }
    }

signals:
    // One signal to rule them all
    void settingsChanged();

private:
    explicit RSettingsBridge(QObject* parent = nullptr) : QObject(parent) {}
    static RSettingsBridge* m_instance;
};
