//ALGORITHM
//lat determines Northness
//long determines Eastness
//start square
var sqTLElat = 32.6066;
var sqTLElong = 74.6355;
var sqBRElat = 32.6065;		//isnt getting updated
var sqBRElong = 74.6356;	//isnt getting updated
//start edge
var inlat = 32.6066;
var inlong = 74.6355;

var latitude;
var longitude;
var t = 10;

const delay = ms => new Promise(res => setTimeout(res, ms));
async function main(){
//get into while loop
	
		for(var i = 0; i < 1000; i++){
			let land;
			latitude = (Math.random() * 0.0025) + 32.5065;
			longitude = (Math.random() * 0.0012) + 74.6794;
			latitude = Math.round(1000000*(latitude - 0.0001))/1000000;
			longitude = Math.round(1000000*(longitude - 0.0001))/1000000;
			let apiCall = "http://api.geonames.org/countryCodeJSON?formatted=true&lat="+latitude+"&lng="+longitude+"&username=aumbart&style=full";
			await fetch(apiCall)
			.then((res) => res.json())
			.then((json) => {
				land = json.countryCode;
			});
			if(land == "PK")
				land = 1;
			else
				land = 0;
			var para = document.createElement("p");
			var node = document.createTextNode(latitude+" "+longitude+" "+land);
			para.appendChild(node);
			var element = document.getElementById("div1");
			element.appendChild(para);
			
		}
	
}

main();
