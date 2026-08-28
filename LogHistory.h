#pragma once
#include <string>
#include <ostream>

namespace smarthome
{
// vraag 32 (Object Georiënteerde Project - Aanvullend): dynamic
// memory allocation (new)
// vraag 33 (Object Georiënteerde Project - Aanvullend): dynamic
// memory removing (delete)
// Zelfgemaakte, vaste-grootte ringbuffer voor de laatste N
// logberichten. std::vector zou hier ook kunnen, maar dit
// demonstreert bewust manueel geheugenbeheer met new[]/delete[],
// correct gepaard in constructor/destructor (geen memory leak).
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

private:
    std::string* buffer_;
    std::size_t capacity_;
    std::size_t count_ = 0;
    std::size_t next_ = 0;
};
}
