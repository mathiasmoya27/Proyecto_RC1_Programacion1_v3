#include <stdio.h>
#include <string.h>
#include "funciones.h"

float validarFloatRango(float a, float b){
    float num;
    int val;
    do
    {
        val = scanf("%f",&num);
        while((getchar())!='\n');
        if (num < a || num > b || val != 1)
        {
            printf("  [!] Error: el valor ingresado es incorrecto (%.0f - %.0f)\n",a,b);
            printf("  >> ");
        }
    } while (num < a || num > b || val != 1);
    return num;
}

void leerCadena(char *cadena, int n){
    fgets(cadena,n,stdin);
    int len = strlen(cadena) - 1;
    if (cadena[len] == '\n')
    {
        cadena[len] = '\0';
    }
    else
    {
        while((getchar())!='\n');
    }
}

void mostrarSeparador(char simbolo, int n){
    for (int i = 0; i < n; i++)
    {
        printf("%c",simbolo);
    }
    printf("\n");
}

int buscarProducto(char nombres[][20], int cont, char *buscar){
    for (int i = 0; i < cont; i++)
    {
        if (strcmp(nombres[i],buscar) == 0)
        {
            return i;
        }
    }
    return -1;
}

void registrarProducto(char nombres[][20], int *demandas, int *stocks, float *tiempos,
                        float *costos, int *cont, int n){
    char nombre[20];
    int m = *cont;
    for (int i = m; i < (m + n); i++)
    {
        printf("\n");
        mostrarSeparador('-',50);
        printf("  Producto %d\n",i + 1);
        mostrarSeparador('-',50);
        printf("  Nombre: ");
        leerCadena(nombre,20);
        while (buscarProducto(nombres,*cont,nombre) != -1)
        {
            printf("  [!] Error: El producto ya existe, ingrese otro nombre: ");
            leerCadena(nombre,20);
        }
        strcpy(nombres[i],nombre);
        printf("  Cantidad demandada (unidades): ");
        demandas[i] = validarFloatRango(0,10000);
        printf("  Stock disponible (unidades): ");
        stocks[i] = validarFloatRango(0,10000);
        printf("  Tiempo de fabricacion por unidad (horas): ");
        tiempos[i] = validarFloatRango(0,100);
        printf("  Costo de elaboracion por unidad ($): ");
        costos[i] = validarFloatRango(0,10000);
        (*cont)++;
    }
    printf("\n  [OK] Producto(s) registrado(s)\n");
}

void mostrarProductos(char nombres[][20], int *demandas, int *stocks, float *tiempos,
                        float *costos, int m, int n){
    mostrarSeparador('=',104);
    printf(" %-4s %-20s %-10s %-10s %-10s %-12s %-14s %-10s\n","N","Nombre","Demanda","Stock",
                                            "Producir","Tiempo/u","Costo elab/u","Estado");
    printf(" %-4s %-20s %-10s %-10s %-10s %-12s %-14s %-10s\n","","","(unidades)","(unidades)",
                                            "(unidades)","(horas)","($)","");
    mostrarSeparador('-',104);
    for (int i = m; i < (m + n); i++)
    {
        printf(" %-4d %-20s %-10d %-10d %-10d %-12.2f %-14.2f %-10s\n",i + 1,
                                            nombres[i],
                                            demandas[i],
                                            stocks[i],
                                            calcularAProducir(demandas[i],stocks[i]),
                                            tiempos[i],
                                            costos[i],
                                            (stocks[i] >= demandas[i] ? "Cubierto" : "Producir"));
    }
    mostrarSeparador('=',104);
}

void editarProducto(char nombres[][20], int *demandas, int *stocks, float *tiempos,
                        float *costos, int cont){
    char buscar[20], nuevoNombre[20];
    printf("  Nombre del producto a editar: ");
    leerCadena(buscar,20);
    int indice = buscarProducto(nombres,cont,buscar);
    if (indice == -1)
    {
        printf("  [!] Error: El producto no existe\n");
        return;
    }
    mostrarProductos(nombres,demandas,stocks,tiempos,costos,indice,1);
    printf("  Nuevo nombre: ");
    leerCadena(nuevoNombre,20);
    int repetido = buscarProducto(nombres,cont,nuevoNombre);
    if (repetido != -1 && repetido != indice)
    {
        printf("  [!] Error: Ya existe otro producto con ese nombre\n");
        return;
    }
    strcpy(nombres[indice],nuevoNombre);
    printf("  Nueva cantidad demandada (unidades): ");
    demandas[indice] = validarFloatRango(0,10000);
    printf("  Nuevo stock (unidades): ");
    stocks[indice] = validarFloatRango(0,10000);
    printf("  Nuevo tiempo de fabricacion por unidad (horas): ");
    tiempos[indice] = validarFloatRango(0,100);
    printf("  Nuevo costo de elaboracion por unidad ($): ");
    costos[indice] = validarFloatRango(0,10000);
    printf("  [OK] Producto editado\n");
}

void eliminarProducto(char nombres[][20], int *demandas, int *stocks, float *tiempos,
                        float *costos, int *cont){
    char buscar[20];
    printf("  Nombre del producto a eliminar: ");
    leerCadena(buscar,20);
    int indice = buscarProducto(nombres,*cont,buscar);
    if (indice == -1)
    {
        printf("  [!] Error: El producto no existe\n");
        return;
    }
    for (int j = indice; j < *cont - 1; j++)
    {
        strcpy(nombres[j],nombres[j + 1]);
        demandas[j] = demandas[j + 1];
        stocks[j] = stocks[j + 1];
        tiempos[j] = tiempos[j + 1];
        costos[j] = costos[j + 1];
    }
    (*cont)--;
    printf("  [OK] Producto eliminado\n");
}

void agregarStock(char nombres[][20], int *stocks, int cont){
    char buscar[20];
    printf("  Nombre del producto: ");
    leerCadena(buscar,20);
    int indice = buscarProducto(nombres,cont,buscar);
    if (indice == -1)
    {
        printf("  [!] Error: El producto no existe\n");
        return;
    }
    printf("  Stock actual: %d unidades\n",stocks[indice]);
    printf("  Cantidad a agregar al stock (unidades): ");
    int cantidad = validarFloatRango(1,10000);
    stocks[indice]+=cantidad;
    printf("  [OK] El nuevo stock es: %d unidades\n",stocks[indice]);
}

int calcularAProducir(int demanda, int stock){
    if (stock >= demanda)
    {
        return 0;
    }
    return demanda - stock;
}

float calcularTiempoTotal(int *demandas, int *stocks, float *tiempos, int cont){
    float total = 0;
    for (int i = 0; i < cont; i++)
    {
        total+=calcularAProducir(demandas[i],stocks[i]) * tiempos[i];
    }
    return total;
}

float calcularCostosTotales(int *demandas, int *stocks, float *costos, int cont){
    float total = 0;
    for (int i = 0; i < cont; i++)
    {
        total+=calcularAProducir(demandas[i],stocks[i]) * costos[i];
    }
    return total;
}

void verificarDemanda(int *demandas, int *stocks, float *tiempos, float *costos,
                        int cont, float tiempoDisponible, float costosDisponibles){
    float tiempoTotal = calcularTiempoTotal(demandas,stocks,tiempos,cont);
    float costosTotales = calcularCostosTotales(demandas,stocks,costos,cont);
    mostrarSeparador('=',60);
    printf("  %-28s %-14s %-14s\n","","Requerido","Disponible");
    mostrarSeparador('-',60);
    printf("  %-28s %-14.2f %-14.2f\n","Tiempo (horas)",tiempoTotal,tiempoDisponible);
    printf("  %-28s %-14.2f %-14.2f\n","Costos de elaboracion ($)",costosTotales,costosDisponibles);
    mostrarSeparador('-',60);
    if (tiempoTotal <= tiempoDisponible)
    {
        printf("  [OK] Tiempo suficiente (sobran %.2f horas)\n",tiempoDisponible - tiempoTotal);
    }
    else
    {
        printf("  [X]  Tiempo insuficiente (faltan %.2f horas)\n",tiempoTotal - tiempoDisponible);
    }
    if (costosTotales <= costosDisponibles)
    {
        printf("  [OK] Presupuesto suficiente (sobran $%.2f)\n",costosDisponibles - costosTotales);
    }
    else
    {
        printf("  [X]  Presupuesto insuficiente (faltan $%.2f)\n",costosTotales - costosDisponibles);
    }
    mostrarSeparador('=',60);
    if (tiempoTotal <= tiempoDisponible && costosTotales <= costosDisponibles)
    {
        printf("  >>> La fabrica SI puede cumplir con la demanda <<<\n");
    }
    else
    {
        printf("  >>> La fabrica NO puede cumplir con la demanda <<<\n");
    }
    mostrarSeparador('=',60);
}
