#include "SmartHomeWindow.h"
#include "DeviceFactory.h"
#include "Camera.h"
#include "Light.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QStringList>
#include <QFont>
#include <QTimer>

namespace smarthome
{
    SmartHomeWindow::SmartHomeWindow(House& house, QWidget* parent)
        : QWidget(parent), house_(house)
    {
        setWindowTitle("Smart Home Simulator");
        setMinimumWidth(560);

        setStyleSheet(
            "QWidget { background-color: #1e1f26; color: #e8e8e8; font-family: 'Segoe UI'; }"
            "QPushButton { background-color: #33364a; border: none; border-radius: 6px;"
            "  padding: 8px 14px; color: #e8e8e8; font-weight: 600; }"
            "QPushButton:hover { background-color: #454969; }"
            "QPushButton:pressed { background-color: #2a2c3d; }"
            "QFrame#card { background-color: #262836; border-radius: 10px; }"
            "QFrame#card:hover { background-color: #2e3145; }"
            "QLineEdit, QComboBox { background-color: #2a2c3d; border: 1px solid #3a3d52;"
            "  border-radius: 6px; padding: 6px 10px; color: #e8e8e8; }"
        );

        auto* outerLayout = new QVBoxLayout(this);
        outerLayout->setSpacing(14);
        outerLayout->setContentsMargins(20, 20, 20, 20);

        auto* title = new QLabel("🏠  Smart Home Dashboard — " + QString::fromStdString(house_.getName()));
        QFont titleFont = title->font();
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        title->setFont(titleFont);
        outerLayout->addWidget(title);

        // vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra (House)
        // Dropdown om tussen kamers van het huis te wisselen.
        roomSelector_ = new QComboBox();
        connect(roomSelector_, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &SmartHomeWindow::onRoomChanged);
        outerLayout->addWidget(roomSelector_);

        activeCountLabel_ = new QLabel();
        activeCountLabel_->setStyleSheet("color: #8ea6ff; font-size: 13px;");
        outerLayout->addWidget(activeCountLabel_);

        typeCounterLabel_ = new QLabel();
        typeCounterLabel_->setStyleSheet("color: #a0a8c0; font-size: 12px;");
        outerLayout->addWidget(typeCounterLabel_);

        searchBox_ = new QLineEdit();
        searchBox_->setPlaceholderText("🔍 Zoek op naam...");
        connect(searchBox_, &QLineEdit::textChanged, this, &SmartHomeWindow::onSearchTextChanged);
        outerLayout->addWidget(searchBox_);

        deviceListLayout_ = new QVBoxLayout();
        deviceListLayout_->setSpacing(10);
        outerLayout->addLayout(deviceListLayout_);

        auto* actionRow = new QHBoxLayout();
        auto* addButton = new QPushButton("➕ Nieuw device");
        auto* motionButton = new QPushButton("🎥 Simuleer beweging");
        auto* resetButton = new QPushButton("🔄 Reset alles");
        connect(addButton, &QPushButton::clicked, this, &SmartHomeWindow::onAddDeviceClicked);
        connect(motionButton, &QPushButton::clicked, this, &SmartHomeWindow::onSimulateMotionClicked);
        connect(resetButton, &QPushButton::clicked, this, &SmartHomeWindow::onResetClicked);
        actionRow->addWidget(addButton);
        actionRow->addWidget(motionButton);
        actionRow->addWidget(resetButton);
        outerLayout->addLayout(actionRow);

        auto* separator = new QFrame();
        separator->setFrameShape(QFrame::HLine);
        separator->setStyleSheet("background-color: #3a3d52;");
        outerLayout->addWidget(separator);

        auto* fileRow = new QHBoxLayout();
        auto* saveButton = new QPushButton("💾  Opslaan naar bestand");
        auto* loadButton = new QPushButton("📂  Laden vanuit bestand");
        connect(saveButton, &QPushButton::clicked, this, &SmartHomeWindow::onSaveClicked);
        connect(loadButton, &QPushButton::clicked, this, &SmartHomeWindow::onLoadClicked);
        fileRow->addWidget(saveButton);
        fileRow->addWidget(loadButton);
        outerLayout->addLayout(fileRow);

        statusBarLabel_ = new QLabel("Geen acties uitgevoerd.");
        statusBarLabel_->setStyleSheet("color: #7a7d8f; font-size: 11px; padding-top: 6px;");
        outerLayout->addWidget(statusBarLabel_);

        populateRoomSelector();
        rebuildForCurrentRoom();
    }

    // vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra (House)
    // Geeft de Room terug die momenteel geselecteerd is in de
    // dropdown. std::map<std::string, Room> wordt hier doorlopen op
    // basis van de geselecteerde tekst, niet op index -- consistent
    // met hoe House zelf kamers opzoekt (via naam, niet positie).
    Room& SmartHomeWindow::currentRoom()
    {
        std::string roomName = roomSelector_->currentText().toStdString();
        Room* room = house_.findRoom(roomName);
        // findRoom kan in theorie nullptr geven als de selectie niet
        // meer bestaat; in de praktijk kan dat hier niet gebeuren
        // omdat de dropdown enkel bestaande kamernamen bevat.
        return *room;
    }

    void SmartHomeWindow::populateRoomSelector()
    {
        roomSelector_->blockSignals(true);
        roomSelector_->clear();
        for (const auto& pair : house_.rooms())
        {
            roomSelector_->addItem(QString::fromStdString(pair.first));
        }
        roomSelector_->blockSignals(false);
    }

    void SmartHomeWindow::onRoomChanged(int /*index*/)
    {
        rebuildForCurrentRoom();
    }

    // vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra (House)
    // Breekt de huidige device-kaarten af en bouwt ze opnieuw op voor
    // de nu geselecteerde kamer, en herkoppelt de automatiseringsregel
    // aan de devices van die specifieke kamer.
    void SmartHomeWindow::rebuildForCurrentRoom()
    {
        QLayoutItem* item;
        while ((item = deviceListLayout_->takeAt(0)) != nullptr)
        {
            delete item->widget();
            delete item;
        }
        nameLabels_.clear();
        statusBadges_.clear();
        deviceCards_.clear();

        buildUi();
        setupAutomationRules();
    }

    QString SmartHomeWindow::iconForType(const std::string& typeName) const
    {
        if (typeName == "Light")      return "💡";
        if (typeName == "Thermostat") return "🌡️";
        if (typeName == "DoorLock")   return "🔒";
        if (typeName == "Camera")     return "📷";
        return "❓";
    }

    void SmartHomeWindow::buildUi()
    {
        const auto& devices = currentRoom().devices();
        for (std::size_t i = 0; i < devices.size(); ++i)
        {
            addDeviceRow(i);
        }
        refreshLabels();
    }

    void SmartHomeWindow::addDeviceRow(std::size_t index)
    {
        const auto& devices = currentRoom().devices();
        auto* card = new QFrame();
        card->setObjectName("card");
        auto* cardLayout = new QHBoxLayout(card);
        cardLayout->setContentsMargins(14, 10, 14, 10);

        auto* nameLabel = new QLabel(
            iconForType(devices[index]->getTypeName()) + "  " +
            QString::fromStdString(devices[index]->getName()));
        QFont nameFont = nameLabel->font();
        nameFont.setBold(true);
        nameLabel->setFont(nameFont);
        nameLabels_.push_back(nameLabel);

        auto* badge = new QLabel();
        badge->setAlignment(Qt::AlignCenter);
        badge->setMinimumWidth(180);
        statusBadges_.push_back(badge);

        auto* toggleButton = new QPushButton("Toggle");
        int idx = static_cast<int>(index);
        connect(toggleButton, &QPushButton::clicked, this, [this, idx]() {
            onToggleClicked(idx);
        });

        cardLayout->addWidget(nameLabel, 2);
        cardLayout->addWidget(badge, 3);
        cardLayout->addWidget(toggleButton, 1);

        deviceCards_.push_back(card);
        deviceListLayout_->addWidget(card);
    }

    void SmartHomeWindow::refreshLabels()
    {
        Room& room = currentRoom();
        const auto& devices = room.devices();

        int activeCount = room.countDevicesIf([](const Device& d) { return d.isOn(); });
        activeCountLabel_->setText(
            QString("● %1 van %2 devices actief in %3")
                .arg(activeCount).arg(devices.size())
                .arg(QString::fromStdString(room.getName())));

        QStringList parts;
        for (const auto& pair : room.countDevicesByType())
        {
            parts << QString("%1: %2").arg(QString::fromStdString(pair.first)).arg(pair.second);
        }
        typeCounterLabel_->setText(parts.join("   ·   "));

        for (std::size_t i = 0; i < devices.size() && i < statusBadges_.size(); ++i)
        {
            QLabel* badge = statusBadges_[i];
            badge->setText(QString::fromStdString(devices[i]->status()));

            if (devices[i]->isOn())
            {
                badge->setStyleSheet(
                    "background-color: #204d33; color: #6dffa8; border-radius: 6px; padding: 4px;");
            }
            else
            {
                badge->setStyleSheet(
                    "background-color: #3a3a42; color: #a0a0a8; border-radius: 6px; padding: 4px;");
            }
        }
    }

    void SmartHomeWindow::logAction(const std::string& message)
    {
        log_.add(message);
        statusBarLabel_->setText(QString::fromStdString(log_.last()));
    }

    void SmartHomeWindow::setupAutomationRules()
    {
        Room& room = currentRoom();
        Camera* firstCamera = nullptr;
        Light* firstLight = nullptr;
        for (const auto& device : room.devices())
        {
            if (firstCamera == nullptr)
            {
                firstCamera = dynamic_cast<Camera*>(device.get());
            }
            if (firstLight == nullptr)
            {
                firstLight = dynamic_cast<Light*>(device.get());
            }
        }

        if (firstCamera == nullptr || firstLight == nullptr)
        {
            return;
        }

        Rule securityLightRule;
        securityLightRule.description =
            "Beveiligingsverlichting: " + firstCamera->getName() + " detecteerde beweging -> " +
            firstLight->getName() + " automatisch aangezet";
        securityLightRule.condition = [firstCamera, firstLight]() {
            return firstCamera->isMotionDetected() && !firstLight->isOn();
        };
        securityLightRule.action = [firstLight]() {
            firstLight->toggle();
        };
        ruleEngine_.addRule(securityLightRule);

        connect(firstCamera, &Camera::motionDetectedSignal,
                &ruleEngine_, &RuleEngine::evaluateAll, Qt::DirectConnection);

        connect(&ruleEngine_, &RuleEngine::ruleTriggered, this, [this](const std::string& desc) {
            logAction("🤖 Automatisering: " + desc);
            refreshLabels();
        });
    }

    void SmartHomeWindow::onToggleClicked(int deviceIndex)
    {
        const auto& devices = currentRoom().devices();
        if (deviceIndex >= 0 && static_cast<std::size_t>(deviceIndex) < devices.size())
        {
            devices[deviceIndex]->toggle();
            logAction(devices[deviceIndex]->getName() + " getoggeld");
            refreshLabels();
        }
    }

    void SmartHomeWindow::onSaveClicked()
    {
        house_.saveToFile("house_save.json");
        logAction("Volledig huis opgeslagen naar house_save.json");
        QMessageBox::information(this, "Opgeslagen", "Het huis is opgeslagen naar house_save.json");
    }

    void SmartHomeWindow::onLoadClicked()
    {
        house_.loadFromFile("house_save.json");
        populateRoomSelector();
        rebuildForCurrentRoom();
        logAction("Huis geladen vanuit house_save.json");
        QMessageBox::information(this, "Geladen", "Het huis is geladen vanuit house_save.json");
    }

    void SmartHomeWindow::onAddDeviceClicked()
    {
        QStringList types = { "Light", "Thermostat", "DoorLock", "Camera" };
        bool typeOk = false;
        QString type = QInputDialog::getItem(this, "Nieuw device", "Kies een type:", types, 0, false, &typeOk);
        if (!typeOk)
        {
            return;
        }

        bool nameOk = false;
        QString name = QInputDialog::getText(this, "Nieuw device", "Naam van het device:", QLineEdit::Normal, "", &nameOk);
        if (!nameOk || name.trimmed().isEmpty())
        {
            return;
        }

        auto device = createDeviceFromType(type.toStdString(), name.toStdString());
        if (device == nullptr)
        {
            QMessageBox::warning(this, "Fout", "Onbekend devicetype.");
            return;
        }

        currentRoom().addDevice(std::move(device));
        rebuildForCurrentRoom();
        logAction(name.toStdString() + " (" + type.toStdString() + ") toegevoegd");
    }

    void SmartHomeWindow::onSimulateMotionClicked()
    {
        const auto& devices = currentRoom().devices();
        for (std::size_t i = 0; i < devices.size(); ++i)
        {
            if (auto* camera = dynamic_cast<Camera*>(devices[i].get()))
            {
                if (!camera->isOn())
                {
                    camera->toggle();
                    logAction(camera->getName() + " automatisch aangezet");
                }

                camera->triggerMotion();
                logAction(camera->getName() + ": beweging gesimuleerd!");
                refreshLabels();

                if (i < deviceCards_.size())
                {
                    QFrame* card = deviceCards_[i];
                    card->setStyleSheet("background-color: #7a2020; border-radius: 10px;");
                    QTimer::singleShot(500, this, [card]() {
                        card->setStyleSheet("background-color: #262836; border-radius: 10px;");
                    });
                }

                QMessageBox::warning(this, "🚨 Beweging gedetecteerd!",
                    QString::fromStdString(camera->getName()) + " heeft beweging gedetecteerd!");
                return;
            }
        }
        QMessageBox::information(this, "Geen camera gevonden",
            "Er is geen Camera-device in deze kamer.");
    }

    void SmartHomeWindow::onResetClicked()
    {
        const auto& devices = currentRoom().devices();
        for (const auto& device : devices)
        {
            if (device->isOn())
            {
                device->toggle();
            }
        }
        logAction("Alle devices in " + currentRoom().getName() + " gereset naar uit");
        refreshLabels();
    }

    void SmartHomeWindow::onSearchTextChanged(const QString& text)
    {
        const auto& devices = currentRoom().devices();
        std::string searchTerm = text.toStdString();

        for (std::size_t i = 0; i < devices.size() && i < deviceCards_.size(); ++i)
        {
            bool matches = searchTerm.empty() ||
                (devices[i]->getName().find(searchTerm) != std::string::npos);
            deviceCards_[i]->setVisible(matches);
        }
    }
}