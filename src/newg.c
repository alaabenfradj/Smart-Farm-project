#include "newg.h"
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>


enum
{
EID,
ETYPE,
EVALMAX,
EVALMIN,
EETAT,
EJOUR,
EMOIS,
EANNEE,
EEMPLACEMENT,
COLUMNS,
};



////////////////////////////////////////////////////////////////////////////////////////////

int login_verif (char login_ins[],char mdp_ins[])
{
int yes =-1;

FILE *f=NULL;
char nom_yes[20];
char prenom_yes[20];
char login_yes[20];
char mdp_yes[20];

f=fopen("inscription.txt","r");
if (f!=NULL)
{
while(fscanf(f,"%s %s %s %s \n",nom_yes,prenom_yes,login_yes,mdp_yes)!=EOF)
{
if((strcmp(login_yes,login_ins)==0)&&(strcmp(mdp_yes,mdp_ins)==0))
yes=1;
}
fclose(f);
}
return yes ;
}


/////////////////////////////////////////////////////////////////////////////////////////////

void ajouter_capteur(capteur c)
{
   FILE *f;
   FILE *max;
   int x ;
   f=fopen("capteur.txt","a+");
   
   if (f!=NULL)
   {
       fprintf(f,"%d %s %.2f %.2f %s %d %d %d %s\n",c.id,c.type,c.Vmax,c.Vmin,c.etat,c.d.jour,c.d.mois,c.d.annee,c.emplacement);

   fclose(f);
   }
   else
        printf("impossible d ouvrir le fichier");
}

void supprimer_capteur(int identifiant,int jour,int mois , int annee,capteur c)
{
	
    
    FILE *f,*ft;
    f=fopen("capteur.txt","r");
    ft=fopen("tmp.txt","a+");
    if (f!=NULL)
    {
        while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
        {
            if ((identifiant!=c.id)||(jour!=c.d.jour)||(mois!=c.d.mois)||(annee!=c.d.annee))
                fprintf(ft,"%d %s %.2f %.2f %s %d %d %d %s\n",c.id,c.type,c.Vmax,c.Vmin,c.etat,c.d.jour,c.d.mois,c.d.annee,c.emplacement);

        }
    }
    fclose(f);
    fclose(ft);
    remove("capteur.txt");
    rename("tmp.txt","capteur.txt");

}

void chercher_capteursbyID(int capt)
{
    capteur c;
    FILE *f;
    FILE *che;
    f=fopen("capteur.txt","r");
    che=fopen("chercher.txt","w");
    if (f!=NULL)
    {
       while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
            {
                if (capt==c.id)
                  {
                    fprintf(che,"%d %s %.2f %.2f %s %d %d %d %s\n",c.id,c.type,c.Vmax,c.Vmin,c.etat,c.d.jour,c.d.mois,c.d.annee,c.emplacement);
                  }
            }
    }
    else
    printf("Erreur");

    fclose(f);
    fclose(che);
}

/*int chercher_capteursdiff(char etat)
{
    capteur c;
    FILE *f;
    FILE *d;
    f=fopen("capteur.txt","r");
    d=fopen("diffectueux.txt","w");
    if (f!=NULL)
    {
        while(fscanf(f,"%d %s %f %s %d %d %d",&c.id,c.type,&c.valeur,c.etat,&c.d.jour,&c.d.mois,&c.d.annee)!=EOF)
            {
                if (strcmp("PANNE",c.etat)==0)
                  {
                    fprintf(d,"%d %s %.2f %s %d %d %d\n",c.id,c.type,c.valeur,c.etat,c.d.jour,c.d.mois,c.d.annee);
                  }
            }
    }
    else
    printf("Erreur");

    fclose(f);
    fclose(d);
}
void modifier_capteur(int cpt,capteur c)
{

  
    FILE *f;
    FILE *ft;
    f=fopen("capteur.txt","r");
    ft=fopen("tmp.txt","w");
    if (f!=NULL)
    {
        while(fscanf(f,"%d %s %f %f %s %d %d %d",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee)!=EOF)
        {
            if (cpt==c.id)
            {

                fprintf(ft,"%d %s %.2f %s %d %d %d\n",c.id,c.type,c.valeur,c.etat,c.d.jour,c.d.mois,c.d.annee);
            }
            else
                fprintf(ft,"%d %s %.2f %s %d %d %d\n",c.id,c.type,c.valeur,c.etat,c.d.jour,c.d.mois,c.d.annee);

        }
    }
    fclose(f);
    fclose(ft);
    remove("capteur.txt");
    rename("tmp.txt","capteur.txt");
}
*/


void afficher_capteurs(GtkWidget *liste)
{


	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
char type [30];
float vmax ;
float vmin ;
char etat [30] ;	
int jour ,mois , annee ;
char emplacement[30];

capteur c;
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",EID,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Type",renderer,"text",ETYPE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("ValeurMax",renderer,"text",EVALMAX,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("ValeurMin",renderer,"text",EVALMIN,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Etat",renderer,"text",EETAT,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",EJOUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",EMOIS,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",EANNEE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("MARQUE",renderer,"text",EEMPLACEMENT,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

}

store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_FLOAT,G_TYPE_FLOAT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING);

f=fopen("capteur.txt","r");
if (f==NULL)
return;

else 
{
f=fopen("capteur.txt","a+");
while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
{
ident=c.id;
strcpy(type,c.type);
vmax=c.Vmax;
vmin=c.Vmin;
strcpy(etat,c.etat);
jour=c.d.jour;
mois=c.d.mois;
annee=c.d.annee;
strcpy(emplacement,c.emplacement);


gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,EID,ident,ETYPE,type,EVALMAX,vmax,EVALMIN,vmin,EETAT,etat,EJOUR,jour,EMOIS,mois,EANNEE,annee,EEMPLACEMENT,emplacement,-1);
}

fclose (f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}


}



void afficher_capteurs2(GtkWidget *liste)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
char type [30];
float vmax ;
float vmin ;
char etat [30] ;	
int jour ,mois , annee ;
char emplacement[30];

capteur c;
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",EID,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Type",renderer,"text",ETYPE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("ValeurMax",renderer,"text",EVALMAX,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("ValeurMin",renderer,"text",EVALMIN,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Etat",renderer,"text",EETAT,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",EJOUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",EMOIS,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",EANNEE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("MARQUE",renderer,"text",EEMPLACEMENT,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

}

store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_FLOAT,G_TYPE_FLOAT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING);

f=fopen("chercher.txt","r");
if (f==NULL)
return;

else 
{
f=fopen("chercher.txt","a+");
while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
{
ident=c.id;
strcpy(type,c.type);
vmax=c.Vmax;
vmin=c.Vmin;
strcpy(etat,c.etat);
jour=c.d.jour;
mois=c.d.mois;
annee=c.d.annee;
strcpy(emplacement,c.emplacement);

gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,EID,ident,ETYPE,type,EVALMAX,vmax,EVALMIN,vmin,EETAT,etat,EJOUR,jour,EMOIS,mois,EANNEE,annee,EEMPLACEMENT,emplacement,-1);
}

fclose (f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}


}

void afficher_capteurs3(GtkWidget *liste)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
char type [30];
float vmax ;
float vmin ;
char etat [30] ;	
int jour ,mois , annee ;
char emplacement[30];

capteur c;
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",EID,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Type",renderer,"text",ETYPE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("ValeurMax",renderer,"text",EVALMAX,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("ValeurMin",renderer,"text",EVALMIN,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Etat",renderer,"text",EETAT,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",EJOUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",EMOIS,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",EANNEE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("MARQUE",renderer,"text",EEMPLACEMENT,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

}

store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_FLOAT,G_TYPE_FLOAT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING);

f=fopen("diffectueux.txt","r");
if (f==NULL)
return;

else 
{
f=fopen("diffectueux.txt","a+");
while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
{
ident=c.id;
strcpy(type,c.type);
vmax=c.Vmax;
vmin=c.Vmin;
strcpy(etat,c.etat);
jour=c.d.jour;
mois=c.d.mois;
annee=c.d.annee;
strcpy(emplacement,c.emplacement);

gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,EID,ident,ETYPE,type,EVALMAX,vmax,EVALMIN,vmin,EETAT,etat,EJOUR,jour,EMOIS,mois,EANNEE,annee,EEMPLACEMENT,emplacement,-1);
}

fclose (f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}


}

void afficher_capteurs4(GtkWidget *liste)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
char type [30];
float vmax ;
float vmin ;
char etat [30] ;	
int jour ,mois , annee ;
char emplacement[30];

capteur c;
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",EID,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Type",renderer,"text",ETYPE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("ValeurMax",renderer,"text",EVALMAX,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("ValeurMin",renderer,"text",EVALMIN,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Etat",renderer,"text",EETAT,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",EJOUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",EMOIS,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",EANNEE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("MARQUE",renderer,"text",EEMPLACEMENT,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

}

store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_FLOAT,G_TYPE_FLOAT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING);

f=fopen("ok.txt","r");
if (f==NULL)
return;

else 
{
f=fopen("ok.txt","a+");
while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
{
ident=c.id;
strcpy(type,c.type);
vmax=c.Vmax;
vmin=c.Vmin;
strcpy(etat,c.etat);
jour=c.d.jour;
mois=c.d.mois;
annee=c.d.annee;
strcpy(emplacement,c.emplacement);

gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,EID,ident,ETYPE,type,EVALMAX,vmax,EVALMIN,vmin,EETAT,etat,EJOUR,jour,EMOIS,mois,EANNEE,annee,EEMPLACEMENT,emplacement,-1);
}

fclose (f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}


}


//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////partie 2////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////



enum
{

TID,
TJOUR,
TMOIS,
TANNEE,
TVAL,
};


void afficher_capteurs_temp(GtkWidget *liste)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
int jour ,mois , annee ;
float valeur ;


alarmant a;
store=NULL;
FILE *f,*t;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",TID,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",TJOUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",TMOIS,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",TANNEE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Valeur",renderer,"text",TVAL,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


}

store=gtk_list_store_new(5,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_FLOAT);

f=fopen("temperature.txt","r");
//t=fopen("tempdse.txt","w");
if (f==NULL)
return;

else 
{
f=fopen("temperature.txt","r");
while(fscanf(f,"%d %d %d %d %f",&a.id,&a.jo,&a.mo,&a.an,&a.val)!=EOF)
{




ident=a.id;
jour=a.jo;
mois=a.mo;
annee=a.an;
valeur=a.val;

//fprintf(t,"%d %d %d %d %f\n",ident,jour,mois,annee,valeur);
gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,TID,ident,TJOUR,jour,TMOIS,mois,TANNEE,annee,TVAL,valeur,-1);
}

fclose (f);
//fclose (t);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}


}


enum
{

TID1,
TJOUR1,
TMOIS1,
TANNEE1,
TVAL1,
};

void afficher_capteurs_hum(GtkWidget *liste)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
int jour ,mois , annee ;
float valeur ;


alarmant a;
store=NULL;
FILE *f,*t;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",TID1,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",TJOUR1,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",TMOIS1,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",TANNEE1,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Valeur",renderer,"text",TVAL1,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


}

store=gtk_list_store_new(5,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_FLOAT);

f=fopen("humidite.txt","r");
//t=fopen("tempdse.txt","w");
if (f==NULL)
return;

else 
{
f=fopen("humidite.txt","r");
while(fscanf(f,"%d %d %d %d %f",&a.id,&a.jo,&a.mo,&a.an,&a.val)!=EOF)
{




ident=a.id;
jour=a.jo;
mois=a.mo;
annee=a.an;
valeur=a.val;


gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,TID1,ident,TJOUR1,jour,TMOIS1,mois,TANNEE1,annee,TVAL1,valeur,-1);
}

fclose (f);

gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}


}


void chercher_alamantes_temp(int j,int m, int a)
{

capt c;
 FILE *f=NULL,*g=NULL;
 g=fopen("Alarm_temp.txt","w");
 f=fopen("temperature.txt","r");

  if(f==NULL)
  return;
 else
 {
  while(fscanf(f, "%d %d %d %d %f\n",&c.id,&c.jour,&c.mois,&c.annee,&c.valeur)!=EOF)
  {
if((a==c.annee)&&(m==c.mois)&&(c.jour==j)){
   if(c.valeur<0 || c.valeur>45 )
    {
     if(g==NULL)
      {
       return;
      }
     else
      {
       fprintf(g,"%d %d %d %d %.2f\n",c.id,c.jour,c.mois,c.annee,c.valeur);
      }
    }
    }
 }
  fclose(f);
  fclose(g);
 }
}

void chercher_alamantes_humid(int jr,int mo, int an)
{

capt c;
 FILE *f=NULL,*g=NULL;
 g=fopen("Alarm_hum.txt","w");
 f=fopen("humidite.txt","r");

  if(f==NULL)
  return;
 else
 {
  while(fscanf(f, "%d %d %d %d %f\n",&c.id,&c.jour,&c.mois,&c.annee,&c.valeur)!=EOF)
  {
if((an==c.annee)&&(mo==c.mois)&&(c.jour==jr)){
   if(c.valeur<20 || c.valeur>150 )
    {
     if(g==NULL)
      {
       return;
      }
     else
      {
       fprintf(g,"%d %d %d %d %.2f\n",c.id,c.jour,c.mois,c.annee,c.valeur);
      }
    }
    }
 }
  fclose(f);
  fclose(g);
 }
}



enum
{

TID3,
TJOUR3,
TMOIS3,
TANNEE3,
TVAL3,
};




void afficher_capteurs_temp_alarm(GtkWidget *liste)
{


	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
int jour ,mois , annee ;
float valeur ;


alarmant a;
store=NULL;
FILE *f,*t;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",TID3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",TJOUR3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",TMOIS3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",TANNEE3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Valeur",renderer,"text",TVAL3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


}

store=gtk_list_store_new(5,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_FLOAT);

f=fopen("Alarm_temp.txt","r");

if (f==NULL)
return;

else 
{
f=fopen("Alarm_temp.txt","r");
while(fscanf(f,"%d %d %d %d %f",&a.id,&a.jo,&a.mo,&a.an,&a.val)!=EOF)
{




ident=a.id;
jour=a.jo;
mois=a.mo;
annee=a.an;
valeur=a.val;


gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,TID3,ident,TJOUR3,jour,TMOIS3,mois,TANNEE3,annee,TVAL3,valeur,-1);
}

fclose (f);

gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}



}


enum
{

TIDH,
TJOURH,
TMOISH,
TANNEEH,
TVALH,
};


void afficher_capteurs_hum_alarm(GtkWidget *liste)
{


	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
int jour ,mois , annee ;
float valeur ;


alarmant a;
store=NULL;
FILE *f,*t;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",TIDH,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",TJOURH,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",TMOISH,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",TANNEEH,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Valeur",renderer,"text",TVALH,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


}

store=gtk_list_store_new(5,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_FLOAT);

f=fopen("Alarm_hum.txt","r");

if (f==NULL)
return;

else 
{
f=fopen("Alarm_hum.txt","r");
while(fscanf(f,"%d %d %d %d %f",&a.id,&a.jo,&a.mo,&a.an,&a.val)!=EOF)
{




ident=a.id;
jour=a.jo;
mois=a.mo;
annee=a.an;
valeur=a.val;


gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,TIDH,ident,TJOURH,jour,TMOISH,mois,TANNEEH,annee,TVALH,valeur,-1);
}

fclose (f);

gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}



}



void chercher_plus_alamantes_temp()
{

capt c;
 FILE *f=NULL,*g=NULL;
 g=fopen("Alarm_temp_plus.txt","w");
 f=fopen("temperature.txt","r");
int id ;
  if(f==NULL)
  return;
 else
 {
  while(fscanf(f, "%d %d %d %d %f\n",&c.id,&c.jour,&c.mois,&c.annee,&c.valeur)!=EOF)
  {
if((c.id==3)||(c.id==5)||(c.id==7)){
   if(c.valeur<0 || c.valeur>45 )
    {
     if(g==NULL)
      {
       return;
      }
     else
      {
       fprintf(g,"%d %d %d %d %.2f\n",c.id,c.jour,c.mois,c.annee,c.valeur);
      }
    }
    }
 }
  fclose(f);
  fclose(g);
 }
}




void afficher_capteurs_temp_plus_alarm(GtkWidget *liste)
{


	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
int jour ,mois , annee ;
float valeur ;


alarmant a;
store=NULL;
FILE *f,*t;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",TID3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",TJOUR3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",TMOIS3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",TANNEE3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Valeur",renderer,"text",TVAL3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


}

store=gtk_list_store_new(5,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_FLOAT);

f=fopen("Alarm_temp_plus.txt","r");

if (f==NULL)
return;

else 
{
f=fopen("Alarm_temp_plus.txt","r");
while(fscanf(f,"%d %d %d %d %f",&a.id,&a.jo,&a.mo,&a.an,&a.val)!=EOF)
{




ident=a.id;
jour=a.jo;
mois=a.mo;
annee=a.an;
valeur=a.val;


gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,TID3,ident,TJOUR3,jour,TMOIS3,mois,TANNEE3,annee,TVAL3,valeur,-1);
}

fclose (f);

gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}



}






void chercher_plus_alamantes_hum()
{

capt c;
 FILE *f=NULL,*g=NULL;
 g=fopen("Alarm_hum_plus.txt","w");
 f=fopen("humidite.txt","r");
int id ;
  if(f==NULL)
  return;
 else
 {
  while(fscanf(f, "%d %d %d %d %f\n",&c.id,&c.jour,&c.mois,&c.annee,&c.valeur)!=EOF)
  {
if((c.id==3)||(c.id==5)||(c.id==7)){
   if( c.valeur>100 )
    {
     if(g==NULL)
      {
       return;
      }
     else
      {
       fprintf(g,"%d %d %d %d %.2f\n",c.id,c.jour,c.mois,c.annee,c.valeur);
      }
    }
    }
 }
  fclose(f);
  fclose(g);
 }
}




void afficher_capteurs_hum_plus_alarm(GtkWidget *liste)
{


	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

int ident;
int jour ,mois , annee ;
float valeur ;


alarmant a;
store=NULL;
FILE *f,*t;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",TID3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",TJOUR3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",TMOIS3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",TANNEE3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new();
column =gtk_tree_view_column_new_with_attributes("Valeur",renderer,"text",TVAL3,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


}

store=gtk_list_store_new(5,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_FLOAT);

f=fopen("Alarm_hum_plus.txt","r");

if (f==NULL)
return;

else 
{
f=fopen("Alarm_hum_plus.txt","r");
while(fscanf(f,"%d %d %d %d %f",&a.id,&a.jo,&a.mo,&a.an,&a.val)!=EOF)
{




ident=a.id;
jour=a.jo;
mois=a.mo;
annee=a.an;
valeur=a.val;


gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,TID3,ident,TJOUR3,jour,TMOIS3,mois,TANNEE3,annee,TVAL3,valeur,-1);
}

fclose (f);

gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}



}












void marquedef()
{
FILE *f=fopen("capteur.txt","r");
FILE *fc=fopen("marquedef.txt","a+");
capteur c;
if(f==NULL)
return;

else
{
while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
if(strcmp(c.etat,"PANNE")==0)
{
 fprintf(fc,"%d %s %.2f %.2f %s %d %d %d %s\n",c.id,c.type,c.Vmax,c.Vmin,c.etat,c.d.jour,c.d.mois,c.d.annee,c.emplacement);
                  
}
}

 fclose(f);
 fclose(fc);

}
/*
int nmbrmarque()
{
FILE *f=fopen("marquedef.txt","r");
if(f==NULL)
return;
int A=0,B=0,C=0;
else
{
while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
{
if(strcmp("FarmTRX",c.emplacement)==0)
A++;
if(strcmp("MC_Sieve_Sensor",c.emplacement)==0)
B++;
if(strcmp("TOPCON",c.emplacement)==0)
C++;
}

   if ( A > B && A > C )
      printf("%d is the largest.", a);
   else if ( b > a && b > c )
      printf("%d is the largest.", b);
   else if ( c > a && c > b )
      printf("%d is the largest.", c);
   else   
      printf("Values are not unique");


}


}
*/
/*


FarmTRX
MC_Sieve_Sensor
TOPCON

capteur c;
    FILE *f;
    FILE *che;
    f=fopen("capteur.txt","r");
    che=fopen("chercher.txt","w");
    if (f!=NULL)
    {
       while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
            {
                if (capt==c.id)
                  {
                    fprintf(che,"%d %s %.2f %.2f %s %d %d %d %s\n",c.id,c.type,c.Vmax,c.Vmin,c.etat,c.d.jour,c.d.mois,c.d.annee,c.emplacement);
                  }
            }
    }
    else
    printf("Erreur");

    fclose(f);
    fclose(che);
*/





