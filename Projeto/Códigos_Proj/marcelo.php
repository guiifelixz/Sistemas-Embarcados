<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Heatmaps</title>
    <style>
      /* Always set the map height explicitly to define the size of the div
       * element that contains the map. */
      #map {
        height: 100%;
      }
      /* Optional: Makes the sample page fill the window. */
      html, body {
        height: 100%;
        margin: 0;
        padding: 0;
      }
      #floating-panel {
        position: absolute;
        top: 10px;
        left: 25%;
        z-index: 5;
        background-color: #fff;
        padding: 5px;
        border: 1px solid #999;
        text-align: center;
        font-family: 'Roboto','sans-serif';
        line-height: 30px;
        padding-left: 10px;
      }
      #floating-panel {
        background-color: #fff;
        border: 1px solid #999;
        left: 25%;
        padding: 5px;
        position: absolute;
        top: 10px;
        z-index: 5;
      }
    </style>
  </head>

  <body>
    <div id="floating-panel">
      <button onclick="toggleHeatmap()">Toggle Heatmap</button>
      <button onclick="changeGradient()">Change gradient</button>
      <button onclick="changeRadius()">Change radius</button>
      <button onclick="changeOpacity()">Change opacity</button>
    </div>
    <div id="map"></div>



<?php
//Funcao para ler o arquivo 
function getCSV($name) {
   $file = fopen($name, "r");
   $result = array();
   $i = 0;
   while (!feof($file)):
      if (substr(($result[$i] = fgets($file)), 0, 10) !== ';;;;;;;;') :
         $i++;
      endif;
   endwhile;
   fclose($file);
   return $result;
}
//variavel recebe funcao que le o arquivo
$foo = getCSV('datamarcelo.csv');


//monta variavel para ustilizar na funcao do google
foreach ( $foo as $linha ) {
	$pieces = explode(",", $linha);
	$temp=$pieces[0];
	$lat=$pieces[1];
	$long=$pieces[2];
       $pontos.="new google.maps.LatLng("."$lat".","."$long"."),";
}
$size = strlen($pontos); 
$ponto = substr($pontos,0, $size-1);  //retira a virgula da ultima linha do arquivo

$center="lat: -15.989704, lng: -48.044422"; //define o local principal do mapa

?>

    <script>

      // This example requires the Visualization library. Include the libraries=visualization
      // parameter when you first load the API. For example:
      // <script src="https://maps.googleapis.com/maps/api/js?key=YOUR_API_KEY&libraries=visualization">

      var map, heatmap;

      function initMap() {
        map = new google.maps.Map(document.getElementById('map'), {
          zoom: 20,
          center: {<?=$center;?>},  //posicao central do mapa
          mapTypeId: 'satellite'
        });

        heatmap = new google.maps.visualization.HeatmapLayer({
          data: getPoints(),
          map: map
        });
      }

      function toggleHeatmap() {
        heatmap.setMap(heatmap.getMap() ? null : map);
      }

      function changeGradient() {
        var gradient = [
          'rgba(0, 255, 255, 0)',
          'rgba(0, 255, 255, 1)',
          'rgba(0, 191, 255, 1)',
          'rgba(0, 127, 255, 1)',
          'rgba(0, 63, 255, 1)',
          'rgba(0, 0, 255, 1)',
          'rgba(0, 0, 223, 1)',
          'rgba(0, 0, 191, 1)',
          'rgba(0, 0, 159, 1)',
          'rgba(0, 0, 127, 1)',
          'rgba(63, 0, 91, 1)',
          'rgba(127, 0, 63, 1)',
          'rgba(191, 0, 31, 1)',
          'rgba(255, 0, 0, 1)'
        ]
        heatmap.set('gradient', heatmap.get('gradient') ? null : gradient);
      }

      function changeRadius() {
        heatmap.set('radius', heatmap.get('radius') ? null : 20);
      }

      function changeOpacity() {
        heatmap.set('opacity', heatmap.get('opacity') ? null : 0.2);
      }



      // Heatmap data: 500 Points
      function getPoints() {
        return [
           <?=$ponto;?>  //pontos lidos do arquivo
        ];
      }


    </script>
    <script async defer
        src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAcYeig8Tiju_eqYHAqXgvXTl-0GimNLgY&libraries=visualization&callback=initMap">
    </script>
  </body>
</html>