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
	
	for(var long = 74.6564; long <= 74.6584; long = Math.round(10000*(long + 0.0001))/10000){
		for(var lat = 32.5587; lat >= 32.5567; lat = Math.round(10000*(lat - 0.0001))/10000){
			let land;
			latitude = lat;
			longitude = long;
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
			var node = document.createTextNode(lat+" "+long+" "+land);
			para.appendChild(node);
			var element = document.getElementById("div1");
			element.appendChild(para);
			
		}
	}
}

main();
