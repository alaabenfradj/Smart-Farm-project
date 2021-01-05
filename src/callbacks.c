#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "newg.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int x,y ;
int idf;
char vmaxi[30];
char vmini[30];
char typef[30];
char etatf[30];
int  jf ,mf,af;
char emplacementf[30];



void
on_inscrire_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
FILE *f=NULL;
	GtkWidget *t7al ,*tsakker;
	GtkWidget *nom , *prenom ,*login ,*mdp;

char nom1 [20];
char prenom1[20];
char login1[20] ;
char mdp1[20];
nom = lookup_widget (objet, "entry_nom_ins");
prenom = lookup_widget (objet, "entry_prenom_ins");
login = lookup_widget (objet, "entry_login_ins");
mdp = lookup_widget (objet, "entry_mdp_ins");

strcpy(nom1,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(prenom1,gtk_entry_get_text(GTK_ENTRY(prenom)));
strcpy(login1,gtk_entry_get_text(GTK_ENTRY(login)));
strcpy(mdp1,gtk_entry_get_text(GTK_ENTRY(mdp)));

f=fopen("inscription.txt","a+");

if (f!=NULL)
{
fprintf(f,"%s %s %s %s \n",nom1,prenom1,login1,mdp1);
fclose(f);

}
else 
printf("\n NOT Found");

t7al=create_authentification();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"inscription");
gtk_widget_destroy(tsakker);
}


void
on_connecter_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker,*treeview1;
	GtkWidget *login_Gest,*password_Gest;

char login_G[20] ;
char mdp_G[20];
int LOG_yes;

login_Gest=lookup_widget (objet, "entrylogin");
password_Gest=lookup_widget (objet, "entrymdp");

strcpy(login_G,gtk_entry_get_text(GTK_ENTRY(login_Gest)));
strcpy(mdp_G,gtk_entry_get_text(GTK_ENTRY(password_Gest)));
LOG_yes=login_verif(login_G,mdp_G);

	if(LOG_yes==1)
	{

t7al=create_gestion_capteur();
gtk_widget_show(t7al);

tsakker=lookup_widget(objet,"authentification");
gtk_widget_destroy(tsakker);

treeview1=lookup_widget(t7al,"treeview1");
afficher_capteurs(treeview1);
	}
}


void
on_retoursauthentifier_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
gtk_main_quit();
}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

GtkTreeIter iter;
gint *id;
gchar *type;
gfloat *valeurmax;
gfloat *valeurmin;
gchar *etat;
gint *jour;
gint *mois;
gint *annee;
gchar *emplacement;

GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model,&iter,path));
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&type,2,&valeurmax,3,&valeurmin,4,&etat,5,&jour,6,&mois,7,&annee,8,&emplacement,-1);


idf=id;
strcpy(typef,type);

//valeurf=valeur;
strcpy(etatf,etat);
jf=jour;
mf=mois;
af=annee;
strcpy(emplacementf,emplacement);








////////////////////////////////////////////////////////////////////////////////////////
capteur c ;
/*
FILE *t=fopen("captselected.txt","w");
 if (t!=NULL)
   {
       fprintf(t,"%d %s %.2f %.2f %s %d %d %d %s\n",id,type,valeurmax,valeurmin,etat,jour,mois,annee,emplacement);

   fclose(t);
   }
   else
        printf("impossible d ouvrir le fichier");
*/


}
}


void
on_supprimerg_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker;
t7al=create_supprimer_capteur();
gtk_widget_show (t7al);

tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);


}


void
on_modifierg_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker;
t7al=create_modifier_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);

///////////////////////////////////////////////////////////////////////////
/*GtkTreeSelection *selection ;
GtkTreeModel *model;
GtkTreeIter iter;
GtkWidget *treeView1,*labelvaleur;




gchar* id;
gchar* type;
gchar* valeur;
gchar* etat;
gchar* jour;
gchar* mois;
gchar* annee;

gint index_=-1;

treeView1=lookup_widget(t7al,"treeview1");
selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView1));
if(gtk_tree_selection_get_selected(selection,&model,&iter))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&type,2,&valeur,3,&etat,4,&jour,5,&mois,6,&annee,-1);

valeurf=atof(valeur);

}
char val[30];
sprintf(val,"%f",valeurf);
labelvaleur=lookup_widget(objet,"entry2");
gtk_entry_set_text(GTK_ENTRY(labelvaleur),val);

*/
///////////////////////////////////////////////////////////////////////////

}


void
on_ajouter_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker;
t7al=create_ajouter_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);
}




void
on_retourg_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker;
t7al=create_authentification();
gtk_widget_show (t7al);

tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);
}


void
on_butt_cherch_gest_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *treeview1,*in1 ;
	int capt;

GtkWidget *t7al ,*tsakker;
char ident[30];

in1= lookup_widget(objet,"entry4");
strcpy(ident,gtk_entry_get_text(GTK_ENTRY(in1)));

capt=atoi(ident);

chercher_capteursbyID(capt);

t7al=create_gestion_capteur();
gtk_widget_show (t7al);

treeview1=lookup_widget(t7al,"treeview1");
afficher_capteurs2(treeview1);

tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);

}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=2;} 
}


void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=1;} 
}


void
on_valider_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{

GtkWidget *in1,*in2,*in3,*in4,*in5;
GtkWidget *j,*m,*a;
capteur c;
char valeurD[30],idD[30];


in1= lookup_widget(objet,"entry_identf");//id
in2= lookup_widget(objet,"entry_valeur");//valeurmax
in3= lookup_widget(objet,"combobox7");//etat
in4= lookup_widget(objet,"entry5");//valeurmin
in5= lookup_widget(objet,"combobox10");//Emplacement

j= lookup_widget(objet,"spinbutton1");
m= lookup_widget(objet,"spinbutton2");
a= lookup_widget(objet,"spinbutton3");

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////CONTROL/////////////////////////////////////			
///////////////////////////////////////////////////////////////////////////////////////
if ((strcmp(gtk_entry_get_text(GTK_ENTRY(in1)),"")!= 0) && (strcmp(gtk_entry_get_text(GTK_ENTRY(in2)),"")!= 0)&& (strcmp(gtk_entry_get_text(GTK_ENTRY(in4)),"")!= 0)&&(gtk_combo_box_get_active (GTK_COMBO_BOX(in3)) != -1)&&(gtk_combo_box_get_active (GTK_COMBO_BOX(in5)) != -1)&& (x==1) || (x==2))
{
c.id=atoi(gtk_entry_get_text(GTK_ENTRY(in1)));
c.Vmax=atof(gtk_entry_get_text(GTK_ENTRY(in2)));
c.Vmin=atof(gtk_entry_get_text(GTK_ENTRY(in4)));

strcpy(c.etat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(in3)));
strcpy(c.emplacement,gtk_combo_box_get_active_text(GTK_COMBO_BOX(in5)));

if (x==1)
strcpy(c.type,"Temperature");
else 
if(x==2)
strcpy(c.type,"Humidite");

c.d.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(j));
c.d.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m));
c.d.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a));

ajouter_capteur(c);

GtkWidget *t7al ,*tsakker,*treeview1;

t7al=create_gestion_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"ajouter_capteur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");

afficher_capteurs(treeview1);


}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////CONTROL/////////////////////////////////////			
///////////////////////////////////////////////////////////////////////////////////////
else
{
GtkWidget *in1o,*in2o,*in3o,*in4o,*in5o,*label,*label2;
in1o= lookup_widget(objet,"entry_identf");
in2o= lookup_widget(objet,"entry_valeur");
in3o= lookup_widget(objet,"combobox7");
in4o= lookup_widget(objet,"entry5");
in5o= lookup_widget(objet,"combobox10");

label=lookup_widget (objet,"label145");
label2=lookup_widget (objet,"label_etat");

if (strcmp(gtk_entry_get_text(GTK_ENTRY(in1o)),"")== 0)
{
gtk_entry_set_text(GTK_ENTRY(in1o),"Obligatoire");
}
if (strcmp(gtk_entry_get_text(GTK_ENTRY(in2o)),"")== 0)
{
gtk_entry_set_text(GTK_ENTRY(in2o),"Obligatoire");
}
if (strcmp(gtk_entry_get_text(GTK_ENTRY(in4o)),"")== 0)
{
gtk_entry_set_text(GTK_ENTRY(in4o),"Obligatoire");
}

if (gtk_combo_box_get_active (GTK_COMBO_BOX(in5o)) == -1)
{
gtk_label_set_text(GTK_LABEL(label),"Obligatoire");
}

if (gtk_combo_box_get_active (GTK_COMBO_BOX(in3o)) == -1)
{
gtk_label_set_text(GTK_LABEL(label2),"Obligatoire");
}


}


}


void
on_retoura_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker,*treeview1;

t7al=create_gestion_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"ajouter_capteur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");

afficher_capteurs(treeview1);
}


void
on_supprimer_capteur_show              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *label;
char ids[50];
char labelsh[50];
strcpy(labelsh,"Capteur : ");
sprintf(ids,"%d",idf);
strcat(labelsh,ids);
label=lookup_widget (objet,"label_supp_non");
gtk_label_set_text(GTK_LABEL(label),labelsh);
}


void
on_annuler_supprimer_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker,*treeview1;
t7al=create_gestion_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"supprimer_capteur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");

afficher_capteurs(treeview1);
}


void
on_ok_supprimer_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
int identifiant;
int jour ;

identifiant=idf ;
jour=jf;

capteur c ;
supprimer_capteur(identifiant,jour,mf,af,c);


GtkWidget *t7al ,*tsakker,*treeview1;
t7al=create_gestion_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"supprimer_capteur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");

afficher_capteurs(treeview1);

}


void
on_modifier_capteur_show               (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *labelid,*labelvaleur,*labeltype,*labeletat,*in3,*in6;
char ids[50];

sprintf(ids,"%d",idf);
labelid=lookup_widget (objet,"entry1");
gtk_entry_set_text(GTK_ENTRY(labelid),ids);




if (strcmp(etatf,"PANNE")==0)
{
in3= lookup_widget(objet,"combobox8");
gtk_combo_box_set_active(GTK_COMBO_BOX(in3), 0);
}
else 
{
in3= lookup_widget(objet,"combobox8");
gtk_combo_box_set_active(GTK_COMBO_BOX(in3), 1);
}

if (strcmp(emplacementf,"Serre1")==0)
{
in6= lookup_widget(objet,"combobox11");
gtk_combo_box_set_active(GTK_COMBO_BOX(in6), 0);
}
else
 if(strcmp(emplacementf,"Serre2")==0)
{
in6= lookup_widget(objet,"combobox11");
gtk_combo_box_set_active(GTK_COMBO_BOX(in6), 1);
}
else
{
in6= lookup_widget(objet,"combobox11");
gtk_combo_box_set_active(GTK_COMBO_BOX(in6), 2);
}




GtkWidget *j,*m,*a;

j= lookup_widget(objet,"spinbutton4");
m= lookup_widget(objet,"spinbutton5");
a= lookup_widget(objet,"spinbutton6");

gtk_spin_button_set_value(GTK_SPIN_BUTTON(j),jf);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(m),mf);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(a),af);



}


void
on_radiobutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{
y=1;
} 
}


void
on_radiobutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{
y=2;
} 
}


void
on_ok_modifier_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{

int identifiant;
int jour ;
capteur c ;
identifiant=idf ;
jour=jf;


GtkWidget *in1,*in2,*in3,*in4,*in5;
GtkWidget *j,*m,*a;
capteur c2 ;

in1= lookup_widget(objet,"entry1");
in2= lookup_widget(objet,"entry2");
in4= lookup_widget(objet,"entry6");
in3= lookup_widget(objet,"combobox8");
in5= lookup_widget(objet,"combobox11");
j= lookup_widget(objet,"spinbutton4");
m= lookup_widget(objet,"spinbutton5");
a= lookup_widget(objet,"spinbutton6");

if ( (strcmp(gtk_entry_get_text(GTK_ENTRY(in2)),"")!= 0)&& (strcmp(gtk_entry_get_text(GTK_ENTRY(in4)),"")!= 0)&& (y==1) || (y==2))
{



c2.id=atoi(gtk_entry_get_text(GTK_ENTRY(in1)));
c2.Vmax=atof(gtk_entry_get_text(GTK_ENTRY(in2)));
c2.Vmin=atof(gtk_entry_get_text(GTK_ENTRY(in4)));
strcpy(c2.etat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(in3)));
strcpy(c2.emplacement,gtk_combo_box_get_active_text(GTK_COMBO_BOX(in5)));

if (y==1)
strcpy(c2.type,"Temperature");
else 
if(y==2)
strcpy(c2.type,"Humidite");

c2.d.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(j));
c2.d.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m));
c2.d.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a));

ajouter_capteur(c2);
supprimer_capteur(identifiant,jour,mf,af,c);

GtkWidget *t7al ,*tsakker,*treeview1;
t7al=create_gestion_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"modifier_capteur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");

afficher_capteurs(treeview1);

}
else
{
GtkWidget *in1o,*in2o,*in3o,*in4o,*in5o;
in1o= lookup_widget(objet,"entry1");
in2o= lookup_widget(objet,"entry2");
in4o= lookup_widget(objet,"entry6");
in3o= lookup_widget(objet,"combobox8");
in5o= lookup_widget(objet,"combobox11");

if (strcmp(gtk_entry_get_text(GTK_ENTRY(in2o)),"")== 0)
{
gtk_entry_set_text(GTK_ENTRY(in2o),"Obligatoire");
}
if (strcmp(gtk_entry_get_text(GTK_ENTRY(in4o)),"")== 0)
{
gtk_entry_set_text(GTK_ENTRY(in4o),"Obligatoire");
}

}

}


void
on_retour_modifier_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker,*treeview1;
t7al=create_gestion_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"modifier_capteur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");

afficher_capteurs(treeview1);
}


void
on_ok_ajout_valeur_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *in1,*in2,*j,*m,*a;

capteur c2 ;
char val_max[30];
char val_min[30];
in1= lookup_widget(objet,"entry_valeur_ajout_valeur");
strcpy(val_max,gtk_entry_get_text(GTK_ENTRY(in1)));

in2= lookup_widget(objet,"entry7");
strcpy(val_min,gtk_entry_get_text(GTK_ENTRY(in2)));

if ( (strcmp(gtk_entry_get_text(GTK_ENTRY(in1)),"")!= 0)&& (strcmp(gtk_entry_get_text(GTK_ENTRY(in2)),"")!= 0))
{
c2.id=idf;

c2.Vmax=atof(val_max);
c2.Vmin=atof(val_min);

strcpy(c2.etat,etatf);

strcpy(c2.type,typef);

strcpy(c2.emplacement,emplacementf);

j= lookup_widget(objet,"spinbutton7");
m= lookup_widget(objet,"spinbutton8");
a= lookup_widget(objet,"spinbutton9");

c2.d.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(j));
c2.d.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m));
c2.d.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a));


ajouter_capteur(c2);

GtkWidget *t7al ,*tsakker,*treeview1;
t7al=create_gestion_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"ajout_valeur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");

afficher_capteurs(treeview1);


}
else 
{
GtkWidget *in1o,*in2o;
in1o= lookup_widget(objet,"entry_valeur_ajout_valeur");
in2o= lookup_widget(objet,"entry7");


if (strcmp(gtk_entry_get_text(GTK_ENTRY(in1o)),"")== 0)
{
gtk_entry_set_text(GTK_ENTRY(in1o),"Obligatoire");
}
if (strcmp(gtk_entry_get_text(GTK_ENTRY(in2o)),"")== 0)
{
gtk_entry_set_text(GTK_ENTRY(in2o),"Obligatoire");
}
}

}

void
on_button5_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al ,*tsakker,*treeview1;
t7al=create_gestion_capteur();
gtk_widget_show (t7al);
tsakker=lookup_widget(objet,"ajout_valeur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");

afficher_capteurs(treeview1);
}


void
on_ajout_valeur_show                   (GtkWidget       *objet,
                                        gpointer         user_data)
{

GtkWidget *j,*m,*a;

j= lookup_widget(objet,"spinbutton7");
m= lookup_widget(objet,"spinbutton8");
a= lookup_widget(objet,"spinbutton9");

gtk_spin_button_set_value(GTK_SPIN_BUTTON(j),jf);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(m),mf);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(a),af);


}


void
on_retour_alarmant_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview1,*t7al,*tsakker;
tsakker=lookup_widget(objet,"Alarmants");
gtk_widget_destroy (tsakker);


t7al=create_gestion_capteur();
gtk_widget_show (t7al);


treeview1=lookup_widget(t7al,"treeview1");
afficher_capteurs(treeview1);
}


void
on_alarmants_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{

/////////////////////////////////////////////////////////////////////////////

GtkWidget *treeview2,*treeview3,*t7al,*tsakker;
tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);


t7al=create_Alarmants();
gtk_widget_show (t7al);

treeview2=lookup_widget(t7al,"treeview2");
afficher_capteurs_temp(treeview2);

/////////////////////////////////////////////////////////////////////////////

treeview3=lookup_widget(t7al,"treeview3");
afficher_capteurs_hum(treeview3);





}


void
on_ajout_val_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *t7al,*tsakker;

t7al=create_ajout_valeur();
gtk_widget_show (t7al);

tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);

}


void
on_refrech_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview1,*t7al,*tsakker;

t7al=create_gestion_capteur();
gtk_widget_show (t7al);

tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);

treeview1=lookup_widget(t7al,"treeview1");
afficher_capteurs(treeview1);
}


void
on_chercher_diff_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *in1,*treeview1,*t7al,*tsakker;
char etat[30];

in1= lookup_widget(objet,"combobox9");
strcpy(etat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(in1)));
if (strcmp(etat,"PANNE")==0){
    capteur c;
    FILE *f;
    FILE *d;
    f=fopen("capteur.txt","r");
    d=fopen("diffectueux.txt","w");
    if (f!=NULL)
    {
        while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
            {
                if (strcmp("PANNE",c.etat)==0)
                  {
                    fprintf(d,"%d %s %.2f %.2f %s %d %d %d %s\n",c.id,c.type,c.Vmax,c.Vmin,c.etat,c.d.jour,c.d.mois,c.d.annee,c.emplacement);
                  }
            }
    }
    else
    printf("Erreur");

    fclose(f);
    fclose(d);


t7al=create_gestion_capteur();
gtk_widget_show (t7al);

treeview1=lookup_widget(t7al,"treeview1");


tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);

afficher_capteurs3(treeview1);
}

else 
{

 capteur c;
    FILE *f;
    FILE *k;
    f=fopen("capteur.txt","r");
    k=fopen("ok.txt","w");
    if (f!=NULL)
    {
       while(fscanf(f,"%d %s %f %f %s %d %d %d %s",&c.id,c.type,&c.Vmax,&c.Vmin,c.etat,&c.d.jour,&c.d.mois,&c.d.annee,c.emplacement)!=EOF)
            {
                if (strcmp("OK",c.etat)==0)
                  {
                     fprintf(k,"%d %s %.2f %.2f %s %d %d %d %s\n",c.id,c.type,c.Vmax,c.Vmin,c.etat,c.d.jour,c.d.mois,c.d.annee,c.emplacement);
                  }
            }
    }
    else
    printf("Erreur");

    fclose(f);
    fclose(k);


t7al=create_gestion_capteur();
gtk_widget_show (t7al);

treeview1=lookup_widget(t7al,"treeview1");

tsakker=lookup_widget(objet,"gestion_capteur");
gtk_widget_destroy (tsakker);

afficher_capteurs4(treeview1);


}

}





void
on_gestion_capteur_show                (GtkWidget       *objet,
                                        gpointer         user_data)
{

	GtkWidget *in1 ;
in1= lookup_widget(objet,"entry4");
gtk_entry_set_text(GTK_ENTRY(in1),"Chercher par ID");

GtkWidget *label;




}






void
on_cheralarm_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{

int jourt,moist,anneet;

GtkWidget *treeview1,*treeview3,*t7al,*tsakker,*ja,*ma,*aa;

ja= lookup_widget(objet,"ja");
ma= lookup_widget(objet,"ma");
aa= lookup_widget(objet,"aa");


jourt=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ja));
moist=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ma));
anneet=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aa));

chercher_alamantes_temp(jourt,moist,anneet);

t7al=create_Alarmants();
gtk_widget_show (t7al);



tsakker=lookup_widget(objet,"Alarmants");
gtk_widget_destroy (tsakker);



treeview3=lookup_widget(t7al,"treeview2");
afficher_capteurs_temp_alarm(treeview3);


treeview1=lookup_widget(t7al,"treeview3");
afficher_capteurs_hum(treeview1);



}






void
on_cherHum_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{

int jourt,moist,anneet;

GtkWidget *treeview2,*treeview3,*t7al,*tsakker,*ja,*ma,*aa;

ja= lookup_widget(objet,"spinbutton10");
ma= lookup_widget(objet,"spinbutton11");
aa= lookup_widget(objet,"spinbutton12");


jourt=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ja));
moist=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ma));
anneet=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aa));

chercher_alamantes_humid(jourt,moist,anneet);

t7al=create_Alarmants();
gtk_widget_show (t7al);



tsakker=lookup_widget(objet,"Alarmants");
gtk_widget_destroy (tsakker);

treeview3=lookup_widget(t7al,"treeview3");
afficher_capteurs_hum_alarm(treeview3);

treeview2=lookup_widget(t7al,"treeview2");
afficher_capteurs_temp(treeview2);



}





void
on_plusalarm_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview2,*treeview1,*t7al,*tsakker,*ja,*ma,*aa;

chercher_plus_alamantes_temp();
chercher_plus_alamantes_hum();
t7al=create_Alarmants();
gtk_widget_show (t7al);



tsakker=lookup_widget(objet,"Alarmants");
gtk_widget_destroy (tsakker);


treeview1=lookup_widget(t7al,"treeview3");
afficher_capteurs_hum_plus_alarm(treeview1);

treeview2=lookup_widget(t7al,"treeview2");
afficher_capteurs_temp_plus_alarm(treeview2);

}


void
on_actualiser_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview2,*treeview3,*t7al,*tsakker;

t7al=create_Alarmants();
gtk_widget_show (t7al);

tsakker=lookup_widget(objet,"Alarmants");
gtk_widget_destroy (tsakker);



treeview2=lookup_widget(t7al,"treeview2");
afficher_capteurs_temp(treeview2);


treeview3=lookup_widget(t7al,"treeview3");
afficher_capteurs_hum(treeview3);
}


void
on_def_marque_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *label;
label=lookup_widget (objet,"labeldef");



marquedef();


capteur c;

int A=0,B=0,C=0;

FILE *f=fopen("marquedef.txt","r");
if(f==NULL)
return;

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
     gtk_label_set_text(GTK_LABEL(label),"FarmTRX");
   else if ( B > A && B > C )
      gtk_label_set_text(GTK_LABEL(label),"MC_Sieve_Sensor");
   else  
      gtk_label_set_text(GTK_LABEL(label),"TOPCON");
   


}


}




