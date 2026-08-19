# Smart Home Simulator

## Vraag 1 — Topic + beschrijving

**Smart Home Simulator**

Dit project is een objectgeoriënteerde C++-applicatie die een eenvoudig
domoticasysteem simuleert. De gebruiker beheert een kamer vol slimme
toestellen — een lamp, een thermostaat, een deurslot en een
beveiligingscamera — die elk aan- en uitgeschakeld kunnen worden en hun
eigen status kunnen tonen. Het programma draait momenteel volledig in de
console en focust op het correct toepassen van OOP-principes zoals
overerving, abstractie, polymorfisme, encapsulatie en objectcompositie.

De kernstructuur bestaat uit een abstracte basisklasse `Device`, waarvan
`Light`, `Thermostat`, `DoorLock` en `Camera` erven. Elke afgeleide klasse
implementeert zijn eigen versie van de virtuele functies `toggle()` en
`status()`, waardoor polymorf gedrag ontstaat: dezelfde aanroep
(`device->status()`) geeft een ander, type-specifiek resultaat
afhankelijk van het onderliggende toestel. De `Room`-klasse past
objectcompositie toe door een verzameling toestellen te beheren via
`std::unique_ptr`, wat veilig geheugenbeheer garandeert zonder dangling
pointers.

Dit project vormt de basis van een uitbreidbare domotica-engine en kan
later uitgebreid worden met meerdere kamers, een grafische interface
(Qt), sensordata via een achtergrondthread, bestandsopslag van de
huisconfiguratie, of communicatie met echte hardware.

## Vraag 2 — GitHub link

https://github.com/fegorissen/Domotica-Project

(martijn-leemans toegevoegd als collaborator)

## Vraag 3 — Useful and correct class

**Waar**

*Zie: `Thermostat.h`*

Thermostat is een nuttige en correcte klasse omdat het één duidelijke,
afgebakende verantwoordelijkheid heeft: één verwarmingstoestel
voorstellen. Het hergebruikt alles wat gemeenschappelijk is via `Device`
(naam, aan/uit), en voegt enkel zijn eigen, specifieke data
(`targetTemperature_`) en gedrag toe. Net als `Light`, `DoorLock` en
`Camera` doet het precies één ding, wat de code overzichtelijk en
makkelijk uitbreidbaar maakt.

## Vraag 4 — Useful and correct abstraction

**Waar**

*Zie: `Device.h`*

De abstractie is nuttig en correct omdat `Device` enkel de essentiële
interface blootlegt (`toggle()`, `status()`, `getName()`, `isOn()`)
zonder te tonen hoe een specifiek toestel zijn status precies
samenstelt. Wie met een `Device` werkt, weet nooit hoe de interne
implementatie van een `Light` of `Camera` eruitziet — enkel dat elk
`Device` een `status()` heeft. Dat is precies het doel van abstractie:
het "wat" blootleggen, het "hoe" verbergen.

## Vraag 5 — Useful and correct encapsulation

**Waar**

*Zie: `Camera.h`*

De encapsulatie is nuttig en correct omdat `motionDetected_` `private`
is: enkel bereikbaar via `triggerMotion()` en indirect via `status()`.
Van buitenaf kan niemand deze waarde rechtstreeks fout instellen — de
klasse zelf bewaakt wanneer en hoe deze waarde verandert, wat de
interne staat altijd consistent houdt.

## Vraag 6 — Useful and correct inheritance

**Waar**

*Zie: `Light.h`*

De overerving is nuttig en correct omdat `Light` via `public Device`
een correcte "is-a"-relatie aangaat: elke `Light` ís ook een `Device`,
en kan overal gebruikt worden waar een `Device` verwacht wordt (bv. in
`Room`'s `vector<unique_ptr<Device>>`). `Light` hoeft de gemeenschap-
pelijke code (naam bijhouden, aan/uit-status) niet te herhalen — dat
regelt `Device` al — en voegt enkel zijn eigen, specifieke data
(`brightness_`) toe.

## Vraag 7 — Useful and correct polymorphism

**Waar**

*Zie: `Room.cpp`, functie `printAllDevices()`*

Polymorfisme is hier nuttig en correct toegepast omdat `device->
status()` telkens het juiste, type-specifieke resultaat teruggeeft
(Light/Thermostat/DoorLock/Camera), zonder dat `Room` ooit weet welk
concreet type er precies in de vector zit. Welke implementatie van
`status()` effectief draait, wordt pas tijdens uitvoering bepaald via
dynamic dispatch — dankzij de virtuele functies in `Device`. Dat maakt
de code flexibel en uitbreidbaar: een nieuw type `Device` toevoegen
vereist geen enkele wijziging aan deze functie.

## Vraag 8 — Useful and correct object composition

**Waar**

*Zie: `Room.h`*

Objectcompositie is hier nuttig en correct toegepast omdat `Room`
"has-a" verzameling `Device`'s (via `unique_ptr`), niet via overerving
— een `Room` ís geen `Device`. De devices worden als bouwstenen
gecombineerd om de functionaliteit van een kamer (toestellen groeperen,
opzoeken, tonen) te realiseren. Dit maakt de code modulair: `Room`
hoeft nooit te weten welke soorten `Device` erin zitten, enkel dat het
`Device`'s zijn.

## Vraag 9 — Useful and correct base class

**Waar**

*Zie: `Device.h`*

`Device` is een nuttige en correcte base class omdat het enkel bevat
wat écht gemeenschappelijk is aan alle toestellen (naam, aan/uit-
status, de interface), zonder implementatiedetails van specifieke
toestellen op te leggen. Alle afgeleide klassen gebruiken deze basis
zinvol, zonder overbodige of geforceerde overerving.

## Vraag 10 — Useful and correct abstract base class

**Waar**

*Zie: `Device.h`*

`Device` is een échte abstracte base class: `toggle()` en `status()`
zijn pure virtual (`= 0`), waardoor `Device` nooit rechtstreeks
geïnstantieerd kan worden (`Device d("test");` geeft een compile-
fout). Dat is logisch, want een "generiek toestel" zonder concreet
gedrag heeft geen betekenis — enkel de afgeleide, concrete types
(Light, Thermostat, ...) wel.

## Vraag 11 — Useful and correct virtual function

**Waar**

*Zie: `Device.h` (destructor), `Doorlock.h` (override)*

De destructor is expliciet `virtual`, essentieel omdat objecten via
een `Device`-pointer beheerd worden (zie `main.cpp`/`Room.cpp`).
Zonder `virtual` zou bij vernietiging altijd enkel de opruiming van
`Device` zelf draaien, nooit die van het echte, afgeleide type.
Daarnaast gebruiken alle afgeleide klassen consequent `override` in
plaats van `virtual` te herhalen — de compiler controleert dan of de
functie-signatuur écht overeenkomt met de basisklasse.

## Vraag 12 — No mistake in object-oriented programming

**Waar**

*Zie: `Room.cpp` (nullptr-check), `main.cpp` (samenvatting)*

- Geen dangling pointers: `Room` bezit zijn devices via `unique_ptr`
  in plaats van rauwe pointers naar lokale variabelen.
- Geen crash bij een niet-bestaand device: `findDevice()` geeft
  `nullptr` terug, en dat wordt altijd expliciet gecontroleerd vóór
  gebruik.
- Geen ontbrekende virtuele destructor: `Device::~Device()` is
  `virtual`.
- Consequent `override` i.p.v. `virtual` te herhalen in elke
  afgeleide klasse.
- Geen public data members: alle velden zijn `protected`/`private`
  met gecontroleerde toegang via functies.
- Geen overerving gebruikt waar compositie hoorde: `Room` erft niet
  van `Device`, het bevat `Device`'s als lid.

---

## Bouwen in Qt Creator

1. Open Qt Creator → **File → Open File or Project...** → selecteer `CMakeLists.txt`.
2. Kies een kit met een C++17-compiler.
3. **Build → Rebuild All**, dan **Run**.

## Klassenstructuur

| Klasse | Rol |
|---|---|
| `Device` | Abstracte basisklasse — legt de gemeenschappelijke interface vast |
| `Light`, `Thermostat`, `DoorLock`, `Camera` | Afgeleide klassen — elk hun eigen toestel |
| `Room` | Beheert een verzameling `Device`'s via objectcompositie |
