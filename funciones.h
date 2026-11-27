float validarFloatRango(float a, float b);
void leerCadena(char *cadena, int n);
void mostrarSeparador(char simbolo, int n);
int buscarProducto(char nombres[][20], int cont, char *buscar);
void registrarProducto(char nombres[][20], int *demandas, int *stocks, float *tiempos,
                        float *costos, int *cont, int n);
void mostrarProductos(char nombres[][20], int *demandas, int *stocks, float *tiempos,
                        float *costos, int m, int n);
void editarProducto(char nombres[][20], int *demandas, int *stocks, float *tiempos,
                        float *costos, int cont);
void eliminarProducto(char nombres[][20], int *demandas, int *stocks, float *tiempos,
                        float *costos, int *cont);
void agregarStock(char nombres[][20], int *stocks, int cont);
int calcularAProducir(int demanda, int stock);
float calcularTiempoTotal(int *demandas, int *stocks, float *tiempos, int cont);
float calcularCostosTotales(int *demandas, int *stocks, float *costos, int cont);
void verificarDemanda(int *demandas, int *stocks, float *tiempos, float *costos,
                        int cont, float tiempoDisponible, float costosDisponibles);
