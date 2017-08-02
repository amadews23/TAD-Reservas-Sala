/********************************************************
* NOMBRE: #Bartolome#
* PRIMER APELLIDO: #Vich#
* SEGUNDO APELLIDO: #Lozano#
* EMAIL: #amadews23@hotmail.com#
********************************************************/
/*********************************************************************
* INTERFAZ de Módulo: GestionReservasSala , PRACTICA 4
*
* Descripción:
*   Procedimientos y funciones para manejo de reservas
*
*********************************************************************/
#pragma once
/*=================================================================
 Declaración de constantes, Tipos y variables globales
 La practica 4 dice: "20 reservas por mes" y
 "3 meses maximos desde el actual" MesActual 1(Enero) AnyoActual 2017
 ================================================================*/

const int MaxReservas = 63;       /*Como solo se pueden hacer 20 reservas por (3)mes como 20*3=60 +3 */
const int MaxTiempoReservas = 12; /*Maximo de horas para reservar*/
const int TamanyoNombre = 21;     /*El tamanyo maximo del nombre es 20 +1 para \0*/
const int HoraInicio = 8;
const int MesActual = 1;          /*El numero de mes minimo para reservar*/
const int MaxMes = 3;             /*El numero de mes maximo para reservar */
const int MaxReservasMes = 21;     /*El nº maximo de reservas para un mes+1*/
/*const int MaxReservasMes = 3;*/   /*Esta linea comentada es para poder probar con 2 reservas maximas por mes(2+1)*/
const int AnyoActual = 2017;      /*El anyo de inicio permitido es 2017*/
extern int numReservas;
extern int numeroreserva;

typedef char TipoCliente[TamanyoNombre];
//enum para decidir como comportarse la funcion comprobacion Fecha-Hora-Duracion(FHD)
typedef enum TipoComprobacion { Dia, Mes, Anyo, Hora, Duracion };

typedef bool TipoVectorDisponibilidad[MaxReservas];

typedef struct TipoFecha {
  int dia;
  int mes;
  int anyo;
};

typedef enum TipoEstado { libre, ocupado };

typedef struct TipoReserva {
  TipoCliente nombre;
  TipoCliente apellido;
  TipoFecha fecha;
  int hora;
  int duracion;
};

/*-- Vector Reserva donde se almacenan las reservas--*/
typedef TipoReserva TipoVectorReserva[MaxReservas+1];

/*-- Vector que sera usado para reservas del mismo dia y generar apartir de el el vectorDisponibilidad--*/
typedef TipoReserva TipoVectorMismaFecha[MaxTiempoReservas];

/*-- Tipo Abstracto GestionReservaSala --*/
typedef struct GestionReservaSala {
  /*-- Procedimiento para solicitar datos para nueva reserva--*/
  void NuevaReserva(TipoVectorReserva vectorReserva);
  /*-- Procedimiento para solicitar datos para anular reserva--*/
  void AnularReserva(TipoVectorReserva vectorReserva);
  /*-- Procedimiento que solicita datos y muestra la reservas del dia --*/
  void ReservasdelDia(TipoVectorReserva vectorReserva);
  /*-- Procedimiento que solicita datos y muestra las reservas del dia --*/
  void ReservasdelMes(TipoVectorReserva vectorReserva);
  /*-- Inicializa el vectorResrva--*/
  void InicializarVectorReservas(TipoVectorReserva vectorReserva);

 private:
   /*--  Funcion para devolver el indice del vectorReserva de una reserva dada--*/
  int BuscarReserva(TipoReserva reserva, const TipoVectorReserva vectorReserva);
  /*-- Procedimiento que sobreescribe la reserva a anular y bajando la posicion del resto de elementos--*/
  void BorrayOrdenaReserva(TipoReserva reserva, TipoVectorReserva vectorReserva, int numeroreserva);
   /*-- Inserta los datos del registro Tiporeserva en VectorReserva--*/
  void InsertarVectorReservas(TipoReserva reserva, TipoVectorReserva vectorReserva);
  /*-- Procedimiento para inicializar el registro reserva --*/
  void InicializarReserva(TipoReserva & reserva);
  /*-- Procedimiento para incializar el vector disponibilidad --*/
  void InicializarVectorDisponibilidad(TipoVectorDisponibilidad vectorDisponibilidad);
  /*-- Procedimiento para inicializar el vectorMismafecha--*/
  void InicializarVectorMismaFecha(TipoVectorMismaFecha vectorMismafecha);
  /*-- Procedimiento que crea el vectorMismaFecha que almacena datos de reservas con la misma fecha--*/
  void CrearVectorMismaFecha(TipoFecha fecha,const TipoVectorReserva vectorReserva,TipoVectorMismaFecha vectorMismafecha);
  /*-- Procedimiento que crea el vectorDisponibilidad que almacena las horas ocupadas para un dia determinado--*/
  void CrearVectorDisponibilidad(TipoVectorMismaFecha vectorMismafecha, TipoVectorDisponibilidad vectorDisponibilidad);
  /*-- Funcion que comprueba que no exceda el maximo de reserva en total--*/
  bool ComprobarCantReservas();
  /*--Funcion que devuelve el numero de maximo de horas a reservar (sin tener en cuenta Si hay reserva) --*/
  int ComprobarMaximoPermitido(int hora);
  /*-- Funcion que devuelve verdadero si hay disponibilidad el Dia y La Hora --*/
  bool ComprobarDisponibilidadDiaHora(TipoFecha fecha, int hora ,const TipoVectorReserva vectorReserva);
  /*--Funcion que devuelve verdadero si coincide la fecha--*/
  bool ComprobarNoCoincideFecha(TipoFecha fecha, const TipoVectorReserva vectorReserva);
  /*--Funcion que devuelve verdadero si hay disponibilidad  la Hora y la Duracion indicada--*/
  bool ComprobarDisponibilidadHorasDuracion(TipoFecha fecha, int hora, int duracion ,const TipoVectorReserva vectorReserva);
  /*-- Funcion que comprueba que entre el nombre y el apellido no superen 20 chars--*/
  bool ComprobarTamNombre(TipoCliente nombre, TipoCliente apellido);
  /*-- Funcion que comprueba que los valores introducidos cumplen los valores minimos deseados para una fecha--*/
  bool ComprobarFHD(int numero, TipoComprobacion comprobacion);
  /*-- Funcion que devuelve el numero de reservas que lleva el mes--*/
  int ComprobarCantReservasMes(const TipoVectorReserva vectorReserva, TipoFecha fecha);
 // void OrdenaVectorReserva( TipoVectorReserva vectorReserva, int index );
};
