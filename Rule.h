#pragma once
#include <string>
#include <functional>

namespace smarthome
{
// vraag 51 (Object Georiënteerde Project - Aanvullend): nice extra
// Een Rule combineert een conditie en een actie, beide als
// std::function -- dit maakt het mogelijk willekeurige
// combinaties van device-checks en -acties te definiëren als
// lambda's (vraag 40), zonder een aparte klasse per regel te
// moeten schrijven. Dit is het kernbouwblok van een klein
// automatiseringssysteem, vergelijkbaar met wat echte smart-home
// hubs gebruiken ("als X, dan Y").
struct Rule
{
    std::string description;
    std::function<bool()> condition;
    std::function<void()> action;
};
}
