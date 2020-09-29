[top]
components : proptemp@Proptemp
out : temphab
in : tempe frio calor
link : tempe exterior@proptemp
link : frio frio@proptemp
link : calor calor@proptemp
link : habitacion@proptemp temphab

[proptemp]
tempExterior : 20
tempHabitacion : 20
modificador : 20

