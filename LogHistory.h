#pragma once
#include <string>
#include <ostream>
#include <QDateTime>

namespace smarthome
{
// vraag 32 (Object Georiënteerde Project - Aanvullend): dynamic memory allocation (new)
// vraag 33 (Object Georiënteerde Project - Aanvullend): dynamic memory removing (delete)
// vraag 42 (Object Georiënteerde Project - Aanvullend): useful Qt class
// QDateTime (uit Qt Core) wordt gebruikt om elk logbericht een
// echte, correct geformatteerde tijdstempel te geven -- nuttiger
// en minder foutgevoelig dan zelf datum/tijd-logica te schrijven
// met <ctime>.
class LogHistory
{
public:
    explicit LogHistory(std::size_t capacity = 10);
    ~LogHistory();

    LogHistory(const LogHistory&) = delete;
    LogHistory& operator=(const LogHistory&) = delete;

    void add(const std::string& message);
    void printAll(std::ostream& os) const;

private:
    std::string* buffer_;
    std::size_t capacity_;
    std::size_t count_ = 0;
    std::size_t next_ = 0;
};
}
