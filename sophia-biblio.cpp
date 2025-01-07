#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

using namespace std;

void menu();
bool parseDate(const char* date, std::tm& tm);

struct Ouvrage
{
    char code[5];
    char titre[30];
    char auteur[30];
    char discipline[20];
    char date_arrivage[12];
    char provenance[20];
};
struct Ouvrage info_ouvrage;

struct Abonne
{
    char nif[25];
    char prenom[25];
    char nom[25];
    char adresse[25];
    char phone[10];
    char date_inscription[20];
};
struct Abonne info_abonne;

struct Pret
{
    char numero[5];
    char code_abonne[25];
    char code_ouvrage[5];
    char date_sortie[20];
    char date_entree[20];
}; 
struct Pret info_pret;

bool parseDate(const char* date, std::tm& tm) {
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

class LesOuvrages
{

public:
    void creerFichierOuvrage()
    {
        // Tentative d'ouverture du fichier en lecture pour vérifier son existence
        fstream ouvrages("ouvrages.dat", ios::in);

        if (ouvrages.is_open())
        {
            ouvrages.close();
        }
        else
        {
            // Le fichier n'existe pas, le créer
            cout << "Le fichier 'ouvrages.dat' n'existe pas, création en cours..." << endl;
            ouvrages.open("ouvrages.dat", ios::app); // ios::app crée le fichier s'il n'existe pas
            if (ouvrages)
            {
                cout << "Fichier 'ouvrages.dat' créé avec succès." << endl;
            }
            else
            {
                cerr << "Erreur lors de la création du fichier 'ouvrages.dat'." << endl;
            }
            ouvrages.close();
        }
    }

    void ajouterOuvrage()
    {
        char choix;
        fstream ouvrages("ouvrages.dat", ios::in | ios::out | ios::app); 
        do
        {
            system("cls");
            cout << "\nEntrer le code : ";
            cin >> info_ouvrage.code;
            cin.ignore(); // Ignore le caractère '\n' qui traine

            cout << "\nEntrer le Titre : ";
            cin.getline(info_ouvrage.titre, sizeof(info_ouvrage.titre)); // Permet d'inclure des espaces

            cout << "\nEntrer le nom de l'auteur : ";
            cin.getline(info_ouvrage.auteur, sizeof(info_ouvrage.auteur));

            cout << "\nEntrer la discipline / categorie : ";
            cin.getline(info_ouvrage.discipline, sizeof(info_ouvrage.discipline));

            cout << "\nEntrer la date d'arrivage : ";
            cin.getline(info_ouvrage.date_arrivage, sizeof(info_ouvrage.date_arrivage));

            cout << "\nEntrer la provenance : ";
            cin.getline(info_ouvrage.provenance, sizeof(info_ouvrage.provenance));

            ouvrages.seekp(0, ios::end);
            ouvrages.write((char *)&info_ouvrage, sizeof(info_ouvrage));

            cout << "\nVoulez-vous continuer (o/n) : ";
            choix = getch();

        } while ((choix != 'n') && (choix != 'N'));
        ouvrages.close();
        menu();
    }

    void afficherOuvrage(char *vcode)
    {
        // Ouvrage info_ouvrage;
        fstream ouvrages("ouvrages.dat", ios::in);

        if (!ouvrages)
        {
            cerr << "Erreur : Impossible d'ouvrir le fichier 'ouvrages.dat'.\n";
            return;
        }



        int ligne = 0;

        do
        {
            if (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                if (strcmp(info_ouvrage.code, vcode) == 0)
                {
                    cout.width(5);
                    cout << left << info_ouvrage.code;
                    cout.width(30);
                    cout << left << info_ouvrage.titre;
                    cout.width(25);
                    cout << left << info_ouvrage.auteur;
                    cout.width(20);
                    cout << left << info_ouvrage.discipline;
                    cout.width(17);
                    cout << left << info_ouvrage.date_arrivage;
                    cout.width(20);
                    cout << right << info_ouvrage.provenance << endl;
                    ligne++;
                    if (ligne == 20)
                    {
                        cout << "\nAppuyez sur une touche pour continuer...";
                        getch();
                        ligne = 0;
                        system("cls");
                    }
                    break;
                }
            }
        } while (!ouvrages.eof());
        ouvrages.close();
        // do
        // {
        //     if (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
        //     {
        //         cout.width(5);
        //         cout << left << info_ouvrage.code;
        //         cout.width(30);
        //         cout << left << info_ouvrage.titre;
        //         cout.width(25);
        //         cout << left << info_ouvrage.auteur;
        //         cout.width(20);
        //         cout << left << info_ouvrage.discipline;
        //         cout.width(17);
        //         cout << left << info_ouvrage.date_arrivage;
        //         cout.width(20);
        //         cout << right << info_ouvrage.provenance << endl;
        //         ligne++;
        //         if (ligne == 20)
        //         {
        //             cout << "\nAppuyez sur une touche pour continuer...";
        //             getch();
        //             ligne = 0;
        //             system("cls");
        //         }
        //     }
        // } while (!ouvrages.eof());

        // ouvrages.close();
        // cout << "\nFin de l'Affichage. Appuyez sur une Enter pour quitter.";
        getch();
    }

    void rechercheOuvrage()
    {
        char vcode[5];
        int trouver = 0;
        system("cls");
        fstream ouvrages("ouvrages.dat", ios::in);
        cout << "\nEntrer le code : ";
        cin.getline(vcode, sizeof(vcode));
        do
        {
            if (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                if (strcmp(info_ouvrage.code, vcode) == 0)
                {
                    trouver = 1;
                    system("cls");
                    cout << "\n Voici l'information pour l'ouvrage ayant le code : " << vcode << endl;
                    cout << setw(20) << "\n Code " << ": " << info_ouvrage.code;
                    cout << setw(20) << "\n Titre " << ": " << info_ouvrage.titre;
                    cout << setw(20) << "\n Auteur " << ": " << info_ouvrage.auteur;
                    cout << setw(20) << "\n Discipline " << ": " << info_ouvrage.discipline;
                    cout << setw(20) << "\n Date d'arrivage " << ": " << info_ouvrage.date_arrivage;
                    cout << setw(20) << "\n Provenance " << ": " << info_ouvrage.provenance << endl;
                    cout << "\n Appuyez sur Enter pour revenir au menu principal.";
                    break;
                }
            }
        } while (!ouvrages.eof());
        ouvrages.close();
        if (trouver == 0)
        {
            cout << "\nOuvrage introuvable.";
        }
        getch();
        menu();
    }

    void rechercheDiscipline()
    {
        char vcode[20];
        int trouver = 0;
        system("cls");
        fstream ouvrages("ouvrages.dat", ios::in);
        cout << "\nEntrer la discipline que vous voulez trier : ";
        cin.getline(vcode, sizeof(vcode));

        system("cls"); 
        cout << "\n";
        cout.width(69);
        cout << right << "Liste des Ouvrages de Discipline : " << vcode << endl;

        cout << setw(82) << right << string(52, '=') << endl;
        cout << "\n";	

        // Rewrited header
        cout.width(5);
        cout << left << "Code";
        cout.width(30);
        cout << left << "Titre";
        cout.width(25);
        cout << left << "Auteur";
        cout.width(20);
        cout << left << "Discipline";
        cout.width(17);
        cout << left << "Date d'arrivage";
        cout.width(20);
        cout << right << "Provenance" << endl;
        cout << string(117, '-') << endl;

        int ligne = 0;
        do
        {
            if (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                if (strcmp(info_ouvrage.discipline, vcode) == 0)
                {
                    trouver = 1;
                    cout.width(5);
                    cout << left << info_ouvrage.code;
                    cout.width(30);
                    cout << left << info_ouvrage.titre;
                    cout.width(25);
                    cout << left << info_ouvrage.auteur;
                    cout.width(20);
                    cout << left << info_ouvrage.discipline;
                    cout.width(17);
                    cout << left << info_ouvrage.date_arrivage;
                    cout.width(20);
                    cout << right << info_ouvrage.provenance << endl;
                    ligne++;
                    if (ligne == 20)
                    {
                        cout << "\nAppuyez sur une touche pour continuer...";
                        getch();
                        ligne = 0;
                        system("cls");
                    }
                }
            }
        } while (!ouvrages.eof());
        ouvrages.close();
        if (trouver == 0)
        {
            cout << "\n Discipline introuvable.";
        }
        getch();
        menu();
    }

    void rechercheOuvragesParAuteur()
    {
        char vcode[20];
        int trouver = 0;
        system("cls");
        fstream ouvrages("ouvrages.dat", ios::in);
        // On n'alloue pas de code aux auteurs car ils ne constituent pas un module dans notre programme. De ce fait, j'utilise leurs noms
        cout << "\nEntrer le nom de l'auteur dont vous voulez consulter les oeuvres : ";
        cin.getline(vcode, sizeof(vcode));

        system("cls"); 
        cout << "\n";
        cout.width(69);
        cout << right << "Liste des Ouvrages de : " << vcode << endl;

        cout << setw(82) << right << string(40, '=') << endl;
        cout << "\n";	
        cout.width(5);
        cout << left << "Code";
        cout.width(30);
        cout << left << "Titre";
        cout.width(25);
        cout << left << "Auteur";
        cout.width(20);
        cout << left << "Discipline";
        cout.width(17);
        cout << left << "Date d'arrivage";
        cout.width(20);
        cout << right << "Provenance" << endl;
        cout << string(117, '-') << endl;

        int ligne = 0;
        do
        {
            if (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                if (strcmp(info_ouvrage.auteur, vcode) == 0)
                {
                    trouver = 1;
                    cout.width(5);
                    cout << left << info_ouvrage.code;
                    cout.width(30);
                    cout << left << info_ouvrage.titre;
                    cout.width(25);
                    cout << left << info_ouvrage.auteur;
                    cout.width(20);
                    cout << left << info_ouvrage.discipline;
                    cout.width(17);
                    cout << left << info_ouvrage.date_arrivage;
                    cout.width(20);
                    cout << right << info_ouvrage.provenance << endl;
                    ligne++;
                    if (ligne == 20)
                    {
                        cout << "\n Appuyez sur une touche pour continuer...";
                        getch();
                        ligne = 0;
                        system("cls");
                    }
                }
            }
        } while (!ouvrages.eof());
        ouvrages.close();
        if (trouver == 0)
        {
            cout << "\n Auteur introuvable. Appuyez sur une touche pour continuer...";
        }
        getch();
        menu();
    }


    void modifierOuvrage()
    {
        char x_code[5];
        char x_titre[30];
        char x_auteur[30];
        char x_discipline[20];
        char x_date_arrivage[12];
        char x_provenance[20];
        char vcode[10];

        char choix;
        int trouver = 0;
        system("cls");
        cout << "\nEntrer le code : ";
        cin.getline(vcode, sizeof(vcode));

        fstream ouvrages("ouvrages.dat", ios::in | ios::out);

        do
        {
            if (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                if (strcmp(info_ouvrage.code, vcode) == 0)
                {
                    trouver = 1;
                    system("cls");
                    cout << "\n Voici l'information pour l'ouvrage ayant le code : " << vcode << endl;
                    cout << setw(20) << "\n Code " << ": " << info_ouvrage.code;
                    cout << setw(20) << "\n Titre " << ": " << info_ouvrage.titre;
                    cout << setw(20) << "\n Auteur " << ": " << info_ouvrage.auteur;
                    cout << setw(20) << "\n Discipline " << ": " << info_ouvrage.discipline;
                    cout << setw(20) << "\n Date d'arrivage " << ": " << info_ouvrage.date_arrivage;
                    cout << setw(20) << "\n Provenance " << ": " << info_ouvrage.provenance << endl;
                    cout << "\n Voulez-vous modifier l'ouvrage (o/n) ? ";
                    choix = getch();
                    if (choix == 'o' || choix == 'O')
                    {
                        system("cls");
                        cout << "\n Entrer le nouveau code : ";
                        cin.getline(x_code, sizeof(x_code));
                        if (strlen(x_code) != 0)
                            strcpy(info_ouvrage.code, x_code);
                        cout << "\n Entrer le nouveau titre : ";
                        cin.getline(x_titre, sizeof(x_titre));
                        if (strlen(x_titre) != 0)
                            strcpy(info_ouvrage.titre, x_titre);
                        cout << "\n Entrer le nouveau auteur : ";
                        cin.getline(x_auteur, sizeof(x_auteur));
                        if (strlen(x_auteur) != 0)
                            strcpy(info_ouvrage.auteur, x_auteur);
                        cout << "\n Entrer la nouvelle discipline : ";
                        cin.getline(x_discipline, sizeof(x_discipline));
                        if (strlen(x_discipline) != 0)
                            strcpy(info_ouvrage.discipline, x_discipline);
                        cout << "\n Entrer la nouvelle date d'arrivage : ";
                        cin.getline(x_date_arrivage, sizeof(x_date_arrivage));
                        if (strlen(x_date_arrivage) != 0)
                            strcpy(info_ouvrage.date_arrivage, x_date_arrivage);
                        cout << "\n Entrer la nouvelle provenance : ";
                        cin.getline(x_provenance, sizeof(x_provenance));
                        if (strlen(x_provenance) != 0)
                            strcpy(info_ouvrage.provenance, x_provenance);
                        if (ouvrages.tellp() >= sizeof(info_ouvrage))
                        {
                            ouvrages.seekp(ouvrages.tellp() - static_cast<std::streamoff>(sizeof(info_ouvrage)), ios::beg);
                        }

                        ouvrages.write((char *)&info_ouvrage, sizeof(info_ouvrage));
                        // break;
                        system("cls");
                        cout << "\n Modification reussie." << endl;
                        cout << "\n Appuyez sur Enter pour revenir au menu principal.";
                        getch();
                    }
                }
            }
        } while (!ouvrages.eof());
        ouvrages.close();
        if (!trouver)
        {
            cout << "\nOuvrage introuvable.";
            getch();
        }
        menu();
    }

    void supprimerOuvrage()
    {
        char vcode[10];
        char choix;
        int trouver = 0;
        system("cls");
        cout << "\n Entrer le code :";

        cin >> vcode;
        fstream ouvrages("ouvrages.dat", ios::in);
        fstream bak("temp.bak", ios::app);
        bak.close();
        fstream temp("temp.bak", ios::out | ios::in);
        do
        {
            if (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                if (strcmp(info_ouvrage.code, vcode) == 0)
                {
                    trouver = 1;
                    cout << setw(20) << "\n Code " << ": " << info_ouvrage.code;
                    cout << setw(20) << "\n Titre " << ": " << info_ouvrage.titre;
                    cout << setw(20) << "\n Auteur " << ": " << info_ouvrage.auteur;
                    cout << setw(20) << "\n Discipline " << ": " << info_ouvrage.discipline;
                    cout << setw(20) << "\n Date d'arrivage " << ": " << info_ouvrage.date_arrivage;
                    cout << setw(20) << "\n Provenance " << ": " << info_ouvrage.provenance;
                    cout << setw(20) << "\n\n Voulez-vous le supprimer o/n ?";
                    choix = getch();
                    if ((choix == 'o') || (choix == 'O'))
                    {
                        // ouvrages.seekp(ouvrages.tellp() - static_cast<std::streamoff>(sizeof(info_ouvrage)), ios::beg);
                        // ouvrages.seekp(ouvrages.tellp() + static_cast<std::streamoff>(sizeof(info_ouvrage)), ios::cur);
                        // temp.write((char *)&info_ouvrage, sizeof(info_ouvrage));
                    }
                    // 
                    else
                    {
                        temp.write((char *)&info_ouvrage, sizeof(info_ouvrage));
                    }
                }
                else
                {
                    temp.write((char *)&info_ouvrage, sizeof(info_ouvrage));
                }
            }
        } while (!ouvrages.eof());
        ouvrages.close();
        temp.close();

        remove("ouvrages.dat");
        rename("temp.bak", "ouvrages.dat");

        if (!trouver)
        {
            cout << "\n Ouvrage introuvable.";
        }
        else
        {
            system("cls");
            if ((choix != 'o') && (choix != 'O')){
                cout << "\n Abandon de l'operation." << endl;
            } else
            cout << "\n Suppression reussie." << endl;
        }
        cout << "\n Appuyez sur Enter pour revenir au menu principal.";
        char c = getch();
        menu();
    }

     
    void afficherOuvragesTriesParTitre() {
        std::vector<Ouvrage> ouvragesList;
        std::ifstream fichiers("ouvrages.dat", std::ios::binary);

        if (!fichiers) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier 'ouvrages.dat'.\n";
            return;
        }

        // Chargement des ouvrages dans un vecteur
        Ouvrage ouvrage;
        while (fichiers.read(reinterpret_cast<char*>(&ouvrage), sizeof(ouvrage))) {
            ouvragesList.push_back(ouvrage);
        }
        fichiers.close();

        std::sort(ouvragesList.begin(), ouvragesList.end(), [](const Ouvrage& a, const Ouvrage& b) {
            std::string titre1 = a.titre;
            titre1[0] = std::tolower(titre1[0]);

            std::string titre2 = b.titre;
            titre2[0] = std::tolower(titre2[0]);
            
            // return strcmp(tolower(a.titre), tolower(b.titre)) < 0;
            return titre1 < titre2;
        });
        

        system("cls");
        cout << '\n';
        cout << setw(79) << right << "Liste des Ouvrages (Tri par Titre)\n\n";
        cout.width(5);
        cout << left << "Code";
        cout.width(30);
        cout << left << "Titre";
        cout.width(25);
        cout << left << "Auteur";
        cout.width(20);
        cout << left << "Discipline";
        cout.width(17);
        cout << left << "Date d'arrivage";
        cout.width(20);
        cout << right << "Provenance" << endl;
        cout << string(117, '-') << endl;

        int ligne = 0;

        for (const auto& o : ouvragesList) {
            cout.width(5);
            cout << left << o.code;
            cout.width(30);
            cout << left << o.titre;
            cout.width(25);
            cout << left << o.auteur;
            cout.width(20);
            cout << left << o.discipline;
            cout.width(17);
            cout << left << o.date_arrivage;
            cout.width(20);
            cout << right << o.provenance << endl;
            ligne++;
            if (ligne == 20)
            {
                cout << "\nAppuyez sur une touche pour continuer...";
                getch();
                ligne = 0;
                system("cls");
            }
        }
        cout << "\n\n Cliquez sur une touche pour continuer";
        getch();
        menu();
    }


    void gotoxy(int x, int y)
    {
        COORD point;
        point.X = x;
        point.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
    }
};

class LesAbonnes
{

public:
    void creerFichierAbonne()
    {
        // Tentative d'ouverture du fichier en lecture pour vérifier son existence
        fstream abonnes("abonnes.dat", ios::in);

        if (abonnes.is_open())
        {
            // Le fichier existe déjà
            abonnes.close();
        }
        else
        {
            // Le fichier n'existe pas, le créer
            cout << "Le fichier 'abonnes.dat' n'existe pas, création en cours..." << endl;
            abonnes.open("abonnes.dat", ios::app); // ios::app crée le fichier s'il n'existe pas
            if (abonnes)
            {
                cout << "Fichier 'abonnes.dat' créé avec succès." << endl;
            }
            else
            {
                cerr << "Erreur lors de la création du fichier 'abonnes.dat'." << endl;
            }
            abonnes.close();
        }
    }

    void ajouterAbonne()
    {
        char choix;
        fstream abonnes("abonnes.dat", ios::in | ios::out | ios::app); // ios::app pour ajouter à la fin
        do
        {
            system("cls");
            cout << "\n Entrer le NIF : ";
            cin >> info_abonne.nif;
            cin.ignore(); // Ignore le caractère '\n' qui traine

            cout << "\n Entrer le prenom : ";
            cin.getline(info_abonne.prenom, sizeof(info_abonne.prenom)); // Permet d'inclure des espaces

            cout << "\n Entrer le nom : ";
            cin.getline(info_abonne.nom, sizeof(info_abonne.nom));

            cout << "\n Entrer l'adresse : ";
            cin.getline(info_abonne.adresse, sizeof(info_abonne.adresse));

            cout << "\n Entrer le telephone : ";
            cin.getline(info_abonne.phone, sizeof(info_abonne.phone));

            cout << "\n Entrer la date d'inscription : ";
            cin.getline(info_abonne.date_inscription, sizeof(info_abonne.date_inscription));

            abonnes.seekp(0, ios::end);
            abonnes.write((char *)&info_abonne, sizeof(info_abonne));

            cout << "\n Voulez-vous continuer (o/n) : ";
            choix = getch();

        } while ((choix != 'n') && (choix != 'N'));
        abonnes.close();
        menu(); 
    }

    void afficherAbonnes()
    {
        fstream abonnes("abonnes.dat", ios::in);

        if (!abonnes)
        {
            cerr << "Erreur : Impossible d'ouvrir le fichier 'abonnes.dat'.\n";
            return;
        }

        system("cls"); // Effacer l'écran
        cout.width(69);
        cout << right << "Liste des Abonnes\n\n";

        // Rewrited header
        cout.width(5);
        cout << left << "NIF";
        cout.width(30);
        cout << left << "Prenoms";
        cout.width(25);
        cout << left << "Noms";
        cout.width(20);
        cout << left << "Adresse";
        cout.width(17);
        cout << left << "Telephone";
        cout.width(20);
        cout << right << "Date d'inscription" << endl;
        cout << string(117, '-') << endl;

        int ligne = 0;


        do
        {
            if (abonnes.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                cout.width(5);
                cout << left << info_abonne.nif;
                cout.width(30);
                cout << left << info_abonne.prenom;
                cout.width(25);
                cout << left << info_abonne.nom;
                cout.width(20);
                cout << left << info_abonne.adresse;
                cout.width(17);
                cout << left << info_abonne.phone;
                cout.width(20);
                cout << right << info_abonne.date_inscription << endl;
                ligne++;
                if (ligne == 20)
                {
                    cout << "\nAppuyez sur une touche pour continuer...";
                    getch();
                    ligne = 0;
                    system("cls");
                }
            }
        } while (!abonnes.eof());

        abonnes.close();
        cout << "\nFin de l'Affichage. Appuyez sur une Enter pour quitter.";
        getch();
    }

    void rechercheAbonne()
    {
        char vcode[25];
        int trouver = 0;
        system("cls");
        fstream abonnes("abonnes.dat", ios::in);
        cout << "\n Entrer le NIF : ";
        cin.getline(vcode, sizeof(vcode));
        do
        {
            if (abonnes.read((char *)&info_abonne, sizeof(info_abonne)))
            {
                if (strcmp(info_abonne.nif, vcode) == 0)
                {
                    trouver = 1;
                    system("cls");
                    cout << "\n Voici l'information pour l'abonne ayant le NIF : " << vcode << endl;
                    cout << setw(22) << "\n NIF " << ": " << info_abonne.nif;
                    cout << setw(22) << "\n Prenom " << ": " << info_abonne.prenom;
                    cout << setw(22) << "\n Nom " << ": " << info_abonne.nom;
                    cout << setw(22) << "\n Adresse " << ": " << info_abonne.adresse;
                    cout << setw(22) << "\n Telephone " << ": " << info_abonne.phone;
                    cout << setw(22) << "\n Date d'inscription " << ": " << info_abonne.date_inscription << endl;
                    cout << "\n Appuyez sur Enter pour revenir au menu principal.";
                    getch();
                    break;
                }
            }
        } while (!abonnes.eof());
        abonnes.close();
        if (trouver == 0)
        {
            cout << "\nAbonne introuvable.";
        }
        menu();
    }

    void rechercheDiscipline()
    {
        char vcode[20];
        int trouver = 0;
        system("cls");
        fstream ouvrages("ouvrages.dat", ios::in);
        cout << "\nEntrer la discipline que vous voulez trier : ";
        cin.getline(vcode, sizeof(vcode));

        system("cls"); // Effacer l'écran
        cout.width(69);
        cout << right << "Liste des Ouvrages de Discipline : " << vcode << endl;

        // Rewrited header
        cout.width(5);
        cout << left << "Code";
        cout.width(30);
        cout << left << "Titre";
        cout.width(25);
        cout << left << "Auteur";
        cout.width(20);
        cout << left << "Discipline";
        cout.width(17);
        cout << left << "Date d'arrivage";
        cout.width(20);
        cout << right << "Provenance" << endl;
        cout << string(117, '-') << endl;

        int ligne = 0;
        do
        {
            if (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                if (strcmp(info_ouvrage.discipline, vcode) == 0)
                {
                    trouver = 1;
                    cout.width(5);
                    cout << left << info_ouvrage.code;
                    cout.width(30);
                    cout << left << info_ouvrage.titre;
                    cout.width(25);
                    cout << left << info_ouvrage.auteur;
                    cout.width(20);
                    cout << left << info_ouvrage.discipline;
                    cout.width(17);
                    cout << left << info_ouvrage.date_arrivage;
                    cout.width(20);
                    cout << right << info_ouvrage.provenance << endl;
                    ligne++;
                    if (ligne == 20)
                    {
                        cout << "\nAppuyez sur une touche pour continuer...";
                        getch();
                        ligne = 0;
                        system("cls");
                    }
                }
            }
        } while (!ouvrages.eof());
        getch();
        ouvrages.close();
        if (trouver == 0)
        {
            cout << "\nDiscipline introuvable.";
            getch();
        }
    }

    void modifierAbonne()
    {
        char x_nif[25];
        char x_prenom[25];
        char x_nom[25];
        char x_adresse[25];
        char x_phone[10];
        char x_date_inscription[20];
        char vcode[25];

        char choix;
        int trouver = 0;
        system("cls");
        cout << "\n Entrer le NIF : ";
        cin.getline(vcode, sizeof(vcode));

        fstream abonnes("abonnes.dat", ios::in | ios::out);

        do
        {
            if (abonnes.read((char *)&info_abonne, sizeof(info_abonne)))
            {
                if (strcmp(info_abonne.nif, vcode) == 0)
                {
                    trouver = 1;
                    system("cls");
                    cout << "\n Voici l'information pour l'abonne ayant le NIF : " << vcode << endl;
                    cout << setw(22) << "\n NIF " << ": " << info_abonne.nif;
                    cout << setw(22) << "\n Prenom " << ": " << info_abonne.prenom;
                    cout << setw(22) << "\n Nom " << ": " << info_abonne.nom;
                    cout << setw(22) << "\n Adresse " << ": " << info_abonne.adresse;
                    cout << setw(22) << "\n Telephone " << ": " << info_abonne.phone;
                    cout << setw(22) << "\n Date d'inscription " << ": " << info_abonne.date_inscription << endl;
                    cout << "\n Voulez-vous modifier l'abonne (o/n) ? ";
                    choix = getch();
                    if (choix == 'o' || choix == 'O')
                    {
                        system("cls");
                        cout << "\nEntrer le nouveau NIF : ";
                        cin.getline(x_nif, sizeof(x_nif));
                        if (strlen(x_nif) != 0)
                            strcpy(info_abonne.nif, x_nif);
                        cout << "\nEntrer le nouveau prenom : ";
                        cin.getline(x_prenom, sizeof(x_prenom));
                        if (strlen(x_prenom) != 0)
                            strcpy(info_abonne.prenom, x_prenom);
                        cout << "\nEntrer le nouveau nom : ";
                        cin.getline(x_nom, sizeof(x_nom));
                        if (strlen(x_nom) != 0)
                            strcpy(info_abonne.nom, x_nom);
                        cout << "\nEntrer la nouvelle adresse : ";
                        cin.getline(x_adresse, sizeof(x_adresse));
                        if (strlen(x_adresse) != 0)
                            strcpy(info_abonne.adresse, x_adresse);
                        cout << "\nEntrer le nouveau telephone : ";
                        cin.getline(x_phone, sizeof(x_phone));
                        if (strlen(x_phone) != 0)
                            strcpy(info_abonne.phone, x_phone);
                        cout << "\nEntrer la nouvelle date d'inscription : ";
                        cin.getline(x_date_inscription, sizeof(x_date_inscription));
                        if (strlen(x_date_inscription) != 0)
                            strcpy(info_abonne.date_inscription, x_date_inscription);
                        if (abonnes.tellp() >= sizeof(info_abonne))
                        {
                            abonnes.seekp(abonnes.tellp() - static_cast<std::streamoff>(sizeof(info_abonne)), ios::beg);
                        }

                        abonnes.write((char *)&info_abonne, sizeof(info_abonne));
                        system("cls");
                        cout << "\n Modification reussie." << endl;
                        cout << "\n Appuyez sur Enter pour revenir au menu principal.";
                        getch();
                    }
                }
            }
        } while (!abonnes.eof());
        abonnes.close();
        if (!trouver)
        {
            cout << "\n Abonne introuvable.";
            getch();
        }
        menu();
    }

    void supprimerAbonne()
    {
        char vcode[25];
        char choix;
        int trouver = 0;
        system("cls");
        cout << "\n Entrer le NIF :";

        cin.getline(vcode, sizeof(vcode));
        fstream abonnes("abonnes.dat", ios::in);
        fstream bak("temp.bak", ios::app);
        bak.close();
        fstream temp("temp.bak", ios::out | ios::in);
        do
        {
            if (abonnes.read((char *)&info_abonne, sizeof(info_abonne)))
            {
                if (strcmp(info_abonne.nif, vcode) == 0)
                {
                    trouver = 1;
                    system("cls");
                    cout << "\n Voici l'information pour l'abonne ayant le NIF : " << vcode << endl;
                    cout << setw(22) << "\n NIF " << ": " << info_abonne.nif;
                    cout << setw(22) << "\n Prenom " << ": " << info_abonne.prenom;
                    cout << setw(22) << "\n Nom " << ": " << info_abonne.nom;
                    cout << setw(22) << "\n Adresse " << ": " << info_abonne.adresse;
                    cout << setw(22) << "\n Telephone " << ": " << info_abonne.phone;
                    cout << setw(22) << "\n Date d'inscription " << ": " << info_abonne.date_inscription << endl;
                    cout << "\n Voulez-vous le supprimer o/n ?";
                    choix = getch();
                    if ((choix == 'o') || (choix == 'O'))
                    {
                    }
                    else
                    {
                        temp.write((char *)&info_abonne, sizeof(info_abonne));
                    }
                }
                else
                {
                    temp.write((char *)&info_abonne, sizeof(info_abonne));
                }
            }
        } while (!abonnes.eof());
        abonnes.close();
        temp.close();

        remove("abonnes.dat");
        rename("temp.bak", "abonnes.dat");

        if (!trouver)
        {
            cout << "\n Abonne introuvable.";
        }
        else
        {
            system("cls");
            if ((choix != 'o') && (choix != 'O')){
                cout << "\n Abandon de l'operation." << endl;
            } else
            cout << "\n Suppression reussie." << endl;
        }
        cout << "\n Appuyez sur Enter pour revenir au menu principal.";
        char c = getch();
        menu();
    }

    void afficherAbonnesTriesParNom() {
        std::vector<Abonne> abonnesList;
        std::ifstream fichiers("abonnes.dat", std::ios::binary);

        if (!fichiers) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier 'abonnes.dat'.\n";
            return;
        }

        Abonne abonne;
        while (fichiers.read(reinterpret_cast<char*>(&abonne), sizeof(abonne))) {
            abonnesList.push_back(abonne);
        }
        fichiers.close();

        std::sort(abonnesList.begin(), abonnesList.end(), [](const Abonne& a, const Abonne& b) {
            std::string titre1 = a.nom;
            titre1[0] = std::tolower(titre1[0]);

            std::string titre2 = b.nom;
            titre2[0] = std::tolower(titre2[0]);
            
            return titre1 < titre2;
        });
        

        system("cls");
        cout << '\n';
        cout << setw(79) << right << "Liste des Abonnes (Tri par Nom)\n\n";
        cout.width(25);
        cout << left << "NIF";
        cout.width(15);
        cout << left << "Nom";
        cout.width(25);
        cout << left << "Prenom";
        cout.width(25);
        cout << left << "Adresse";
        cout.width(10);
        cout << left << "Phone";
        cout.width(15);
        cout << right << "Date d'inscription" << endl;
        cout << string(118, '-') << endl;

        int ligne = 0;

        for (const auto& o : abonnesList) {
            cout.width(25);
            cout << left << o.nif;
            cout.width(15);
            cout << left << o.nom;
            cout.width(25);
            cout << left << o.prenom;
            cout.width(25);
            cout << left << o.adresse;
            cout.width(10);
            cout << left << o.phone;
            cout.width(15);
            cout << right << o.date_inscription << endl;
            ligne++;
            if (ligne == 20)
            {
                cout << "\n Appuyez sur une touche pour continuer...";
                getch();
                ligne = 0;
                system("cls");
            }
        }
        cout << "\n\n Cliquez sur une touche pour continuer";
        getch();
        menu();
    }
};


class Prets
{
public:
    void creerFichierPret()
    {
        // Tentative d'ouverture du fichier en lecture pour vérifier son existence
        fstream prets("prets.dat", ios::in);

        if (prets.is_open())
        {
            prets.close();
        }
        else
        {
            // Le fichier n'existe pas, le créer
            cout << "Le fichier 'prets.dat' n'existe pas, création en cours..." << endl;
            prets.open("prets.dat", ios::app);
            if (prets)
            {
                cout << "Fichier 'prets.dat' créé avec succès." << endl;
            }
            else
            {
                cerr << "Erreur lors de la création du fichier 'prets.dat'." << endl;
            }
            prets.close();
        }
    }
    void enregistrerPret()
    {
        char choix;
        fstream prets("prets.dat", ios::in | ios::out | ios::app);

        do
        {
            system("cls");
            cout << "\n Entrez le numero du pret: ";
            cin.getline(info_pret.numero, sizeof(info_pret.numero));
            cout << "\n Entrez le NIF du preteur: ";
            cin.getline(info_pret.code_abonne, sizeof(info_pret.code_abonne));
            cout << "\n Entrez le code de l'ouvrage: ";
            cin.getline(info_pret.code_ouvrage, sizeof(info_pret.code_ouvrage));
            // Today date ???
            cout << "\n Entrez la date du pret: ";
            cin.getline(info_pret.date_sortie, sizeof(info_pret.date_sortie));
            cout << "\n Entrez la date de fin du pret: ";
            cin.getline(info_pret.date_entree, sizeof(info_pret.date_entree));

            prets.seekp(0, ios::end);
            prets.write((char *)&info_pret, sizeof(info_pret));

            cout << "\n Y a-t-il d'autres prets a sauvegarder? (o/n)";
            choix = getch();
        } while (choix != 'n' && choix != 'N');
        prets.close();
        menu();
    }

    void suppressionPret()
    {
        char given_nb[25];
        char choix;
        int trouver = 0;
        system("cls");
        cout << "\n Entrer le numero du pret :";

        cin >> given_nb;
        fstream prets("prets.dat", ios::in);
        fstream bak("temp.bak", ios::app);
        bak.close();
        fstream temp("temp.bak", ios::out | ios::in);
        do
        {
            if (prets.read((char *)&info_pret, sizeof(info_pret)))
            {
                if (strcmp(info_pret.numero, given_nb) == 0)
                {
                    trouver = 1;
                    system("cls");
                    cout << "\n Voici l'information pour le pret ayant le numero : " << given_nb << endl;
                    cout << setw(22) << "\n Numero " << ": " << info_pret.numero;
                    cout << setw(22) << "\n Code Abonne " << ": " << info_pret.code_abonne;
                    cout << setw(22) << "\n Code Ouvrage " << ": " << info_pret.code_ouvrage;
                    cout << setw(22) << "\n Date de sortie " << ": " << info_pret.date_sortie;
                    cout << setw(22) << "\n Date d'entree " << ": " << info_pret.date_entree << endl;
                    cout << "\n Voulez-vous marquer ce pret comme acquitte o/n ?";
                    choix = getch();
                    if ((choix == 'o') || (choix == 'O'))
                    {
                    }
                    else
                    {
                        temp.write((char *)&info_pret, sizeof(info_pret));
                    }
                }
                else
                {
                    temp.write((char *)&info_pret, sizeof(info_pret));
                }
            }
        } while (!prets.eof());
        prets.close();
        temp.close();

        remove("prets.dat");
        rename("temp.bak", "prets.dat");

        if (!trouver)
        {
            cout << "\n Pret introuvable.";
        }
        else
        {
            system("cls");
            if ((choix != 'o') && (choix != 'O')){
                cout << "\n Abandon de l'operation." << endl;
            } else
            cout << "\n Remise reussie." << endl;
        }
        cout << "\n Appuyez sur Enter pour revenir au menu principal.";
        char c = getch();
        menu();
    }

    void afficherPreteurs()
    {
        fstream prets("prets.dat", ios::in);

        if (!prets)
        {
            cerr << "Erreur : Impossible d'ouvrir le fichier 'prets.dat'.\n";
            return;
        }
        system("cls");
        cout.width(69);
        cout << right << "Liste des Prets\n\n";

        // Rewrited header
        cout.width(10);
        cout << left << "Numero";
        cout.width(15);
        cout << left << "Code Ouvrage";
        cout.width(25);
        cout << left << "Code Abonne";
        cout.width(25);
        cout << left << "Date de sortie";
        cout.width(25);
        cout << left << "Date d'entree" << endl;
        cout << string(117, '-') << endl;

        int ligne = 0;

        // do
        // {
        //     if (prets.read((char *)&info_pret, sizeof(info_pret)))
        //     {
        //         if (abonnes.read((char *)&info_abonne, sizeof(info_abonne)))
        //         {
        //             while (!abonnes.eof())
        //             {
        //                 if (info_pret.code_abonne == info_abonne.nif)
        //                 {
        //                     cout.width(5);
        //                     cout << left << info_abonne.nif;
        //                     cout.width(30);
        //                     cout << left << info_abonne.prenom;
        //                     cout.width(25);
        //                     cout << left << info_abonne.nom;
        //                     cout.width(20);
        //                     cout << left << info_abonne.adresse;
        //                     cout.width(17);
        //                     cout << left << info_abonne.phone;
        //                     cout.width(20);
        //                     cout << right << info_abonne.date_inscription << endl;
        //                     ligne++;
        //                     if (ligne == 20)
        //                     {
        //                         cout << "\n Appuyez sur une touche pour continuer...";
        //                         getch();
        //                         ligne = 0;
        //                         system("cls");
        //                     }
        //                 }
        //                 break;
        //             }
        //         }
        //     }
        // } while (!prets.eof());


        do
        {
            if (prets.read((char *)&info_pret, sizeof(info_pret)))
            {
                cout.width(10);
                cout << left << info_pret.numero;
                cout.width(15);
                cout << left << info_pret.code_ouvrage;
                cout.width(25);
                cout << left << info_pret.code_abonne;
                cout.width(25);
                cout << left << info_pret.date_sortie;
                cout.width(25);
                cout << left << info_pret.date_entree << endl;
                ligne++;
                if (ligne == 20)
                {
                    cout << "\n Appuyez sur une touche pour continuer...";
                    getch();
                    ligne = 0;
                    system("cls");
                }
            }
        } while (!prets.eof());

        prets.close();
        cout << "\n Fin de l'Affichage. Appuyez sur une Enter pour quitter.";
        getch();
        prets.close();
        // abonnes.close();
        // cout << "\n Fin de l'Affichage. Appuyez sur une Enter pour revenir au menu principal.";
        // getch();
        menu();
    }
    
    void afficherTotalPretsAbonnes()
{
    char vcode[25];
    int trouver = 0;

    fstream prets("prets.dat", ios::in | ios::binary);
    fstream ouvrages("ouvrages.dat", ios::in | ios::binary);

    if (!prets)
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier 'prets.dat'.\n";
        return;
    }
    if (!ouvrages)
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier 'ouvrages.dat'.\n";
        return;
    }

    system("cls");
    cout << "\n Entrer le code (NIF) de l'abonne : ";
    cin >> vcode;

    system("cls");
    cout << "\n";
    cout.width(75);
    cout << right << "Liste des ouvrages pretes par l'abonne (" << vcode << ") :\n";
    cout << setw(82) << right << string(50, '=') << "\n\n";

    cout.width(5);
    cout << left << "Code";
    cout.width(30);
    cout << left << "Titre";
    cout.width(25);
    cout << left << "Auteur";
    cout.width(20);
    cout << left << "Discipline";
    cout.width(17);
    cout << left << "Date d'arrivage";
    cout.width(20);
    cout << right << "Provenance" << endl;
    cout << string(117, '-') << endl;

    // Lecture du fichier "prets.dat" pour vérifier les prêts de l'abonné
    while (prets.read((char *)&info_pret, sizeof(info_pret)))
    {
        if (strcmp(info_pret.code_abonne, vcode) == 0) // Correspondance trouvée
        {
            trouver = 1;
            char code_ouvrage[10];
            strcpy(code_ouvrage, info_pret.code_ouvrage);

            // Recherche dans "ouvrages.dat" pour trouver les informations de l'ouvrage
            ouvrages.clear(); // Réinitialiser le curseur
            ouvrages.seekg(0, ios::beg);

            while (ouvrages.read((char *)&info_ouvrage, sizeof(info_ouvrage)))
            {
                if (strcmp(info_ouvrage.code, code_ouvrage) == 0)
                {
                    // Afficher les informations de l'ouvrage
                    cout.width(5);
                    cout << left << info_ouvrage.code;
                    cout.width(30);
                    cout << left << info_ouvrage.titre;
                    cout.width(25);
                    cout << left << info_ouvrage.auteur;
                    cout.width(20);
                    cout << left << info_ouvrage.discipline;
                    cout.width(17);
                    cout << left << info_ouvrage.date_arrivage;
                    cout.width(20);
                    cout << right << info_ouvrage.provenance << endl;
                    break;
                }
            }
        }
    }

    // Si aucun prêt n'a été trouvé
    if (!trouver)
    {
        cout << " Aucun pret actif trouve pour cet abonne.\n";
    }

    // Fermeture des fichiers
    prets.close();
    ouvrages.close();

    cout << "\n Fin de l'affichage. Appuyez sur une touche pour revenir au menu principal.";
    getch();
    menu();
}

    void recherchePretParAbonne()
    {
        char vcode[25];
        int trouver = 0;
        system("cls");
        fstream prets("prets.dat", ios::in);
        cout << "\n Entrer le code de l'abonne (NIF) : ";
        cin.getline(vcode, sizeof(vcode));
        cout << right << "Liste des Ouvrages Pretes Par l'Abonne Identifie par le NIF : " << vcode << "\n\n";

        // Rewrited header
        cout.width(5);
        cout << left << "Code";
        cout.width(30);
        cout << left << "Titre";
        cout.width(25);
        cout << left << "Auteur";
        cout.width(20);
        cout << left << "Discipline";
        cout.width(17);
        cout << left << "Date d'arrivage";
        cout.width(20);
        cout << right << "Provenance" << endl;
        cout << string(117, '-') << endl;
        do
        {
            if (prets.read((char *)&info_pret, sizeof(info_pret)))
            {
                if (strcmp(info_pret.code_abonne, vcode) == 0)
                {
                    trouver = 1;
                    LesOuvrages y;
                    system("cls");
                    y.afficherOuvrage(info_pret.code_ouvrage);
                    // cout << "\n Voici l'information pour l'abonne ayant le NIF : " << vcode << endl;
                    // cout << setw(22) << "\n NIF " << ": " << info_abonne.nif;
                    // cout << setw(22) << "\n Prenom " << ": " << info_abonne.prenom;
                    // cout << setw(22) << "\n Nom " << ": " << info_abonne.nom;
                    // cout << setw(22) << "\n Adresse " << ": " << info_abonne.adresse;
                    // cout << setw(22) << "\n Telephone " << ": " << info_abonne.phone;
                    // cout << setw(22) << "\n Date d'inscription " << ": " << info_abonne.date_inscription << endl;
                    // cout << "\n Appuyez sur Enter pour revenir au menu principal.";
                    // getch();
                    // break;
                }
            }
        } while (!prets.eof());
        prets.close();
        if (trouver == 0)
        {
            cout << "\n Aucun pret trouve pour cet utilisateur.";
        }
        getch();
        menu();
    }


void listerAbonnesEnContravention() {
    // Ouverture des fichiers
    std::ifstream prets("prets.dat", std::ios::binary);
    std::ifstream abonnes("abonnes.dat", std::ios::binary);

    if (!prets) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier 'prets.dat'.\n";
        return;
    }
    if (!abonnes) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier 'abonnes.dat'.\n";
        return;
    }

    // Récupérer la date actuelle
    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    char date_actuelle[11];
    std::strftime(date_actuelle, sizeof(date_actuelle), "%Y-%m-%d", now);

    // Fonction pour calculer la différence en jours entre deux dates
    auto calculerDifferenceJours = [](const char* date1, const char* date2) -> int {
        std::tm tm1 = {}, tm2 = {};
        if (!parseDate(date1, tm1) || !parseDate(date2, tm2)) {
            std::cerr << "Erreur : Format de date invalide.\n";
            return 0; // Si les dates sont invalides, retourner 0
        }
        time_t time1 = mktime(&tm1);
        time_t time2 = mktime(&tm2);
        return static_cast<int>(difftime(time2, time1) / (60 * 60 * 24));
    };

    // Affichage du titre
    system("cls");
    cout << "\n";
    cout.width(60);
    cout << right << "Liste des abonnes en contravention\n";
    cout << std::string(80, '-') << "\n";
    cout << std::left << setw(10) << "NIF"
              << setw(25) << "Nom"
              << setw(25) << "Prenom"
              << setw(15) << "Jours de retard\n";
    cout << std::string(80, '-') << "\n";

    // Parcourir le fichier "prets.dat"
    Pret info_pret; 
    while (prets.read(reinterpret_cast<char*>(&info_pret), sizeof(info_pret))) {
        int jours_ecoules = calculerDifferenceJours(info_pret.date_sortie, date_actuelle);
        if (jours_ecoules > 15) {
            // L'abonné est en contravention, rechercher ses informations dans "abonnes.dat"
            Abonne info_abonne; 
            abonnes.clear();
            abonnes.seekg(0, std::ios::beg);
            while (abonnes.read(reinterpret_cast<char*>(&info_abonne), sizeof(info_abonne))) {
                if (strcmp(info_abonne.nif, info_pret.code_abonne) == 0) {
                    // Affichage des infos abonné
                    cout << std::left << setw(10) << info_abonne.nif
                              << setw(25) << info_abonne.nom
                              << setw(25) << info_abonne.prenom
                              << setw(15) << jours_ecoules - 15 << "\n";
                    break;
                }
            }
        }
    }

    prets.close();
    abonnes.close();

    cout << "\nFin de l'affichage. Appuyez sur une touche pour revenir au menu principal.";
    getch();
    menu(); 
}


};

void moduleOuvrages() {
    LesOuvrages x;
    x.creerFichierOuvrage();
    char choix;
    bool quitter = false;

    system("cls");
    cout << "\n";
    cout << setw(72) << right << "GESTION DE SOPHIA-BIBLIO\n";
    cout << setw(68) << right << "MODULE OUVRAGES\n";
    cout << setw(71) << right << string(24, '=') << "\n\n";

    cout << left;
    cout.width(5);  cout << " 1.";  cout << " Ajouter un ouvrage\n";
    cout.width(5);  cout << " 2.";  cout << " Rechercher un ouvrage\n";
    cout.width(5);  cout << " 3.";  cout << " Modifier un ouvrage\n";
    cout.width(5);  cout << " 4.";  cout << " Supprimer un ouvrage\n";
    cout.width(5);  cout << " 5.";  cout << " Liste des ouvrages d'un auteur specifique\n";
    cout.width(5);  cout << " 6.";  cout << " Liste des ouvrages d'une discipline specifique\n";
    cout.width(5);  cout << " 7.";  cout << " Liste des ouvrages par ordre alphabetique\n";
    cout.width(5);  cout << " 8."; cout << " Quitter (Cliquez sur 0)\n\n";

    cout << " Veuillez choisir une option : ";

    while (!quitter) {
        choix = getch();

        switch (choix) {
            case '1': x.ajouterOuvrage(); break;
            case '2': x.rechercheOuvrage(); break;
            case '3': x.modifierOuvrage(); break;
            case '4': x.supprimerOuvrage(); break;
            case '5': x.rechercheOuvragesParAuteur(); break;
            case '6': x.rechercheDiscipline(); break;
            case '7': x.afficherOuvragesTriesParTitre(); break;
            case '8':
                cout << "Quitter le programme. Au revoir !\n";
                quitter = true;
                break;
            default:
                cout << "Option invalide. Veuillez réessayer.\n";
        }
        cout << "\n";
    }
}

void moduleAbonnes() {
    LesAbonnes x;
    x.creerFichierAbonne();
    char choix;
    bool quitter = false;

    system("cls");
    cout << "\n";
    cout << setw(72) << right << "GESTION DE SOPHIA-BIBLIO\n";
    cout << setw(68) << right << "MODULE ABONNES\n";
    cout << setw(71) << right << string(24, '=') << "\n\n";

    cout << left;
    cout.width(5);  cout << " 1.";  cout << " Ajouter un abonne\n";
    cout.width(5);  cout << " 2.";  cout << " Rechercher un abonne\n";
    cout.width(5);  cout << " 3.";  cout << " Modifier un abonne\n";
    cout.width(5);  cout << " 4.";  cout << " Supprimer un abonne\n";
    cout.width(5);  cout << " 5.";  cout << " Liste des abonnes par ordre alphabetique\n";
    cout.width(5);  cout << " 6."; cout << " Quitter (Cliquez sur 0)\n\n";

    cout << " Veuillez choisir une option : ";

    while (!quitter) {
        choix = getch();

        switch (choix) {
            case '1': x.ajouterAbonne(); break;
            case '2': x.rechercheAbonne(); break;
            case '3': x.modifierAbonne(); break;
            case '4': x.supprimerAbonne(); break;
            case '5': x.afficherAbonnesTriesParNom(); break;
            case '6': case '0':
                cout << "Quitter le programme. Au revoir !\n";
                quitter = true;
                exit(0);
            default:
                cout << "Option invalide. Veuillez réessayer.\n";
        }
        cout << "\n";
    }
}

void modulePrets() {
    Prets x;
    x.creerFichierPret();
    char choix;
    bool quitter = false;

    system("cls");
    cout << "\n";
    cout << setw(72) << right << "GESTION DE SOPHIA-BIBLIO\n";
    cout << setw(66) << right << "MODULE PRETS\n";
    cout << setw(71) << right << string(24, '=') << "\n\n";

    cout << left;
    cout.width(5);  cout << " 1.";  cout << " Preter un ouvrage\n";
    cout.width(5);  cout << " 2.";  cout << " Remettre un ouvrage\n";
    cout.width(5);  cout << " 3.";  cout << " Liste des abonnes n'ayant pas encore remis leur ouvrage\n";
    cout.width(5);  cout << " 4.";  cout << " Liste des abonnes en contravention\n";
    cout.width(5);  cout << " 5."; cout << " Liste des ouvrages pretes par un abonne\n";
    cout.width(5);  cout << " 6."; cout << " Quitter (Cliquez sur 0)\n\n";

    cout << " Veuillez choisir une option : ";

    while (!quitter) {
        choix = getch();

        switch (choix) {
            case '1': x.enregistrerPret(); break;
            case '2': x.suppressionPret(); break;
            case '3': x.afficherPreteurs(); break;
            case '4': x.listerAbonnesEnContravention(); break;
            case '5': x.afficherTotalPretsAbonnes(); break;
            case '6': case '0':
                cout << "Quitter le programme. Au revoir !\n";
                quitter = true;
                exit(0);
            default:
                cout << "Option invalide. Veuillez réessayer.\n";
        }
        cout << "\n";
    }
}

void menu() {
    char choix;
    bool quitter = false;
    system("cls");
    cout << "\n";
    cout << setw(80) << right << "GESTION DE SOPHIA-BIBLIO | MENU PRINCIPAL\n";
    cout << setw(79) << right << string(41, '=') << "\n\n";

    cout << left;
    cout.width(5);  cout << " 1.";  cout << " Gestion des ouvrages (Ajouter, Rechercher, Modifier, Supprimer, etc.)\n";
    cout.width(5);  cout << " 2.";  cout << " Gestion des abonnes (Ajouter, Rechercher, Modifier, Supprimer, etc.)\n";
    cout.width(5);  cout << " 3.";  cout << " Gestion des prets (Preter un ouvrage, Remettre un ouvrage, etc.)\n";
    cout.width(5);  cout << " 4."; cout << " Quitter (Cliquez sur 0)\n\n";

    cout << " Veuillez choisir une option : ";

    while (!quitter) {
        choix = getch();

        switch (choix) {
            case '1': moduleOuvrages(); break;
            case '2': moduleAbonnes(); break;
            case '3': modulePrets(); break;
            case '4': case '0':
                cout << "Quitter le programme. Au revoir !\n";
                quitter = true;
                exit(0);
            default:
                cout << "Option invalide. Veuillez réessayer.\n";
        }
        cout << "\n";
    }
}


int main()
{
    menu();
    return 0;
}