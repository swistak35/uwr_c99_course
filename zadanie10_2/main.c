#include <stdio.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "stack.h"

// Używając GTK+ stworzyć interfejs okienkowy do programu wyznaczającego kolejne kwadraty
// magiczne zadanego rozmiaru (jako parametr wywołania programu). Użyć rozwiązania
// zadania 2 z listy 5 do generowania kwadratów magicznych.

bool kwadrat_magiczny();
void zamien(int a, int b);
void nastepny_kwadrat();
bool czy_kwadrat_domyslny();
void btn_next_clicked();

GtkWidget ** labels;
int * tab;
int n, nkw, suma;
struct stack_element * stack;

int main(int argc, char** argv) {
  n = argv[1][0] - '0';
  nkw = n*n;
  stack = list_init();

  // Obliczanie sumy, jaka musi być w kazdym rzedzie
  suma = 0;
  for (int i=1;i<=nkw;i++)
      suma += i;
  suma /= n;

  // Inicjalizacja pol liczbami 1, 2, 3, ..., n^2
  tab = malloc(sizeof(int) * (nkw+1));
  for (int i=0;i<nkw;i++)
      tab[i] = i+1;

  // -------- INTERFEJS ---------
  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Kwadraty magiczne");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  GtkWidget * vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  GtkWidget * btn_next = gtk_button_new_with_label("Następny kwadrat");
  g_signal_connect(G_OBJECT(btn_next), "clicked", G_CALLBACK(btn_next_clicked), (gpointer)window);
  gtk_box_pack_start(GTK_BOX (vbox), btn_next, TRUE, TRUE, 0);
  gtk_widget_show(btn_next);

  GtkWidget * table = gtk_table_new(n, n, TRUE);
  labels = malloc(sizeof(GtkWidget *) * nkw);
  for (int i=0;i<nkw;i++) {
    labels[i] = gtk_label_new("000");
    gtk_table_attach_defaults(GTK_TABLE(table), labels[i], i % n, (i % n) + 1, i/n, (i/n) + 1);
    gtk_widget_show(labels[i]);
  }
  gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 0);
  gtk_widget_show(table);

  gtk_widget_show(vbox);
  gtk_widget_show(window);
  btn_next_clicked();
  gtk_main();

  return 0;
}

// Sprawdza czy kwadrat jest domyslny, tzn. np. dla n=3: 1,2,3,4,5,6,7,8,9
bool czy_kwadrat_domyslny() {
  for (int i=0;i<nkw;i++) {
    if (tab[i] != i+1)
      return false;
  }
  return true;
}

void nastepny_kwadrat() {
  int tmpsuma, indeks, roznica;
  bool found;

  while (!is_empty(stack)) {
    list_shift(&stack, &tab, nkw+1);
    roznica = nkw - tab[nkw];

    found = false; // flaga, czy znalezlismy rzedy, ktore mozemy uciac
    if (roznica % n == 0) {
      for (int i=0;i<(roznica/n) && !found;i++) {
        tmpsuma = 0;
        for (int j=0;j<n;j++) {
          // Trochę dziwny wzór, ale chodzi tylko o zsumowanie ostatnich kawałków
          //   i jeśli są różne od sumy, której potrzebujemy, to odcinamy
          indeks = nkw - i*n - j - 1;
          tmpsuma += *(tab + indeks);
        }
        if (tmpsuma != suma) {
          found = true;
          break;
        }
      }
    }
    if (found) continue;

    // Algorytm permutacji przez selekcję
    if (tab[nkw] == 1) {
      if (kwadrat_magiczny()) break;
    } else {
      tab[nkw]--;
      stack = list_unshift(stack, tab, nkw+1);
      for (int i=0;i<tab[nkw];i++) {
        zamien(i, tab[nkw]);
        stack = list_unshift(stack, tab, nkw+1);
        zamien(i, tab[nkw]);
      }
    }
  }

  if (czy_kwadrat_domyslny() && is_empty(stack)) {
    tab[nkw] = nkw;
    stack = list_unshift(stack, tab, nkw+1);
    nastepny_kwadrat();
  }
}

bool kwadrat_magiczny() {
  int tmpsuma;

  // Pierwsza przekatna
  tmpsuma = 0;
  for (int i=0;i<n;i++)
    tmpsuma += tab[i*n+i];
  if (tmpsuma != suma)
    return false;

  // Druga przekatna
  tmpsuma = 0;
  for (int i=1;i<=n;i++)
    tmpsuma += tab[i*(n-1)];
  if (tmpsuma != suma)
    return false;

  // Kolumny
  for (int i=0;i<n;i++) {
    tmpsuma = 0;
    for (int j=0;j<n;j++)
      tmpsuma += tab[i+j*n];
    if (tmpsuma != suma)
      return false;
  }

  // Rzedow nie sprawdzamy, bo niewlasciwe na biezaco odcinamy
  return true;
}

void zamien(int a, int b) {
  int tmp;
  tmp = tab[a];
  tab[a] = tab[b];
  tab[b] = tmp;
}

void btn_next_clicked() {
  nastepny_kwadrat();
  char * content;

  for (int i=0;i<nkw;i++) {
    content = gtk_label_get_text(GTK_LABEL(labels[i]));
    sprintf(content, "%d", tab[i]);
    gtk_label_set_text(GTK_LABEL(labels[i]), content);
  }
}
