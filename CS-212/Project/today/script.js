// Function to convert a given wind direction in degrees to the general cardinal direction
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

// Function to convert the date number from getDay() into its appropriate word
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

// Function to convert the hour number from getHour() into non-military time
function convertHourNum(hourNum) {
    if(hourNum > 12){
        return hourNum - 12 + ":00 PM";
    } else {
        return hourNum + ":00 AM";
    }
}

// Function to change the background of the website based on the current weather (very general images)
function weatherBackground(weather) {
    if(weather == 'Clear') {
        document.getElementById('main').style.backgroundImage = "url('clear.jpg')";
    } else if(weather == 'Thunderstorm'){
        document.getElementById('main').style.backgroundImage = "url('thunderstorm.webp')";
    } else if(weather == 'Drizzle'){
        document.getElementById('main').style.backgroundImage = "url('drizzle.webp')";
    } else if(weather == 'Rain'){
        document.getElementById('main').style.backgroundImage = "url('rain.jpg')";
    } else if(weather == 'Snow'){
        document.getElementById('main').style.backgroundImage = "url('snow.webp')";
    } else if(weather == 'Clouds'){
        document.getElementById('main').style.backgroundImage = "url('clouds.jpg')";
    } else {
        document.getElementById('main').style.backgroundImage = "url('other.avif')";
    }
}

// Upon website load: Prompt user if we can have their location
function getCurrentLocation(){
    if(navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(showPosition);
    } else {
        console.log("Geolocation is not supported by this browser.");
    }
}

// Acquire the coordinates of the users current location, and loads the weather data based on it
function showPosition(position) {
    let latitude = position.coords.latitude;
    let longitude = position.coords.longitude;

    loadCurrentWeather(latitude,longitude);
}

// Starts the website up with users current location
getCurrentLocation();

// Function fills the website with the weather at the users current area
async function loadCurrentWeather(lat,long) {
    try{
        const response = await fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${long}&appid=e6393dba1bb0c1575774d3fc7b6b6e68`);
        if(!response.ok){
            throw new Error("Could not fetch weather resource");
        }

        const dataWeather = await response.json();
        const weatherTemperature = dataWeather['main']['temp'];
        const weather = dataWeather['weather'][0]['main'];

        console.log(weather);

        weatherBackground(weather);

        let windDegrees = dataWeather['wind']['deg'];

        document.getElementById('area').innerHTML = "TODAY'S WEATHER AT CURRENT LOCATION"
        document.getElementById('temp').innerHTML = Math.round((weatherTemperature - 273.15)*9/5+32) + "° F";
        document.getElementById('highTemp').innerHTML = Math.round((dataWeather['main']['temp_max'] - 273.15)*9/5+32) + "° F";
        document.getElementById('lowTemp').innerHTML = Math.round((dataWeather['main']['temp_min'] - 273.15)*9/5+32) + "° F";
        document.getElementById('feelslike').innerHTML = Math.round((dataWeather['main']['feels_like'] - 273.15)*9/5+32) + "° F";
        document.getElementById('wind').innerHTML = "Wind: " + Math.round(dataWeather['wind']['speed']*2.23694,0) + " mph ";
        document.getElementById('wind').innerHTML += "<br>(" + windDirection(windDegrees) + ")";
        document.getElementById('humidity').innerHTML = dataWeather['main']['humidity'] + "%";
        document.getElementById('pressure').innerHTML = dataWeather['main']['pressure'] + " hPa";
    }
    catch(error){
        console.error(error);
    }
}

// Function that acquires weather location and data
async function loadWeather() {
    try{
        
        const location = document.getElementById("location").value;

        console.log(location);

        const response = await fetch(`https://maps.googleapis.com/maps/api/geocode/json?address=${location}&key=AIzaSyBk2xxSujsNoxM5TxR_A_7Fjnvzj8LfisA`);
    
        console.log(response)

        if(!response.ok){
            throw new Error("Could not fetch location resource");
        }
    
        const data = await response.json();
        const longitude = data['results'][0]['geometry']['location']['lng'];
        const latitude = data['results'][0]['geometry']['location']['lat'];
        console.log(longitude);
        console.log(latitude);
        
        try{
            const response = await fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${latitude}&lon=${longitude}&appid=e6393dba1bb0c1575774d3fc7b6b6e68`);
        
            if(!response.ok){
                throw new Error("Could not fetch weather resource.");
            }

            const dataWeather = await response.json();
            const weatherTemperature = dataWeather['main']['temp'];

            const weather = dataWeather['weather'][0]['main'];

            console.log(weather);

            weatherBackground(weather);

            let windDegrees = dataWeather['wind']['deg'];

            document.getElementById('area').innerHTML = "TODAY'S WEATHER AT " + location.toUpperCase();
            document.getElementById('temp').innerHTML = Math.round((weatherTemperature - 273.15)*9/5+32) + "° F";
            document.getElementById('highTemp').innerHTML = Math.round((dataWeather['main']['temp_max'] - 273.15)*9/5+32) + "° F";
            document.getElementById('lowTemp').innerHTML = Math.round((dataWeather['main']['temp_min'] - 273.15)*9/5+32) + "° F";
            document.getElementById('feelslike').innerHTML = Math.round((dataWeather['main']['feels_like'] - 273.15)*9/5+32) + "° F";
            document.getElementById('wind').innerHTML = "Wind: " + Math.round(dataWeather['wind']['speed']*2.23694,0) + " mph ";
            document.getElementById('wind').innerHTML += "<br>(" + windDirection(windDegrees) + ")";
            document.getElementById('humidity').innerHTML = dataWeather['main']['humidity'] + "%";
            document.getElementById('pressure').innerHTML = dataWeather['main']['pressure'] + " hPa";
        }
        catch(error){
            console.error(error);
        }
    }
    catch(error){
        console.error(error);
    }
}   
