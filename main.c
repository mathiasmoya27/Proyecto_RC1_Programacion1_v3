#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    char nombres[100][20];
    int demandas[100];
    int stocks[100];
    float tiempos[100];
    float costos[100];
    float tiempoDisponible = 0, costosDisponibles = 0;
    int contP = 0, disponibles = 0, opc, opc2;

    do
    {
        printf("\n");
        mostrarSeparador('=',56);
        printf("            Sistema de produccion y demanda\n");
        mostrarSeparador('=',56);
        printf("   1. Registrar producto(s)\n");
        printf("   2. Mostrar productos\n");
        printf("   3. Buscar producto\n");
        printf("   4. Editar producto\n");
        printf("   5. Eliminar producto\n");
        printf("   6. Agregar stock\n");
        printf("   7. Ingresar tiempo y Costos de elaboracion disponibles\n");
        printf("   8. Calcular tiempo total de fabricacion\n");
        printf("   9. Calcular Costos de elaboracion\n");
        printf("  10. Verificar si se puede cumplir la demanda\n");
        printf("  11. Salir\n");
        mostrarSeparador('-',56);
        printf("  Productos registrados: %d/100\n",contP);
        mostrarSeparador('-',56);
        printf("  >> ");
        opc = validarFloatRango(1,11);
        printf("\n");
        switch (opc)
        {
        case 1:
            if (contP == 100)
            {
                printf("  [!] Error: Ya se registraron los 100 productos\n");
                break;
            }
            printf("  Cuantos productos desea ingresar (maximo %d): ",100 - contP);
            int n = validarFloatRango(1,100 - contP);
            registrarProducto(nombres,demandas,stocks,tiempos,costos,&contP,n);
            break;
        case 2:
            if (contP == 0)
            {
                printf("  [!] No hay productos registrados\n");
                break;
            }
            mostrarProductos(nombres,demandas,stocks,tiempos,costos,0,contP);
            break;
        case 3:
            if (contP == 0)
            {
                printf("  [!] No hay productos registrados\n");
                break;
            }
            char buscar[20];
            printf("  Nombre del producto a buscar: ");
            leerCadena(buscar,20);
            int indice = buscarProducto(nombres,contP,buscar);
            if (indice == -1)
            {
                printf("  [!] Error: El producto no existe\n");
                break;
            }
            mostrarProductos(nombres,demandas,stocks,tiempos,costos,indice,1);
            break;
        case 4:
            if (contP == 0)
            {
                printf("  [!] No hay productos registrados\n");
                break;
            }
            editarProducto(nombres,demandas,stocks,tiempos,costos,contP);
            break;
        case 5:
            if (contP == 0)
            {
                printf("  [!] No hay productos registrados\n");
                break;
            }
            eliminarProducto(nombres,demandas,stocks,tiempos,costos,&contP);
            break;
        case 6:
            if (contP == 0)
            {
                printf("  [!] No hay productos registrados\n");
                break;
            }
            agregarStock(nombres,stocks,contP);
            break;
        case 7:
            printf("  Tiempo de produccion disponible (horas): ");
            tiempoDisponible = validarFloatRango(0,100000);
            printf("  Presupuesto para Costos de elaboracion ($): ");
            costosDisponibles = validarFloatRango(0,10000000);
            disponibles = 1;
            printf("  [OK] Datos registrados\n");
            break;
        case 8:
            if (contP == 0)
            {
                printf("  [!] No hay productos registrados\n");
                break;
            }
            printf("  >> El tiempo total de fabricacion es: %.2f horas\n",
                                            calcularTiempoTotal(demandas,stocks,tiempos,contP));
            break;
        case 9:
            if (contP == 0)
            {
                printf("  [!] No hay productos registrados\n");
                break;
            }
            printf("  >> Los Costos de elaboracion totales son: $%.2f\n",
                                            calcularCostosTotales(demandas,stocks,costos,contP));
            break;
        case 10:
            if (contP == 0)
            {
                printf("  [!] No hay productos registrados\n");
                break;
            }
            if (disponibles == 0)
            {
                printf("  [!] Error: Primero ingrese el tiempo y los Costos de elaboracion disponibles (opcion 7)\n");
                break;
            }
            verificarDemanda(demandas,stocks,tiempos,costos,contP,tiempoDisponible,costosDisponibles);
            break;
        case 11:
            printf("  Gracias por usar el sistema. Hasta pronto!\n");
            return 0;
            break;
        default:
            printf("  [!] No existe la opcion\n");
            break;
        }
        printf("\n  Desea seleccionar otra opcion 1.Si/2.No: ");
        opc2 = validarFloatRango(1,2);
    } while (opc2 == 1);

    return 0;
}
