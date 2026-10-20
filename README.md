# Sistema de Gestión de Expedientes Académicos y Administrativos

## Descripción del Proyecto
Este proyecto implementa un sistema administrativo y académico centralizado para gestionar expedientes de estudiantes universitarios. A partir de una base de datos en formato `.csv`, el programa carga los registros en estructuras de datos dinámicas en memoria principal, permitiendo:
1. Consultar el padrón completo de alumnos registrados.
2. Dar de alta nuevos expedientes o dar de baja registros existentes por matrícula.
3. Reorganizar el padrón por distintos parámetros según la necesidad administrativa: **orden alfabético por nombre** (para listas de asistencia) o **orden descendente por promedio** (para listados de excelencia y mérito académico).
4. Realizar consultas rápidas por **rangos de promedio** (por ejemplo, candidatos a beca entre `90.0` y `100.0`, o alumnos en situación de regularización) aprovechando una estructura de árbol que mantiene el orden natural de los datos.
5. Persistir cualquier alta, baja o nuevo ordenamiento escribiendo los cambios directamente en el archivo `expedientes.csv`.

---

## SICT0302B: Toma decisiones

### 1. Selecciona y usa una estructura lineal adecuada al problema
Se implementó desde cero una **Lista Doblemente Ligada (`DList`)** mediante plantillas en el archivo `DList.h`. 
* **Justificación técnica:** Se eligió una lista doblemente encadenada en lugar de un arreglo estático o `std::vector` porque el padrón de alumnos sufre inserciones y eliminaciones dinámicas durante la ejecución, además de requerir reordenamientos constantes de sus enlaces sin realocar bloques completos de memoria contigua. Al contar con los punteros `head` y `tail`, insertar un nuevo alumno al final (`addLast`) toma tiempo constante $O(1)$, y cada nodo (`DLink`) mantiene referencias tanto al siguiente (`next`) como al anterior (`previous`), permitiendo desconectar cualquier nodo para eliminarlo en tiempo constante $O(1)$ una vez localizado.
* **Ubicación en el código:** Las operaciones de inserción (`addLast`), búsqueda lineal (`findByMatricula`), eliminación (`removeByMatricula`) y liberación de memoria (`clear`) se encuentran en `DList.h` (líneas 48, 61, 74 y 91 respectivamente).

### 2. Selecciona un algoritmo de ordenamiento adecuado al problema
El usuario puede elegir interactivamente en el menú bajo qué criterio ordenar la lista doblemente ligada. Ambos algoritmos operan **de forma 100% nativa sobre la `DList`** en el archivo `Sorts.h`, sin convertir los datos a vectores auxiliares:
* **Merge Sort sobre punteros (Ordenamiento alfabético por `nombre`):** Se seleccionó Merge Sort porque garantiza una complejidad de $O(n \log n)$ incluso en el peor de los casos y es un algoritmo **estable**. Además, al implementarse directamente manipulando los punteros `next` y `previous` de la `DList` y dividiendo la lista con la técnica de punteros *slow/fast* (`split`), **elimina la necesidad de crear arreglos temporales**, reduciendo la complejidad espacial auxiliar de $O(n)$ a $O(1)$ (sin considerar la pila de llamadas recursivas). Se encuentra en `Sorts.h` en las funciones `split`, `mergePorNombre`, `mergeSortRec` y `mergeSortPorNombre` (líneas 17 a 84).
* **Insertion Sort sobre nodos (Ordenamiento descendente por `promedio`):** Se implementó para organizar a los estudiantes de mayor a menor promedio. Es sumamente adecuado cuando el padrón ya fue ordenado previamente y el usuario únicamente registra uno o pocos alumnos nuevos al final de la lista, escenario en el cual Insertion Sort alcanza un rendimiento cercano a su mejor caso $O(n)$ con complejidad espacial $O(1)$. Se encuentra en `Sorts.h` en la función `insertionSortPorPromedio` (línea 90).

#### ¿Qué significa que un método sea estático (`static`) y por qué se utiliza en `Sorts`?
En C++ y Programación Orientada a Objetos, declarar un método con la palabra reservada `static` significa que el método **pertenece a la clase en sí misma y no a una instancia particular** de esa clase. Por lo tanto, no requiere de un puntero implícito `this` ni modifica atributos internos de un objeto.
* **Justificación de su uso:** Usar métodos estáticos permite invocarlos limpiamente mediante `Sorts::mergeSortPorNombre(registros)` sin tener que instanciar un objeto `Sorts` vacío e innecesario en memoria.

### 3. Usa un árbol adecuado para resolver un problema
Para organizar los datos **de forma natural** y resolver el problema de filtrado eficiente por calificaciones, se implementó un **Árbol Binario de Búsqueda (`BST`)** en el archivo `BST.h`.
* **Justificación técnica:** Mientras que en la `DList` buscar todos los alumnos dentro de un rango de promedios requiere recorrer toda la estructura linealmente ($O(n)$) o reordenarla primero, el `BST` inserta cada `Expediente` comparando su `promedio` como llave principal (y desempatando por `matricula` para admitir promedios repetidos sin pérdida de datos). Como el archivo `expedientes.csv` almacena los registros en orden arbitrario (desordenado por promedio), es muy poco probable que el árbol se degenere, manteniendo un comportamiento promedio de $O(\log n)$ en inserción y permitiendo **podar subárboles enteros** durante las consultas de rango e imprimir los resultados ordenados ascendentemente mediante un recorrido *In-Order*.
* **Ubicación en el código:** Las funciones `addRec`, `inOrderRangeRec`, `add` y `consultarRangoPromedio` se encuentran en `BST.h` (líneas 28, 43, 76 y 83).

---

## SICT0301B: Evalúa los componentes

### Análisis de Complejidad Temporal y Espacial Completo

#### 1. Estructura Lineal: Lista Doblemente Ligada (`DList.h`)
* **Inserción al final (`addLast`):**
  * **Complejidad Temporal:** $O(1)$ en el mejor, promedio y peor caso, ya que se enlaza directamente el nuevo nodo utilizando el puntero `tail`.
  * **Complejidad Espacial:** $O(1)$ por operación individual.
* **Búsqueda por matrícula (`findByMatricula`):**
  * **Complejidad Temporal:** $O(1)$ en el mejor caso (el expediente buscado está en `head`), y $O(n)$ en el caso promedio y peor, porque debe recorrer secuencialmente los punteros `next` comparando cada matrícula.
  * **Complejidad Espacial:** $O(1)$.
* **Eliminación por matrícula (`removeByMatricula`):**
  * **Complejidad Temporal:** $O(n)$ en el caso promedio y peor. Aunque desconectar los punteros `previous` y `next` y hacer `delete` toma tiempo constante $O(1)$, primero invoca a `findByMatricula` para localizar el nodo ($O(n) + O(1) = O(n)$).
  * **Complejidad Espacial:** $O(1)$.
* **Limpieza de la estructura (`clear` / Destructor):**
  * **Complejidad Temporal:** $O(n)$ en todos los casos, ya que visita y libera cada uno de los $n$ nodos.

#### 2. Algoritmos de Ordenamiento (`Sorts.h`)
* **Merge Sort sobre nodos (`mergeSortPorNombre`):**
  * **Complejidad Temporal:** $O(n \log n)$ en el mejor, promedio y peor caso. La función `split` divide la lista en dos mitades en $O(n)$ a través de $\log_2(n)$ niveles de recursión, y `mergePorNombre` reenlaza los nodos en $O(n)$ por cada nivel. Posteriormente, actualizar `tail` recorre la lista en $O(n)$, manteniendo el total en $O(n \log n) + O(n) = O(n \log n)$.
  * **Complejidad Espacial:** $O(1)$ en arreglos auxiliares (ya que reasigna punteros existentes sin duplicar nodos), y $O(\log n)$ en el *call stack* debido a la profundidad del árbol de llamadas recursivas.
* **Insertion Sort sobre nodos (`insertionSortPorPromedio`):**
  * **Complejidad Temporal:** 
    * **Mejor caso:** $O(n)$ cuando la lista ya se encuentra ordenada descendentemente por promedio (el ciclo interno `while` no realiza desplazamientos).
    * **Caso promedio y peor:** $O(n^2)$ cuando la lista está en orden inverso (ascendente), requiriendo comparar y desplazar valores hacia atrás con el puntero `previous` en cada iteración ($\frac{n(n-1)}{2}$ comparaciones).
  * **Complejidad Espacial:** $O(1)$ adicional (algoritmo *in-place*).

#### 3. Árbol Binario de Búsqueda (`BST.h`)
* **Inserción de un nodo (`add` / `addRec`):**
  * **Complejidad Temporal:** $O(\log n)$ en el caso promedio (árbol balanceado) y $O(n)$ en el peor de los casos (si los datos se insertaran estrictamente ordenados generando un árbol degenerado).
  * **Complejidad Espacial:** $O(\log n)$ promedio en la pila de recursión ($O(n)$ peor caso).
* **Construcción / Sincronización del árbol completo (`sincronizarArbol`):**
  * **Complejidad Temporal:** $O(n \log n)$ en el caso promedio y $O(n^2)$ en el peor caso, ya que realiza $n$ inserciones sucesivas en el `BST`.
* **Consulta por rango de promedios (`consultarRangoPromedio` / `inOrderRangeRec`):**
  * **Complejidad Temporal:** $O(\log n + k)$ en el caso promedio (donde $k$ es el número de expedientes que caen dentro del rango $[min, max]$, gracias a la poda de ramas fuera del intervalo), y $O(n)$ en el peor caso (cuando el rango abarca todos los nodos del árbol o el árbol está degenerado).
  * **Complejidad Espacial:** $O(h)$ en la pila de recursión, donde $h$ es la altura del árbol ($O(\log n)$ promedio, $O(n)$ peor caso).

#### 4. Lectura, Escritura de Archivos e Impresión (`main.cpp`)
* **Carga / Lectura de datos (`cargarExpedientes`):**
  * **Complejidad Temporal:** $O(n \log n)$ en el caso promedio ($O(n^2)$ peor caso). Leer las $n$ líneas del archivo `.csv` e insertarlas al final de la `DList` toma $n \times O(1) = O(n)$, mientras que insertar simultáneamente cada uno de los $n$ registros en el `BST` toma $n \times O(\log n) = O(n \log n)$.
  * **Complejidad Espacial:** $O(n)$ para almacenar los $n$ nodos tanto en la `DList` como en el `BST`.
* **Escritura de datos a disco (`guardarExpedientes`):**
  * **Complejidad Temporal:** $O(n)$ en todos los casos, dado que recorre linealmente la `DList` desde `head` hasta `tail` una sola vez escribiendo cada registro en `expedientes.csv`.
  * **Complejidad Espacial:** $O(1)$ de memoria adicional en RAM.
* **Impresión en consola (`mostrarExpedientes`):**
  * **Complejidad Temporal:** $O(n)$ en todos los casos, puesto que visita secuencialmente los $n$ nodos de la lista ejecutando `imprimir()` en tiempo constante $O(1)$ por nodo.
  * **Complejidad Espacial:** $O(1)$.

---

## SICT0303B: Implementa acciones científicas

### 1. Implementa mecanismos para consultar información de las estructuras correctos y útiles
El programa ofrece un menú interactivo robusto con 9 opciones que permiten explotar todas las estructuras implementadas:
* **Opción 1:** Despliega el padrón completo almacenado en la `DList`.
* **Opción 3:** Permite buscar un estudiante específico por su `matricula` directamente en la `DList`.
* **Opción 5 y 6:** Permiten al usuario elegir dinámicamente por qué parámetro ordenar los expedientes (por `nombre` con Merge Sort o por `promedio` con Insertion Sort) y muestran el reporte resultante.
* **Opción 7:** Permite consultar el `BST` introduciendo un promedio mínimo y máximo para obtener los alumnos dentro de ese rango ordenados de forma natural.

### 2. Implementa mecanismos de lectura de archivos correctos y útiles
Al iniciar el programa, la función `cargarExpedientes()` lee automáticamente el archivo `expedientes.csv`, ignora la cabecera, separa cada columna con `std::stringstream` y pobla tanto la `DList` como el `BST` sin requerir captura manual previa.

### 3. Implementa mecanismos de escritura de archivos correctos y útiles
Mediante la **Opción 8** del menú (`guardarExpedientes()`), cualquier nuevo estudiante registrado en la sesión (**Opción 2**), cualquier baja realizada (**Opción 4**) o el nuevo ordenamiento aplicado sobre la `DList` (**Opciones 5 y 6**) se escribe de vuelta en `expedientes.csv`, garantizando la persistencia de los datos para futuras ejecuciones.
