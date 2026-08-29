#pragma once
#include <QObject>
#include <vector>
#include "Rule.h"

namespace smarthome
{
// vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra
// vraag 43 (Object Georiënteerde Project - Aanvullend): useful usage of signals/slots
// RuleEngine houdt een lijst van Rule-objecten bij en evalueert ze
// allemaal telkens evaluateAll() aangeroepen wordt (als slot,
// gekoppeld aan device-signals zoals Camera::motionDetectedSignal).
// Dit ontkoppelt volledig WAT er gecontroleerd/uitgevoerd wordt
// (de Rules) van WANNEER dat gebeurt (elk signal verbonden met
// evaluateAll()).
class RuleEngine : public QObject
{
    Q_OBJECT

public:
    explicit RuleEngine(QObject* parent = nullptr);

    void addRule(Rule rule);

public slots:
    void evaluateAll();

signals:
    void ruleTriggered(const std::string& description);

private:
    std::vector<Rule> rules_;
};
}
