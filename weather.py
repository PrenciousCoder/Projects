import requests
import json
import sys


#API Declarartion
api_key=""
base_url="https://api.openweathermap.org/data/2.5/weather?"

city=sys.argv[1]
url=base_url+"appid="+api_key+"&q="+city
response=requests.get(url).json()

def kelvin_2_celcius(kelvin):
    return kelvin-273



#Temperature in Kelvin
temp_kelvin=response['main']['temp']
temp_min_kelvin=response['main']['temp_min']
temp_max_kelvin=response['main']['temp_max']
temp_feels_like=response['main']['feels_like']


#Temperature in Celcius
temp_celcius=kelvin_2_celcius(temp_kelvin)
temp_feels_like_celcius=kelvin_2_celcius(temp_feels_like)
temp_min_celcius=kelvin_2_celcius(temp_min_kelvin)
temp_max_celcius=kelvin_2_celcius(temp_max_kelvin)

#Other Information
humidity=response['main']['humidity']
sky_status=response['weather'][0]['description']
visibility=response['visibility']
wind_speed=response['wind']['speed']



#File opening
with open("weather_report.txt","a") as f:
    print("",file=f)
    print(f"\033{city}\033[0m",file=f)
    print(f"Temperature: {temp_celcius}",file=f)
    print(f"Feels like Temperature: {temp_feels_like_celcius}",file=f)
    print(f"Minimum Temperature: {temp_min_celcius}",file=f)
    print(f"Maximum Temperature: {temp_max_celcius}",file=f)
    print(f"Humidity: {humidity}",file=f)
    print(f"Sky Status: {sky_status}",file=f)
    print(f"Visibility: {visibility}",file=f)
    print(f"Wind Speed: {wind_speed}",file=f)






#print(json.dumps(response,indent=2))


