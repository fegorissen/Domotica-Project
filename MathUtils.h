#pragma once

// vraag 27 (Object Georiënteerde Project - Aanvullend): everything in
// one or more self-made namespace(s)
// Alle klassen en functies van dit project zitten in de zelfgemaakte
// namespace "smarthome", zodat ze nooit botsen met gelijknamige
// klassen/functies uit externe libraries.
namespace smarthome
{
// vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class
template <typename T>
const T& clamp(const T& value, const T& low, const T& high)
{
    if (value < low)
    {
        return low;
    }
    if (value > high)
    {
        return high;
    }
    return value;
}
}
