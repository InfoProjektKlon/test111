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
}