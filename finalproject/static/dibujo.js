//////////////////////////////////////////
//DIBUJO MEDIANTE CLICKEAR UN BOTON
/////////////////////////////////////////

//Obtener las variables desde el HTML por su id:
var texto = document.getElementById("texto_lineas");
var buton = document.getElementById("boton");

//Levantar un evento que escuche cuando se haga el click
buton.addEventListener("click", dibujoClick);

//Definir las variables del canvas, en este caso
var dibujo_click = document.getElementById("dibujo_click");
var lienzo = dibujo_click.getContext("2d");
var ancho =  dibujo_click.width


//FUNCIONES:

//Esta función sucede cuando se da el click

function dibujoClick()
{
    //Limpiar el lienzo cada vez que se haga click
    lienzo.clearRect(0, 0, dibujo_click.width, dibujo_click.height);

    //La función para dibujar lineas
    function dibujarLinea(color, x_ini, y_ini, x_fin, y_fin)
    {
        lienzo.beginPath();
        lienzo.strokeStyle = color;
        lienzo.moveTo(x_ini, y_ini);
        lienzo.lineTo(x_fin, y_fin);
        lienzo.stroke();
        lienzo.closePath();
    }

    //La cantidad de lineas es una entrada de número:

    var lineas = parseInt(texto.value);

    //El for para correr la impresion
    for(i=0; i < lineas; i++)
    {
        //Recordemos que tenemos una fucion que grafica especificamente con unas condiciones.
        //Se debe encontrar el intervalo desde los cuales saldrán las líneas
        //Antes era 10 por defecto, ahora depende de la cantidad
        var lineas_verdaderas = parseInt(ancho/lineas)
        var delta = i * lineas_verdaderas;
        var delta_minus = (i + 1) * lineas_verdaderas;

        dibujarLinea("yellow", 0, delta, delta_minus, ancho);
        dibujarLinea("yellow", ancho, delta, ancho - delta_minus, ancho)
        dibujarLinea("yellow", ancho-delta,0,0,delta_minus)
        dibujarLinea("yellow", ancho-delta, 0, ancho, ancho- delta_minus)
    }
    lienzo.beginPath();
    lienzo.strokeStyle = "red";
    lienzo.moveTo(0, 0);
    lienzo.lineTo(ancho, 0);
    lienzo.lineTo(ancho, ancho);
    lienzo.lineTo(0, ancho);
    lienzo.lineTo(0, 0);
    lienzo.stroke();
    lienzo.closePath();

}
