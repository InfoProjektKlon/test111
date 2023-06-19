/*
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


int Schaltung() {

    int min = 20;
    int max = 60;

    srand(time(NULL));
    int ZufallSekunden = rand() % (max - min + 1) + min;

    return ZufallSekunden;

}



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
*/

 
//Sadik
#include <iostream>
#include <cstdlib>
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
   
    
    int randNum = rand() % (max - min + 1) + min;

    return randNum;
}

struct PKW {   //Struct für alle Fahrer
    float vmax;    //Geschwindigkeitsbegraenkung
    float beschleunigung1;
    float beschleunigung2;
    float beschleunigung3;
    float aktuelle_Position;
};

int Schaltung() {
    
    int min = 0;
    int max = 30;

   
    int t_ampel = rand() % (max - min + 1) + min;

    return t_ampel;
}

int main(){
    srand(time(NULL));
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

    int StreckenCounter = 0;    
    int AmpelPosition[100];


    if (eingabe == 1) { //Zufall (liefert immer selben Wert?)


        while (StreckenCounter < Streckenlänge - 250) {
            
          
            StreckenCounter += AmpelAbstand_random();
            AmpelPosition[Ampelanzahl] = StreckenCounter;

            // debug    cout << StreckenCounter<< endl;
            Ampelanzahl++;
            if (StreckenCounter >= Streckenlänge - 250) {
                Ampelanzahl--;
                AmpelPosition[Ampelanzahl] = Streckenlänge - 150;  //Platziert letzte Ampel auf s-150 
                break;
        }

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
    PKW_A.vmax = 50;
    PKW_A.aktuelle_Position = 0.0;
    PKW_A.beschleunigung1 = 2.0 * (2.0 / 3.0); // a * faktor
    PKW_A.beschleunigung2 = 3.0 * (2.0 / 3.0);
    PKW_A.beschleunigung3 = 6.0 * (2.0 / 3.0);

    int aktuelle_ampel = 0;
    float Distanz = 0.0;
    float t_acc;
    float t_vmax;
    float t_brake;
    float t_150m;
    float t_150m_vmax;
    float s_acc;
    float s_vmax;
    float s_brake;
    float s_150m_vmax;
    float zwischenzeit = 0.0;
    float gesamtzeit = 0.0;
    int ampelzeit[100];

    for (int i = 0; i < Ampelanzahl + 1; i++) {  //erzeugt alle Ampelzeiten für jede ampel. 
        ampelzeit[i] = Schaltung();
    }
      //noch ein for loop für alle Fahrer notwendig
    for (int accIndex = 1; accIndex <= 3; accIndex++) { //für alle 3 Beschleunigungen eines Fahrers
        float acc;
        switch (accIndex) {
        case 1:
            acc = PKW_A.beschleunigung1;
            cout << "Beschleunigung[m/s^2]: " << acc << endl;
            break;
        case 2:
            acc = PKW_A.beschleunigung2;
            cout << "Beschleunigung[m/s^2]: " << acc << endl;
            break;
        case 3:
            acc = PKW_A.beschleunigung3;
            cout << "Beschleunigung[m/s^2]: " << acc << endl;
            break;
        }


        //Zeitberechnungen (in Bearbeitung)
        while (aktuelle_ampel <= Ampelanzahl) {  //Abschnitt
            Distanz = AmpelPosition[aktuelle_ampel] - PKW_A.aktuelle_Position;
            t_acc = PKW_A.vmax / (3.6 * acc);
            s_acc = 0.5 * acc * (t_acc * t_acc);
            s_brake = s_acc;  //
            t_brake = t_acc;
            // cout << "Ampel: " << aktuelle_ampel << endl;
            // cout << "Zeit: " << Schaltung() << endl;
            // cout << "Ampelposition: " << AmpelPosition[aktuelle_ampel] << endl;
            if (Distanz >= 2 * s_acc) { //vmax wird erreicht. 
                // cout << "if" << endl;
                s_vmax = Distanz - s_acc - s_brake; // Strecke in der vmax gefahren wird 
                t_vmax = s_vmax/(PKW_A.vmax/3.6);
                zwischenzeit = t_acc + t_vmax + t_brake + ampelzeit[aktuelle_ampel];
            }

            else { //vmax wird nicht erreicht. Sonderfall für Fahrer A bei 2m/s^2 (falls Abschnitt<144,58m)  und Fahrer C

            }
           
            gesamtzeit += zwischenzeit;
            PKW_A.aktuelle_Position = AmpelPosition[aktuelle_ampel];
            //cout << "t_acc: " << t_acc << "t_vmax: " << t_vmax << "Ampelzeit: " << ampelzeit[aktuelle_ampel] << "Gesamtzeit: " << gesamtzeit << "s_acc: " << s_acc << "s_vmax: " << s_vmax << endl;
            aktuelle_ampel++;
        }
        s_150m_vmax = 150 - s_acc; //
        t_150m_vmax = s_150m_vmax / (PKW_A.vmax / 3.6);
        t_150m = t_acc + t_150m_vmax; //Zeit für die letzten 150m
        //cout << t_150m << endl;
        gesamtzeit += t_150m;     //
        cout << "Gesamtzeit[s]: " << gesamtzeit <<  endl; 
        PKW_A.aktuelle_Position = 0.0; //reset 
        aktuelle_ampel = 0; //reset
        gesamtzeit = 0; //reset
        zwischenzeit = 0; //reset
    }

return 0;
}

/*
pair<int, bool> Schaltung() {    //50/50 Ampel entweder rot oder grün
    bool grün = rand() % 2; //  0 = false (Ampel rot) , 1 = true (Ampel grün)
    int ZufallSekunden = 0;

    if (!grün) {
        ZufallSekunden = rand() % 21 + 10; // Zufällige Wartezeit zwischen 10 und 30 Sekunden generieren
    }

    return make_pair(ZufallSekunden, grün);
}

*/

        /*    "Grüne Welle" Versuch (klappt nicht)
             pair<int, bool> result = Schaltung();
             int ZufallSekunden = result.first; //Ampelzeit
             bool grün = result.second;    //Ampel grün oder nicht

             cout << AktuelleAmpel << endl;
             if (grün) {
                 cout << "Ampel ist gruen." << endl;
             }
             else {
                 cout << "Ampel ist rot. Wartezeit: " << ZufallSekunden << " Sekunden." << endl;
             }

             Distanz = AmpelPosition[AktuelleAmpel] - PKW_A.Aktuelle_Position;
             t_acc = ((PKW_A.Vmax/3.6) / PKW_A.NeueBeschleunigung);
             s_acc = 0.5 * PKW_A.NeueBeschleunigung * (t_acc * t_acc);

             if (Distanz >= 2 * s_acc) { //falls vmax erreicht wird

                 if (!grün) { //Ampel Rot
                     cout << "ifif" << endl;
                     s_brake = s_acc;
                     t_brake = t_acc;
                     s_vmax = Distanz - s_acc - s_brake;
                     t_vmax = sqrt((2 * s_vmax) / PKW_A.NeueBeschleunigung);
                     zwischenzeit = t_acc + t_vmax + t_brake + ZufallSekunden;
                     gesamtzeit = gesamtzeit + zwischenzeit;
                     AktuelleAmpel++;
                     //debug cout << s_vmax << "Strecke mit vmax" << t_vmax << "Zeit mit vmax" << endl;
                 }
                 else { //Ampel Grün
                     cout << "ifelse" << endl;
                     s_vmax = Distanz - s_acc;
                     t_vmax = s_vmax / (PKW_A.Vmax / 3.6);

                     zwischenzeit = t_acc + t_vmax; //
                     gesamtzeit = gesamtzeit + zwischenzeit;
                     cout << s_vmax << "Strecke mit vmax" << t_vmax << "Zeit mit vmax" << endl;

                     while (grün) {

                         PKW_A.Aktuelle_Position = AmpelPosition[AktuelleAmpel];
                         Distanz = AmpelPosition[AktuelleAmpel] - PKW_A.Aktuelle_Position;
                         t_vmax = Distanz / (PKW_A.Vmax / 3.6);
                         AktuelleAmpel++;
                     }
                 }
             }

             else {
                 if (!grün) { // Ampel Rot (vmax wird nicht erreicht)
                     cout << "else" << endl;
                     float s_acc2 = 0.5 * Distanz;
                     float t_acc2 = sqrt((2 * s_acc2) / PKW_A.NeueBeschleunigung);
                     float t_brake2 = t_acc2;
                     zwischenzeit = t_acc2 + t_brake2 + ZufallSekunden;
                     gesamtzeit = gesamtzeit + zwischenzeit;

                 }
             }

             cout << gesamtzeit << endl;
             PKW_A.Aktuelle_Position = AmpelPosition[AktuelleAmpel];
             AktuelleAmpel++;
         */
 
