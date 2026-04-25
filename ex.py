import requests


def get_cities_hh():
    url = "https://api.hh.ru/areas/113"
    response = requests.get(url)
    data = response.json()

    cities = []

    def extract_cities(area):
        for sub in area.get("areas", []):
            if not sub.get("areas"):
                cities.append(sub["name"])
            else:
                extract_cities(sub)

    extract_cities(data)
    return cities
