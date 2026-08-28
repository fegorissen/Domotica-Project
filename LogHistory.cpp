#include "LogHistory.h"

namespace smarthome
{
// vraag 32 (Object Georiënteerde Project - Aanvullend): dynamic
// memory allocation (new)
// new[] vraagt hier expliciet een array van 'capacity' strings op
// de heap aan -- dit gebeurt NIET automatisch zoals bij een
// gewone lokale variabele, en moet later handmatig weer
// vrijgegeven worden (zie de destructor hieronder).
LogHistory::LogHistory(std::size_t capacity)
    : buffer_(new std::string[capacity]), capacity_(capacity)
{
}

// vraag 33 (Object Georiënteerde Project - Aanvullend): dynamic
// memory removing (delete)
// delete[] geeft het geheugen dat in de constructor met new[]
// werd aangevraagd weer vrij. Dit MOET gebeuren, anders zou elke
// LogHistory die vernietigd wordt een memory leak achterlaten --
// de correcte paring van new[]/delete[] voorkomt dat.
LogHistory::~LogHistory()
{
    delete[] buffer_;
}

void LogHistory::add(const std::string& message)
{
    buffer_[next_] = message;
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
}
