#include <iostream>
#include <cstdlib> //Für Zufallszahlen
#include <cmath>   //Verwenden von sqrt
#include <SFML/Graphics.hpp> //Verwendung der GUIs
#include <TGUI/TGUI.hpp> //Verwendung der GUIs
#include <iomanip>  // Runden der Ergebnisse in der Ausgabe

using namespace std;
/*
int StreckenLange()
{ // Input Streckenlänge vom Benutzer

    int Streckelaenge;
    cout << "Streckenlaenge in m eingeben(Maximal 20000m):";
    cin >> Streckelaenge;
    return Streckelaenge;
}
*/
int AmpelAbstand_random() // Generierung von zufällige Ampelabständen
{
    int min = 100;
    int max = 1500;
    int randNum = rand() % (max - min + 1) + min;

    return randNum;
}

struct PKW                 // Struct für alle Fahrer
{
    float vmax;            // Maximale Geschwindigkeit
    float beschleunigung1; // Tatsächliche Beschleungigung eines Fahrer(Beschleunigung*Faktor)
    float beschleunigung2; // s.o
    float beschleunigung3; // s.o
};

int Schaltung() // Zufällige Ampelzeit zwischen min und max
{
    int min = 0;
    int max = 30;

    int t_ampel = rand() % (max - min + 1) + min;

    return t_ampel;
}


void AmpelPositionen_Zufall(int& eingabe, int& Ampelanzahl, int AmpelPosition[], int Streckenlaenge) // Funktion zur zufaelligen Positionierung der Ampeln auf der Rennstrecke
{
    int StreckenCounter = 0;
    int Abstand;

    if (eingabe == 1) // Zufällig
    {
        while (StreckenCounter < Streckenlaenge - 250)
        {
            StreckenCounter += AmpelAbstand_random();
            AmpelPosition[Ampelanzahl] = StreckenCounter;
            Ampelanzahl++;
            if (StreckenCounter > Streckenlaenge - 250)
            {
                Ampelanzahl--;
                AmpelPosition[Ampelanzahl] = Streckenlaenge - 150;
                break;
            }
        }
    }
}

/*  Jeden Ampelabstand einzeln eingeben. Konnt im GUI nicht umgesetzt werden.
void AmpelPosition_Benutzer(int& eingabe, int& Ampelanzahl, int AmpelPosition[], int Streckenlaenge)
{
    int StreckenCounter = 0;
    int Abstand;

    while (true)
    {
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
            cout << "Ampelabstand ungültig" << endl;
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
*/



float* BerechneZeiten(int* AmpelPosition, int& Ampelanzahl) //Gesamtzeitberechnung aller drei Fahrer
{
    srand(time(NULL));
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
    int ampelzeit[10000]; // Ampelzeiten für alle Ampeln werden im Array gespeichert und für die Zeitberechnung aller Fahrer benutzt

    float s_acc2;   // Zurückgelegte Strecke bei kurzer Distanz
    float t_acc2;   // Beschleunigungszeit s.o
    float s_brake2; // Bremsweg bei kurzer Distanz
    float t_brake2; // Bremszeit s.o

    for (int i = 0; i < Ampelanzahl + 1; i++) // Erzeugt alle Ampelzeiten für die Zeitberechnung.
    {
        ampelzeit[i] = Schaltung();
    }
    for (int PKWIndex = 1; PKWIndex <= 3; PKWIndex++) // Fahrer A,B,C fahren nacheinander durch die Strecke
    {
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

        for (int accIndex = 1; accIndex <= 3; accIndex++) // 3 Beschleunigungen pro Fahrer
        {
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

            while (aktuelle_ampel <= Ampelanzahl) // Streckenabschnittsweise berechnung bis zur letzten Ampel
            {
                Distanz = AmpelPosition[aktuelle_ampel] - aktuelle_Position;
                t_acc = vmax / (3.6 * acc);
                s_acc = 0.5 * acc * (t_acc * t_acc); // S=1/2*a*t²
                s_brake = s_acc;
                t_brake = t_acc;

                if (Distanz >= 2 * s_acc) // Falls Vmax erreicht wird
                {
                    s_vmax = Distanz - s_acc - s_brake; // Strecke in der vmax gefahren wird
                    t_vmax = s_vmax / (vmax / 3.6);
                    zwischenzeit = t_acc + t_vmax + t_brake + ampelzeit[aktuelle_ampel];
                }

                else // Falls Vmax nicht erreicht wird
                {
                    s_acc2 = Distanz * 0.5;
                    s_brake2 = s_acc2;
                    t_acc2 = sqrt((2 * s_acc2) / acc); // t=Wurzel(2*s/a)
                    t_brake2 = t_acc2;
                    zwischenzeit = t_acc2 + t_brake2 + ampelzeit[aktuelle_ampel];
                }
                gesamtzeit += zwischenzeit;
                aktuelle_Position = AmpelPosition[aktuelle_ampel];
                aktuelle_ampel++;
            }

            s_150m_vmax = 150 - s_acc;
            t_150m_vmax = s_150m_vmax / (vmax / 3.6);
            t_150m = t_acc + t_150m_vmax; // Zeit für die letzten 150m
            gesamtzeit += t_150m;

            Zeiten[n] = gesamtzeit;
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

// Definierung der Fensterkonstanten
const int window_width = 900;
const int window_height = 600;

class StringConverter //Eingliederung des StringConverters
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

    // Erstellung des Fensters
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Fahrtvergleich");
    window.setFramerateLimit(60);
    tgui::Gui gui{ window };

    locale::global(locale("German_germany")); // Umlaute und Potenzen in der Konsole richtig anzeigen

    // 9 Boxen für die Ergebnisse erstellen
    std::vector<tgui::Label::Ptr> Zeiten(9);
    for (int i = 0; i < 9; i++) {
        Zeiten[i] = tgui::Label::create();
        Zeiten[i]->setPosition(670.f, 50.f + i * 30.f);
        Zeiten[i]->setSize(110, 25);
        Zeiten[i]->setTextSize(19);
        Zeiten[i]->getRenderer()->setBackgroundColor(sf::Color::White);
        Zeiten[i]->getRenderer()->setBorders(1);
        Zeiten[i]->getRenderer()->setTextColor(sf::Color::Black);
        gui.add(Zeiten[i]);
    }

    //Label für Fahrer erstellen
    std::vector<tgui::Label::Ptr> LabelFahrer(10);
    for (int j = 0; j < 10; j++) {
        LabelFahrer[j] = tgui::Label::create();
        LabelFahrer[j]->setPosition(400.f, 20.f + j * 30.f);
        LabelFahrer[j]->setSize(100, 25);
        LabelFahrer[j]->setTextSize(13);
        LabelFahrer[j]->getRenderer()->setTextColor(sf::Color::Black);
        LabelFahrer[j]->getRenderer()->setBorders(0);
        LabelFahrer[j]->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
        gui.add(LabelFahrer[j]);
    }

    // Label für Beschleunigungen erstellen
    std::vector<tgui::Label::Ptr> LabelBeschleunigung(10);
    for (int g = 0; g < 10; g++) {
        LabelBeschleunigung[g] = tgui::Label::create();
        LabelBeschleunigung[g]->setPosition(530.f, 20.f + g * 30.f);
        LabelBeschleunigung[g]->setSize(120, 25);
        LabelBeschleunigung[g]->setTextSize(13);
        LabelBeschleunigung[g]->getRenderer()->setTextColor(sf::Color::Black);
        LabelBeschleunigung[g]->getRenderer()->setBorders(0);
        LabelBeschleunigung[g]->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
        gui.add(LabelBeschleunigung[g]);
    }

    //Label für Zuordnung der Ergebnisse zu Fahrer und Beschleunigung
    LabelFahrer[0]->setTextSize(14);
    LabelFahrer[0]->getRenderer()->setTextColor(sf::Color::Blue);
    LabelFahrer[0]->setText("Fahrer");
    LabelFahrer[1]->setText("PKW A:");
    LabelFahrer[2]->setText("Vmax=50km/h");
    LabelFahrer[3]->setText("");
    LabelFahrer[4]->setText("PKW B:");
    LabelFahrer[5]->setText("Vmax=50km/h");
    LabelFahrer[6]->setText("");
    LabelFahrer[7]->setText("PKW C:");
    LabelFahrer[8]->setText("Vmax=85km/h");
    LabelFahrer[9]->setText("");

    LabelBeschleunigung[0]->getRenderer()->setTextColor(sf::Color::Blue);
    LabelBeschleunigung[0]->setTextSize(14);
    LabelBeschleunigung[0]->setText("Beschleunigung");
    LabelBeschleunigung[1]->setText("2 [m/s^2]");
    LabelBeschleunigung[2]->setText("3 [m/s^2]");
    LabelBeschleunigung[3]->setText("6 [m/s^2]");
    LabelBeschleunigung[4]->setText("2 [m/s^2]");
    LabelBeschleunigung[5]->setText("3 [m/s^2]");
    LabelBeschleunigung[6]->setText("6 [m/s^2]");
    LabelBeschleunigung[7]->setText("2 [m/s^2]");
    LabelBeschleunigung[8]->setText("3 [m/s^2]");
    LabelBeschleunigung[9]->setText("6 [m/s^2]");

    tgui::Label::Ptr LabelErgebnis = tgui::Label::create();
    LabelErgebnis->setPosition(670.f, 20.f);
    LabelErgebnis->setSize(100, 20);
    LabelErgebnis->setTextSize(14);
    LabelErgebnis->setText("Ergebnis");
    LabelErgebnis->getRenderer()->setTextColor(sf::Color::Blue);
    LabelErgebnis->getRenderer()->setBorders(0);
    LabelErgebnis->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
    gui.add(LabelErgebnis);

    // Information und Eingabe der Streckenlaenge 
    tgui::Label::Ptr Label1 = tgui::Label::create();
    Label1->setPosition(50.f, 113.f);
    Label1->setSize(400, 20);
    Label1->setTextSize(13);
    Label1->setText("Streckenlaenge in m eingeben(Maximal 99999m):");
    Label1->getRenderer()->setTextColor(sf::Color::Black);
    Label1->getRenderer()->setBorders(0);
    Label1->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
    gui.add(Label1);

    tgui::EditBox::Ptr BoxStreckelaenge = tgui::EditBox::create();
    BoxStreckelaenge->setDefaultText("Ganzzahlig");
    BoxStreckelaenge->setPosition(50.f, 130.f);
    BoxStreckelaenge->setSize(150, 22);
    BoxStreckelaenge->setTextSize(13);
    BoxStreckelaenge->setMaximumCharacters(5); // zur Begrenzung der maximalen Eingabe
    BoxStreckelaenge->getRenderer()->setBackgroundColor(sf::Color::White);
    BoxStreckelaenge->getRenderer()->setBorders(1);
    BoxStreckelaenge->getRenderer()->setTextColor(sf::Color::Black);
    gui.add(BoxStreckelaenge);

    //Informationen zur Ausfuehrung
    tgui::Label::Ptr LabelFeedback = tgui::Label::create();
    LabelFeedback->setPosition(50.f, 400.f);
    LabelFeedback->setSize(500, 100);
    LabelFeedback->setTextSize(16);
    LabelFeedback->getRenderer()->setTextColor(sf::Color::Red);
    LabelFeedback->getRenderer()->setBorders(0);
    LabelFeedback->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
    gui.add(LabelFeedback);

    int Ampelanzahl = 0;
    int AmpelPosition[10000];  // Absolute Position aller Ampeln auf der Gesamten Strecke

    // Information, Eingabe und Berechnung mit manuellen Ampelabstaende
    tgui::Label::Ptr Label2 = tgui::Label::create();
    Label2->setPosition(50.f, 160.f);
    Label2->setSize(300, 20);
    Label2->setTextSize(13);
    Label2->setText("Ampelabstand fuer alle Ampeln eingeben:");
    Label2->getRenderer()->setTextColor(sf::Color::Black);
    Label2->getRenderer()->setBorders(0);
    Label2->getRenderer()->setBackgroundColor(sf::Color(195, 195, 195, 255));
    gui.add(Label2);

    tgui::EditBox::Ptr BoxAmpelabstand = tgui::EditBox::create();
    BoxAmpelabstand->setDefaultText("Ganzzahlig zwischen 100m und 1500m");
    BoxAmpelabstand->setPosition(50.f, 180.f);
    BoxAmpelabstand->setSize(300, 22);
    BoxAmpelabstand->setTextSize(13);
    BoxAmpelabstand->setMaximumCharacters(4);
    BoxAmpelabstand->getRenderer()->setBackgroundColor(sf::Color::White);
    BoxAmpelabstand->getRenderer()->setBorders(1);
    BoxAmpelabstand->getRenderer()->setTextColor(sf::Color::Black);
    gui.add(BoxAmpelabstand);

    //Label4 Beschreibung des ersten Buttons für den Benutzer
    tgui::Label::Ptr Label3 = tgui::Label::create();
    Label3->setPosition(50.f, 260.f);
    Label3->setSize(175, 20);
    Label3->setTextSize(13);
    Label3->setText("Zufaelliger Ampelabstand:");
    Label3->getRenderer()->setTextColor(sf::Color::Black);
    Label3->getRenderer()->setBorders(0);
    gui.add(Label3);

    //Button1 Generierung zufaelliger Ampelabstände + Berechnung
    tgui::Button::Ptr Button1 = tgui::Button::create();
    Button1->setPosition(230.f, 255.f);
    Button1->setText("Berechnen");
    Button1->setTextSize(13);
    Button1->getRenderer()->setBackgroundColor(sf::Color::White);
    Button1->getRenderer()->setBorders(1);
    Button1->getRenderer()->setTextColor(sf::Color::Black);
    Button1->connect("pressed", [&]()
        {
            int Streckenlaenge = StringConverter::toInt(BoxStreckelaenge->getText());
            int eingabe = 1;
            srand(time(NULL));

            AmpelPositionen_Zufall(eingabe, Ampelanzahl, AmpelPosition, Streckenlaenge);
            float* Gesamtzeiten = BerechneZeiten(AmpelPosition, Ampelanzahl);

            for (int i = 0; i < 9; i++) {
                float gesamtzeit = Gesamtzeiten[i];
                //Runden auf 2 Nachkommastellen
                std::ostringstream stream;
                stream << std::fixed << std::setprecision(2) << gesamtzeit;
                std::string gerundet = stream.str();
                Zeiten[i]->setText(gerundet + " s");
            }


            LabelFeedback->setText("Fuer erneute Berechnung Programm Neustarten!");
        });
    gui.add(Button1);

    tgui::Label::Ptr Label4 = tgui::Label::create();
    Label4->setPosition(50.f, 300.f);
    Label4->setSize(240, 20);
    Label4->setTextSize(13);
    Label4->setText("Eigener Ampelabstand:");
    Label4->getRenderer()->setTextColor(sf::Color::Black);
    Label4->getRenderer()->setBorders(0);
    gui.add(Label4);

    tgui::Button::Ptr Button2 = tgui::Button::create();   // Benutzer gibt alle Ampelabstände an
    Button2->setPosition(230.f, 300.f);
    Button2->setText("Berechnen");
    Button2->setTextSize(13);
    Button2->getRenderer()->setBackgroundColor(sf::Color::White);
    Button2->getRenderer()->setBorders(1);
    Button2->getRenderer()->setTextColor(sf::Color::Black);
    Button2->connect("pressed", [&]()
        {
            int Streckenlaenge = StringConverter::toInt(BoxStreckelaenge->getText());
            int eingabe = 2;
            int StreckenCounter = 0;
            int Abstand = StringConverter::toInt(BoxAmpelabstand->getText());
            srand(time(NULL));


            while (1)
            {
                StreckenCounter += Abstand;
                AmpelPosition[Ampelanzahl] = StreckenCounter;

                Ampelanzahl++;

                if (Abstand < 100 || Abstand > 1500)
                {
                    cout << "Ampelabstand ungültig" << endl;
                    LabelFeedback->setText("Ungueltige Eingabe! Programm neustarten.");
                    break;
                }
                if (StreckenCounter > Streckenlaenge - 250)
                {
                    Ampelanzahl--;
                    AmpelPosition[Ampelanzahl] = Streckenlaenge - 150;
                    LabelFeedback->setText(" Letzte Ampel bei " + std::to_string(Streckenlaenge - 150) + " metern.\nFuer erneute Berechnung Programm Neustarten!");
                    //cout << "Letzte Ampel bei " << Streckenlaenge - 150 << " metern" << endl;                     ist Sinnvoll, falls richtige Position der Ampelanlage angegeben wird
                    break;
                }
            }

            float* Gesamtzeiten = BerechneZeiten(AmpelPosition, Ampelanzahl);

            for (int i = 0; i < 9; i++) {
                float gesamtzeit = Gesamtzeiten[i];
                //Runden auf 2 Nachkommastellen
                ostringstream stream;
                stream << std::fixed << std::setprecision(2) << gesamtzeit;
                string gerundet = stream.str();
                Zeiten[i]->setText(gerundet + " s");
            }


        });
    gui.add(Button2);

    // Oeffnen und Schließen des Fensters 
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
    return 0;
}