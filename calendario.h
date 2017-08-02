/********************************************************
* NOMBRE: #Bartolome#
* PRIMER APELLIDO: #Vich#
* SEGUNDO APELLIDO: #Lozano#
* EMAIL: #amadews23@hotmail.com#
********************************************************/
/*******************************************************
* Interfaz de módulo: calendario
*
* Descripción:
*   Procedimientos y funciones para la impresión de un
*   calendario, y manejo de fechas
*
********************************************************/
#pragma once

/*=================================================================
 Declaración de constantes, Tipos y variables globales
 ================================================================*/
extern bool bisiesto;
typedef enum TipoDia { Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo } ;
typedef enum TipoMes { Enero, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre };
typedef char TipoNombreMes[11];
typedef char Tipocelda[3];
const int maxceldas = 42;
typedef int TipoVectormes[maxceldas];
typedef Tipocelda TipoVectorMes[maxceldas];

typedef struct CalendarioMes {

  /*============================================================================================================
  Funcion que devuelve verdadero si la fecha es correcta,
  ==============================================================================================================*/
  bool FechaCorrecta(int dia, int mes, int anyo);
  /*============================================================================================================
  Procedimiento para dibujar Calendario
  =============================================================================================================*/
  void CrearMes(int mes, int anyo, TipoVectorMes vm, TipoNombreMes nombremes);
  /*============================================================================================================
  Funcion que devuelve verdadero si el dia es laborable,
  ==============================================================================================================*/
  bool ComprobarDiaLaborable(int dia, int mes, int anyo);
  /*=============================================================================================================
  Calcula 1º dia de la semana del mes solicitado
  =============================================================================================================*/
  int PrimerDiaMes(int anyo, TipoMes mes);

 private:
   /*=============================================================================================================
  Es bisiesto un anyo?
  =============================================================================================================*/
  bool EsBisiesto( int anyo);
  /*=============================================================================================================
  Numero de dias de un mes
  =============================================================================================================*/
  int NumeroDiasMes (TipoMes mes, bool bisiesto);
  /*=============================================================================================================
  Bisiestos acumulados
  =============================================================================================================*/
  int CalcularBisiestoAcumulado (int anyo);
  /*=============================================================================================================
  primer dia de la semana de Enero
  =============================================================================================================*/
  int PrimerDiaMesEnero(int anyo);

};
