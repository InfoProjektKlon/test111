// Sadik
#include <iostream>
#include <cstdlib> //Für Zufallszahlen
#include <cmath>   //Verwenden von sqrt
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

using namespace std;

int StreckenLange()
{ // Input Streckenlänge vom Benutzer

    int Streckelaenge;
    cout << "Streckenlaenge in m eingeben(Maximal 20000m):";
    cin >> Streckelaenge;
    return Streckelaenge;
}

int AmpelAbstand_random()
{ // Zufällige Ampelabstände
    int min = 100;
    int max = 1500;

    int randNum = rand() % (max - min + 1) + min;

    return randNum;
}

struct PKW
{                          // Struct für alle Fahrer
    float vmax;            // Maximale Geschwindigkeit
    float beschleunigung1; // Tatsächliche Beschleungigung eines Fahrer(Beschleunigung*Faktor)
    float beschleunigung2; // s.o
    float beschleunigung3; // s.o
};

int Schaltung()
{ // Zufällige Ampelzeit zwischen min und max

    int min = 0;
    int max = 30;

    int t_ampel = rand() % (max - min + 1) + min;

    return t_ampel;
}









float* Berechne(int* AmpelPosition, int& Ampelanzahl)
{

    PKW PKW_A;
    PKW_A.vmax = 50;
    PKW_A.beschleunigung1 = 2.0 * (2.0 / 3.0); // Tatsächliche Beschleunigung = Beschleunigung * Faktor(Fahrer A)
    PKW_A.beschleunigung2 = 3.0 * (2.0 / 3.0);
    PKW_A.beschleunigung3 = 6.0 * (2.0 / 3.0);

    PKW PKW_B;
    PKW_B.vmax = 50;
    PKW_B.beschleunigung1 = 2.0;
    PKW_B.beschleunigung2 = 3.0;
    PKW_B.beschleunigung3 = 6.0;

    PKW PKW_C;
    PKW_C.vmax = 85;
    PKW_C.beschleunigung1 = 2.0;
    PKW_C.beschleunigung2 = 3.0;
    PKW_C.beschleunigung3 = 6.0;

    //float Gesamtzeiten[9] = {0.0};

    float* Zeiten = new float[9];

    int n = 0;
    float aktuelle_Position = 0.0;
    int aktuelle_ampel = 0;
    float Distanz = 0.0;      // Länge eines Streckenabschnitts
    float t_acc;              // Zeit bis vmax erreicht wird
    float t_vmax;             // Zeit pro Abschnitt in der vmax gefahren wird
    float t_brake;            // Bremszeit von vmax auf 0 Kmh
    float t_150m;             // Zeit für den letzten Streckenabschnitt (Letzte Ampel bis zum Ziel)
    float t_150m_vmax;        // Zeit für den letzten Abschnitt in dem vmax gefahren wird
    float s_acc;              // Zurückgelegte Strecke bis vmax erreicht wird
    float s_vmax;             // Strecke pro Abschnitt in der vmax gefahren wird
    float s_brake;            // Bremsweg
    float s_150m_vmax;        // Zurückgelegte Strecke im letzten Streckenabschnitt mit vmax
    float zwischenzeit = 0.0; // Zeit für den jeweiligen Streckenabschnitt inklusive Ampel Wartezeit am Ende der Strecke
    float gesamtzeit = 0.0;
    int ampelzeit[200]; // Ampelzeiten für alle Ampeln werden im Array gespeichert und für die Zeitberechnung aller Fahrer benutzt

    float s_acc2;   // Zurückgelegte Strecke bei kurzer Distanz
    float t_acc2;   // Beschleunigungszeit s.o
    float s_brake2; // Bremsweg bei kurzer Distanz
    float t_brake2; // Bremszeit s.o

    for (int i = 0; i < Ampelanzahl + 1; i++)
    { // Erzeugt alle Ampelzeiten für die Zeitberechnung.
        ampelzeit[i] = Schaltung();
    }
    for (int PKWIndex = 1; PKWIndex <= 3; PKWIndex++)
    { // Fahrer A,B,C fahren nacheinander durch die strecke
        float vmax;
        switch (PKWIndex)
        {
        case 1:
            vmax = PKW_A.vmax;
            cout << "Fahrer A:" << endl;
            break;
        case 2:
            vmax = PKW_B.vmax;
            PKW_A.beschleunigung1 = PKW_B.beschleunigung1;
            PKW_A.beschleunigung2 = PKW_B.beschleunigung2;
            PKW_A.beschleunigung3 = PKW_B.beschleunigung3;
            cout << "Fahrer B:" << endl;
            break;
        case 3:
            vmax = PKW_C.vmax;
            PKW_A.beschleunigung1 = PKW_C.beschleunigung1;
            PKW_A.beschleunigung2 = PKW_C.beschleunigung2;
            PKW_A.beschleunigung3 = PKW_C.beschleunigung3;
            cout << "Fahrer C:" << endl;
            break;
        }

        for (int accIndex = 1; accIndex <= 3; accIndex++)
        { // 3 Beschleunigungen pro Fahrer
            float acc;
            switch (accIndex)
            {
            case 1:
                acc = PKW_A.beschleunigung1;
                cout << "  Beschleunigung[m/s^2]: " << acc << endl;
                break;
            case 2:
                acc = PKW_A.beschleunigung2;
                cout << "  Beschleunigung[m/s^2]: " << acc << endl;
                break;
            case 3:
                acc = PKW_A.beschleunigung3;
                cout << "  Beschleunigung[m/s^2]: " << acc << endl;
                break;
            }

            while (aktuelle_ampel <= Ampelanzahl)
            { // Streckenabschnittsweise berechnung bis zur letzten Ampel
                Distanz = AmpelPosition[aktuelle_ampel] - aktuelle_Position;
                t_acc = vmax / (3.6 * acc);
                s_acc = 0.5 * acc * (t_acc * t_acc); // S=1/2*a*t²
                s_brake = s_acc;                     //
                t_brake = t_acc;
                // cout << "Ampel: " << aktuelle_ampel << endl;
                // cout << "Zeit: " << Schaltung() << endl;
                // cout << "Ampelposition: " << AmpelPosition[aktuelle_ampel] << endl;
                if (Distanz >= 2 * s_acc)
                {                                       // Falls vmax erreicht wird.
                    s_vmax = Distanz - s_acc - s_brake; // Strecke in der vmax gefahren wird
                    t_vmax = s_vmax / (vmax / 3.6);
                    zwischenzeit = t_acc + t_vmax + t_brake + ampelzeit[aktuelle_ampel];
                    // cout << "s_vmax" << s_vmax << "t_vmax" << t_vmax << endl;
                }

                else
                { // Falls vmax nicht erreicht wird. Sonderfall für Fahrer A bei 2m/s^2 (falls Abschnitt<144,58m)  und Fahrer C

                    s_acc2 = Distanz * 0.5;
                    s_brake2 = s_acc2;
                    t_acc2 = sqrt((2 * s_acc2) / acc); // t=Wurzel(2*s/a)
                    t_brake2 = t_acc2;
                    zwischenzeit = t_acc2 + t_brake2 + ampelzeit[aktuelle_ampel];
                }
                // cout << "zwischenzeit" << zwischenzeit << endl;
                gesamtzeit += zwischenzeit;
                aktuelle_Position = AmpelPosition[aktuelle_ampel];
                // cout << "t_acc: " << t_acc << "t_vmax: " << t_vmax << "Ampelzeit: " << ampelzeit[aktuelle_ampel] << "Gesamtzeit: " << gesamtzeit << "s_acc: " << s_acc << "s_vmax: " << s_vmax << endl;
                aktuelle_ampel++;
            }

            s_150m_vmax = 150 - s_acc;
            t_150m_vmax = s_150m_vmax / (vmax / 3.6);
            t_150m = t_acc + t_150m_vmax; // Zeit für die letzten 150m
            gesamtzeit += t_150m;
            Zeiten[n] = gesamtzeit;
            // cout << " t_acc: " << t_acc << "t_acc2" << t_acc2 << " t_150m: " << t_150m << " s_acc: " << s_acc << "s_150m_vmax" << s_150m_vmax << endl;
            cout << "    Gesamtzeit[s]: " << Zeiten[n] << endl;
            aktuelle_Position = 0.0; // reset  für den nächsten Durchlauf
            aktuelle_ampel = 0;      // reset s.o
            gesamtzeit = 0;          // reset s.o
            zwischenzeit = 0;        // reset s.o
            n++;
        }
    }

    return Zeiten;
}


const int window_width = 800;
const int window_height = 600;
class StringConverter
{
public:
    static int toInt(const std::string& str)
    {
        std::istringstream stream(str);
        int value;
        stream >> value;
        return value;
    }
    static std::string toString(int value) {
        std::ostringstream stream;
        stream << value;
        return stream.str();
    }
};


int main()
{
    //Das Kommt in die Main Funktion 


    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Fahrtvergleich");
    window.setFramerateLimit(60);
    tgui::Gui gui{ window };


    // Label 1 und BoxStreckenlaenge 

    tgui::Label::Ptr Label1 = tgui::Label::create();
    Label1->setPosition(50.f, 113.f);
    Label1->setSize(210, 20);
    Label1->setTextSize(13);
    Label1->setText("Streckenlänge in m eingeben(Maximal 20000m):");
    Label1->getRenderer()->setTextColor(sf::Color::Black);
    Label1->getRenderer()->setBorders(0);
    Label1->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
    gui.add(Label1);

    tgui::EditBox::Ptr BoxStreckelaenge = tgui::EditBox::create();
    BoxStreckelaenge->setDefaultText("Ganzahlig");
    BoxStreckelaenge->setPosition(50.f, 130.f);
    BoxStreckelaenge->setSize(150, 22);
    BoxStreckelaenge->setTextSize(13);
    BoxStreckelaenge->setMaximumCharacters(5); // Muss nicht immer dabei sein macht aber sinn dann können wir gut begrenzen
    BoxStreckelaenge->getRenderer()->setBackgroundColor(sf::Color::White);
    BoxStreckelaenge->getRenderer()->setBorders(1);
    BoxStreckelaenge->getRenderer()->setTextColor(sf::Color::Black);
    gui.add(BoxStreckelaenge);

    // Label 2 und Boxeingabe

    tgui::Label::Ptr Label2 = tgui::Label::create();
    Label2->setPosition(50.f, 163.f);
    Label2->setSize(210, 20);
    Label2->setTextSize(13);
    Label2->setText("Ampelabstand selber eingeben oder durch zufall. 1 für zufall 2 für selber:");
    Label2->getRenderer()->setTextColor(sf::Color::Black);
    Label2->getRenderer()->setBorders(0);
    Label2->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
    gui.add(Label2);

    tgui::EditBox::Ptr Boxeingabe = tgui::EditBox::create();
    Boxeingabe->setDefaultText("1 oder 2");
    Boxeingabe->setPosition(50.f, 180.f);
    Boxeingabe->setSize(150, 22);
    Boxeingabe->setTextSize(13);
    Boxeingabe->setMaximumCharacters(1);
    Boxeingabe->getRenderer()->setBackgroundColor(sf::Color::White);
    Boxeingabe->getRenderer()->setBorders(1);
    Boxeingabe->getRenderer()->setTextColor(sf::Color::Black);
    gui.add(Boxeingabe);


    // Label 3 und BoxAbstand

    tgui::Label::Ptr Label3 = tgui::Label::create();
    Label3->setPosition(50.f, 213.f);
    Label3->setSize(210, 20);
    Label3->setTextSize(13);
    Label3->setText("Abstand eingeben, zwischen 100m und 1500m:");
    Label3->getRenderer()->setTextColor(sf::Color::Black);
    Label3->getRenderer()->setBorders(0);
    Label3->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
    gui.add(Label3);

    tgui::EditBox::Ptr BoxAbstand = tgui::EditBox::create();
    BoxAbstand->setDefaultText("Ganzahlig");
    BoxAbstand->setPosition(50.f, 230.f);
    BoxAbstand->setSize(150, 22);
    BoxAbstand->setTextSize(13);
    BoxAbstand->setMaximumCharacters(4);
    BoxAbstand->getRenderer()->setBackgroundColor(sf::Color::White);
    BoxAbstand->getRenderer()->setBorders(1);
    BoxAbstand->getRenderer()->setTextColor(sf::Color::Black);
    gui.add(BoxAbstand);

    //Button1
    tgui::Button::Ptr Button1 = tgui::Button::create();
    Button1->setPosition(100.f, 380.f);
    Button1->setText("Auswerten");
    Button1->setTextSize(13);
    Button1->getRenderer()->setBackgroundColor(sf::Color::White);
    Button1->getRenderer()->setBorders(1);
    Button1->getRenderer()->setTextColor(sf::Color::Black);
    Button1->connect("pressed", [&]()
        {
            int Streckelaenge;
            int eingabe;
            int Abstand;
            Streckelaenge = StringConverter::toInt(BoxStreckelaenge->getText());
            eingabe = StringConverter::toInt(Boxeingabe->getText());
            Abstand = StringConverter::toInt(BoxAbstand->getText());
        });
    gui.add(Button1);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            gui.handleEvent(event);
        }
        window.clear(sf::Color(195, 195, 195, 255));
        gui.draw();
        window.display();
    }

    int Ampelanzahl = 0;
    int AmpelPosition[200];  // Absolute Position aller Ampeln auf der Gesamten Strecke

  //  locale::global(locale("German_germany")); // Umlaute und Potenzen in der Konsole richtig anzeigen


    srand(time(NULL));                        // Neuer Seed. Nutzung der Systemzeit zur Generierung von Zufallszahlen.
    int Streckenlaenge = StreckenLange();

    int eingabe; // lokal 
    do
    {
        cout << "Ampelabstand selber eingeben oder durch zufall. 1 fuer zufall 2 fuer selber:";
        cin >> eingabe;
        if (eingabe != 1 && eingabe != 2)
        {
            cout << "Fehlerhafte eingabe" << endl;
        }

    } while (eingabe != 1 && eingabe != 2); // Schleife wird solange durchlaufen bis 1 oder 2 ausgewählt wird vom Benutzer

    int StreckenCounter = 0; // Streckenzähler um zu bestimmen wie lange die Schleifen laufen sollen


    if (eingabe == 1)
    { // Zufällig

        while (StreckenCounter < Streckenlaenge - 250)
        {

            StreckenCounter += AmpelAbstand_random();     // Aufsummieren der Ampelabstände auf den Strecken"zähler"
            AmpelPosition[Ampelanzahl] = StreckenCounter; // Absolute Ampelposition(Strecke zwischen Ampel und Nullpunkt)
            // cout << AmpelPosition[Ampelanzahl] << endl;
            //  debug    cout << StreckenCounter<< endl;
            Ampelanzahl++; // erhöht Ampelanzahl um 1
            if (StreckenCounter > Streckenlaenge - 250)
            { // Platziert letzte Ampel auf s-150m falls Benutzer einen größeren Wert eingibt
                Ampelanzahl--;
                AmpelPosition[Ampelanzahl] = Streckenlaenge - 150;
                break;
            }
        }
    }

    if (eingabe == 2)
    { // Benutzereingabe

        int Abstand = 0; // Ampelabstand
        while (1)
        {
            AmpelPosition[Ampelanzahl];
            cout << "Abstand eingeben, zwischen 100m und 1500m:" << endl;
            cin >> Abstand;

            if (Abstand >= 100 && Abstand <= 1500)
            {

                StreckenCounter += Abstand;
                AmpelPosition[Ampelanzahl] = StreckenCounter;
                cout << "Noch " << Streckenlaenge - AmpelPosition[Ampelanzahl] << " meter bis zum ende der Strecke" << endl;
                Ampelanzahl++;
            }
            else
            {
                cout << "Ampelabstand ungueltig" << endl;
            }
            if (StreckenCounter > Streckenlaenge - 250)
            {
                Ampelanzahl--;
                AmpelPosition[Ampelanzahl] = Streckenlaenge - 150;
                cout << "Letzte Ampel bei " << Streckenlaenge - 150 << " metern" << endl;
                break;
            }
        }
    }



    float* Gesamtzeiten = Berechne(AmpelPosition, Ampelanzahl); // Für das GUI die 9 Einträge des Arrays abrufen






    return 0;
}