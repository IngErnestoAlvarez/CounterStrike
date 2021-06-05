# CounterStrike
Counter Strike en 2D

## Configuracion

1. Descargar cmake: 
```bash
apt-get install cmake
```

2. Clonar el repositorio dentro de la carpeta lib. (Si no está
la carpeta lib, crearla)
. tiene que quedar `/lib/googletest`


## Correr pruebas y programa

1. Estar dentro de la carpeta build (Si no está crearla):
```bash
cd build
```

2. ejecutar el comando para debug
```bash
cmake .. -D CMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
```

3. Dentro de build correr los Makefiles generados pro cmake:
```bash
make all
make CounterStrike_run
make CounterStrike_tst
```

4. Dentro de la carpeta *build* habrá carpetas *src*, *test*:

    - En la carpeta *src* para ejecutar el programa:
    ```bash
    cd build/src
    ./CounterStrike_run
    ```

    - En *test* para ejecutar las pruebas:
    ```bash
    cd build/test
    ./CounterStrike_tst
    ```
