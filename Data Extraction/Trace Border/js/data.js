//ALGORITHM
//lat determines Northness
//long determines Eastness
//start square
var sqTLElat = 32.5067;
var sqTLElong = 74.6796;
//var sqBRElat = 32.6065;		//isnt getting updated
//var sqBRElong = 74.6356;	//isnt getting updated
//start edge
var inlat = 32.5066;
var inlong = 74.6797;

var latitude;
var longitude;
var t = 10;

const delay = ms => new Promise(res => setTimeout(res, ms));

async function main(){
//get into while loop
	while(sqTLElat > 32.5066 && sqTLElat <= 32.6066 && sqTLElong < 74.6948 && sqTLElong > 74.5948){		//technically it should be 2 BREs but TLE doesn't cause much of a problem either just an extra row just an extra column
		await delay(2100);
		//lat long of points
		let Alat = sqTLElat, Along = sqTLElong;
		let Blat = sqTLElat, Blong = Math.round(10000*(sqTLElong + 0.0001))/10000;
		let Clat = Math.round(10000*(sqTLElat - 0.0001))/10000, Clong = Math.round(10000*(sqTLElong + 0.0001))/10000;
		let Dlat = Math.round(10000*(sqTLElat - 0.0001))/10000, Dlong = sqTLElong;
		//Extract country of A,B,C,D
		let countryA, countryB, countryC, countryD;
		
		//Fetching country of point A
		latitude = sqTLElat;
		longitude = sqTLElong;
		let apiCall = "http://api.geonames.org/countryCodeJSON?formatted=true&lat="+latitude+"&lng="+longitude+"&username=aumbart&style=full";
		await fetch(apiCall)
		.then((res) => res.json())
		.then((json) => {
			countryA = json.countryCode;
		});
		
		//Fetching country of point B
		latitude = Blat;
		longitude = Blong;
		apiCall = "http://api.geonames.org/countryCodeJSON?formatted=true&lat="+latitude+"&lng="+longitude+"&username=dumbart&style=full";
		await fetch(apiCall)
		.then((res) => res.json())
		.then((json) => {
			countryB = json.countryCode;
		});
		
		//Fetching country of point C
		latitude = Clat;
		longitude = Clong;
		apiCall = "http://api.geonames.org/countryCodeJSON?formatted=true&lat="+latitude+"&lng="+longitude+"&username=numbart&style=full";
		await fetch(apiCall)
		.then((res) => res.json())
		.then((json) => {
			countryC = json.countryCode;
		});
		
		//Fetching country of point D
		latitude = Dlat;
		longitude = Dlong;
		apiCall = "http://api.geonames.org/countryCodeJSON?formatted=true&lat="+latitude+"&lng="+longitude+"&username=lumbart&style=full";
		await fetch(apiCall)
		.then((res) => res.json())
		.then((json) => {
			countryD = json.countryCode;
		});
		//changing to 1 for PK and 0 for IN
		if(countryA == "PK")
			countryA = 1;
		else
			countryA = 0;
		if(countryB == "PK")
			countryB = 1;
		else
			countryB = 0;
		if(countryC == "PK")
			countryC = 1;
		else
			countryC = 0;
		if(countryD == "PK")
			countryD = 1;
		else
			countryD = 0;
		//Print points
		if(!((Alat == inlat && Along == inlong) || (Dlat == inlat && Dlong == inlong))){
			var para = document.createElement("p");
			var node = document.createTextNode(Alat+" "+Along+" "+countryA);
			para.appendChild(node);
			var element = document.getElementById("div1");
			element.appendChild(para);
		}
		if(!((Blat == inlat && Blong == inlong) || (Alat == inlat && Along == inlong))){
			var para = document.createElement("p");
			var node = document.createTextNode(Blat+" "+Blong+" "+countryB);
			para.appendChild(node);
			var element = document.getElementById("div1");
			element.appendChild(para);
			//console.log(Blat+" "+Blong+" "+countryB);
		}
		if(!((Clat == inlat && Clong == inlong) || (Blat == inlat && Blong == inlong))){
			var para = document.createElement("p");
			var node = document.createTextNode(Clat+" "+Clong+" "+countryC);
			para.appendChild(node);
			var element = document.getElementById("div1");
			element.appendChild(para);
			//console.log(Clat+" "+Clong+" "+countryC);
		}
		if(!((Dlat == inlat && Dlong == inlong) || (Clat == inlat && Clong == inlong))){
			var para = document.createElement("p");
			var node = document.createTextNode(Dlat+" "+Dlong+" "+countryD);
			para.appendChild(node);
			var element = document.getElementById("div1");
			element.appendChild(para);
			//console.log(Dlat+" "+Dlong+" "+countryD);
		}
		//check A(if A,B have different parity or not, if so is A not the in-edge, if so set parameters of next square print shit and move on with life)
		if(countryA != countryB && !(inlat == Alat && inlong == Along)){
			inlat = Blat;
			inlong = Blong;
			sqTLElat = Math.round(10000*(sqTLElat + 0.0001))/10000;
				sqTLElong = sqTLElong;
			
		}
		//check B
		else if(countryB != countryC && !(inlat == Blat && inlong == Blong)){
			inlat = Clat;
			inlong = Clong;
			sqTLElat = sqTLElat;
			sqTLElong = Math.round(10000*(sqTLElong + 0.0001))/10000;
		}
		//check C
		else if(countryC != countryD && !(inlat == Clat && inlong == Clong)){
			inlat = Dlat;
			inlong = Dlong;
			sqTLElat = Math.round(10000*(sqTLElat - 0.0001))/10000;
			sqTLElong = sqTLElong;
		}
		//check D
		else if(countryD != countryA && !(inlat == Dlat && inlong == Dlong)){
			inlat = Alat;
			inlong = Along;
			sqTLElat = sqTLElat;
			sqTLElong = Math.round(10000*(sqTLElong - 0.0001))/10000;
		}
	}
}

main();
