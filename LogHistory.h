#pragma once
#include <string>
#include <ostream>
#include <QDateTime>

namespace smarthome
{
// vraag 32 (Object Georiënteerde Project - Aanvullend): dynamic memory allocation (new)
// vraag 33 (Object Georiënteerde Project - Aanvullend): dynamic memory removing (delete)
// vraag 42 (Object Georiënteerde Project - Aanvullend): useful Qt class
// Zelfgemaakte, vaste-grootte ringbuffer voor de laatste N
// logberichten, elk voorzien van een QDateTime-tijdstempel.
class LogHistory
{
public:
    explicit LogHistory(std::size_t capacity = 10);
    ~LogHistory();

    // Kopiëren van een handgemaakte buffer is foutgevoelig (dubbele
    // vrijgave van hetzelfde geheugen als je niet oplet) en er is
    // geen zinvolle use case voor -- expliciet verboden i.p.v. per
    // ongeluk een gevaarlijke shallow copy toe te laten.
    LogHistory(const LogHistory&) = delete;
    LogHistory& operator=(const LogHistory&) = delete;

    void add(const std::string& message);
    void printAll(std::ostream& os) const;

    // vraag 47 (Object Georiënteerde Project - Aanvullend): usage of a GUI
    // Geeft het meest recent toegevoegde bericht terug (inclusief
    // tijdstempel), gebruikt door de statusbalk in SmartHomeWindow
    // om de laatste actie live te tonen.
    std::string last() const;

private:
    std::string* buffer_;
    std::size_t capacity_;
    std::size_t count_ = 0;
    std::size_t next_ = 0;
};
}
