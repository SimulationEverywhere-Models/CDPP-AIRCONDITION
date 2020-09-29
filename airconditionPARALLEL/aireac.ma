[top]
components : ucontrol@Ucontrol uf@Ufc uc@Ufc proptemp@Proptemp gentemp@Gentemp
out : consumo tempHab actiFrio actiCalor temp
in : tempd
link : salida@gentemp exterior@proptemp
link : salida@gentemp temp
link : tempd deseada@ucontrol
link : habitacion@proptemp tempHab
link : habitacion@proptemp real@ucontrol
link : frio@ucontrol activar@uf
link : calor@ucontrol activar@uc
link : frio@ucontrol frio@proptemp
link : calor@ucontrol calor@proptemp
link : frio@ucontrol actiFrio
link : calor@ucontrol actiCalor
link : calor@ucontrol activar@uc
link : salida@uf consumo
link : salida@uc consumo

[ucontrol]
tempDeseada : 20.0
tempReal : 20.0
tolerancia : 2.0

[uf]
consumo : 5000

[uc]
consumo : 2000

[proptemp]
tempExterior : 20.0
tempHabitacion : 20.0
modificador : 20.0

[gentemp]
temperatura : 20.0
intervalo : 60.0
