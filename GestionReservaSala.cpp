/********************************************************
* NOMBRE: #Bartolome#
* PRIMER APELLIDO: #Vich#
* SEGUNDO APELLIDO: #Lozano#
* EMAIL: #amadews23@hotmail.com#
********************************************************/
/*********************************************************************
* IMPLEMENTACION de Módulo: GestionReservasSala, PRACTICA 4
*
* Descripción:
*   Procedimientos y funciones para manejo de reservas
*
*********************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "GestionReservaSala.h"
#include "calendario.h"

/*--Declaramos el Tipo Abstracto CalendarioMes como calendario--*/
CalendarioMes calendario;
/*--Iniciamos a 0 el indice de la pocicion a guardar en vector reservas--*/
int index = 0;

/*================================================================================================
 Solicita de reserva e inserta si todo esta OK
=================================================================================================*/
void GestionReservaSala::NuevaReserva(TipoVectorReserva vectorReserva){
  TipoReserva reserva;
  bool fechacorrecta = true;          /*esta variable es true si la fecha existe*/
  bool dialaborable = true;           /*esta variable es true si el dia (fecha) es laborable*/
  bool disponibilidaddiahora = true;  /*esta variable es true si el dia (fecha) es laborable*/
  bool disponibilidadhoras = true;
  bool anyovalido = false;
  bool mesvalido = false;
  int cantidadreservasmes = 0 ;
  int maximopermitido = 12;           /*esta variable devuelve el numero maximo permitido de horas de reserva para la hora indicada*/
  char tecla2;
  /*-- Inicializamos reserva --*/
  InicializarReserva (reserva);
  /*-- Comprobamos que no tengamos el máximo de reservas --*/
  if (ComprobarCantReservas() == true) {
    system("cls");
    printf("Nueva Reserva:\n");
    do {
        printf("      Persona que reserva(Maximo 20 caracteres)?");
        /*--Con esta linea capturamos texto y si hay espacio y despues texto guardamos apellido --*/
        scanf("%s%[^\n]s",&reserva.nombre, &reserva.apellido);
//        scanf("%s",&reserva.nombre);
        fflush(stdin);
    } while (ComprobarTamNombre(reserva.nombre, reserva.apellido) == true  ); //Si es true es de 20 chars o mas
    do {
        do {
            do {
              do {
                do {
                    do {
                        if (cantidadreservasmes == MaxReservasMes) {
                            printf("   Reservas para el mes solicitado: *Todas Ocupadas*\n");
                            printf("   Cantidad de Reservas maximas para este mes es: %d\n", MaxReservasMes-1);
                            cantidadreservasmes = 0;
                        }

                        /*--Si la reserva solicitada supera el maximo de horas permitido --*/
                        if (reserva.duracion > maximopermitido) {
                            printf("   La duración %d horas, supera las %d horas libres, *Ponga menos horas*\n",reserva.duracion, maximopermitido);
                            /*--Para que no sigua saliendo el mensaje anterior volvemos a dejar a 12 el numero de horas permitidas*/
                            maximopermitido = 12;
                        }
                        /*--Si el dia y la hora estan ocupadas--*/
                        if (disponibilidaddiahora == false ) {
                            printf("   La hora %d esta ocupada, *Pruebe otro dia u hora*\n",reserva.hora);
                        }
                        if (fechacorrecta == false) {
                            printf("   El dia del mes no existe, *Repita fecha*\n");
                        }
                        if (dialaborable == false) {
                            printf("   El dia elegido es Sabado o Domingo. *Elija otro dia*\n");
                        }
                        if (disponibilidadhoras == false) {
                            printf("   Lo sentimos las horas estan ocupadas. *Elija otro dia u horario*\n");
                            disponibilidadhoras = true;
                        }

                        printf("      Dia?");
                        fflush(stdin);
                        scanf("%d",&reserva.fecha.dia);
                    } while (ComprobarFHD(reserva.fecha.dia, Dia) == true); /*Comprobamos valores numericos permitidos */
                    do {
                        if (mesvalido == true) {
                            printf("    Solo se puede reserver entre los meses %d y %d ambos incluidos\n", MesActual, MaxMes);
                        }
                        printf("      Mes?");
                        fflush(stdin);
                        scanf("%d",&reserva.fecha.mes);
                        mesvalido = ComprobarFHD(reserva.fecha.mes, Mes);
                    } while (mesvalido == true); /*Comprobamos valores numericos permitidos */
                    do {
                        if (anyovalido == true) {
                            printf("    Solo se puede en el anyo %d \n", AnyoActual);
                        }
                        printf("      Año?");
                        fflush(stdin);
                        scanf("%d",&reserva.fecha.anyo);
                        /*-- fechacorrecta guarda True si la fecha esta bien formada o False si no --*/
                        fechacorrecta = calendario.FechaCorrecta(reserva.fecha.dia, reserva.fecha.mes, reserva.fecha.anyo);
                        /*-- dialaborable guarda True si el dia no es sabado o domingo o False si no --*/
                        dialaborable = calendario.ComprobarDiaLaborable(reserva.fecha.dia, reserva.fecha.mes-1, reserva.fecha.anyo);
                        cantidadreservasmes = ComprobarCantReservasMes(vectorReserva, reserva.fecha);
                        anyovalido = ComprobarFHD(reserva.fecha.anyo, Anyo);
                    } while ( anyovalido == true);
                } while (fechacorrecta == false || dialaborable == false );
              } while ( cantidadreservasmes == MaxReservasMes);

                do {
                    printf("      Hora de comienzo (Hora en punto de 8 a 19)?");
                    fflush(stdin);
                    scanf("%d",&reserva.hora);
                    /*-- disponibilidad hora guarda True si la hora para la fecha indicada esta disponible--*/
                    disponibilidaddiahora = ComprobarDisponibilidadDiaHora(reserva.fecha, reserva.hora, vectorReserva);
                } while ( ComprobarFHD(reserva.hora, Hora) == true );
            } while(disponibilidaddiahora == false ); /*--Comprobar que el dia y la hora estan libres --*/
            do {
                printf("      Duración (Horas completas)?");
                fflush(stdin);
                scanf("%d",&reserva.duracion);
                /*--Devuelve el numero de horas maximas posibles para reservar, sin tener en cuenta si esta ocupado --*/
                maximopermitido = ComprobarMaximoPermitido(reserva.hora);
                disponibilidadhoras = ComprobarDisponibilidadHorasDuracion(reserva.fecha, reserva.hora, reserva.duracion, vectorReserva);
            } while ( ComprobarFHD(reserva.duracion, Duracion) == true   );
            /*--Comprueba que la duracion de la reserva no supere el numero maximo de horas posibles --*/
        } while(maximopermitido < reserva.duracion);
    } while (disponibilidadhoras == false);
    /*-- Guardar valores en vector --*/
    InsertarVectorReservas(reserva, vectorReserva);
    /*--Incrementar la posicion a guardar el siguiente conjunto de valores--*/
    index++;
  } else {
      printf("     Están superadas el numero maximo de reservas permitidas\n");
      scanf("%s",&tecla2);
  }
}
/*================================================================================================
 Solicita datos para anular reserva si todo esta OK la anula
=================================================================================================*/
void GestionReservaSala::AnularReserva(TipoVectorReserva vectorReserva) {
  TipoReserva reserva;

  char tecla2;

  bool fechacorrecta = true; /*Esta variable es true si la fecha existe*/
//  int numeroreserva = 100;
  int numeroreserva;
  InicializarReserva(reserva);
  system("cls");
  printf("Anular Reserva:\n");
  do {
      printf("      Persona que reservó?");
      fflush(stdin);
      /*--Con esta linea capturamos texto, si hay espacio y despues texto guardamos apellido --*/
      scanf("%s%[^\n]s",&reserva.nombre, &reserva.apellido);
  } while (ComprobarTamNombre(reserva.nombre, reserva.apellido) == true );    /*comprobamos que el nombre no exceda de 20 chars*/
  do {
      do {
          if (fechacorrecta == false) {
              printf("    (El dia del mes no existe), *Repita fecha*\n");
          }
          printf("      Dia?");
          fflush(stdin);
          scanf("%d",&reserva.fecha.dia);
      } while (ComprobarFHD(reserva.fecha.dia, Dia) == true); /*Comprobamos valores numericos permitidos*/
      do {
          printf("      Mes?");
          fflush(stdin);
          scanf("%d",&reserva.fecha.mes);
      } while (ComprobarFHD(reserva.fecha.mes, Mes) == true); /*Comprobamos valores numericos permitidos*/
      do {
          printf("      Año?");
          fflush(stdin);
          scanf("%d",&reserva.fecha.anyo);
          /*-- fechacorrecta guarda True si la fecha esta bien formada o False si no, sino repite el bucle de pedir fecha --*/
          fechacorrecta = calendario.FechaCorrecta(reserva.fecha.dia, reserva.fecha.mes, reserva.fecha.anyo);
      } while ( ComprobarFHD(reserva.fecha.anyo, Anyo) == true);
  } while (fechacorrecta == false);
  do {
      printf("      Hora de comienzo?");
      fflush(stdin);
      scanf("%d",&reserva.hora);
  } while ( ComprobarFHD(reserva.hora, Hora) == true );

      scanf("%c",&tecla2);
      numeroreserva = BuscarReserva(reserva,vectorReserva);
      /*--printf("%d\n",numeroreserva);--*/
      if ( numeroreserva <= MaxReservas) {
          printf("    Reserva encontrada. Desea eliminar?\n");
          printf("    (S para Borrar) (C para Cancelar)");
          scanf("%c", &tecla2);
          tecla2 = toupper(tecla2);
          if (tecla2 == 'S') {
              BorrayOrdenaReserva(reserva, vectorReserva, numeroreserva);
              index--;
          } else if (tecla2 == 'N') {

          }

      } else if ( numeroreserva == 100) {
          printf("\n");
          printf("\n");
          printf("    La reserva no existe\n");
          printf("    Pulse un TECLA y ENTER para salir");
          scanf("%c", &tecla2);
      }
}
/*=================================================================================================
 devuelve el nº de indice del vectoReserva si encontro la reserva o 100 si no la encontro
=================================================================================================*/
int GestionReservaSala::BuscarReserva(TipoReserva reserva, const TipoVectorReserva vectorReserva) {
  int numeroreserva = 100;
  for (int a = 0; a < MaxReservas ; a++) {
      if ( strcmpi( vectorReserva[a].nombre , reserva.nombre) == 0 && strcmpi(vectorReserva[a].apellido , reserva.apellido) == 0 && vectorReserva[a].fecha.dia == reserva.fecha.dia && vectorReserva[a].fecha.mes == reserva.fecha.mes && vectorReserva[a].fecha.anyo == reserva.fecha.anyo && vectorReserva[a].hora == reserva.hora ){
          numeroreserva = a;
        }
  }
  return numeroreserva;
}

/*================================================================================================
 Sobreescribe la reserva a anular y el ultimo elemento del vector lo inicaliza a 0
=================================================================================================*/
void GestionReservaSala::BorrayOrdenaReserva(TipoReserva reserva, TipoVectorReserva vectorReserva, int numeroreserva) {
  //  TipoReserva auxreserva;
  for (int a = numeroreserva; a < MaxReservas; a++) {
      vectorReserva[a] = vectorReserva[a+1];
  }
  strcpy(vectorReserva[index].nombre, "");
  strcpy(vectorReserva[index].apellido, "");
  vectorReserva[index].fecha.dia = 0;
  vectorReserva[index].fecha.mes = 0;
  vectorReserva[index].fecha.anyo = 0;
  vectorReserva[index].hora = 0;
  vectorReserva[index].duracion = 0;
}
/*================================================================================================
Solicita los datos de una reserva y si todo esta Ok ;muestra las reservas del dia
=================================================================================================*/
void GestionReservaSala::ReservasdelDia(TipoVectorReserva vectorReserva) {
  /*--Declaramos los vectores-- Para los procedimientos de crear vectorMismafecha y vectorDisponibilidad(de horas)*/
  TipoReserva reserva;
  TipoVectorMismaFecha vectorMismafecha;
  TipoVectorDisponibilidad vectorDisponibilidad;
  typedef char TipoCadena[3];
  typedef TipoCadena TipoVectorCadenas[12];
  TipoVectorCadenas v;
  bool fechacorrecta = true; /*--esta variable es true si la fecha es correcta--*/
  system("cls");
  printf("Reservas del Día:\n");
  do {
      do {
          if (fechacorrecta == false) {
              printf("    (El dia del mes no existe), *Repita fecha*\n");
          }
          printf("      Dia?");
          scanf("%d",&reserva.fecha.dia);
      } while (ComprobarFHD(reserva.fecha.dia, Dia) == true); /*--comprobamos que dia este dentro de los valores numericos permitidos--*/
      do {
          printf("      Mes?");
          scanf("%d",&reserva.fecha.mes);
      } while (ComprobarFHD(reserva.fecha.mes, Mes) == true); /*--comprobamos que mes esta dentro de los valores numericos permitidos--*/
      do {
          printf("      Año?");
          scanf("%d",&reserva.fecha.anyo);
          /*-- fechacorrecta guarda True si la fecha esta bien formada o False si no, sino repite el bucle de pedir fecha --*/
          fechacorrecta = calendario.FechaCorrecta(reserva.fecha.dia, reserva.fecha.mes, reserva.fecha.anyo);
      } while ( ComprobarFHD(reserva.fecha.anyo, Anyo) == true);
  } while (fechacorrecta == false);
      CrearVectorMismaFecha(reserva.fecha, vectorReserva, vectorMismafecha);
      CrearVectorDisponibilidad(vectorMismafecha, vectorDisponibilidad);
      for (int a = 0; a < 12; a++) {
          if(vectorDisponibilidad[a] == true) {
              strcpy(v[a],"RR");
          } else{
              strcpy(v[a],"  ");
          }
      }
      system("cls");
      printf("         Reservas del día: %d/%d/%d\n", reserva.fecha.dia, reserva.fecha.mes, reserva.fecha.anyo);
      printf("\n");
      printf("I-------------I--------------------------I\n");
      printf("I Horas:      I08  10  12  14  16  18  20I\n");
      printf("I-------------I--------------------------I\n");
      printf("I Reservadas: I%s%s%s%s%s%s%s%s%s%s%s%s  I\n",v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],v[10],v[11]);
      printf("I-------------I--------------------------I\n");
      printf("\n");
      for (int a = 0; a < MaxTiempoReservas; a++) {
          if ( vectorMismafecha[a].fecha.dia != 0 && vectorMismafecha[a].fecha.mes != 0) {
              /*--En NuevaReserva: al introducir el apellido este se copia en nombre y junta nombre y apellido --*/
              /*--printf("%d a %d reservada por: %s %s\n", vectorMismafecha[a].hora, vectorMismafecha[a].hora+vectorMismafecha[a].duracion, vectorMismafecha[a].nombre, vectorMismafecha[a].apellido);--*/
              printf("%d a %d reservada por: %s %s\n", vectorMismafecha[a].hora, vectorMismafecha[a].hora+vectorMismafecha[a].duracion, vectorMismafecha[a].nombre);
          }
      }
          printf("\n");
          printf("\n");
          printf("Pulse tecla y ENTER para salir\n");
          scanf("%s",&reserva.nombre);
}
/*================================================================================================
Solicita los datos de mes y anyo y si todo Ok; imprime calendario
=================================================================================================*/
void GestionReservaSala::ReservasdelMes(TipoVectorReserva vectorReserva) {
  TipoNombreMes nombremes;
  TipoReserva reserva;
  TipoVectorMes vm;
  TipoVectorMismaFecha vectorMismafecha;
  TipoVectorDisponibilidad vectorDisponibilidad, vd;
  system("cls");
  printf("Reservas del Mes:\n");
  do {
      printf("      Mes?");
      scanf("%d",&reserva.fecha.mes);
  } while (ComprobarFHD(reserva.fecha.mes, Mes) == true); /*--comprobamos que mes esta dentro de los valores numericos permitidos--*/
  do {
     printf("      Año?");
     scanf("%d",&reserva.fecha.anyo);
  } while ( ComprobarFHD(reserva.fecha.anyo, Anyo) == true);
      calendario.CrearMes(reserva.fecha.mes-1, reserva.fecha.anyo, vm, nombremes);
  for (int a = 0; a < MaxReservas; a++) {
      if(vectorReserva[a].fecha.mes == reserva.fecha.mes && vectorReserva[a].fecha.anyo == reserva.fecha.anyo){
          /*-- printf("%d",vectorReserva[a].fecha.dia); --*/
          CrearVectorMismaFecha(vectorReserva[a].fecha, vectorReserva, vectorMismafecha);
          CrearVectorDisponibilidad(vectorMismafecha, vectorDisponibilidad);
          if ((vectorDisponibilidad[0] && vectorDisponibilidad[1] && vectorDisponibilidad[2] && vectorDisponibilidad[3] &&vectorDisponibilidad[4] && vectorDisponibilidad[5] && vectorDisponibilidad[6] && vectorDisponibilidad[7] && vectorDisponibilidad[8] && vectorDisponibilidad[9] && vectorDisponibilidad[10] && vectorDisponibilidad[11]) == false) {
              strcpy(vm[vectorReserva[a].fecha.dia-1+calendario.PrimerDiaMes(reserva.fecha.anyo, TipoMes(reserva.fecha.mes-1))],"PA");
          } else {
              strcpy(vm[vectorReserva[a].fecha.dia-1+calendario.PrimerDiaMes(reserva.fecha.anyo, TipoMes(reserva.fecha.mes-1))],"TO");
          }
      }
  }
  printf("\n");
  printf("%s             %4d\n",nombremes,reserva.fecha.anyo);
  printf("===========================\n");
  printf("LU  MA  MI  JU  VI | SA  DO\n");
  printf("===========================\n");
  printf("%2s  %2s  %2s  %2s  %2s | %2s  %2s\n",vm[0],vm[1],vm[2],vm[3],vm[4],vm[5],vm[6]);
  printf("%2s  %2s  %2s  %2s  %2s | %2s  %2s\n",vm[7],vm[8],vm[9],vm[10],vm[11],vm[12],vm[13]);
  printf("%2s  %2s  %2s  %2s  %2s | %2s  %2s\n",vm[14],vm[15],vm[16],vm[17],vm[18],vm[19],vm[20]);
  printf("%2s  %2s  %2s  %2s  %2s | %2s  %2s\n",vm[21],vm[22],vm[23],vm[24],vm[25],vm[26],vm[27]);
  printf("%2s  %2s  %2s  %2s  %2s | %2s  %2s\n",vm[28],vm[29],vm[30],vm[31],vm[32],vm[33],vm[34]);
  if( strcmp(vm[35], ".") != 0 ) {
      printf("%2s  %2s  %2s  %2s  %2s | %2s  %2s\n",vm[35],vm[36],vm[37],vm[38],vm[39],vm[40],vm[41]);
  }
  printf("\n");
  printf("\n");
  printf("Pulse tecla y ENTER para salir\n");
  scanf("%s",&reserva.fecha.mes);
}
/*================================================================================================
Incializa vectorReservas
=================================================================================================*/
void GestionReservaSala::InicializarVectorReservas(TipoVectorReserva vectorReserva) {
  TipoReserva reserva;
  InicializarReserva( reserva );
  for (int a = 0; a < MaxReservas; a++) {
      strcpy(vectorReserva[a].nombre, "");
      strcpy(vectorReserva[a].apellido, "");
      vectorReserva[a].fecha.dia = 0;
      vectorReserva[a].fecha.mes = 0;
      vectorReserva[a].fecha.anyo = 0;
      vectorReserva[a].hora = 0;
      vectorReserva[a].duracion = 0;
      vectorReserva[a] = reserva;
  }
}
/*================================================================================================
Inicializa regsitro reserva
=================================================================================================*/
void GestionReservaSala::InicializarReserva(TipoReserva & reserva) {
  strcpy(reserva.nombre, "" );
  strcpy(reserva.apellido, "" );
  reserva.fecha.dia = 0;
  reserva.fecha.mes = 0;
  reserva.fecha.anyo = 0;
  reserva.hora = 0;
  reserva.duracion = 0;
}
/*================================================================================================
 Inserta los datos del registro reserva en vectorReservas
=================================================================================================*/
void GestionReservaSala::InsertarVectorReservas(TipoReserva reserva, TipoVectorReserva vectorReserva) {
  strcpy(vectorReserva[index].nombre,reserva.nombre);
  strcpy(vectorReserva[index].apellido,reserva.apellido);
  vectorReserva[index].fecha.dia = reserva.fecha.dia;
  vectorReserva[index].fecha.mes = reserva.fecha.mes;
  vectorReserva[index].fecha.anyo = reserva.fecha.anyo;
  vectorReserva[index].hora = reserva.hora;
  vectorReserva[index].duracion = reserva.duracion;
}
/*================================================================================================
 Comprueba que no supere el valor maximo de las reservas
=================================================================================================*/
bool GestionReservaSala::ComprobarCantReservas() {
  if (index < MaxReservas) {
      return true;
  } else {
      return false;
  }
}
/*================================================================================================
Comprueba que tamyo del nombre y apellidos no superes 20 chars
=================================================================================================*/
bool GestionReservaSala::ComprobarTamNombre(TipoCliente nombre, TipoCliente apellido) {
  if (strlen(strcat(nombre,apellido)) > 20) {
      return true;
  } else {
      return false;
  }
}
/*================================================================================================
Comprueba que los valores Fecha Hora Dia sean deseables para formar fecha, (no comprueba si la fecha es correcta)
=================================================================================================*/
bool GestionReservaSala::ComprobarFHD(int numero, TipoComprobacion comprobacion){
  if ( comprobacion == Dia) {
      if ( numero <= 0 || numero > 31 ) {
        return true;
      }
      else {
        return false;
      }
  } else if ( comprobacion == Mes) {
      if ( numero < MesActual || numero > MaxMes ) {
          return true;
      }else{
          return false;
      }
  }
  else if ( comprobacion == Anyo) {
      if ( numero < AnyoActual || numero > AnyoActual ) {
          return true;
      } else {
          return false;
      }
  } else if ( comprobacion == Hora) {
      if ( numero < HoraInicio || numero > 19) {
          return true;
      }else{
          return false;
      }
  }
  else if ( comprobacion == Duracion) {
      if ( numero <= 0 || numero > 12 ) {
        return true;
      } else{
          return false;
      }
  }
}

/*============================================================================================================
Funcion que devuelve verdadero si hay La hora y el dia indicado no esta ocupado
==============================================================================================================*/
bool GestionReservaSala::ComprobarDisponibilidadDiaHora(TipoFecha fecha, int hora, const TipoVectorReserva vectorReserva) {

  for (int a = 0; a < MaxReservas ; a++) {
      if (vectorReserva[a].fecha.dia == fecha.dia && vectorReserva[a].fecha.mes == fecha.mes && vectorReserva[a].fecha.anyo == fecha.anyo && vectorReserva[a].hora == hora ) {
          return false;
      }
  }
  return true;
}
/*============================================================================================================
Funcion que devuelve el numero de maximo de horas a reservar (sin tener en cuenta Si hay reserva)
como: hora + horaspermitidas = 20 ,entonces:  horaspermitidas = 20 - hora
==============================================================================================================*/
int GestionReservaSala::ComprobarMaximoPermitido(int hora) {
 int duracionpermitida;
 duracionpermitida = 20 - hora;
 return duracionpermitida;
}
/*============================================================================================================
Procedimiento que crea un vector que almacena los datos que coinciden en la misma fecha
este vector es usado para crear el vector disponibilidad
==============================================================================================================*/
void GestionReservaSala::CrearVectorMismaFecha(TipoFecha fecha, const TipoVectorReserva vectorReserva,TipoVectorMismaFecha vectorMismafecha) {
  int b = 0;
  InicializarVectorMismaFecha(vectorMismafecha);
  for (int a=0; a < MaxReservas; a++) {
      if( fecha.dia == vectorReserva[a].fecha.dia && fecha.mes == vectorReserva[a].fecha.mes && fecha.anyo == vectorReserva[a].fecha.anyo) {
          vectorMismafecha[b] = vectorReserva[a];
          b++;
      }
  }
}
/*================================================================================================
Crea el VectorDisponibilidad que es usado para comprobar las horas libres y ocupadas
=================================================================================================*/
void GestionReservaSala::CrearVectorDisponibilidad(TipoVectorMismaFecha vectorMismafecha, TipoVectorDisponibilidad vectorDisponibilidad) {
  int c = 0;
  int d = 0;
  InicializarVectorDisponibilidad(vectorDisponibilidad);
 /*--( hora -8 ) coincide con la posicion de vector disponibilidad--*/
  for (int a = 0; a < MaxTiempoReservas; a++) {
      if (vectorMismafecha[a].hora > 0 ) {
          for(int b =0 ; b < vectorMismafecha[a].duracion; b++) {
              vectorDisponibilidad[vectorMismafecha[a].hora-8+b]=true;
          }
      }
 }
}
/*================================================================================================
Comprobacion de si una fecha coincide con otra u otras
=================================================================================================*/
bool GestionReservaSala::ComprobarNoCoincideFecha(TipoFecha fecha, const TipoVectorReserva vectorReserva) {
  for (int a = 0; a < MaxReservas ; a++) {
      if (vectorReserva[a].fecha.dia == fecha.dia && vectorReserva[a].fecha.mes == fecha.mes && vectorReserva[a].fecha.anyo == fecha.anyo ) {
          return false;
      }
  }
      return true;
}
/*================================================================================================
Inicializa vectorDisponibilidad
=================================================================================================*/
void GestionReservaSala::InicializarVectorDisponibilidad(TipoVectorDisponibilidad vectorDisponibilidad) {
  for (int a = 0; a < MaxReservas; a++) {
      vectorDisponibilidad[a] = false;
  }
}
/*================================================================================================
Inicializa vectorMismafecha
=================================================================================================*/
void GestionReservaSala::InicializarVectorMismaFecha(TipoVectorMismaFecha vectorMismafecha) {
  for (int a = 0; a < MaxTiempoReservas; a++) {
      strcpy(vectorMismafecha[a].nombre, "") ;
      strcpy(vectorMismafecha[a].apellido, "") ;
      vectorMismafecha[a].fecha.dia = 0;
      vectorMismafecha[a].fecha.mes = 0;
      vectorMismafecha[a].fecha.anyo = 0;
      vectorMismafecha[a].hora = 0;
      vectorMismafecha[a].duracion = 0;
  }
}
/*================================================================================================
Comprueba si para una duracion determinada hay disponibilidad
=================================================================================================*/
bool GestionReservaSala::ComprobarDisponibilidadHorasDuracion (TipoFecha fecha, int hora, int duracion, const TipoVectorReserva vectorReserva) {
  bool libre = true;
  /*--Esta variable almacena la posicion en vectorDisponibilidad de la primera hora ocupada --*/
  int primerahora = hora -8;
  /*--En vector disponibilidad buscar si estan ocupadas desde primerahora hasta el fin de (f)horasocupada(primerahora+duracion)-1 --*/
  int fhorasocupada = (primerahora+duracion) -1 ;
  /*--Declaramos el vector que almacena las reservas con misma fecha--*/
  TipoVectorMismaFecha vectorMismafecha;
  /*--Declaramos el vector que almacena las horas ocupadas en una fecha--*/
  TipoVectorDisponibilidad vectorDisponibilidad;
  /*--Creamos el vector que almacena las reservas con misma fecha--*/
  CrearVectorMismaFecha(fecha, vectorReserva, vectorMismafecha);
  /*--Creamos el vector que almacena las horas ocupadas de una fecha--*/
  CrearVectorDisponibilidad(vectorMismafecha, vectorDisponibilidad);
  /*-- Recorremos vector disponibilidad para comprobar si hay horas libres (0) u ocupadas (1) --*/
  /*-- Desde posicion 0 hasta la posicion que nos interesa (fhorascupada)--*/
  for (int a = 0 ;  a <= fhorasocupada ; a++) {
    /*--Comparamos desde la primera hora que es la que preguntamos: si la primerahora esta ocupada?--*/
      if (a == primerahora) {
          if(vectorDisponibilidad[a] == true) {
              return false;
          }
      }
  }
  return true;
}
/*================================================================================================
 Comprueba que no se superen las reservas maximas para un mes
=================================================================================================*/
int GestionReservaSala::ComprobarCantReservasMes(const TipoVectorReserva vectorReserva, TipoFecha fecha) {
  int totalreservasmes = 0;
  for (int a = 0; a < MaxReservas; a++) {
      if ( vectorReserva[a].fecha.anyo == fecha.anyo && vectorReserva[a].fecha.mes == fecha.mes) {
          totalreservasmes = a;
      }
  }
  if (totalreservasmes != 0 ) {
          totalreservasmes = totalreservasmes+1;
  }
  return totalreservasmes+1;
}

