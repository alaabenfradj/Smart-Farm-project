#ifndef GESTION_H_INCLUDED
#define GESTION_H_INCLUDED
#include <gtk/gtk.h>



typedef struct{
int jour ;
int mois ;
int annee ;
}date ;

typedef struct{
int id;
char type[30];
float Vmax ;
float Vmin ;
char etat[30] ;
date d;
char emplacement[30];
}capteur;




int login_verif (char login_ins[],char mdp_ins[]);
void ajouter_capteur(capteur c);
void supprimer_capteur(int identifiant,int jour,int mois , int annee,capteur c);
void chercher_capteursbyID(int capt);
void modifier_capteur(int cpt,capteur c);
int chercher_capteursdiff(char etat);

void afficher_capteurs(GtkWidget *liste);
void afficher_capteurs2(GtkWidget *liste);
void afficher_capteurs3(GtkWidget *liste);
void afficher_capteurs4(GtkWidget *liste);


///////////////////////////////////////////////////partie2/////////////////////////////////////////////////

typedef struct {
int id ;
int jo ;
int mo;
int an;
float val;
}alarmant ;


typedef struct
{
int id;
int jour;
int mois ;
int annee;
float valeur;
}capt;

void afficher_capteurs_temp(GtkWidget *liste);
void afficher_capteurs_hum(GtkWidget *liste);

void chercher_alamantes_temp(int j,int m, int a);
void chercher_alamantes_humid(int jr,int mo, int an);

void afficher_capteurs_temp_alarm(GtkWidget *liste);
void afficher_capteurs_hum_alarm(GtkWidget *liste);


void afficher_capteurs_temp_plus_alarm(GtkWidget *liste);
void chercher_plus_alamantes_temp();

void afficher_capteurs_hum_plus_alarm(GtkWidget *liste);
void chercher_plus_alamantes_hum();

void marquedef();
#endif // GESTION_H_INCLUDED
