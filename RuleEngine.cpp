#include "RuleEngine.h"

namespace smarthome
{
    RuleEngine::RuleEngine(QObject* parent)
        : QObject(parent)
    {
    }

    void RuleEngine::addRule(Rule rule)
    {
        rules_.push_back(std::move(rule));
    }

    // vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra
    // Loop over alle regels; als de conditie waar is, voer de actie
    // uit en meld het via het ruleTriggered-signal. Regels weten
    // niets van elkaar of van wie de engine aanroept -- volledige
    // ontkoppeling.
    void RuleEngine::evaluateAll()
    {
        for (auto& rule : rules_)
        {
            if (rule.condition())
            {
                rule.action();
                emit ruleTriggered(rule.description);
            }
        }
    }
}
