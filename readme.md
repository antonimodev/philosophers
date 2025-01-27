# Philosophers

El proyecto Philosophers es un clásico problema de concurrencia que simula una situación en la que varios filósofos están sentados alrededor de una mesa redonda, alternando entre pensar, comer y dormir. Cada filósofo necesita dos tenedores para comer, pero solo hay un tenedor entre cada par de filósofos, lo que puede generar problemas de sincronización como condiciones de carrera o interbloqueos (*deadlocks*). El objetivo es implementar una solución eficiente y segura para gestionar estos recursos compartidos.

## Objetivo

Implementar una solución en C que:
- Permita que los filósofos coman, piensen y duerman de forma concurrente.
- Evite condiciones de carrera y deadlocks mediante el uso adecuado de primitivas de sincronización como hilos (*threads*) y mutexes (*mutual exclusion locks*).
- Asegure el correcto registro de los estados y tiempos de cada filósofo.
- Cumpla con las normas de programación establecidas por la escuela 42.

## Requisitos del proyecto

### Argumentos

El programa debe aceptar los siguientes argumentos:

- **number_of_philosophers**: Número de filósofos sentados a la mesa.
- **time_to_die**: Tiempo (*en milisegundos*) que un filósofo puede estar sin comer antes de morir.
- **time_to_eat**: Tiempo (*en milisegundos*) que tarda un filósofo en comer.
- **time_to_sleep**: Tiempo (*en milisegundos*) que tarda un filósofo en dormir.
- **number_of_times_each_philosopher_must_eat** (*opcional*): Número de veces que cada filósofo debe comer antes de que el programa termine. Si no se especifica, el programa debe continuar indefinidamente hasta que uno de los filósofos muera.

## Restricciones

- No se permite el uso de variables globales.
- Cada función debe tener como máximo 25 líneas.
- Está prohibido usar for, do...while, switch/case, y arrays de longitud variable.
- Uso estricto de primitivas de sincronización de la biblioteca pthread (como pthread_mutex_t).

## Ejemplo de ejecución:
```
./philo 4 410 200 200 10
```
## Formato de salida
```
[timestamp_in_ms] [philosopher_id] está pensando
[timestamp_in_ms] [philosopher_id] está comiendo
[timestamp_in_ms] [philosopher_id] está durmiendo
[timestamp_in_ms] [philosopher_id] ha muerto
```
### Ejemplo en terminal
<img src="https://github.com/antonimodev/philosophers/blob/main/img/philos_alive.png" alt="Philosophers alive" width="400"/>
<img src="https://github.com/antonimodev/philosophers/blob/main/img/philos_died.png" alt="Philosophers dead" width="400"/>