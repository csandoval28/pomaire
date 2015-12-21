<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <script src="http://d3js.org/d3.v3.min.js"></script>
  <style>
 svg {
       
        background-image: url('mapa_pomaire.png');
        -webkit-background-size: cover;
        -moz-background-size: cover;
        -o-background-size: cover;
        background-size: cover;
		
		position: absolute;
        top: 90%;
        left: 50%;
        margin-right: -50%;
        transform: translate(-50%, -80%);
        border-radius: 25px;
		/*border-color: green;
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
  
    <script type="text/javascript">

 
      function draw(data) {
	  

   // alert(position.coords.latitude); 
   //1p -33.390834, -70.501063
   //2p -33.392028, -70.501049
   //3p -33.390917, -70.499416
   //4p -33.391914, -70.499756
   

	

      /*
        D3.js setup code
      */

          "use strict";
          var margin = 10,
              width = 1200 - margin,
              height = 858 - margin;

	      var radius = 15;
          var colorh = "rgb(26, 129, 158)";
		  var colorm = "rgb(227, 30, 90)";
          //var position = [,]
	
	var divtext = d3.select("body")
            .append("div1")
              .attr("width", "600")
              .attr("height", "300")
            
          var svg = d3.select("body")
            .append("svg")
              .attr("width", width + margin)
              .attr("height", height + margin)
            .append('g')
                .attr('class','chart');

    //Add the SVG Text Element to the svgContainer
            var text = svg.selectAll("text")
                        .data(['show'])
                        .enter()
                        .append("text");
	
	    // Create amount of circles equals to the amount of data
          d3.select('svg')
		    .selectAll("circle")
			.data(["Test"])
			.enter()
			.append("circle")
		
		// Create x-axis scale mapping dates -> pixels	
			var Xaxis = d3.scale.linear()
            .range([margin, width])
            .domain([0,300]);
		
		
		// Create y-axis scale mapping attendance -> pixels
			var Yaxis = d3.scale.linear()
            .range([margin, height])
            .domain([300,0]);
				
			var Axis1 = d3.svg.axis()
            .scale(Xaxis)

			
			var Axis2 = d3.svg.axis()
            .scale(Yaxis)
            .orient("left");
			
		// Display of axis	
		
			d3.select("svg")
            .append("g")
            .attr("class", "x axis")
            .attr("transform", "translate(0," + height + ")")
            .style({ //'stroke': 'Black',
			'fill': 'none', 'stroke-width': '0.5px'})
			.call(Axis1);

          d3.select("svg")
            .append("g")
            .attr("class", "y axis")
            .attr("transform", "translate(" + margin + ",0)")
            .style({ //'stroke': 'Black', 
			'fill': 'none', 'stroke-width': '0.5px'})
			.call(Axis2);
			
			
		//Display Circles	
		   d3.selectAll('circle')
              .attr('cx', function(data, i) {
			    return 500;
				  
              })
              .attr('cy', function(data,i) {
                return 700;
				  
              })
              .attr('r', function(data) {
			  
                  return 33;
              })
			  .style('fill',colorh)
			  .attr('opacity', '1')
			  //Animation
			  // .on('mouseover',mouseover)
               //.on('mouseout',mouseout)
			  ;
			  
	//Legend 1
           var legend = svg.append("g")
              .attr("class", "legend")
              .attr("transform", "translate(" + (width - 250) + "," + 10 + ")")
              .selectAll("g")
              .data(["Man", "Woman"])
              .enter().append("g");

          legend.append("circle")
              .attr("cy", function(d, i) {
                  return i * 30;
              })
              .attr("r", function(d) {
                  if (d == "Hombre") {
                      return radius;
                  } else {
                      return radius;
                  }
              })
              .attr("fill", function(d) {
                  if (d == "Man") {
                      return colorh;
                  } else {
                      return colorm;
                  }
              });

          legend.append("text")
              .attr("y", function(d, i) {
                  return i * 30 + 5;
              })
              .attr("x", radius * 5)
              .style("color","gray")
	          .style("font-size","100%")
	          .style("font-style","italic")
			  .text(function(d) {
                  return d;
              })
			  ;		
			  
//Legend 2
           var legend2 = svg.append("g")
              .attr("class", "legend")
              .attr("transform", "translate(" + (width - 100) + "," + 10  + ")")
              .selectAll("g")
              .data([position.coords.latitude, position.coords.longitude])
              .enter().append("g");
			  
			
			  
			  legend2.append("circle")
			  .attr("cy", function(d, i) {
                  if (i === 0) {
				  return i *15;
				  } else {
				  return 0;
				  }
				  
              })
			  .attr("cx", function(d, i) {
                  if (i === 0) {
				  return -30;
				  } else {
				  return -i *30;
				  }
              })
			  .attr("opacity", function(d, i) {
                  if (i === 0) {
				return '0';
				  } else {
				  return '0.2';
				  }
              })
              .attr("r", function(d) {
                  if (d == "Survided") {
                      return radius;
                  } else {
                      return radius;
                  }
              })
              .attr("fill", function(d) {
                      return colorh;
              })
			  
			  legend2.append("circle")
			  .attr("cy", function(d, i) {
                  if (i === 0) {
				  return i *15;
				  } else {
				  return 0;
				  }
				  
              })
			  .attr("opacity", function(d, i) {
                  if (i === 0) {
				return '0';
				  } else {
				  return '0.2';
				  }
              })
			  .attr("cx", function(d, i) {
                  if (i === 0) {
				  return -25;
				  } else {
				  return -i *25;
				  }
              })
              .attr("r", function(d) {
                  if (d == "Survided") {
                      return radius;
                  } else {
                      return radius;
                  }
              })
              .attr("fill", function(d) {
                      return colorm;
              })
			  
			  legend2.append("text")
              .attr("y", function(d, i) {
                  return i * 30 + 5;
              })
              .attr("x", radius)
              .style("color","gray")
	          .style("font-size","100%")
	          .style("font-style","italic")
			  .text(function(d) {
                  return d;
              })
    
 
function mouseover() {

//Save (x,y) & name points of mouseover function               
var mousex = d3.select(this).attr("cx");
var mousey = d3.select(this).attr("cy");
var mousename = d3.select(this).attr("name");	
var mouseage = d3.select(this).attr("Age");
var namefull = mousename;
var mousenamelength = namefull.length;

//Animation		   
			   d3.select(this)
                  .transition()
                  .duration(500)
				  .style("fill", "green")
				  .attr('opacity','0.4')
                  .attr('r',30)

//Update text				 
				text
				 .attr("font-size", "0px")
                 .attr("x", function(d) { return mousex - mousenamelength*5; })
                 .attr("y", function(d) { return mousey; })
				 .transition()
				 .duration(500)
                 .text( function (d) { return mousename + " Age:" + mouseage; })
                 .attr("font-family", "sans-serif")
                 .attr("font-size", "20px")
                 .attr("fill", "gray")
				 .attr("text-align","left")
				 
				 


}

function mouseout() {			

			d3.select(this)
                  .transition()
                  .duration(500)
                  .attr('r',radius)
				  .style("fill", function(d){
				  
				  if(d3.select(this).attr('sex') === 'female') {
				  return colorm;
				  } else {
				  return colorh;
				  }
				  })
				  .attr('opacity',function(d){
				  
				  if(d3.select(this).attr('survived') === '1') {
				  return '1';
				  } else {
				  return '0.2';
				  }
				  })
		     text
			     .transition()
				 .duration(500)
				 .attr("font-size", "0px")
			 
      }
      };
	  
	 
//Update------------------------------------------------------------------------------------------------------------------	  
	  
	  function draw2(data) {
	  

   // alert(position.coords.latitude); 
   //1p -33.390834, -70.501063
   //2p -33.392028, -70.501049
   //3p -33.390917, -70.499416
   //4p -33.391914, -70.499756
   

	

      /*
        D3.js setup code
      */

          "use strict";
          var margin = 100,
              width = 800 - margin,
              height = 858 - margin;

	      var radius = 15;
          var colorh = "rgb(26, 129, 158)";
		  var colorm = "rgb(227, 30, 90)";
          //var position = [,]
	
		
		// Create x-axis scale mapping dates -> pixels	
			var Xaxis = d3.scale.linear()
            .range([margin, width])
            .domain([0,300]);
		
		
		// Create y-axis scale mapping attendance -> pixels
			var Yaxis = d3.scale.linear()
            .range([margin, height])
            .domain([300,0]);
			
			
		//Display Circles	
		   d3.selectAll('circle')
              .attr('cx', function(data, i) {
			    return 500;
				  
              })
              .attr('cy', function(data,i) {
                return 700;
				  
              })
              .attr('r', function(data) {
			  
                  return radius;
              })
			  .style('fill',colorh)
			  .attr('opacity', '1')
			  //Animation
			  // .on('mouseover',mouseover)
               //.on('mouseout',mouseout)
			  ;
 
function mouseover() {

//Save (x,y) & name points of mouseover function               
var mousex = d3.select(this).attr("cx");
var mousey = d3.select(this).attr("cy");
var mousename = d3.select(this).attr("name");	
var mouseage = d3.select(this).attr("Age");
var namefull = mousename;
var mousenamelength = namefull.length;

//Animation		   
			   d3.select(this)
                  .transition()
                  .duration(500)
				  .style("fill", "green")
				  .attr('opacity','0.4')
                  .attr('r',30)

//Update text				 
				text
				 .attr("font-size", "0px")
                 .attr("x", function(d) { return mousex - mousenamelength*5; })
                 .attr("y", function(d) { return mousey; })
				 .transition()
				 .duration(500)
                 .text( function (d) { return mousename + " Age:" + mouseage; })
                 .attr("font-family", "sans-serif")
                 .attr("font-size", "20px")
                 .attr("fill", "gray")
				 .attr("text-align","left")
				 
				 


}

function mouseout() {			

			d3.select(this)
                  .transition()
                  .duration(500)
                  .attr('r',radius)
				  .style("fill", function(d){
				  
				  if(d3.select(this).attr('sex') === 'female') {
				  return colorm;
				  } else {
				  return colorh;
				  }
				  })
				  .attr('opacity',function(d){
				  
				  if(d3.select(this).attr('survived') === '1') {
				  return '1';
				  } else {
				  return '0.2';
				  }
				  })
		     text
			     .transition()
				 .duration(500)
				 .attr("font-size", "0px")
			 
      }
	  
	  
	  };
	  
      </script>
	  </script>
  <script type="text/javascript">  /*
    Use D3 (not dimple.js) to load the TSV file
    and pass the contents of it to the draw function
    */
	// example date: 27-05-1934 (16:00 h)
var each = [];
var change = 0;

setInterval(function(){ 

if(change===0){
d3.csv('titanic.csv', function(data){return data;}, draw);
change = 1;
} else {
d3.csv('titanic.csv', function(data){return data;}, draw2);
}
	
	  }, 500)

  </script>
  </head>
<body>
<script language="javascript">

    </script>
  <script type="text/javascript">  /*
    Use D3 (not dimple.js) to load the TSV file
    and pass the contents of it to the draw function
    */
	// example date: 27-05-1934 (16:00 h)


  </script>
</body>
</html>
