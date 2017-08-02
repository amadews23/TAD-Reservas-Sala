/********************************************************
* NOMBRE: #Bartolome#
* PRIMER APELLIDO: #Vich#
* SEGUNDO APELLIDO: #Lozano#
* EMAIL: #amadews23@hotmail.com#
********************************************************/
/*******************************************************

Programa Principal GestionReservasSala PRACTICA 4

Descripcion:
  Programa que permite Crear, Anula y Consultar Reservas.

Limitacion:
  Por Constantes desde Enero hasta Marzo de 2017

********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "GestionReservaSala.h"

int main() {
  char tecla = ' ';
  bool continuar = true;
  //declaramos vector tipo vector de reservaas
  TipoVectorReserva vectorReserva;
  //declaramos conjunto de operaciones
  GestionReservaSala reservas;
  //  CalendarioMes calendario;
  reservas.InicializarVectorReservas(vectorReserva);
  do {
      system("cls");

      printf("Gestión de Reservas Sala\n" );
      printf("      Nueva Reserva                    (Pulsar N)\n");
      printf("      Anular Reserva                   (Pulsar A)\n");
      printf("      Reservas de un Día               (Pulsar D)\n");
      printf("      Reservas de un Mes               (Pulsar M)\n");
      printf("      Salir                            (Pulsar S)\n");
      printf("Teclear una opción valida (N|A|D|M|S)\n" );
      scanf( " %c", &tecla );
      tecla = toupper(tecla);
      switch (tecla) {
          case 'N':
              reservas.NuevaReserva(vectorReserva);
              break;
          case 'A':
              reservas.AnularReserva(vectorReserva);
              break;
          case 'D':
              reservas.ReservasdelDia(vectorReserva);
              break;
          case 'M':
              reservas.ReservasdelMes(vectorReserva);
              break;
          case 'S':
              continuar = false;
              break;
          }
  } while (continuar);
}
