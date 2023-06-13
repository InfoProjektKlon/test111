//Eingabe Niko
#include <iostream>
#include <Windows.h>
#include <stdlib.h> //für random Nummern

using namespace std;

struct Fahrer {
    string name;
    double beschleunigung;
    double Faktor;
    bool hält_sich_an_geschwindigkeitsbegrenzung;
};

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

/*
int Schaltung() {

    int min = 20;
    int max = 60;

    srand(time(NULL));
    int ZufallSekunden = rand() % (max - min + 1) + min;

    return ZufallSekunden;

}
*/


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
    cout << "Die Anzahl der Ampeln ist: " << anzahlAmpel << endl;

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
    */

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
//Sadik
#include <iostream>
#include<cstdlib>
#include <cmath>

using namespace std;




int StreckenLange() {

    int Streckelaenge;
    cout << "Streckenlänge in M eingeben" << endl;
    cin >> Streckelaenge;
    return Streckelaenge;
}

int AmpelAbstand_random() {
    int min = 100;
    int max = 1500;
    srand(time(NULL));

    int randNum = rand() % (max - min + 1) + min;

    return randNum;
}

struct PKW {   //Struct für alle Fahrer
    float Vmax;    //Geschwindigkeitsbegraenkung
    float Beschleunigung; //ist auch gleich Bremsfaktor
    float Beschleunigung_Faktor;
    float Aktuelle_Position;
    float Zeit;
    float NeueBeschleunigung = Beschleunigung_Faktor * Beschleunigung;
};

int Schaltung() {

    int min = 20;
    int max = 60;

    srand(time(NULL));
    int ZufallSekunden = rand() % (max - min + 1) + min;

    return ZufallSekunden;

}




int main() {

    int Streckenlänge = StreckenLange();
    int Ampelanzahl = 0;
    int eingabe;

    do {
        cout << "Ampelabstand selber eingeben oder durch zufall, 1 fur zufall 2 für selber" << endl;
        cin >> eingabe;
        if (eingabe != 1 && eingabe != 2) {
            cout << "Fehlerhafte eingabe" << endl;
        }

    } while (eingabe != 1 && eingabe != 2);

    int StreckenCounter = 0;    //
    int AmpelPosition[50];


    if (eingabe == 1) {


        while (StreckenCounter <= Streckenlänge - 250) {
            StreckenCounter += AmpelAbstand_random();
            AmpelPosition[Ampelanzahl] = StreckenCounter;

            // debug    cout << StreckenCounter<< endl;
            Ampelanzahl++;
        }
        if (AmpelPosition[Ampelanzahl] == Streckenlänge - 250) {
            Ampelanzahl++;
            AmpelPosition[Ampelanzahl] = Streckenlänge - 150;
        }
        else {
            AmpelPosition[Ampelanzahl] = Streckenlänge - 150;

        }
    }

    if (eingabe == 2) {

        int Abstand = 0; //Ampelabstand
        while (1) {
            AmpelPosition[Ampelanzahl];
            cout << "Abstand eingeben, zwischen100 und 1500 M" << endl;
            cin >> Abstand;

            if (Abstand >= 100 && Abstand <= 1500) {

                StreckenCounter += Abstand;
                AmpelPosition[Ampelanzahl] = StreckenCounter;
                cout << "Noch " << Streckenlänge - AmpelPosition[Ampelanzahl] << " Meter bis zum ende der Strecke" << endl;
                Ampelanzahl++;
            }
            else {
                cout << "Ampelabstand ungültig" << endl;
            }
            if (StreckenCounter >= Streckenlänge - 250) {
                Ampelanzahl--;
                AmpelPosition[Ampelanzahl] = Streckenlänge - 150;
                break;
            }
        }
    }
    PKW PKW_A;
    PKW_A.Beschleunigung_Faktor = (2.0 / 3.0);
    PKW_A.Vmax = 50;
    PKW_A.Aktuelle_Position = 0.0;
    PKW_A.Beschleunigung = 2.0;
    cout << PKW_A.NeueBeschleunigung;
    float time = sqrt((2 * (AmpelPosition[0] - PKW_A.Aktuelle_Position) / PKW_A.NeueBeschleunigung)); // Zeit für Strecke t=sqrt(2s/a)

    cout << time;
    /*
        PKW PKW_A;
        PKW_A.Beschleunigung_Faktor=2/3;
        PKW_A.Vmax=50;
        PKW_A.Aktuelle_Position=0;
        PKW_A.NeueBeschleunigung=PKW_A.Beschleunigung_Faktor*PKW_A.Beschleinigung;
        PKW PKW_B;
        PKW_B.Beschleunigung_Faktor=1;
        PKW_B.Vmax=50;

        PKW PKW_C;
        PKW_C.Beschleunigung_Faktor=1;
        PKW_C.Vmax=300; // weil wir von einem Auto ausgehen, welcher jetzt nicht abheben soll

        float Beschleunigung=2;
        float time=sqrt((Beschleunigung*(AmpelPosition[1]-PKW_A.Aktuelle_Position)/PKW_A.NeueBeschleunigung));

        cout<<time;
    

    //


return 0;
}
*/