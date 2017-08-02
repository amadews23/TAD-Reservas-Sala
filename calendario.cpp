/*****************************************************************
* NOMBRE: #Bartolome#
* PRIMER APELLIDO: #Vich#
* SEGUNDO APELLIDO: #Lozano#
* EMAIL: #amadews23@hotmail.com#
*****************************************************************/
/****************************************************************
* Módulo: calendario
*
* Descripción:
*   Procedimientos y funciones para la generacion del calendario
* , y realizar operaciones con de fechas
*
*****************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calendario.h"

/*=================================================================
  Función para ver si es bisiesto el año pasado como parámetro
  Son bisiestos los múltiplos de 4, salvo si son también mútiplos
  de 100, que han de ser múltiplos de 400;
  ================================================================*/
bool CalendarioMes::EsBisiesto( int anyo) {
  bool bisiesto;
  if ( anyo % 100 == 0 ) {
      if ( anyo % 400 == 0 ) {
          bisiesto = true;
      } else {
          bisiesto = false;
      }
 } else if ( anyo % 4 == 0 ) {
      bisiesto = true;
 } else {
      bisiesto = false;
 }
 return bisiesto;
}

/*=================================================================
  Funcion que devuelve el numero de dias de un mes
  teniendo en cuenta si es bisiesto
==================================================================*/
int CalendarioMes::NumeroDiasMes( TipoMes mes, bool bisiesto) {
  int ndias;
  switch (mes) {
      case Enero:
      case Marzo:
      case Mayo:
      case Julio:
      case Agosto:
      case Octubre:
      case Diciembre:
          ndias = 31;
          break;
      case Febrero:
          switch(bisiesto) {
              case false:
                  ndias = 28;
                  break;
              case true:
                  ndias = 29;
                  break;
          }
          break;
      case Abril:
      case Junio:
      case Septiembre:
      case Noviembre:
          ndias = 30;
          break;
  }
  return ndias;
}

/*=================================================================
  Funcion que devuelve los bisiestos acumulados para correr los dias
  de la semana en el calendario
===================================================================*/
int CalendarioMes::CalcularBisiestoAcumulado (int anyo) {
  int bisiestoacumulado;
  int b; // si el anyo actual es bisiesto vale uno, sino lo es vale 0, Se usara para restar es caso de ser bisiesto
  const int ainicial = 1600;

  if (EsBisiesto(anyo) == true) {
      b = 1;
  } else if (EsBisiesto(anyo) == false) {
      b = 0;
  }
  bisiestoacumulado = (anyo - ainicial)/4;
  if (anyo >= 1601 && anyo < 1700 ) {
      return (bisiestoacumulado)-b ;
  } else if (anyo >= 1700 && anyo < 1800) {
      return (bisiestoacumulado-1)-b;
  } else if (anyo >= 1800 && anyo < 1900) {
      return (bisiestoacumulado-2)-b;
  } else if (anyo >= 1900 && anyo < 2000) {
      return (bisiestoacumulado-3)-b;
  } else if (anyo >= 2000 && anyo < 2100) {
      return (bisiestoacumulado-3)-b;
  } else if (anyo >= 2100 && anyo < 2200) {
      return (bisiestoacumulado-4)-b;
  } else if (anyo >= 2200 && anyo < 2300) {
      return (bisiestoacumulado-5)-b;
  } else if (anyo >= 2300 && anyo < 2400) {
      return (bisiestoacumulado-6)-b;
  } else if (anyo >= 2400 && anyo < 2500) {
      return (bisiestoacumulado-6)-b;
  } else if (anyo >= 2500 && anyo < 2600) {
      return (bisiestoacumulado-7)-b;
  } else if (anyo >= 2600 && anyo < 2700) {
      return (bisiestoacumulado-8)-b;
  } else if (anyo >= 2700 && anyo < 2800) {
      return (bisiestoacumulado-9)-b;
  } else if (anyo >= 2800 && anyo < 2900) {
      return (bisiestoacumulado-9)-b;
  } else if (anyo >= 2900 && anyo < 3000) {
      return (bisiestoacumulado-10)-b;
  } else if (anyo == 3000) {
      return (bisiestoacumulado-11)-b;
  }
}

/*==================================================================
 Calcula el primer dia de la semana del mes de Enero
====================================================================*/
int CalendarioMes::PrimerDiaMesEnero(int anyo) {
  int unodeEnero;
  const int ai = 1601;
  int bisiestoacumulado , diferenciaanyos;
  bisiestoacumulado = CalcularBisiestoAcumulado(anyo);
  diferenciaanyos = anyo - ai;
  unodeEnero = (bisiestoacumulado + diferenciaanyos)%7;
  return unodeEnero;
}

/*==================================================================
 Sabiendo el primer dia de la semana de Enero devuelve el primer dia
 de la semana del mes solicitado
====================================================================*/
int CalendarioMes::PrimerDiaMes(int anyo, TipoMes mes) {
  int unodeEnero;
  int primerdia;
  int b;
  b = 0;
  //Calculo de primer dia del anyo
  unodeEnero = PrimerDiaMesEnero(anyo);
  if (EsBisiesto(anyo) == true){
      b = 1;
  }
  //Si el anyo es bisiesto Y Si el mes es inferior a Marzo tabla de meses
  if ( mes == Enero ) {
      primerdia = unodeEnero;
  } else if (mes == Febrero) {
      primerdia = unodeEnero + 3;
  } else if ( mes == Marzo || mes == Noviembre) {
      primerdia = unodeEnero + 3 +b;
  } else if ( mes == Abril || mes == Julio) {
      primerdia = unodeEnero + 6 +b;
  } else if ( mes == Mayo ) {
      primerdia = unodeEnero + 1+b;
  } else if ( mes == Junio) {
      primerdia = unodeEnero + 4+b;
  } else if ( mes == Agosto ) {
      primerdia = unodeEnero + 2+b;
  } else if ( mes == Diciembre || mes == Septiembre) {
      primerdia = unodeEnero + 5+b;
  } else if ( mes == Octubre ) {
      primerdia = unodeEnero+b;
  }
  if ( primerdia > 6) {
      primerdia = primerdia%7;
  }
  return primerdia;
//Si el anyo es bisiesto Y Si el mes es Mayor o Igual Marzo tabla de meses + 1
//Si el mes no es bisiesto Y el anyo anterior lo fue: AND mes es == Febrero, +1
//Si el mes no es bisiesto y el anyo anterior no lo fue tabla meses
}

/*==================================================================
 Crea el VectorMes, almacenando el numero de mes y puntos e
 imprimiendo el nombre de mes y anyo
====================================================================*/
void CalendarioMes::CrearMes(int mes, int anyo, TipoVectorMes vm, TipoNombreMes nombremes ) {

  int espacios_i, espacios_f, ndiasmes;
  // TipoVectorMes vm;
  //  reservas.CrearVectorMismoMes(mes, anyo, vectorReserva, vm);
  if (mes == 0) {
      strcpy(nombremes, "ENERO     ");
  } else if (mes == 1) {
      strcpy(nombremes, "FEBRERO   ");
  } else if (mes == 2) {
      strcpy(nombremes, "MARZO     ");
  } else if (mes == 3) {
      strcpy(nombremes, "ABRIL     ");
  } else if (mes == 4) {
      strcpy(nombremes, "MAYO      ");
  } else if (mes == 5) {
      strcpy(nombremes, "JUNIO     ");
  } else if (mes == 6) {
      strcpy(nombremes, "JULIO     ");
  } else if (mes == 7) {
      strcpy(nombremes, "AGOSTO    ");
  } else if (mes == 8) {
      strcpy(nombremes, "SEPTIEMBRE");
  } else if (mes == 9) {
      strcpy(nombremes, "OCTUBRE   ");
  } else if (mes == 10) {
      strcpy(nombremes, "NOVIEMBRE ");
  }
  espacios_i = PrimerDiaMes(anyo, TipoMes(mes));
  ndiasmes = NumeroDiasMes( TipoMes(mes),EsBisiesto(anyo));
  espacios_f = maxceldas - (espacios_i + ndiasmes);

  for (int a = 0; a < espacios_i; a++) {
      strcpy(vm[a],".");
  }
  for (int a = 1; a < ndiasmes+1; a++) {
      sprintf(vm[(espacios_i-1)+a], "%d", a);
  }
  for (int a = 0; a < espacios_f; a++) {
      strcpy(vm[(espacios_i+ndiasmes)+a],".");
  }
}

/*===================================================================
 Comprueba si la fecha es valida
=====================================================================*/
bool CalendarioMes::FechaCorrecta(int dia, int mes, int anyo) {
  bool bisiesto;
  int ndias;
  bisiesto = EsBisiesto(anyo);
  ndias = NumeroDiasMes(TipoMes(mes-1), bisiesto);
  if (dia <= ndias) {
      return true;
  } else {
      return false;
  }
}

/*====================================================================
 Comprueba si un dia es Sabado o Domingo
======================================================================*/
bool CalendarioMes::ComprobarDiaLaborable(int dia, int mes, int anyo) {
  const int maxceldas = 42;
  typedef int TipoVectormes[maxceldas];
  int espacios_i, espacios_f, ndiasmes;
  TipoVectormes vm;
  espacios_i = PrimerDiaMes(anyo, TipoMes(mes));
  ndiasmes = NumeroDiasMes( TipoMes(mes),EsBisiesto(anyo));
  espacios_f = maxceldas - (espacios_i + ndiasmes);
  for (int a = 0; a < espacios_i; a++) {
      vm[a]=0;
  }
  for (int a = 1; a < ndiasmes+1; a++) {
      vm[(espacios_i-1)+a]= a ;
  }
  for (int a = 0; a < espacios_f; a++) {
      vm[(espacios_i+ndiasmes)+a]=0;
  }

  if (dia == vm[5] || dia == vm[6] || dia == vm[12] || dia == vm[13] || dia == vm[19] || dia == vm[20] || dia == vm[26] || dia == vm[27] || dia == vm[33] ||dia == vm[34] ) {
      return false;
  } else {
      return true;
  }
}
