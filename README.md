# TAD-Reservas-Sala
Example of type abstract data

Se compone de 2 Tipos Abstractos de Datos: CalendarioMes y GestionReservasSala.

El programa está formado por:

-Programa principal: reservas.cpp

-Calendario: interfaz calendario.h e implementación: calendario.cpp

-GestionReservasSala: interfaz GestionReservasSala.h e Implementación: GestionReservasSala.cpp

## Tipo Abstracto CalendarioMes: Funciones y procedimientos :

### Públicos:

BoolComprobarDiaLaborable, Devuelve true o false si un dia es Sábado o Domingo.

Bool FechaCorrecta, Devuelve true o false si la fecha está bien formada.

Int PrimerDiaMes, calcular primer dia de la semana a partir del primer dia de la semana de Enero.

Void CrearMes, crea el vectorMes

### Privados:

Int NumeroDiasMes, número de dias que tiene un mes

Bool EsBisiesto, comprobar si un año es bisiesto.

Int CalcularBisiestoAcumulado:, usado para calcular el primer dia de semana de Enero.

Int PrimerDiaMesEnero, calcular primer dia de la semana de Enero.

## Tipo Abastracto GestionReservasSala: Funciones y procedimientos:

### Públicos:

Void NuevaReserva

Void AnularReserva

Void ReservasdelDia

Void ReservasdelMes

Void InicializarVectorReservas, inicializa elementos

### Privados:

Int BuscarReserva, busca una reserva determinada y devuelve el indice del vectorReservas, sino la
encuentra devuelve 100

Void InicializarReserva, inicializa registro reserva

Void InicializarVectorDisponibilidad

Void InicializarVectorMismaFecha

Void InsertarVectorReservas, inserta el registro reserva en vectorReservas.

Void BorrayOrdenaReserva, sobreescribe la reserva encontrada en la función anterior corriendo los
elementos del vectorReserva hacia abajo

Void ComprobarCantReservas, comprueba que no se superen el total de reservas permitidas.

Bool ComprobarCantReservasMes, comprueba que no exceda las reservas maximas para el mes.

Bool ComprobarTamNombre, comprueba que el nombre del cliente no exceda de 20 caracteres.

Bool ComprobarFHD, comprueba que los valores permitidos para fecha, hora y dia.

Bool ComprobarDisponibilidadDiaHora, comprueba si una fecha y hora están ocupados

Bool ComprobarMaximoPermitido, comprueba que se cumpla el maximo de horas permitidos para
una hora determinada.

Bool ComprobarNoCoincideFecha, si una fecha coincide con otra almacenada en vectorReservas.

Bool ComprobarDisponibilidadHorasDuracion, comprueba si para una hora y duración determinadas
es posible reservar.

Void CrearVectorMismaFecha, crea el vectorMismafecha con las reservas que tengan la misma fecha.

Void CrearVectorDisponibilidad, crea el vectorDisponoibilidad de tipo bool que cada elemento es una
hora si el elemento es True la hora esta ocupada si False esta libre.

## Registros(struct):

### En GestionReservasSala:

TipoFecha, compuesto por {dia, mes, anyo}

TipoReserva, compuesto de { nombre, apellido, fecha { dia, mes, anyo}, hora, duracio }

## Vectores:

### Para GestionReservaSala:

TipoVectorReservas, compuesto por el registro TipoReserva.

TipoVectorMismafecha, compuesto por el registro TipoReserva.

TipoVectorDisponibilidad de tipo bool

### Para CalendarioMes:

usa el vectorMes. De tipo celda

Vectores, cadenas de caracteres:

GestionReservasSala: TipoNombre : nombre, apellidos

CalendarioMes: TipoCelda,

## Tipos Enumerados:

GestionResevasSala: TipoComprobacion { Dia, Mes, Anyo, Duracion}

CalendarioMes: TipoDia, TipoMes

## Constantes.

GestionReservasSala: MaxReservas, MaxTiempoReservas, HoraInicio, MesActual, MaxMes,
MaxReservasMes, AnyoActual.

Nos restringen el año, primer mes y ultimo mes con el que se puede trabajar.
Así como el número de reservas máximo por mes y en total. Tamaño máximo de nombre de cliente y
los tiempos máximos para reservar, 12h desde las 8

CalendarioMes: Maxceldas

## Sobre el funcionamiento:

Una vez elegida la opción del menú principal accedemos a la sección deseada.

Al introducir los datos se realiza una primera comprobación (si los números son correctos dentro de los
valores deseables para un día, mes o año). Despúes va realizando otras comprobaciones como si un día y hora estan
ocupados, si la fecha es correcta, si no es Sábado o Domingo, y después si existen horas dentro de lo solicitado y si se
han alcanzado el máximo de reservas por mes.

Vuelve a preguntar individualmente (dia, mes, año) al introducir un valor "no deseable".

Vuelve a preguntar desde dia (otra vez todo menos nombre), lanza su correspondiente mensaje, cuando detecta
que un día no está bien formado, no es laboral, la fecha no está disponible u horas estan ocupadas.

## Aspectos a terner en cuenta:

Este programa es una práctica en C+- (Subconjunto de C y C++) para la UNED, Asignatura Fundamentos de la programación.
Al introducir nombre, sólo manejará un espacio entre nombre y apellido, no es posible poner un segundo
apellido.

A la hora de anular una reserva en el nombre del cliente el programa NO diferencia entre mayúsculas y
minúsculas, pero SI espacios.

## Limitaciones:
Sólo es posible realizar consultas para el periodo comprendido entre Enero y Marzo del 2017. Está limitado por constantes,
por lo tanto sería posible aumentar el periodo.
Y Sólo se podrán realizar un máximo de 20 consultas por mes.
