# CounterStrike
Counter Strike en 2D

# Especificaciones
Obligatorio: Sistema basado en linux.

Recomendado: Utilizar Ubuntu v20.

Se asume que se tienen instaladas las herramientas: g++, cmake, makeFile, git y todas sus dependencias.

# Instalacion:

`sudo apt-get install  libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`

`sudo apt-get install libsdl2`

`sudo apt-get install libyaml-cpp-dev`

`sudo apt-get install libbox2d-dev`

`sudo apt-get install cimg-dev`

`git clone https://github.com/IngErnestoAlvarez/CounterStrike.git`

# Compilacion

Desde la carpeta principal del proyecto, despues de haber instalado las dependencias, ejecutar lo siguiente:

- ``` 
	mkdir build
  ```
- ```
	cd build
  ```
- ```
	cmake ..
  ```
- ```
	make
  ```

- ```
	cd ..
  ```

# Ejecucion

### Servidor:

``` 
./build/CounterStrike_server config/config.yaml 
```

### Cliente:

``` 
./build/CounterStrike_run <TeamID> 
```

Donde \<TeamID\> es el equipo a elegir. (1 o 2)

# Controles:

- **AWSD** para el movimiento
- *Click Izquierdo* para disparar
- **1** para elegir el arma principal
- **2** para elegir el arma secundaria
- **3** para elegir el cuchillo
- **4** para plantar la bomba
- **e** para desactivar la bomba
