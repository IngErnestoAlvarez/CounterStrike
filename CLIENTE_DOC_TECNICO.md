# Semana a Semana

## Semana 1

La primera semana pusimos a prueba los frameworks a utilizar. Del lado del cliente
Estos serían SDL2.0.

Se hicieron pruebas del estilo "front-end" en las cuales se testeaban las funciones
que el framework SDL2.0 proveía, como el uso del teclado, o el uso del mouse o 
imprimir objetos en la pantalla.

Todo esto no fue implementado en el proyecto principal. Fueron programas piloto en
los cuales cada uno cubría una parte del framework, haciendo que sea mas vivida la interacción con sus partes.

Cabe destacar también la incorporación de estos frameworks al programa principal. Sin
problemas de dependencia y la detección de las librerias utilizadas.

## Semana 2

Como SDL2.0 es una extensa y programada, mayoritariamente, en C. Decidimos wrappear el framework para que cumpla con nuestro decisión de trabajo (RAII), conviertiendo el manejo de punteros y memoria dinámica, asi como un paradigma más funcional, en un estilo de programación RAII, orientado a objectos y basado en el stack.

## Semana 3

Si bien gran parte de la semana fue dedicada a continuar con el trabajo de la anterior (conversion del framework SDL2.0), también se pudó comenzar a trabajar en el proyecto principal. Creando la estructura que iba a tener nuestro proyecto.

Como objetivo, el comienzo del proyecto fue basado en la construccion de 1 solo programa single-threaded en el cual habia una conexion directa entre el back-end y el front-end del videojuego, pudiendonos enfocar primeramente en la jugabilidad, funcionalidad y estetica de este.

## Semana 4

La primera vista de nuestro proyecto fue hecha en esta semana. Habiendo tenido ya una base solida en la que se pueda desarrollar, las primeras animaciones e imagenes ya eran parte de la ejecución.

Se implementó: El movimiento de la camara, el stencil para simular la vista del personaje (Que este rote con la camara), la movilidad del personaje y la musica.

## Semana 5

Semana en la que se implementaron los detalles restantes de la UI: Vista de la salud del personaje, de las balas del arma portada, del dinero restante, asi como el sonido de las armas.

También se decidió el protocolo a utilizar para trasladar el núcleo del videojuego a un programa/servidor. Deciendo la manera de desprender completamente las partes para poder generar un videojuego multijugador.

## Semana 6

Se hizo el traslado de manera eficiente del núcleo a una aplicacion back-end. Se generaron las conexiones entre el cliente y el servidor. Asi como también se implementó el disparo entre personajes.

Fue el comienzo del desarrolo de la pantalla de compra asi como de la vista de la cantidad de rondas que lleva el juego.

## Semana 7

Se finaliza la pantalla de compra, añadiendo todas las armas necesarias para el juego. 

Se añaden las vistas para cada arma dentro del juego.

Se crea la vista de la bomba dentro del escenario. Finalizando con la mecánica de planta y desplantar la bomba.

Se crea la pantalla de derrota/victoria despues de cada ronda.

Comienzo de la pantalla final del programa.


## Semana 8

Finalización de la pantalla final, con los puntajes de cada usuario: asesinatos, muertes y dinero recolectado.

Solución de bugs y optimizaciones al modelo dentro del escenario para soportar multiples partidas en simultaneo.
