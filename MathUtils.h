#pragma once

// vraag 25 (Object Georiënteerde Project - Aanvullend): useful template function or class
// Generieke clamp-functie: werkt voor ELK vergelijkbaar type (double
// voor temperatuur, maar evengoed int, unsigned char, ...) zonder dat
// je voor elk type een aparte, bijna identieke functie moet schrijven.
// De compiler genereert automatisch de juiste versie op basis van het
// type dat effectief gebruikt wordt (hier: double, zie Thermostat.cpp).
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
