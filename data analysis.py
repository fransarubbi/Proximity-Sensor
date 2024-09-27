import pandas as pd
import matplotlib.pyplot as plt

# Función para cargar los datos desde un archivo CSV
def cargar_datos(archivo_csv):
    try:
        datos = pd.read_csv(archivo_csv, header=None)  # Lee el archivo CSV sin encabezados
        return datos[0]  # Devuelve la primera columna como una Serie
    except Exception as e:
        print(f"Error al cargar el archivo: {e}")
        return None

# Función para calcular estadísticas
def calcular_estadisticas(datos):
    media = datos.mean()
    mediana = datos.median()
    desviacion_estandar = datos.std()
    minimo = datos.min()
    maximo = datos.max()

    return media, mediana, desviacion_estandar, minimo, maximo

# Función para generar gráficos
def generar_graficos(datos, media, mediana, desviacion_estandar, minimo, maximo):
    plt.figure(figsize=(12, 6))

    # Gráfico de Histograma
    plt.subplot(1, 1, 1)
    plt.hist(datos, bins=20, color='blue', alpha=0.7, edgecolor='black')
    plt.title('Histograma de Frecuencia de Datos')
    plt.xlabel('Valor')
    plt.ylabel('Frecuencia')

    # Añadir texto con estadísticas en el gráfico
    stats_text = f"""
    Valor mínimo: {minimo:.2f}
    Valor máximo: {maximo:.2f}
    Media: {media:.2f}
    Mediana: {mediana:.2f}
    Desviación Estándar: {desviacion_estandar:.2f}
    """
    plt.gca().text(0.05, 0.95, stats_text, transform=plt.gca().transAxes, fontsize=10,
                    verticalalignment='top', bbox=dict(facecolor='white', alpha=0.5))

    plt.tight_layout()
    plt.show()

# Programa principal
def main():
    archivo_csv = 'distancias.csv'  
    datos = cargar_datos(archivo_csv)

    if datos is not None:
        media, mediana, desviacion_estandar, minimo, maximo = calcular_estadisticas(datos)
        generar_graficos(datos, media, mediana, desviacion_estandar, minimo, maximo)

if __name__ == "__main__":
    main()

