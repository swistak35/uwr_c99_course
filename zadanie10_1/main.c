#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

// Używając GTK+ stworzyć program, który w okienku zawiera trzy przyciski:
// ZA, PRZECIW i NIE MAM ZDANIA i który zbiera i wypisuje poniżej przycisków informacje
// o liczbie oddanych głosów oraz jaki procent głosów był za, a jaki przeciw. Nad przyciskami
// powinna być informacja w jakiej sprawie jest przeprowadzane głosowanie (może to być parametr
// wywołania programu lub ustalony przez autora programu tekst). Naciśnięcie odpowiedniego
// przycisku jest tutaj oddaniem głosu. Użyć struktury GtkLabel do umieszczania tekstu w okienku.

// Uwagi: Szukanie okresu poprzez analize tylko cyfr rozwinięcia nie jest poprawne
//   (w długim okresie cyfry muszą występować wielokrotnie).

int votes_up = 0;
int votes_down = 0;
int votes_none = 0;

GtkWidget * label_vote_up, * label_vote_down, * label_vote_none;

int votes_total();
void update_all_labels();
void btn_vote_up_clicked(GtkWidget *widget,gpointer data);
void btn_vote_down_clicked(GtkWidget *widget,gpointer data);
void btn_vote_none_clicked(GtkWidget *widget,gpointer data);

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Głosowanie");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  GtkWidget * vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  GtkWidget * label_topic = gtk_label_new("Czy w restauracji plastycznej powinno być taniej?");
  gtk_box_pack_start(GTK_BOX (vbox), label_topic, TRUE, TRUE, 0);
  gtk_widget_show(label_topic);

  GtkWidget * hbox_buttons = gtk_hbox_new(FALSE, 0);
    GtkWidget * btn_vote_up = gtk_button_new_with_label("ZA");
    g_signal_connect(G_OBJECT(btn_vote_up), "clicked", G_CALLBACK(btn_vote_up_clicked), (gpointer)window);
    gtk_box_pack_start(GTK_BOX (hbox_buttons), btn_vote_up, TRUE, TRUE, 0);
    gtk_widget_show(btn_vote_up);

    GtkWidget * btn_vote_down = gtk_button_new_with_label("PRZECIW");
    g_signal_connect(G_OBJECT(btn_vote_down), "clicked", G_CALLBACK(btn_vote_down_clicked), (gpointer)window);
    gtk_box_pack_start(GTK_BOX (hbox_buttons), btn_vote_down, TRUE, TRUE, 0);
    gtk_widget_show(btn_vote_down);

    GtkWidget * btn_vote_none = gtk_button_new_with_label("NIE MAM ZDANIA");
    g_signal_connect(G_OBJECT(btn_vote_none), "clicked", G_CALLBACK(btn_vote_none_clicked), (gpointer)window);
    gtk_box_pack_start(GTK_BOX (hbox_buttons), btn_vote_none, TRUE, TRUE, 0);
    gtk_widget_show(btn_vote_none);
  gtk_box_pack_start(GTK_BOX(vbox), hbox_buttons, TRUE, TRUE, 0);
  gtk_widget_show(hbox_buttons);

  GtkWidget * hbox_labels = gtk_hbox_new(FALSE, 0);
    label_vote_up = gtk_label_new("ZA: 0.00%");
    gtk_box_pack_start(GTK_BOX (hbox_labels), label_vote_up, TRUE, TRUE, 0);
    gtk_widget_show(label_vote_up);

    label_vote_down = gtk_label_new("PRZECIW: 0.00%");
    gtk_box_pack_start(GTK_BOX (hbox_labels), label_vote_down, TRUE, TRUE, 0);
    gtk_widget_show(label_vote_down);

    label_vote_none = gtk_label_new("GŁOSY: 0");
    gtk_box_pack_start(GTK_BOX (hbox_labels), label_vote_none, TRUE, TRUE, 0);
    gtk_widget_show(label_vote_none);
  gtk_box_pack_start(GTK_BOX(vbox), hbox_labels, TRUE, TRUE, 0);
  gtk_widget_show(hbox_labels);

  gtk_widget_show(vbox);

  gtk_widget_show(window);
  gtk_main();
  return 0;
}

int votes_total() {
  return (votes_up + votes_down + votes_none);
}

void update_all_labels() {
  int total = votes_total();
  char * content;

  content = gtk_label_get_text(GTK_LABEL(label_vote_up));
  sprintf(content, "ZA: %.2f%%", ((float) votes_up / total * 100));
  gtk_label_set_text(GTK_LABEL(label_vote_up), content);

  content = gtk_label_get_text(GTK_LABEL(label_vote_down));
  sprintf(content, "PRZECIW: %.2f%%", ((float) votes_down / total * 100));
  gtk_label_set_text(GTK_LABEL(label_vote_down), content);

  content = gtk_label_get_text(GTK_LABEL(label_vote_none));
  sprintf(content, "GŁOSY: %d", total);
  gtk_label_set_text(GTK_LABEL(label_vote_none), content);
}

void btn_vote_up_clicked(GtkWidget *widget,gpointer data) {
  votes_up++;
  update_all_labels();
}

void btn_vote_down_clicked(GtkWidget *widget,gpointer data) {
  votes_down++;
  update_all_labels();
}

void btn_vote_none_clicked(GtkWidget *widget,gpointer data) {
  votes_none++;
  update_all_labels();
}

