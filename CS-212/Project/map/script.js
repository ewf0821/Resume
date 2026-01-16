async function loadMap() {
    try{
        // acquires location from user when search button clicked
        const location = document.getElementById("location").value;
        
        const response = await fetch(`https://maps.googleapis.com/maps/api/geocode/json?address=${location}&key=AIzaSyBk2xxSujsNoxM5TxR_A_7Fjnvzj8LfisA`);
    
        if(!response.ok){
            throw new Error("Could not fetch location resource");
        }

        const data = await response.json();
        const longitude = data['results'][0]['geometry']['location']['lng'];
        const latitude = data['results'][0]['geometry']['location']['lat'];

        document.getElementById('weathermap').src = `https://openweathermap.org/weathermap?basemap=map&cities=false&layer=radar&lat=${latitude}&lon=${longitude}&zoom=10`;

        // sets search bar to nothing when location is submitted
        document.getElementById("location").value = "";
    }
    catch(error){
        console.error(error);
    }
}