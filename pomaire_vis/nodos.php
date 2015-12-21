<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8">
  <script src="http://d3js.org/d3.v3.min.js"></script>
 <script src="//code.jquery.com/jquery-1.11.3.min.js"></script>
  
  
  <style>
 svg {
       
        background-image: url('mapa_pomaire.png');*/
        -webkit-background-size: cover;
        -moz-background-size: cover;
        -o-background-size: cover;
        background-size: cover;
		
		position: absolute;
        top: 90%;
        left: 50%;
        margin-right: -50%;
        transform: translate(-50%, -50%);
        border-radius: 25px;
		border-color: black;
		border-style: solid;
        border-width: 2px;
	    
}
  .axis {
          font-family: arial;
          font-size: 0.6em;
		  
        }
		
	div1 {
	width-margin: 70px;
	position-align: center;
	}

  </style>
</head>
<body>


 <script type="text/javascript">

</script>
<div id = "display">
  <script type="text/javascript"> 

"use strict";
          var margin = 100,
              width = 1200 - margin,
              height = 650 - margin;
		  
          var fixplot = (height + margin)/2;
		  var sump = 0;
	      var radius = 4;
            var cx = 333;
      var cy = 444;
          var color = "rgb(216, 216, 47)";
		  
		  
		  var display_circles = 1;
//Xaxis_Accelerometer___________________________________________________________________________________________
 		  
  d3.json("getdata.php", function(data) {

          var svg = d3.select("body")
            .append("svg")
              .attr("width", width + margin)
              .attr("height", height + margin)
            .append('g')
                .attr('class','chart');

	
	    // Create amount of circles equals to the amount of data
          d3.select('svg')
		    .selectAll("circle")
			.data(data)
			.enter()
			.append("circle")
			.attr('class')

			
		// Create x-axis scale mapping dates -> pixels	
			var Xaxis = d3.scale.linear()
            .range([margin, width])
            .domain([0,300]);
		
		
		// Create y-axis scale mapping attendance -> pixels
			var Yaxis = d3.scale.linear()
            .range([margin, height])
            .domain([1023,0]);
				
			var Axis1 = d3.svg.axis()
            .scale(Xaxis)
			.ticks(0)

			
			var Axis2 = d3.svg.axis()
            .scale(Yaxis)
            .orient("left");
			
		// Display of axis	
		
			d3.select("svg")
            .append("g")
            .attr("class", "x axis")
            .attr("transform", "translate(0," + height + ")")
            .style({ 'stroke': 'Black',
			'fill': 'none', 'stroke-width': '0.8px'})
			.call(Axis1)//.selectAll("text").remove();;

          d3.select("svg")
            .append("g")
            .attr("class", "y axis")
            .attr("transform", "translate(" + margin + ",0)")
            .style({ 'stroke': 'Black', 
			'fill': 'none', 'stroke-width': '0.8px'})
			.call(Axis2);
			
			
                
//Display Circles	
		   d3.selectAll('.circles')
              .attr('cx', cx)
              .attr('cy', cy)
              .attr('r', radius)
              .style('fill', color)
		
  };
//Update___________________________________________________________________________________________
/*
setInterval(function(){ 
    
 d3.json("getdata.php", function(data) {
	 
	 
	 //UpdateX___________________________________________________________________________________________
	 // Create x-axis scale mapping dates -> pixels	
			var Xaxis = d3.scale.linear()
            .range([margin, width])
            .domain([0,300]);
		
		
		// Create y-axis scale mapping attendance -> pixels
			var Yaxis = d3.scale.linear()
            .range([margin, height])
            .domain([1023,0]);
				
	
		 //Display Circles
	 d3.selectAll('circles')
	          .data(data)
			  //.transition()
			  //.duration(500)
              .attr('cx', '300')
			  .attr('cy', '300')
              .style('fill', colorx)
	 };
 
 })

  

  }, 500);
*/
  </script>
  <div>
</body>
</html>
