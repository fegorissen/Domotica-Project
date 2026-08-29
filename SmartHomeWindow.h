#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <vector>
#include "Room.h"
#include "LogHistory.h"

namespace smarthome
{
    // vraag 47 (Object Georiënteerde Project - Aanvullend): usage of a GUI
    // Volwaardig dashboard bovenop de bestaande Room/Device-logica:
    // titelbalk, live teller, typeteller (std::map, vraag 36),
    // zoekbalk (std::string::find, vraag 35), kleurgecodeerde
    // statuskaarten met icoon en badge, toggle-knoppen, device
    // toevoegen via dialoog, motion-simulatie met visuele flits,
    // reset, opslaan/laden (JSON, vraag 49), en een statusbalk die de
    // laatste actie toont via LogHistory (vraag 32/33/42).
    class SmartHomeWindow : public QWidget
    {
        Q_OBJECT

    public:
        explicit SmartHomeWindow(Room& room, QWidget* parent = nullptr);

    private slots:
        void onToggleClicked(int deviceIndex);
        void onSaveClicked();
        void onLoadClicked();
        void onAddDeviceClicked();
        void onSimulateMotionClicked();
        void onResetClicked();
        void onSearchTextChanged(const QString& text);

    private:
        void buildUi();
        void addDeviceRow(std::size_t index);
        void refreshLabels();
        void logAction(const std::string& message);
        QString iconForType(const std::string& typeName) const;

        Room& room_;
        LogHistory log_;
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