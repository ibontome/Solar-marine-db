# Solar-marine-db

# **INTRODUCCIÓN**

Para terminar este segundo año de mantenimiento electrónico se nos ha planteado seguir con el proyecto empezado el año pasado que consiste en un barco alimentado mediante una placa solar. Aparte de esto debe incluir un piloto automático programado mediante arduino y que la placa solar se oriente hacia el sol automáticamente también durante todo el trayecto para así conseguir el máximo rendimiento. Este proyecto participará en el torneo que se celebrará el 18 de junio de 2022 en Praia da Ribeira, Baiona.

# **Bases de la regata**

Nuestro proyecto es un barco solar, este proyecto tenemos que llevarlo a la regata solar marine. Para poder participar en el proyecto tenemos que cumplir una serie de requisitos y necesidades.

- El barco como fuente de alimentación dispondrá de una placa solar, solamente de una placa solar, por lo tanto, no se puede utilizar ninguna batería para almacenar energía para cuando no haya tanta luz.
- El barco lo tenemos que controlar con una emisora.
- El barco hay que impulsarlo con motores eléctricos y se pueden utilizar más de uno.
- El barco lo podemos construir como queramos y con los materiales que deseemos.
- Solamente podremos utilizar unas pilas para alimentar la emisora del barco (mando radiocontrol). Siguiendo estos pasos construiremos nuestro barco solar.

# **PROCEDIMIENTO**

Para empezar tuvimos que ver en qué condiciones estaba el barco y que necesitaba. Después de la inspección procedimos a hacer una planificación del proyecto. Este proyecto sobre todo necesitaba programación,  una pcb y unas mejoras en el chasis. 

PARTES QUE COMPONEN EL PROYECTO Y EL FUNCIONAMIENTO:

El proyecto se divide en 4 partes:

![PARTES DEL BARCO](https://user-images.githubusercontent.com/96468247/153825744-0b8aecc6-bf2c-4eed-984f-d729d88553c6.png)

# **ARDUINO**

Lo más importante de este proyecto era la programación de un arduino nano para hacer el piloto automático y el MPPT. Para ello tuvimos que hacer dos programas generales y al finalizarlos creamos un programa llamado Solar Marine que juntaba los dos programas anteriores.

**PILOTO AUTOMATICO**

Para el piloto automático, primero tuvimos que conseguir manejar los motores con el mando. Segundo, tuvimos que conectar el teensy con el arduino nano por el serial, ya que el teensy envía datos al módulo bluetooth por el serial. Al conectarlos tuvimos que hacer un programa solo para seleccionar la orientación de la brújula. Finalmente teniendo los dos valores hicimos un programa que sigue la dirección que le asignamos con el mando y hace correcciones para que no se desvíe.

**MPPT**

El MPPT sirve para conseguir todo el rato la mayor potencia posible y para ello varía la velocidad de los motores para subir o bajar la corriente. El MPPT lo tuvimos que programar con arduino. Para ello, lo primero fue conseguir el voltaje y la corriente que teníamos. Después, tuvimos que conseguir la potencia y finalmente hicimos el programa que varía la velocidad de los motores dependiendo de los valores que tenemos.

# **MECANICA** 

En la parte mecánica no tuvimos que hacer mucha cosa ya que el año pasado ya se hizo casi todo, nosotros solo le hemos añadido unas mejoras. 

**LISTONES**

Añadimos unos listones de madera para reforzar la estabilidad del barco.
![1644829115268](https://user-images.githubusercontent.com/96468247/153832324-f5b47bdc-34f0-4172-8ef1-35426df3f29a.jpg)

**GOMAS DE LA PLACA**

Cuando recibimos el barco, las gomas que sujetan las guías de los motores estaban en mal estado, seleccionamos otro material más resistente y lo cambiamos.
![1644831005396](https://user-images.githubusercontent.com/96468247/153837278-2c415607-8189-47f1-a397-191e0adfbcf5.jpg)

**IMPERMEABILIZACION**

Para la impermeabilización  del barco, hemos hecho un cambio de la carcasa que cubría los circuitos por uno nuevo y hemos añadido prensaestopas para impermeabilizar más.

![1644831437435](https://user-images.githubusercontent.com/96468247/153838426-fdee1404-bff1-40a5-b1fb-7d1962980dff.jpg)


# **ELECTRONICA** 

En el proyecto teníamos que hacer una PCB para juntar los componentes electrónicos. Esta ha sido diseñada en Proteus y después fresada con una LPKF.
En la siguiente imagen podemos ver el diseño de la placa: 
![pcb](https://user-images.githubusercontent.com/96468247/153840500-279f602c-aeee-4c96-9c1c-1baceb9a48c8.PNG)
Y en la siguiente imagen podemos apreciar el resultado final:

![1644832259025](https://user-images.githubusercontent.com/96468247/153840832-f83742b2-d365-4516-96bd-5b9d06a57b08.jpg)


