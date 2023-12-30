# Trash Collector

Este proyecto es un juego simple desarrollado en C++ utilizando la biblioteca SFML. El objetivo del juego es recolectar la basura que cae del cielo con un contenedor móvil, evitando las colisiones con las bolsas de basura. A continuación, se proporciona información sobre la estructura del proyecto, las dependencias necesarias, instrucciones de compilación y uso, así como detalles sobre cómo contribuir al proyecto.

## Introducción

Trash Collector es un juego desarrollado como parte de un proyecto de para la clase de Tecnologia de Objetos. El juego utiliza SFML para la manipulación de gráficos y sonido. El objetivo principal del juego es recolectar basura mientras evitas colisionar con obstáculos.

## Dependencias

- g++
- SFML
  - sfml-graphics
  - sfml-audio
  - sfml-window
  - sfml-system


## Instrucciones de Compilación

Para compilar el proyecto, con g++ sigue estos pasos:
```bash
g++ -o main src/main.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
```

Para compilar el proyecto, con Cmake sigue estos pasos:
```c++
mkdir build
cd build
cmake ..
make

```

## Contributing

Una vez compilado, ejecuta el juego con el siguiente comando en la carpeta build o donde se haga compilado:

```c++
./main
