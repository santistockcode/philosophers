*Este proyecto ha sido creado como
parte del currículo de 42 por saalarco*

## Description

Pistas: 

1. Time to die es "desde que empezó a comer"-

2. un tenedor no es el mutex en sí, un tenedor es un puntero, de forma que puedo hacer un bucle con:
    - mutex sobre el puntero
    - puntero
    - chequear si debo morir
    - repeat

3. Para un número par de filósofos por narices desde que termina de comer hasta que vuelva a comer cómo mínimo (dependiendo del time to sleep) va a pasar el mismo time to eat (hasta que los otros 2 dejen los tenedores); para un número impar de filósofos (por ejemplo 3) por narices va a pasar el time to eat X2 (hasta que coman los otros dos).

4. number_of_times_each_philosopher_must_eat se define como "al menos", una vez se ha alcanzado puedo hacer varias cosas, o bien se levanta de la mesa y ya no come más, o bien sigue comiendo hasta que todos hayan comido ese número mínimo (ahí hago lo que quiera).

5. Un deadlock es cuando dos rutinas intentan acceder a las mismas variables tal que: 
    - rutina 1 intenta acceder a 'b' que está siendo usada por rutina 2 y se queda esperando en 'a' hasta que termine y mientras tanto:
    - rutina 2 intenta acceder a 'a' que está siendo usada por rutina 1 y por tanto se queda esperando en 'b' hasta que termine y mientras tanto... etc ad infinitum.

## Instructions

## Resources

- Danielaco23 42.Philosophers