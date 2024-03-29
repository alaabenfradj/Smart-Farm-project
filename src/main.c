/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
  GtkWidget *inscription;
  GtkWidget *authentification;
  GtkWidget *gestion_capteur;
  GtkWidget *ajouter_capteur;
  GtkWidget *supprimer_capteur;
  GtkWidget *modifier_capteur;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory ("../pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  /*inscription = create_inscription ();
  gtk_widget_show (inscription);*/
  authentification = create_authentification ();
  gtk_widget_show (authentification);
 /* gestion_capteur = create_gestion_capteur ();
  gtk_widget_show (gestion_capteur);
  ajouter_capteur = create_ajouter_capteur ();
  gtk_widget_show (ajouter_capteur);
  supprimer_capteur = create_supprimer_capteur ();
  gtk_widget_show (supprimer_capteur);
  modifier_capteur = create_modifier_capteur ();
  gtk_widget_show (modifier_capteur);*/

  gtk_main ();
  return 0;
}

