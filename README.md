# Sistema de Gestión de Expedientes Académicos

## Descripción del Proyecto
Este proyecto es un sistema para administrar información académica. El sistema carga registros de estudiantes desde un archivo `.csv` hacia la memoria principal, permitiendo organizar y consultar los expedientes de manera eficiente. Su objetivo es facilitar procesos como la generación de listas de asistencia (ordenadas alfabéticamente) y la asignación de becas (ordenadas por promedio).

## SICT0302B: Toma decisiones
**Selecciona un algoritmo de ordenamiento adecuado al problema**
Para este primer avance, la información almacenada en memoria se organiza mediante dos algoritmos de ordenamiento:
1. **Merge Sort:** Implementado para ordenar los expedientes alfabéticamente por `nombre`. Elegí este algoritmo porque tiene un redimiento eficiente para cadenas de texto.
2. **Insertion Sort:** Utilizado para ordenar los expedientes por `promedio` (de mayor a menor). Se seleccionó porque en escenarios reales donde la lista de alumnos de excelencia académica ya está parcialmente ordenada (o se agregan pocos registros a la vez), este algoritmo procesa los datos casi en un tiempo lineal.

## SICT0301B: Evalúa los componentes
**Hace un análisis de complejidad correcto y completo para todo el programa y sus componentes.**

* **Algoritmo Merge Sort (Ordenamiento por Nombre):** 
  * Complejidad temporal: $O(n \log n)$ en todos los casos, porque siempre divide la lista a la mitad (log n niveles) y luego une todos los elementos en orden (n comparaciones por nivel).
* **Algoritmo Insertion Sort (Ordenamiento por Promedio):**
  * Complejidad temporal: $O(n^2)$ en el promedio y peor de los casos, pero $O(n)$ en el mejor de los casos (cuando los promedios ya ingresan ordenados).
 
 ## SICT0303B: Implementa acciones científicas
**Implementa mecanismos de lectura de archivos correctos y útiles.**
El sistema cuenta con un módulo que lee el archivo `expedientes.csv`. Toma la matrícula, nombre, carrera y promedio de cada línea, instanciando objetos de la clase `Expediente`.
