# Sistema de Gestión de Expedientes Académicos

## Descripción del Proyecto
Este proyecto es un sistema para administrar información académica. El sistema carga registros de estudiantes desde un archivo `.csv` hacia la memoria principal, permitiendo organizar y consultar los expedientes de manera eficiente. Su objetivo es facilitar procesos como la generación de listas de asistencia (ordenadas alfabéticamente) y la asignación de becas (ordenadas por promedio).

## SICT0302B: Toma decisiones
**Selecciona un algoritmo de ordenamiento adecuado al problema**
Para este primer avance, la información almacenada en memoria se organiza mediante dos algoritmos de ordenamiento:
1. **Merge Sort:** Implementado para ordenar los expedientes alfabéticamente por `nombre`. Elegí este algoritmo porque tiene un redimiento eficiente para cadenas de texto.
2. **Insertion Sort:** Utilizado para ordenar los expedientes por `promedio` (de mayor a menor). Se seleccionó porque en escenarios reales donde la lista de alumnos de excelencia académica ya está parcialmente ordenada (o se agregan pocos registros a la vez), este algoritmo procesa los datos casi en tiempo lineal.
