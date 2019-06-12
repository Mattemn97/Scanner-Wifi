var larg = innerHeight;
var alt = innerWidth;

function setup() {
    createCanvas(alt, larg);
    listaCerchi = [];
    listaColori= ["aqua", "blue" , "fuchsia" , "gray" , "green" , "lime" , "maroon" , "navy" , "olive" , "purple" , "red" , "silver" , "teal" , "white" , "yellow"];
}

setTimeout(function stampoElenco() {
    window.location.reload()
  }, 10000);

function draw() {
   // elenco e carico tutti i dati da Scan.js
    w3.getHttpObject("Risultati.js", stampoElenco);
    function stampoElenco(myObject) {
        var dist;
        var myArray = myObject.AccessPoint;
        for (i = 0; i < myArray.length; i++) {
            dist = calcolaDistanza(calcolaFreq(Number(myArray[i].Canale)), calcoladB(Number(myArray[i].Segnale)));
            var newC = new Cerchio(0, 0, dist, false, i);
            listaCerchi.push(newC);
            myObject.AccessPoint[i].dist = dist;
            myObject.AccessPoint[i].color = listaColori[i];
            myObject.AccessPoint[i].Frequenza = calcolaFreq(Number(myArray[i].Canale));
        }
        w3.displayObject("id01", myObject);
    }

    background(0);
    translate(alt/2, larg/2);
    stroke(255);
    var pt_ori = (alt/25).toFixed(0);
    var pt_vert = (larg/25).toFixed(0);
    //Stampo una griglia di punti
    for(i=-pt_ori;    i<pt_ori;    i++) {
        for(j=-pt_vert;   j<pt_vert;    j++) {
            ellipse(i * 25, j * 25, 1, 1);
        }
    }

    //Stampo i cerchio che localizzarà l'utente
    var utente = new Cerchio(0,0,1,true);
    utente.show();
    //Stampo tutti i cerchi dei singoli dati
    for (i = 0; i < listaCerchi.length; i++) {
        var crf = listaCerchi[i];
        crf.show();
    }
}

function Cerchio(x, y, r, utente,indice) {
    this.x = x;
    this.y = y;
    this.r = r;
    this.utente=utente;
    this.indice=indice;
    this.color=listaColori[this.indice];

    this.show = function() {
        if (this.utente)
        {
            stroke(255,0,0);
            noFill();
            strokeWeight(1);
            ellipse(this.x, this.y, this.r * 2, this.r * 2);
        }
        else {
            stroke(this.color);
            noFill();
            strokeWeight(1);
            ellipse(this.x, this.y, this.r * 2, this.r * 2);
        }
    }
}

function calcolaDistanza(MHr,dB)
{
    return ((Math.pow(Math.pow(10,(-dB -32.45 -20*(Math.log(MHr)/(Math.LN10)))/10),1/2.6))*1000).toFixed(2);
}

function calcoladB(segnale)
{
    return(segnale/2)-100;
}

function calcolaFreq(canale)
{
    if (canale<13)
        return (2407+(5*canale));

    else
        return(5180+(20*((canale-36)/4)));

}
