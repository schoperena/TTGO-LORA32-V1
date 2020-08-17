# TTGO-LORA32-V1

El objetivo de este proyecto es simplemente testear dos módulos TTGO-LORA32-V1 y dar a entender su funcionamiento. Consta de dos proyectos arduino: El primero es LoRa_Sender el cual enviará paquetes LoRa cada 10 segundos, en este caso envía una cadena y un contador. El segundo es LoRa_receiver el cual captura ese paquete y lo muestra en la pantalla la cadena recibida junto al contador.

## Para empezar

Para empezar puedes descargar el repositorio como zip o puedes clonarlo desde la terminal con git:
```
git clone https://github.com/schoperena/TTGO-LORA32-V1.git
```


### Pre-requisitos

Para poder funcionar, se necesita las siguientes librerías en el ide de Arduino:


* LoRa by Sandeep Mistry
* Adafruit SSD1306 by Adafruit
* Adafruit GFX Library by Adafruit

## Como cambiar el boot logo

Dentro de cada proyecto de arduino, se encuentra un archivo logo.h, en el cual se encuentra un arreglo de bytes que se traduce en la imagen de arranque.

##### Como creamos nuestra propia imagen de arranque:

1. Creamos una imagen blanco y negro con dimensiones 128x64, importante
 que los colores sean totalmente blanco (#FFFFFF) y totalmente negro (#000000) para que al convertirlo se interprete bien.
2.  nos dirigimos a la pagina [image2cpp](http://javl.github.io/image2cpp/) para hacer la conversión  y generamos el código.
3. reemplazamos el código en el archivo logo.h.
