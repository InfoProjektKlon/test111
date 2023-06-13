//Eingabe Niko
#include <iostream>
#include <Windows.h>
#include <stdlib.h> //für random Nummern

using namespace std;

//Erzeugen der Variablen
string wahlAmpel; //Eingabe der Anzahl an Ampeln
int anzahlAmpel;//Anzahl der Ampel
int randomAnzahlAmpel;
string abfrageAbstandAmpel;
double abstandAmpel;
int randomAbstandAmpel;
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
    vMax = 50;//Maximalgeschwindigkeit

    // Abfragen Anahl Ampeln etc.
    cout << "Gib eine ganze Streckenlaenge in Metern ein:"<< endl;
    cin >> s;

    while (abfrageAbstandAmpel != "Ja" && abfrageAbstandAmpel != "Nein") {
        cout << "Moechtest du den Abstand der Ampeln auswaehlen? Ja, fuer selber waehlen, Nein fuer random generieren."<< endl;
        cin >> abfrageAbstandAmpel;

        if (abfrageAbstandAmpel == "Ja") {
      
            do {
                cout <<"Wie weit sollen die Ampeln auseinander stehen ? " << endl;
                cin >> abstandAmpel;
                if (abstandAmpel < 100 || abstandAmpel > 1500) {
                    cout << "Bitte gebe einen Abstand von mindestens 100 und maximal 1500 Metern ein!" << endl;
                }
            } while (abstandAmpel < 100 || abstandAmpel > 1500);

        }
        else if (abfrageAbstandAmpel == "Nein") {
            srand(static_cast<unsigned int>(time(0))); // Neue Seed-Wert bei jedem Programmstart
            randomAbstandAmpel = rand() % 1500 + 100; // Zufällige Zahl zwischen 1 und 20
            abstandAmpel = randomAbstandAmpel;
            cout << "Der Abstand der Ampeln ist: " << abstandAmpel << endl;
        }
        else {
            cout << "Fehler: Ungueltige Eingabe fuer die Ampelauswahl!" << endl;
        }
    }

    anzahlAmpel = (s / abstandAmpel) - 1; //Noch nicht berücksichtig, dass hinter der letzten Ampel 150 Meter freie Fahrt sind
    cout << "Die Anzahl der Ampeln ist: " << anzahlAmpel;

    /*
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

    */
}

