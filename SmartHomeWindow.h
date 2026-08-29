#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>
#include <vector>
#include "House.h"
#include "LogHistory.h"
#include "RuleEngine.h"

namespace smarthome
{
    // vraag 47 (Object Georiënteerde Project - Aanvullend): usage of a GUI
    // vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra (House)
    // SmartHomeWindow ontvangt nu een volledig House (i.p.v. één losse
    // Room) en toont een dropdown om tussen kamers te wisselen. Alle
    // bestaande functionaliteit (toggle, save/load, motion, rules)
    // werkt op de momenteel GESELECTEERDE kamer.
    class SmartHomeWindow : public QWidget
    {
        Q_OBJECT

    public:
        explicit SmartHomeWindow(House& house, QWidget* parent = nullptr);

    private slots:
        void onToggleClicked(int deviceIndex);
        void onSaveClicked();
        void onLoadClicked();
        void onAddDeviceClicked();
        void onSimulateMotionClicked();
        void onResetClicked();
        void onSearchTextChanged(const QString& text);
        void onRoomChanged(int index);

    private:
        Room& currentRoom();
        void populateRoomSelector();
        void rebuildForCurrentRoom();
        void buildUi();
        void addDeviceRow(std::size_t index);
        void refreshLabels();
        void logAction(const std::string& message);
        void setupAutomationRules();
        QString iconForType(const std::string& typeName) const;

        House& house_;
        LogHistory log_;
        RuleEngine ruleEngine_;
        QComboBox* roomSelector_;
        QVBoxLayout* deviceListLayout_;
        QLabel* activeCountLabel_;
        QLabel* typeCounterLabel_;
        QLabel* statusBarLabel_;
        QLineEdit* searchBox_;
        std::vector<QLabel*> nameLabels_;
        std::vector<QLabel*> statusBadges_;
        std::vector<QFrame*> deviceCards_;
    };
}