# 🏠 Smart Home Simulator

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Qt](https://img.shields.io/badge/Qt-6-green.svg)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.16%2B-064F8C.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](LICENSE)

Een objectgeoriënteerde C++/Qt-applicatie die een domoticasysteem simuleert: meerdere kamers vol slimme toestellen (lampen, thermostaten, deursloten, camera's) die je zowel via de console als via een grafisch dashboard kan bedienen, opslaan (JSON), en automatiseren via regels.

**🔗 Repository:** https://github.com/fegorissen/Domotica-Project

---

## 📋 Inhoudsopgave

- [✨ Projectbeschrijving](#-projectbeschrijving)
- [🛠️ Build manual](#️-build-manual)
- [🧩 Klassenstructuur](#-klassenstructuur)
- [📚 Basis-opdracht — alle vragen](#-basis-opdracht)
- [📚 Aanvullend-opdracht — alle vragen](#-aanvullend-opdracht)

---

## ✨ Projectbeschrijving

Dit project simuleert een domoticasysteem. Een `House` beheert meerdere `Room`'s, elk gevuld met slimme toestellen (`Light`, `Thermostat`, `DoorLock`, `Camera`) die via een gemeenschappelijke, abstracte `Device`-interface bediend worden.

De kernstructuur bestaat uit een abstracte basisklasse `Device`, waarvan `Light`, `Thermostat`, `DoorLock` en `Camera` erven. Elke afgeleide klasse implementeert zijn eigen versie van de virtuele functies `toggle()` en `status()`, waardoor polymorf gedrag ontstaat. `Room` past objectcompositie toe via `std::unique_ptr`, en `House` breidt dit verder uit met een verzameling `Room`'s via `std::map`.

**Hoogtepunten:**
- 🖼️ Qt Widgets **GUI-dashboard** met live statuskaarten, kleurcodering en een kamer-wisselaar
- 🤖 **Automatiseringssysteem** (`RuleEngine`) dat automatisch reageert op device-events (bv. beveiligingsverlichting bij bewegingsdetectie)
- 💾 **JSON-opslag** via de externe library `nlohmann/json`
- 🧵 **Achtergrondthread** die motion-detectie simuleert
- ⚠️ Eigen **exception handling**
- ✅ Apart, zelfgeschreven **testprogramma** met unit tests
- 🐛 Volledige **bugfix-workflow** via GitHub Issues, branches en pull requests

---

## 🛠️ Build manual

### Vereisten

| Vereiste | Versie |
|---|---|
| C++-compiler | C++17 |
| Qt | 6.x of 5.x, met modules **Core** en **Widgets** |
| nlohmann/json | header-only, zie stap 2 |

### 1️⃣ Qt Creator installeren

1. Ga naar https://www.qt.io/download-qt-installer.
2. Download en start de Qt Online Installer.
3. Maak een gratis Qt-account aan indien gevraagd.
4. Selecteer bij de component-keuze minstens:
   - **Qt Creator** (de IDE)
   - Een recente **Qt**-versie met de **Desktop**-component (bevat Core + Widgets)
   - Een compiler (MinGW op Windows, of je systeem-compiler op Linux/macOS)
5. Voltooi de installatie.

### 2️⃣ Project ophalen + externe library toevoegen

```bash
git clone https://github.com/fegorissen/Domotica-Project.git
```

Download **`json.hpp`** (het single-header bestand) van de [nieuwste nlohmann/json release](https://github.com/nlohmann/json/releases/latest) — onder **Assets**, zoek het losse `json.hpp`-bestand (niet de broncode-zip) — en plaats het in de hoofdmap van het project, naast de andere `.h`-bestanden.

### 3️⃣ Project openen

1. Open Qt Creator.
2. **File → Open File or Project...** → selecteer `CMakeLists.txt`.
3. Kies een **Kit** met een C++17-compiler en de Qt Widgets-module → **Configure Project**.

### 4️⃣ Bouwen en uitvoeren

Het project bevat twee build-doelen:

| Build-doel | Wat het doet |
|---|---|
| **Smarthome** | Het hoofdprogramma (console-demo + GUI-dashboard) |
| **SmarthomeTests** | Apart testprogramma met unit tests |

1. Kies onderaan links het gewenste build-doel.
2. **Build → Rebuild All**.
3. Klik **Run** (`Ctrl+R`).

> Bij het draaien van **Smarthome** verschijnt eerst een uitgebreide console-demo (die zo goed als elk criterium van dit project zichtbaar bewijst), gevolgd door het grafische dashboard.

<details>
<summary>🩹 Problemen oplossen</summary>

- **"multiple definition of main" / rare linkfouten** → verwijder de map die begint met `build`, doe **Build → Run CMake** gevolgd door **Build → Rebuild All**.
- **"Camera does not name a type" of gelijkaardig** → controleer of alle bestanden in `CMakeLists.txt` (`SMARTHOME_SOURCES`) staan, en of `json.hpp` aanwezig is.
- **Ontbrekende Qt Widgets-module** → zorg dat je Qt-installatie de **Widgets**-component bevat, niet enkel Core.

</details>

---

## 🧩 Klassenstructuur

| Klasse | Rol |
|---|---|
| `Device` | Abstracte basisklasse — legt de gemeenschappelijke interface vast |
| `Light`, `Thermostat`, `DoorLock`, `Camera` | Afgeleide klassen — elk hun eigen toestel |
| `Room` | Beheert een verzameling `Device`'s via objectcompositie |
| `House` | Beheert een verzameling `Room`'s via een `std::map` |
| `LogHistory` | Zelfgemaakte ringbuffer (`new[]`/`delete[]`) voor logberichten met tijdstempel |
| `DeviceFactory` | Reconstrueert devices op basis van hun typenaam |
| `DeviceNotFoundException` | Eigen exception-type |
| `MotionSensor` | Achtergrondthread die motion-detectie simuleert |
| `MotionMonitor` | Luistert via een Qt-slot naar `Camera`'s motion-signal |
| `Rule` / `RuleEngine` | Automatiseringsregels (conditie + actie) op basis van device-events |
| `SmartHomeWindow` | Het Qt Widgets GUI-dashboard |

---

## 📚 Basis-opdracht

<details>
<summary><strong>Vraag 1 — Topic + beschrijving</strong></summary>

**Smart Home Simulator**

Dit project is een objectgeoriënteerde C++-applicatie die een eenvoudig domoticasysteem simuleert. De gebruiker beheert een kamer vol slimme toestellen — een lamp, een thermostaat, een deurslot en een beveiligingscamera — die elk aan- en uitgeschakeld kunnen worden en hun eigen status kunnen tonen. De kernstructuur bestaat uit een abstracte basisklasse `Device`, waarvan `Light`, `Thermostat`, `DoorLock` en `Camera` erven, met polymorf gedrag via de virtuele functies `toggle()` en `status()`. `Room` past objectcompositie toe via `std::unique_ptr`.

</details>

<details>
<summary><strong>Vraag 2 — GitHub link</strong></summary>

https://github.com/fegorissen/Domotica-Project

</details>

<details>
<summary><strong>Vraag 3 — Useful and correct class</strong> → ✅ Waar</summary>

De klassen in dit project zijn nuttig en correct omdat elke klasse één duidelijke, afgebakende verantwoordelijkheid heeft. `Thermostat` bijvoorbeeld hergebruikt alles wat gemeenschappelijk is via `Device` (naam, aan/uit), en voegt enkel zijn eigen, specifieke data (`targetTemperature_`) en gedrag toe.

</details>

<details>
<summary><strong>Vraag 4 — Useful and correct abstraction</strong> → ✅ Waar</summary>

De abstractie is nuttig en correct omdat `Device` enkel de essentiële interface blootlegt (`toggle()`, `status()`, `getName()`, `isOn()`) zonder te tonen hoe een specifiek toestel zijn status precies samenstelt.

</details>

<details>
<summary><strong>Vraag 5 — Useful and correct encapsulation</strong> → ✅ Waar</summary>

De encapsulatie is nuttig en correct omdat `motionDetected_` in `Camera` private is: enkel bereikbaar via `triggerMotion()` en indirect via `status()`/`isMotionDetected()`.

</details>

<details>
<summary><strong>Vraag 6 — Useful and correct inheritance</strong> → ✅ Waar</summary>

De overerving is nuttig en correct omdat `Light` via `public Device` een correcte "is-a"-relatie aangaat: elke `Light` ís ook een `Device`.

</details>

<details>
<summary><strong>Vraag 7 — Useful and correct polymorphism</strong> → ✅ Waar</summary>

Polymorfisme is hier nuttig en correct toegepast omdat `device->status()` telkens het juiste, type-specifieke resultaat teruggeeft, zonder dat `Room` ooit weet welk concreet type er precies in de vector zit.

</details>

<details>
<summary><strong>Vraag 8 — Useful and correct object composition</strong> → ✅ Waar</summary>

Objectcompositie is hier nuttig en correct toegepast omdat `Room` "has-a" verzameling `Device`'s (via `unique_ptr`), en `House` op zijn beurt "has-a" verzameling `Room`'s (via `std::map`) — twee niveaus van compositie, niet via overerving.

</details>

<details>
<summary><strong>Vraag 9 — Useful and correct base class</strong> → ✅ Waar</summary>

`Device` is een nuttige en correcte base class omdat het enkel bevat wat écht gemeenschappelijk is aan alle toestellen, zonder implementatiedetails van specifieke toestellen op te leggen.

</details>

<details>
<summary><strong>Vraag 10 — Useful and correct abstract base class</strong> → ✅ Waar</summary>

`Device` is een échte abstracte base class: `toggle()`, `status()`, `getTypeName()` en `clone()` zijn pure virtual, waardoor `Device` nooit rechtstreeks geïnstantieerd kan worden.

</details>

<details>
<summary><strong>Vraag 11 — Useful and correct virtual function</strong> → ✅ Waar</summary>

De destructor is expliciet `virtual`, essentieel omdat objecten via een `Device`-pointer beheerd worden. Alle afgeleide klassen gebruiken consequent `override`.

</details>

<details>
<summary><strong>Vraag 12 — No mistake in object-oriented programming</strong> → ✅ Waar</summary>

Geen dangling pointers (`Room` bezit devices via `unique_ptr`), geen crash bij een niet-bestaand device (`nullptr`-checks overal), geen ontbrekende virtuele destructor, consequent `override`, geen public data members, geen overerving gebruikt waar compositie hoorde.

</details>

---

## 📚 Aanvullend-opdracht

<details>
<summary><strong>Vraag 1 — GitHub link</strong></summary>

https://github.com/fegorissen/Domotica-Project

</details>

<details>
<summary><strong>Vraag 2 — Clean main</strong> → ✅ Waar</summary>

`main()` bevat geen enkele beslissingslogica of berekening zelf — het maakt enkel objecten aan (`Room`, `House`, devices) en roept bestaande klassefuncties aan.

</details>

<details>
<summary><strong>Vraag 3 — No globals, but statics if needed</strong> → ✅ Waar</summary>

Er wordt nergens een globale variabele gebruikt. `Device::nextId_` is een `static` member: gedeeld door alle `Device`-objecten, maar netjes ingekapseld binnen `Device` zelf.

</details>

<details>
<summary><strong>Vraag 4 — Correct protections</strong> → ✅ Waar</summary>

Drie niveaus worden bewust en correct gebruikt: `public` voor de buitenwereld, `protected` voor `name_`/`on_` in `Device` (nodig in afgeleide klassen), `private` voor interne details zoals `nextId_`/`id_`.

</details>

<details>
<summary><strong>Vraag 5 — Maintainability</strong> → ✅ Waar</summary>

Consistente naming doorheen het project: member variables eindigen op `_`, functienamen zijn camelCase, klassenamen zijn PascalCase, en elk bestand bevat comments die uitleggen waarom.

</details>

<details>
<summary><strong>Vraag 6 — Separate header files</strong> → ✅ Waar</summary>

Elke klasse heeft zijn eigen `.h`/`.cpp`-paar: `Device`, `Light`, `Thermostat`, `DoorLock`, `Camera`, `Room`, `House`, `LogHistory`, `MotionSensor`, `MotionMonitor`, `RuleEngine`, `SmartHomeWindow`, `DeviceFactory`, `DeviceNotFoundException`.

</details>

<details>
<summary><strong>Vraag 7 — One complete project that compiles and does not crash</strong> → ✅ Waar</summary>

Alle klassen compileren samen tot één werkend programma zonder warnings, met correct beheerd geheugen via `unique_ptr` en overal `nullptr`-checks.

</details>

<details>
<summary><strong>Vraag 8 — Fully working project</strong> → ✅ Waar</summary>

Elk device-type gedraagt zich functioneel correct en aantoonbaar: `toggle()`, `status()`, `findDevice()`/`findRoom()` werken zowel voor bestaande als niet-bestaande items.

</details>

<details>
<summary><strong>Vraag 9 — Sufficient git commits</strong> → ✅ Waar</summary>

Het project is opgebouwd in duidelijk afgebakende stappen, elk met een eigen, beschrijvende commit-boodschap — zie de volledige geschiedenis op GitHub.

</details>

<details>
<summary><strong>Vraag 10 — Correct files on git</strong> → ✅ Waar</summary>

De repository bevat enkel de juiste bestanden: broncode, `CMakeLists.txt`, `README.md`, `LICENSE`, `.gitignore` en `json.hpp`. De build-map is uitgesloten via `.gitignore`.

</details>

<details>
<summary><strong>Vraag 11 — Working build manual as readme on GitHub</strong> → ✅ Waar</summary>

Zie de volledige [Build manual](#️-build-manual) hierboven — inclusief Qt Creator installeren, de externe library downloaden, en troubleshooting.

</details>

<details>
<summary><strong>Vraag 12 — At least 2 default constructors</strong> → ✅ Waar</summary>

`Light()` en `Room()` zijn default constructors die via constructor forwarding een standaardwaarde doorgeven aan hun parameterized constructor.

</details>

<details>
<summary><strong>Vraag 13 — At least 2 parameterized constructors</strong> → ✅ Waar</summary>

`Device(std::string name)` en `Room(std::string name)` vereisen beide een naam bij aanmaak.

</details>

<details>
<summary><strong>Vraag 14 — At least 2 copy constructors</strong> → ✅ Waar</summary>

`Room(const Room&)` maakt een echte diepe kopie via `clone()` op elk device. `Light(const Light&) = default` is expliciet gedeclareerd en gebruikt door `clone()`.

</details>

<details>
<summary><strong>Vraag 15 — At least 2 destructors</strong> → ✅ Waar</summary>

`Device::~Device()` is `virtual`. `Room::~Room()` en `LogHistory::~LogHistory()` zijn expliciet gedefinieerd om respectievelijk een bevestigingsbericht te tonen en `new[]`-geheugen vrij te geven.

</details>

<details>
<summary><strong>Vraag 16 — Member initialization in constructors</strong> → ✅ Waar</summary>

Consequent gebruikt, bv. `Device::Device(std::string name) : name_(name), id_(nextId_++) {}`.

</details>

<details>
<summary><strong>Vraag 17 — Constructor forwarding</strong> → ✅ Waar</summary>

`Light::Light() : Light("Unnamed Light") {}` en gelijkaardig bij `Room()`.

</details>

<details>
<summary><strong>Vraag 18 — Useful proven (dynamic) polymorphism</strong> → ✅ Waar</summary>

`Room::printAllDevices()` en de deep-copy-logica roepen `clone()`/`status()` aan zonder het concrete type te kennen — bewezen doordat het togglen van een kopie het origineel niet beïnvloedt.

</details>

<details>
<summary><strong>Vraag 19 — Useful usage of "this"</strong> → ✅ Waar</summary>

`Room::operator=` bevat `if (this == &other) return *this;`, essentieel om `room = room;` correct te laten verlopen.

</details>

<details>
<summary><strong>Vraag 20 — Useful member function</strong> → ✅ Waar</summary>

`Room::findDevice()` lost een concreet, herbruikbaar probleem op: een device opzoeken op naam.

</details>

<details>
<summary><strong>Vraag 21 — Default values in function definition</strong> → ✅ Waar</summary>

`Thermostat(std::string name, double targetTemperature = 21.0)`.

</details>

<details>
<summary><strong>Vraag 22 — Useful member variable</strong> → ✅ Waar</summary>

`Room::devices_` is de kern van de klasse: zonder deze variabele zou `Room` niets kunnen doen.

</details>

<details>
<summary><strong>Vraag 23 — Useful getters and setters for member variables</strong> → ✅ Waar</summary>

`Device::setName()` weigert een lege naam; `Thermostat::setTargetTemperature()` begrenst via `clamp()` — echte validatielogica.

</details>

<details>
<summary><strong>Vraag 24 — Correct usage of inline function</strong> → ✅ Waar</summary>

`onOffText(bool)` staat als `inline` functie in `Device.h`, geïncludeerd door meerdere `.cpp`-bestanden.

</details>

<details>
<summary><strong>Vraag 25 — Useful template function or class</strong> → ✅ Waar</summary>

`clamp<T>()` werkt voor zowel `double` (temperatuur) als `unsigned char` (helderheid), bewezen door een 999-graden-test die correct wordt afgekapt op 30.

</details>

<details>
<summary><strong>Vraag 26 — Useful friend function or class</strong> → ✅ Waar</summary>

`operator<<(std::ostream&, const Device&)` heeft `friend`-toegang tot het private `id_`-veld.

</details>

<details>
<summary><strong>Vraag 27 — Everything in one or more self-made namespace(s)</strong> → ✅ Waar</summary>

Alle klassen en functies zitten in de zelfgemaakte namespace `smarthome`.

</details>

<details>
<summary><strong>Vraag 28 — 2 useful unsigned chars or other better usage of memory efficient type</strong> → ✅ Waar</summary>

`Device::id_`/`nextId_` en `Light::brightness_` zijn beide `unsigned char`.

</details>

<details>
<summary><strong>Vraag 29 — At least 4 useful const references for variables</strong> → ✅ Waar</summary>

Meermaals gebruikt via `for (const auto& device : devices_)` in `Room`'s copy constructor, `operator=`, `findDevice()` en `printAllDevices()`.

</details>

<details>
<summary><strong>Vraag 30 — At least 4 useful const references for functions</strong> → ✅ Waar</summary>

`setName(const std::string&)`, `Room(const Room&)`, `operator=(const Room&)`, `findDevice(const std::string&)`, `operator<<(std::ostream&, const Device&)`.

</details>

<details>
<summary><strong>Vraag 31 — At least 4 useful bool</strong> → ✅ Waar</summary>

`Device::on_`, `Camera::motionDetected_`, en lokale `lampFound`/`kelderlampBestaat` in `main.cpp`.

</details>

<details>
<summary><strong>Vraag 32 — Dynamic memory allocation (new)</strong> → ✅ Waar</summary>

`LogHistory`'s constructor gebruikt `new std::string[capacity]`.

</details>

<details>
<summary><strong>Vraag 33 — Dynamic memory removing (delete)</strong> → ✅ Waar</summary>

`LogHistory`'s destructor roept `delete[] buffer_;` aan.

</details>

<details>
<summary><strong>Vraag 34 — 2 useful (modern) call-by-references</strong> → ✅ Waar</summary>

`applyEnergySavingMode(Thermostat&, double)` en `printActiveDeviceCount(Room&)`.

</details>

<details>
<summary><strong>Vraag 35 — Useful string class usage</strong> → ✅ Waar</summary>

`Room::countDevicesContaining()` gebruikt `std::string::find()` met correcte `npos`-check.

</details>

<details>
<summary><strong>Vraag 36 — Useful container class</strong> → ✅ Waar</summary>

`std::map<std::string, int>` (devices per type) en `std::map<std::string, Room>` (`House`) — twee verschillende toepassingen.

</details>

<details>
<summary><strong>Vraag 37 — Useful usage of nullptr</strong> → ✅ Waar</summary>

`Room::findDevice()` en `House::findRoom()` geven `nullptr` terug, telkens expliciet gecontroleerd.

</details>

<details>
<summary><strong>Vraag 38 — Useful usage of (modern) file-I/O</strong> → ✅ Waar</summary>

`Room`/`House` gebruiken `std::ofstream`/`std::ifstream` om hun volledige staat op te slaan/laden.

</details>

<details>
<summary><strong>Vraag 39 — Useful exception handling</strong> → ✅ Waar</summary>

`DeviceNotFoundException` wordt gegooid door `getDeviceOrThrow()` en netjes opgevangen in `main.cpp`.

</details>

<details>
<summary><strong>Vraag 40 — Useful usage of lambda function</strong> → ✅ Waar</summary>

`Room::countDevicesIf()` accepteert een `std::function<bool(const Device&)>`, aangeroepen met verschillende lambda's.

</details>

<details>
<summary><strong>Vraag 41 — Useful usage of threads</strong> → ✅ Waar</summary>

`MotionSensor` draait in zijn eigen `std::thread`, gebruikt `std::atomic<bool>`, en wordt altijd netjes gejoined.

</details>

<details>
<summary><strong>Vraag 42 — Useful Qt class</strong> → ✅ Waar</summary>

`QDateTime::currentDateTime()` geeft elk logbericht in `LogHistory` een echte tijdstempel.

</details>

<details>
<summary><strong>Vraag 43 — Useful usage of signals/slots</strong> → ✅ Waar</summary>

`Camera::motionDetectedSignal` wordt opgevangen door `MotionMonitor` en `RuleEngine` via slots, volledig ontkoppeld.

</details>

<details>
<summary><strong>Vraag 44 — Test-driven development</strong> → ✅ Waar</summary>

Een apart build-doel `SmarthomeTests` bevat 10 unit tests met `assert()`-checks.

</details>

<details>
<summary><strong>Vraag 45 — Solve bug ticket (with pull request or commit message issue link and issue branch)</strong> → ✅ Waar</summary>

Een echte bug (thermostaat-temperatuur ging verloren bij save/load) werd gerapporteerd als GitHub Issue, opgelost op een aparte branch, en gemerged via een pull request.

</details>

<details>
<summary><strong>Vraag 46 — Report a bug ticket on another project</strong> → ❌ Niet waar</summary>

Niet uitgevoerd binnen de tijdspanne van dit project.

</details>

<details>
<summary><strong>Vraag 47 — Usage of a GUI</strong> → ✅ Waar</summary>

`SmartHomeWindow` is een volwaardig Qt Widgets-dashboard met kamer-dropdown, live teller, typeteller, zoekbalk, kleurgecodeerde statuskaarten, toggle-knoppen, een dialoog om devices toe te voegen, motion-simulatie met visuele flits, reset, en opslaan/laden.

</details>

<details>
<summary><strong>Vraag 48 — Usage of OpenGL or other 3D engine</strong> → ❌ Niet waar</summary>

Bewust niet toegepast: past niet natuurlijk bij een domoticasysteem.

</details>

<details>
<summary><strong>Vraag 49 — Useful usage of an external library (not Qt)</strong> → ✅ Waar</summary>

`nlohmann/json` (header-only) slaat de volledige staat op/laadt als leesbare, gestructureerde JSON.

</details>

<details>
<summary><strong>Vraag 50 — Project that communicates with hardware</strong> → ❌ Niet waar</summary>

Niet haalbaar zonder fysieke hardware binnen deze sessie.

</details>

<details>
<summary><strong>Vraag 51 — A nice extra that you think that should deserve grading</strong> → ✅ Waar</summary>

**House-klasse: een nieuw niveau van object compositie.** Bovenop de bestaande `Room`-klasse is een volledig nieuwe `House`-klasse gebouwd die meerdere `Room`'s beheert via een `std::map<std::string, Room>`. Dit is een eigen, structurele uitbreiding van de architectuur: een huis met meerdere kamers, opzoekbaar op naam (met correcte `nullptr`-afhandeling), met een eigen JSON-serialisatie, en volledig geïntegreerd in de GUI via een kamer-wisselaar.

Daarnaast is een `RuleEngine` gebouwd — een klein automatiseringssysteem (`Rule` met conditie + actie als `std::function`) dat volledig ontkoppeld reageert op device-signalen, vergelijkbaar met echte smart-home-hubs (bv. *"als er beweging gedetecteerd wordt en het licht staat uit, zet het licht dan aan"*).

</details>

---

<p align="center"><sub>Gemaakt voor 42EAI1030 C++ programmeren — Object Georiënteerde Project</sub></p>
