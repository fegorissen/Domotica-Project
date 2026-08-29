#include "LogHistory.h"

namespace smarthome
{
// vraag 32 (Object Georiënteerde Project - Aanvullend): dynamic memory allocation (new)
LogHistory::LogHistory(std::size_t capacity)
    : buffer_(new std::string[capacity]), capacity_(capacity)
{
}

// vraag 33 (Object Georiënteerde Project - Aanvullend): dynamic memory removing (delete)
LogHistory::~LogHistory()
{
    delete[] buffer_;
}

// vraag 42 (Object Georiënteerde Project - Aanvullend): useful Qt class
// QDateTime::currentDateTime() (Qt Core) haalt hier het huidige
// tijdstip op, en .toString()/.toStdString() zetten dat om naar
// een leesbare, herbruikbare std::string-tijdstempel die vóór
// elk logbericht geplakt wordt.
void LogHistory::add(const std::string& message)
{
    QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss");
    std::string fullMessage = "[" + timestamp.toStdString() + "] " + message;
    buffer_[next_] = fullMessage;
    next_ = (next_ + 1) % capacity_;
    if (count_ < capacity_)
    {
        ++count_;
    }
}

void LogHistory::printAll(std::ostream& os) const
{
    std::size_t start = (count_ < capacity_) ? 0 : next_;
    for (std::size_t i = 0; i < count_; ++i)
    {
        os << buffer_[(start + i) % capacity_] << "\n";
    }
}

// vraag 47 (Object Georiënteerde Project - Aanvullend): usage of a GUI
// Berekent de index van het laatst toegevoegde bericht in de
// ringbuffer. "next_" wijst altijd naar de VOLGENDE lege plek, dus
// het laatst toegevoegde bericht staat één positie terug (met
// wraparound via de modulo, vandaar + capacity_ om nooit negatief
// te worden).
std::string LogHistory::last() const
{
    if (count_ == 0)
    {
        return "";
    }
    std::size_t lastIndex = (next_ + capacity_ - 1) % capacity_;
    return buffer_[lastIndex];
}
}
