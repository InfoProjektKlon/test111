//Eingabe Niko
#include <iostream>
#include <Windows.h>
#include <stdlib.h> //für random Nummern

using namespace std;

//Erzeugen der Variablen
string wahlAmpel; //Eingabe der Anzahl an Ampeln
int anzahlAmpel;//Anzahl der Ampel
int randomAnzahlAmpel;
double s; //Streckenlänge
double sAbschnitte; //Streckenlänge der Abschnitte
double anzahlAbschnitte;
double t; //Gesamtzeit
double t1; //Zeit nach 1/4 der Strecke
double t2; //Zeit für den zweiten Abschnitt
double t3; //Wartezeit an der Ampel
double tAbschnitt; //Zeit zwischen einer Ampel
double tEnde;//Zeit von letzten Apel bis zum Ziel
double a1; //Beschleuningung 2 m/s
double a2; //Beschleunigung 3 m/s
double a3; //Beschleunigung 6 m/s

double vMax;//maximal Geschwindigkeit von 50 km/h
double tVMax;//Zeit bis vMax
double sVMax;//Strecke bis vMax

int main()
{
    // Abfragen Anahl Ampeln etc.
    cout << "Gib eine ganze Streckenlaenge in Metern ein: ";
    cin >> s;
    while (wahlAmpel != "Ja" && wahlAmpel != "Nein") {
        cout << "Moechtest du die Anzahl der Ampeln auswaehlen? Ja, fuer selber waehlen, Nein fuer random generieren.";
        cin >> wahlAmpel;

        if (wahlAmpel == "Ja") {
            cout << "Wieviele Ampeln sollen auf der Strecke sein?";
            cin >> anzahlAmpel;
            cout << "Die Anzahl der Ampeln ist: " << anzahlAmpel << endl;
        }
        else if (wahlAmpel == "Nein") {
            srand(static_cast<unsigned int>(time(0))); // Neue Seed-Wert bei jedem Programmstart
            randomAnzahlAmpel = rand() % 20 + 1; // Zufällige Zahl zwischen 1 und 20
            anzahlAmpel = randomAnzahlAmpel;
            cout << "Die Anzahl der Ampeln ist: " << anzahlAmpel << endl;
        }
        else {
            cout << "Fehler: Ungueltige Eingabe fuer die Ampelauswahl!" << endl;
        }
    }

    a1 = 2;
    vMax = 50 / 3.6;
    anzahlAbschnitte = anzahlAmpel + 1; //Anzahl Abschnitte 
    sAbschnitte = s / anzahlAbschnitte; //Länge der Abschnitte
    cout << "Die Anzahl der Abschnitte ist: " << anzahlAbschnitte << endl;
    cout << "Die Laenge der Abschnitte: " << sAbschnitte << endl;

    tVMax = vMax / a1;//Zeit bis zum Erreichen der maximal Geschwindigkeit 
    sVMax = 0.5 * a1 * (tVMax * tVMax);//zurückgelegte Strecke bis Vmax

    cout << "Die Zeit bis Vmax: " << tVMax << endl;
    cout << "Die Laenge bis Vmax: " << sVMax << endl;

    if (sVMax < 1 / 2 * sAbschnitte) { //falls die Höchstgeschwindigkeit nicht erreicht wird

        tAbschnitt = 2 * sqrt((2 * 1 / 2 * sAbschnitte) / a1); //s=1/2*a*t^2, zweimal ein halben Abschnitt, da beschleunigung und bremsen
        tEnde = sqrt((2 * sAbschnitte) / a1);

        t = (anzahlAbschnitte - 1) * tAbschnitt + tEnde;

    }
    else if (sVMax > 1 / 2 * sAbschnitte) {
        tAbschnitt = 2 * tVMax + ((sAbschnitte - 2 * sVMax) / vMax); //Abschnittszeit: 2 x Zeit für Beschleunigen und einmal Zeit für die Strecke der maximal Geschwindigkeit 
        tEnde = tVMax + ((sAbschnitte - sVMax) / vMax);

        t = (anzahlAbschnitte - 1) * tAbschnitt + tEnde;
    }

    cout << "Zeit fuer die Abschnitte: " << tAbschnitt << " Sekunden" << endl;
    cout << "Zeit fuer das Ende: " << tEnde << " Sekunden" << endl;
    cout << "Das Auto benoetigt " << t << " Sekunden fuer die " << s << " Meter lange Strecke.";
}


    /*
//Eingabe Tobi
#include <iostream>
#include <vector>
#include <random>

// Funktion zur Generierung einer zufälligen Zahl im angegebenen Bereich
int zufallszahlGenerieren(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Funktion zur Durchführung der Simulation
void simulationDurchführen(double gesamtstrecke, int anzahlAmpeln, int minAbstand, int maxAbstand, double zusätzlicheStrecke) {
    // Parameter für die Fahrer
    double fahrerA_beschleunigung = 2.0 / 3.0;
    double fahrerB_beschleunigung = 1.0;
    double fahrerC_beschleunigung = 6.0;

    // Vektor zur Speicherung der Ampelpositionen
    std::vector<double> ampelPositionen;

    // Generiere die Positionen der Ampeln
    for (int i = 0; i < anzahlAmpeln; i++) {
        double abstand = zufallszahlGenerieren(minAbstand, maxAbstand);
        ampelPositionen.push_back(abstand);
    }

    // Sortiere die Ampelpositionen in aufsteigender Reihenfolge
    std::sort(ampelPositionen.begin(), ampelPositionen.end());

    // Füge die zusätzliche freie Strecke hinter der letzten Ampel hinzu
    ampelPositionen.push_back(gesamtstrecke + zusätzlicheStrecke);

    // Schleife zur Simulation der Fahrt für jeden Fahrertyp
    for (int fahrertyp = 1; fahrertyp <= 3; fahrertyp++) {
        double aktuellePosition = 0.0;
        double aktuelleGeschwindigkeit = 0.0;
        double gesamtzeit = 0.0;
        int anzahlStopps = 0;

        std::cout << "Simulation für Fahrertyp " << fahrertyp << ":" << std::endl;

        // Schleife zur Simulation der Fahrt entlang der Strecke
        while (aktuellePosition < gesamtstrecke) {
            double abstandZurNaechstenAmpel = ampelPositionen[anzahlStopps] - aktuellePosition;
            double zeitBisNaechsteAmpel = abstandZurNaechstenAmpel / aktuelleGeschwindigkeit;

            // Überprüfe, ob die Ampel erreicht wird, bevor sie grün wird
            if (zeitBisNaechsteAmpel <= 0.0) {
                anzahlStopps++;
                continue;
            }

            // Berechne die Zeit bis zur nächsten Ampel basierend auf der aktuellen Geschwindigkeit
            double zeitBisNaechsteAmpel = zeitBisNaechsteAmpel;

            // Berechne die Zeit zum Beschleunigen oder Bremsen basierend auf dem Fahrertyp
            double beschleunigungszeit = 0.0;
            if (fahrertyp == 1)
                beschleunigungszeit = std::sqrt((2.0 * abstandZurNaechstenAmpel) / fahrerA_beschleunigung);
            else if (fahrertyp == 2)
                beschleunigungszeit = std::sqrt((2.0 * abstandZurNaechstenAmpel) / fahrerB_beschleunigung);
            else if (fahrertyp == 3)
                beschleunigungszeit = std::sqrt((2.0 * abstandZurNaechstenAmpel) / fahrerC_beschleunigung);

            // Überprüfe, ob die Beschleunigungszeit kleiner oder gleich der Zeit bis zur nächsten Ampel ist
            if (beschleunigungszeit <= zeitBisNaechsteAmpel) {
                // Fahrzeug beschleunigen
                aktuelleGeschwindigkeit += (beschleunigungszeit * fahrerC_beschleunigung);
                aktuellePosition += (0.5 * beschleunigungszeit * aktuelleGeschwindigkeit);
                gesamtzeit += beschleunigungszeit;
            }
            else {
                // Fahrzeug bis zur Ampel fahren und anhalten
                aktuellePosition += (0.5 * zeitBisNaechsteAmpel * aktuelleGeschwindigkeit);
                gesamtzeit += zeitBisNaechsteAmpel;
                anzahlStopps++;
            }
        }

        std::cout << "Gesamtzeit: " << gesamtzeit << " s" << std::endl;
        std::cout << "Anzahl der Ampelstopps: " << anzahlStopps << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    // Parameter für die Simulation
    double gesamtstrecke = 1000.0; // Beispielwert
    int anzahlAmpeln = 10; // Beispielwert
    int minAbstand = 100; // Beispielwert
    int maxAbstand = 1500; // Beispielwert
    double zusaetzlicheStrecke = 150.0; // Beispielwert

    // Simulation durchführen
    simulationDurchführen(gesamtstrecke, anzahlAmpeln, minAbstand, maxAbstand, zusaetzlicheStrecke);

    return 0;

  
} */