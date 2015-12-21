<!DOCTYPE html>
<html lang="en" dir="ltr">
<head>
<title>Pomaire Monitoring</title>
<meta charset="iso-8859-1">
<link rel="stylesheet" href="styles/layout.css" type="text/css">
<script src="http://d3js.org/d3.v3.min.js"></script>
<script src="//code.jquery.com/jquery-1.11.3.min.js"></script>
  
<!--[if lt IE 9]><script src="scripts/html5shiv.js"></script><![endif]-->
<style>
    body {
        background-image: url('http://7-themes.com/data_images/out/2/6775290-beautiful-ground-wallpaper.jpg');
    }
    table, th, td {
        border: 1px solid black;
        border-radius: 5px;
        
                    }
    #hello {

        border-radius: 25px;
        border: 2px solid #73AD21;
        padding: 20px; 
        position:absolute;
        top:0;
        left:0;
       
        right:0;
        
        
        }
    h1   {
        color:black;
        text-align: center;
        font-family: fantasy;
        font-size: 350%;
        line-height: 80%;
        }
    
    p    {
       color:black;
        text-align: center;
        font-family: fantasy;
        line-height: 80%;
    
        }
    svg {
       
       background-image: url('mapa_pomaire.png');
        -webkit-background-size: cover;
        -moz-background-size: cover;
        -o-background-size: cover;
        background-size: cover;
		
		position: fixed;
        top: 90%;
        left: 50%;
        margin-right: -50%;
        transform: translate(-50%, -65%);
        border-radius: 25px;
        float:left;
		border-color: rgb(128, 64, 21);
		border-style: solid;
        border-width: 2px;
	    height: auto;
}
  .axis {
          font-family: arial;
          font-size: 0.6em;
		  
        }
		
	
    </style>
    </head>
<body>
    <h1>Pomaire</h1>
      <p>Monitoreo ambiental en tiempo real. </p>
        <p>Factoria ® 2015</p>
    <div id="hell" >

            <?php include 'nodos2.1.php';?> 
      
    
    </div>
</body>
</html>
