<!DOCTYPE HTML>

<html>
	<head>
		<title>Mapa - >Escape Velocity by HTML5 UP</title>
		<meta charset="utf-8" />
		<meta name="viewport" content="width=device-width, initial-scale=1" />
		<!--[if lte IE 8]><script src="assets/js/ie/html5shiv.js"></script><![endif]-->
		<link rel="stylesheet" href="assets/css/main.css" />
		<!--[if lte IE 8]><link rel="stylesheet" href="assets/css/ie8.css" /><![endif]-->
	</head>
	<body class="left-sidebar">
		<div id="page-wrapper">

			<!-- Header -->
				<div id="header-wrapper" class="wrapper">
					<div id="header">

						<!-- Logo -->
							<div id="logo">
								<h1><a href="index.html">Equipe UNBAJA</a></h1>
								<p></p>
							</div>

						<!-- Nav -->
							<nav id="nav">
								<ul>
									<li class="current"><a href="index.html">Home</a></li>
									<li><a href="mapa.html">Mapa</a></li>
									<li><a href="gps.html">Dados do GPS</a></li>
									<li><a href="mpu.html">Dados do acelerômetro e giroscópio</a></li>
								</ul>
							</nav>

					</div>
				</div>

			<!-- Main -->
				<div id="titulo" class="wrapper style1">
				<div class="title">Mapa</div>
				</div>

				<div id="map" class="wrapper style1">
					<section id="intro" class="container">

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
						$foo = getCSV('teste_final.csv');
						
						
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
						
						$center="lat: -15.818267, lng: -48.060509"; //define o local principal do mapa
						
						?>
						

						<script>

						var map;	
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

 					function getPoints() {
        					return [
           					<?=$ponto;?>  //pontos lidos do arquivo
        					];
      					}						

						</script>

						
						
					</section>
				</div>

		</div>

		</div>



		<!-- Scripts -->

			<script src="assets/js/jquery.min.js"></script>
			<script src="assets/js/jquery.dropotron.min.js"></script>
			<script src="assets/js/skel.min.js"></script>
			<script src="assets/js/skel-viewport.min.js"></script>
			<script src="assets/js/util.js"></script>
			<!--[if lte IE 8]><script src="assets/js/ie/respond.min.js"></script><![endif]-->
			<script src="assets/js/main.js"></script>
			<script async defer
        			src="https://maps.googleapis.com/maps/api/js?key=AIzaSyDSbHv2gnqaJT8xgBjaGviCNytVz8A99VA&libraries=visualization&callback=initMap">
    		</script>
			

	</body>
</html>