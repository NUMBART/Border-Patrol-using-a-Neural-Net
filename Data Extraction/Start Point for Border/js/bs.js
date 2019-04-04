//Google Maps API key
// AIzaSyDrT1OwA3YWvz_Y1G3SfjBYj4Vm5aBKtzY 

var Alat = 32.5066000;
var Along = 74.5948320;
var Blat = 32.5066000;
var Blong = 74.6948320;
var latitude;
var longitude;

async function main(){
	document.write(Alat);
	for(let i = 1; i <= 40; ++i, console.log("latitude = " + Alat + "\nlongitude = " + Along+"\n"))
	{
		let midlat = (Alat + Blat)/2
		let midlong = (Along + Blong)/2;
		
		//Finding country
		latitude = midlat;
		longitude = midlong;
		let apiCall = "http://api.geonames.org/countryCodeJSON?formatted=true&lat="+latitude+"&lng="+longitude+"&username=numbart&style=full";
		await fetch(apiCall)
		.then((res) => res.json())
		.then((json) => {
			let country = json.countryCode;
			console.log("country = " + country);
			if(country == "PK")
			{
				Alat = midlat;
				Along = midlong;
				console.log(apiCall);
			}
			else
			{
				Blat = midlat;
				Blong = midlong;console.log(apiCall);
			}
		});
		//end Finding country
		
		
	}
	//document.write("latitude = " + Alat + "\nlongitude = " + Along);
}

main();
