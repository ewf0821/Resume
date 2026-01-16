
// This will actually be for 5 days, with 3 hour intervals throughout

function windDirection(windDirection) {
    if(windDirection > 337.5 || windDirection < 22.5){
        return "North";
    } else if(windDirection > 22.5 && windDirection < 67.5){
        return "North East";
    } else if(windDirection > 67.5 && windDirection < 112.5){
        return "East";
    } else if(windDirection > 112.5 && windDirection < 157.5){
        return "South East";
    } else if(windDirection > 157.5 && windDirection < 202.5){
        return "South";
    } else if(windDirection > 202.5 && windDirection < 247.5){
        return "South West";
    } else if(windDirection > 247.5 && windDirection < 292.5){
        return "West";
    } else if(windDirection > 292.5 && windDirection < 337.5){
        return "North West";
    } else{
        return "Unknown Wind Direction.";
    }
}

function convertDayNum(dayNum) {
    if(dayNum == 0) {
        return "Sunday";
    } else if(dayNum == 1) {
        return "Monday";
    } else if(dayNum == 2) {
        return "Tuesday";
    } else if(dayNum == 3) {
        return "Wednesday";
    } else if(dayNum == 4) {
        return "Thursday";
    } else if(dayNum == 5) {
        return "Friday";
    } else if(dayNum == 6) {
        return "Saturday";
    }
}

function convertHourNum(hourNum) {
    if(hourNum > 12){
        return hourNum - 12 + ":00 PM";
    } else {
        return hourNum + ":00 AM";
    }
}

function weatherBackground(weather, index) {
    if(weather == 'Clear') {
        document.getElementById('background' + index).style.backgroundImage = "url('clear.jpg')";
    } else if(weather == 'Thunderstorm'){
        document.getElementById('background' + index).style.backgroundImage = "url('thunderstorm.webp')";
    } else if(weather == 'Drizzle'){
        document.getElementById('background' + index).style.backgroundImage = "url('drizzle.webp')";
    } else if(weather == 'Rain'){
        document.getElementById('background' + index).style.backgroundImage = "url('rain.jpg')";
    } else if(weather == 'Snow'){
        document.getElementById('background' + index).style.backgroundImage = "url('snow.webp')";
    } else if(weather == 'Clouds'){
        document.getElementById('background' + index).style.backgroundImage = "url('clouds.jpg')";
    } else {
        document.getElementById('background' + index).style.backgroundImage = "url('other.avif')";
    }
}

// Upon website load: prompt user if we can have their location
function getCurrentLocation(){
    if(navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(showPosition);
    } else {
        console.log("Geolocation is not supported by this browser.");
    }
}

function showPosition(position) {
    let latitude = position.coords.latitude;
    let longitude = position.coords.longitude;

    loadCurrentForecast(latitude,longitude);
}

getCurrentLocation();

async function loadCurrentForecast(lat,long) {
    try{
        const response = await fetch(`https://api.openweathermap.org/data/2.5/forecast?lat=${lat}&lon=${long}&appid=e6393dba1bb0c1575774d3fc7b6b6e68`);
        if(!response.ok){
            throw new Error("Could not fetch weather resource");
        }

        const dataWeather = await response.json();
        document.getElementById('area').innerHTML = "5 DAY FORECAST FOR CURRENT LOCATION";

        for (let i=0; i < 40; i++){
            let weather = dataWeather['list'][i]['weather'][0]['main'];
            weatherBackground(weather,i+1);

            let windDegrees = dataWeather['list'][i]['wind']['deg'];
            let date = new Date(dataWeather['list'][i]['dt']*1000);
            document.getElementById('date'+(i+1)).innerHTML = convertDayNum(date.getDay()) + " at " + convertHourNum(date.getHours());
            document.getElementById('temp'+(i+1)).innerHTML = Math.round((dataWeather['list'][i]['main']['temp']-273.15)*9/5+32) + "° F";
            document.getElementById('wind'+(i+1)).innerHTML = Math.round(dataWeather['list'][i]['wind']['speed']*2.23694,0) + " mph ";
            document.getElementById('wind'+(i+1)).innerHTML += "(" + windDirection(windDegrees) + ")";
        }

    }
    catch(error){
        console.error(error);
    }
}

async function loadForecast(){
    try{
        
        const location = document.getElementById("location").value;
        document.getElementById('area').innerHTML = "5 DAY FORECAST FOR " + location.toUpperCase();
        console.log(location);

        const response = await fetch(`https://maps.googleapis.com/maps/api/geocode/json?address=${location}&key=AIzaSyBk2xxSujsNoxM5TxR_A_7Fjnvzj8LfisA`);

        if(!response.ok){
            throw new Error("Could not fetch location resource");
        }
    
        const data = await response.json();
        const longitude = data['results'][0]['geometry']['location']['lng'];
        const latitude = data['results'][0]['geometry']['location']['lat'];
        
        try{
            const response = await fetch(`https://api.openweathermap.org/data/2.5/forecast?lat=${latitude}&lon=${longitude}&appid=e6393dba1bb0c1575774d3fc7b6b6e68`);
            if(!response.ok){
                throw new Error("Could not fetch weather resource");
            }

            const dataWeather = await response.json();
            
            for (let i=0; i < 40; i++){
                let weather = dataWeather['list'][i]['weather'][0]['main'];
                weatherBackground(weather,i+1);
                
                let windDegrees = dataWeather['list'][i]['wind']['deg'];
                let date = new Date(dataWeather['list'][i]['dt']*1000);
                document.getElementById('date'+(i+1)).innerHTML = convertDayNum(date.getDay()) + " at " + convertHourNum(date.getHours());
                document.getElementById('temp'+(i+1)).innerHTML = Math.round((dataWeather['list'][i]['main']['temp']-273.15)*9/5+32) + "° F";
                document.getElementById('wind'+(i+1)).innerHTML = Math.round(dataWeather['list'][i]['wind']['speed']*2.23694,0) + " mph ";
                document.getElementById('wind'+(i+1)).innerHTML += "(" + windDirection(windDegrees) + ")";
            }
        }
        catch(error){
            console.error(error);
        }
    }
    catch(error){
        console.error(error);
    }
}
